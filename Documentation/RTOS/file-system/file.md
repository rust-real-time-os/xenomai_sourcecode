# 文件系统

evl中的文件系统主要涉及两方面内容：
1. 首先是evl中所有的基础能力都被抽象为element，具体的表现形式是一个/dev/evl下的字符设备，贯彻了everything is a file的思想。所以我们的文件系统需要为element的使用提供一些基础能力。
2. 然后是evl中的文件的输入和输出，是通过一个叫file proxy的能力表示的，这个是evl进行输入和输出的基础能力。

## 概述

1. /include/evl/factory.h
   - element和factory的头文件；
2. /include/evl/file.h
   - 文件系统的头文件，包含数据结构的定义，函数的声明，以及几个内联函数的声明；
3. /include/uapi/evl/proxy.h
   - 代理系统的头文件，包含一个evl_proxy_attrs结构体；
4. /kernel/evl/factory.c
   - element和factory的相关实现；
5. /kernel/evl/file.c
   - 文件系统的主要内容；
6. /kernel/evl/proxy.c
   - 代理系统的主要内容；

## 流程图

### 数据结构

1. 文件系统
   - evl_file
      ```C
      struct evl_file {
         struct file *filp;
         struct evl_crossing crossing;
      };
      ```
      - elv中的file结构，相比于vfs中的file，加了一个evl_crossing，作为同步机制；
      - file
         - file是vfs中的数据结构，定义在/include/linux/fs.h中，用来表示文件的数据部分；
         - file中新增了一个oob_data的void指针；
      - files_struct
         - file是vfs中的数据结构，用来表示一个进程中和打开文件相关的内容；
      - evl_crossing
         - 定义在/include/evl/crossing.h，是一个用来在两个内核之间同步的结构体；
   - evl_fd
      ```C
      struct evl_fd {
         unsigned int fd;
         struct evl_file *efilp;
         struct files_struct *files;
         struct rb_node rb;
         struct list_head poll_nodes; /* poll_item->node */
      };
      ```
      - 首先是文件的fd；
      - 然后和文件联系起来；
      - 接着是一个进程中文件的相关内容；
      - 最后是一个node节点；
      - evl_poll_node
         - 是一个轮询的节点
      - evl_file_binding
   - evl_element
      ```C
      struct evl_element {
         struct rcu_head rcu;
         struct evl_factory *factory;
         struct cdev cdev;
         struct device *dev;
         struct filename *devname;
         unsigned int minor;
         int refs;
         bool zombie;
         hard_spinlock_t ref_lock;
         fundle_t fundle;
         int clone_flags;
         struct rb_node index_node;
         struct irq_work irq_work;
         struct work_struct work;
         struct hlist_node hash;
         struct {
            struct file *filp;
            int efd;
         } fpriv;
      };
      ```
     - 定义在/include/evl/factory.c中，是evl一个对内核基础能力的抽象；
     - 分类
       - thread
       - monitor
       - clock
       - ovservable
       - cross-buffer
       - file proxy
     - 详细内容
       ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220124104610.png)
   - evl_factory
      ```C
      struct evl_factory {
         const char *name;
         const struct file_operations *fops;
         unsigned int nrdev;
         struct evl_element *(*build)(struct evl_factory *fac,
                  const char __user *u_name,
                  void __user *u_attrs,
                  int clone_flags,
                  u32 *state_offp);
         void (*dispose)(struct evl_element *e);
         const struct attribute_group **attrs;
         int flags;
         struct {
            struct device_type type;
            struct class *class;
            struct cdev cdev;
            struct device *dev;
            dev_t sub_rdev;
            kuid_t kuid;
            kgid_t kgid;
            unsigned long *minor_map;
            struct evl_index index;
            DECLARE_HASHTABLE(name_hash, EVL_DEVHASH_BITS);
            struct mutex hash_lock;
         }; /* Internal. */
      };
      ```
     - 这个是一个对如何操作element的抽象；
     - 分类
       - evl_control_factory
       - evl_thread_factory
       - evl_monitor_factory
       - evl_poll_factory
       - evl_xbuf_factory
       - evl_proxy_factory
       - evl_observable_factory
     - 以文件系统为例
         ```C
         struct evl_factory evl_proxy_factory = {
            .name	=	EVL_PROXY_DEV,
            .fops	=	&proxy_fops,
            .build =	proxy_factory_build,
            .dispose =	proxy_factory_dispose,
            .nrdev	=	CONFIG_EVL_NR_PROXIES,
            .flags	=	EVL_FACTORY_CLONE,
         };

         static const struct file_operations proxy_fops = {
            .open		= evl_open_element,
            .release	= proxy_release,
            .oob_write	= proxy_oob_write,
            .oob_read	= proxy_oob_read,
            .oob_poll	= proxy_oob_poll,
            .write		= proxy_write,
            .read		= proxy_read,
            .poll		= proxy_poll,
            .mmap		= proxy_mmap,
         };
         ```

