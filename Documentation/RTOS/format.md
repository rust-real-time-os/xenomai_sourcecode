# Xenomai源码文档格式

- [Xenomai源码文档格式](#xenomai源码文档格式)
  - [文档内容](#文档内容)
  - [注释格式](#注释格式)
    - [注释的总体要求](#注释的总体要求)
    - [注释格式详细内容](#注释格式详细内容)
    - [其它](#其它)
  - [参考链接](#参考链接)

## 文档内容

在描述一个子系统时，子系统的文档应当包括下面三方面内容：
1. 在代码文件中，给出这个子系统相关的**数据结构的注释**；
2. 在代码文件中，给出这个子系统相关的**函数的注释**；
3. 在/Documentation/RTOS/下面写下这个系统相关的文档，格式暂定为markdown（按照内核的规范，应该是.rst）。文档内容主要是两部分，一部分是**概述**，讲述这个子系统下的数据结构和函数有哪些；另一部分是梳理清除函数的调用关系和数据结构在这个过程的变化，需要针对数据结构和函数分别画出**流程图**，可以非常简略，但是需要准确刻画调用关系；这个部分参考这个[博客](https://mp.weixin.qq.com/s?__biz=MzU1MDkzMzQzNQ==&mid=2247484026&idx=1&sn=f02dd3a0086c9375ca3c92171732024f&chksm=fb9844aeccefcdb825c272d4148d5b7f7136e65b2eabf7ab4fdf2f56dfefaf0ce411d4a14c8f&scene=178&cur_album_id=1344408180989853698#rd)的内容。

下面具体说明1和2中的注释格式。

## 注释格式

注释的格式和Linux内核注释的格式保持一致[1][2]。

### 注释的总体要求

![注释要求](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220110145923.png)

- 注释格式遵循规范，有利于开发人员理解相关的源代码，同时利用@符号和一定的格式规范，开发人员可以用分析工具抽取源码的注释而形成文档，减少工作量；
- **不是对所有的内容注释**，只对自己认为必要的内容注释，减少工作量；
- 对函数来说，注释的重点在于这个函数做了什么，而不是这个函数如何完成这个任务；
- 自己写完注释，可以用scripts/kernel-doc检查一下；
- 注释的详细格式在下一小节讲解；

### 注释格式详细内容

1. 数据结构
   - 注释的方法
     - kernel中的注释都是用/\*comment\*/，不能用//；如果我们想要注释被抽取出来，我们需要用\/\*\*开头，\*\*\/结尾，见例子1；如果我们不想让注释被抽取出来，那么用就\/\*\*开头，\*\*\/结尾，常见于只是给开发者一个提醒的情况，见例子2；
     - 如果我们是给网络相关的代码写注释那么应该写为

        ```C
        /*comment
        */
        ```
        而不是

        ```C
        /*
          comment
        */
        ```

   - 注释的位置
     - 数据结构的注释分为两部分；
     - 首先是介绍这个数据结构的大概内容，将函数的注释写在数据结构定义的位置，注释和数据结构之间没有空行；
     - 在数据结构内对成员写注释，可以写在同一行，也可以写在成员的上面。（从我看到的例子归纳，）注释一般是写在成员的上方，见例子3；但是有一个特殊情况，如果有一组很相似的成员，并且需要介绍这组成员的概况和具体内容，那么就在这些成员的上面写总体的注释，然后在每一个成员后面分别写注释，见例子4；但是也偶见注释写在了成员后面的情况，见例子5，我们尽量不采用这种写法；
   - 注释的格式

      ```C
      /**
       * struct struct_name - Brief description.
      * @member1: Description of member1.
      * @member2: Description of member2.
      *           One can provide multiple line descriptions
      *           for members.
      *
      * Description of the structure.
      */
      ```

   - 例子
     - 例子1
      ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220110214750.png) 
     - 例子2
      ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220110210619.png)
     - 例子3
      ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220110205658.png) 
     - 例子4
      ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220110205531.png)
     - 例子5
      ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220110210455.png)
2. 函数
   - 注释的方法
     - 和数据结构部分的内容一样；
   - 注释的位置
     - 函数的注释分为两部分；
     - 首先是介绍函数的大概内容，将函数的注释写在函数定义的位置，注释和函数之间没有空行；
     - 在函数内部的关键位置，可以写这部分的注释；
   - 注释的格式
      ```C
      /**
       * function_name() - Brief description of function.
      * @arg1: Describe the first argument.
      * @arg2: Describe the second argument.
      *        One can provide multiple line descriptions
      *        for arguments.
      *
      * A longer description, with more discussion of the function function_name()
      * that might be useful to those using or modifying it. Begins with an
      * empty comment line, and may include additional embedded empty
      * comment lines.
      *
      * The longer description may have multiple paragraphs.
      *
      * Context: Describes whether the function can sleep, what locks it takes,
      *          releases, or expects to be held. It can extend over multiple
      *          lines.
      * Return: Describe the return value of function_name.
      *
      * The return value description can also have multiple paragraphs, and should
      * be placed at the end of the comment block.
      */
      ```
      - 如果参数的数量是不确定的
        ```C
        * @...: description
        ```
   - 例子
     - 例子1
      ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220110210730.png) 
     - 例子2
      ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220110215018.png)

### 其它

1. 内核中的注释除了针对数据结构和函数还有其它的内容，这里就不详细介绍了，可以参考[2]中的内容。
2. 这个文档缺乏对结构体嵌套和函数返回值等情况下的介绍，如果遇到这些情况，可以参考[2]中的内容，或者后期再补齐这部分内容。

## 参考链接

[1] https://www.kernel.org/doc/html/latest/process/coding-style.html#commenting  
[2] https://www.kernel.org/doc/html/latest/doc-guide/index.html#doc-guide