2. 代理系统
   - proxy_ring
     - 这个是沟通out-of-banb和in-band两部分的桥梁；
     - 在这个数据结构的基础上，封装了
       - proxy_out
         - 描述数据从oob向ib流动的情况；
       - proxy_in
         - 描述数据从ib向oob流动的情况；
   - evl_proxy
     - 抽象了oob的element，增加了和代理系统相关的数据项；
   - evl_proxy_factory
     - 是evl_factory的一个实现，规定了用户使用文件系统的能力
      ```C
      struct evl_factory evl_proxy_factory = {
         .name	=	EVL_PROXY_DEV,
         .fops	=	&proxy_fops,
         .build =	proxy_factory_build,
         .dispose =	proxy_factory_dispose,
         .nrdev	=	CONFIG_EVL_NR_PROXIES,
         .flags	=	EVL_FACTORY_CLONE,
      };
      ```

### 函数

1. 文件系统
   - evl_open_file
     - int evl_open_file(struct evl_file *efilp, struct file *filp)
     - 将一个带外文件打开，可以让带内的函数操作；
   - evl_release_file
     - void evl_release_file(struct evl_file *efilp)
     - 将一个带外文件关闭；
   - evl_get_file
     - struct evl_file *evl_get_file(unsigned int fd)
     - 根据fd返回带外文件结构体；
   - evl_get_fileref
     - static inline void evl_get_fileref(struct evl_file *efilp)
     - 同步机制，表示文件被使用；
   - evl_put_file
     - static inline void evl_put_file(struct evl_file *efilp)
     - 同步机制，表示文件被使用完成；
   - evl_init_element
     - int evl_init_element(struct evl_element *e, struct evl_factory *fac, int clone_flags);
     - 在驱动部分，使用某个element前需要初始化它；
   - evl_init_user_element
     - int evl_init_user_element(struct evl_element *e,	struct evl_factory *fac, const char __user *u_name, int clone_flags);
     - 初始化某个元素，让其和对应的factory等关联；
   - evl_destroy_element
     - void evl_destroy_element(struct evl_element *e);
     - 摧毁某个元素；
   - evl_get_element
     - void evl_get_element(struct evl_element *e);
     - 给元素索引加1；
   - evl_put_element
     - void evl_put_element(struct evl_element *e)；
     - 给元素索引减1；
   - evl_open_element
     - int evl_open_element(struct inode *inode, struct file *filp);
     - 驱动部分的核心功能；
   - evl_release_element
     - int evl_release_element(struct inode *inode, struct file *filp);
     - 驱动部分的核心功能；
   - evl_create_core_element_device
     - int evl_create_core_element_device(struct evl_element *e, struct evl_factory *fac, const char *name);
     - 注册设备，用于时钟子系统和线程管理子系统；
   - evl_remove_element_device
     - void evl_remove_element_device(struct evl_element *e);
     - 注销设备；
   - evl_index_factory_element
     - static inline void evl_index_factory_element(struct evl_element *e)
   - evl_unindex_factory_element
     - static inline void evl_unindex_factory_element(struct evl_element *e)
   - evl_may_access_factory
     - bool evl_may_access_factory(struct evl_factory *fac);
   - 还有一些内容是用来启动内核的
     - 这部分内容和其它系统无关，可以单独写
     <!-- - evl_create_factory
     - evl_delete_factory
     - evl_early_init_factories
     - evl_early_cleanup_factories
     - evl_late_init_factories
     - evl_late_cleanup_factories -->
2. 代理系统
   - proxy_oob_write
   - proxy_oob_read
   - proxy_oob_poll
   - proxy_write
   - proxy_read
   - proxy_poll
   - proxy_mmap

### todo

1. 完善文档，画流程图；
2. 启动流程；
3. poll轮询；

