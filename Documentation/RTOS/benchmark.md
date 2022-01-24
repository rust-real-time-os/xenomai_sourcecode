# benchmark

- [benchmark](#benchmark)
  - [衡量实时性方法](#衡量实时性方法)
    - [实验方法的细节](#实验方法的细节)
  - [实时任务的场景](#实时任务的场景)
  - [实时性指标](#实时性指标)
    - [实时性指标的分类](#实时性指标的分类)
    - [实时性指标内容讲解](#实时性指标内容讲解)
  - [实验测试方法](#实验测试方法)
    - [方法](#方法)
    - [伪代码](#伪代码)
  - [注意事项](#注意事项)
  - [参考文献](#参考文献)

内核实时性的测量是一个随着运行任务变化很大的过程，我们的测量只能给出一个大体上的结果。干扰的因素繁多，所以我们只能尽可能全面的测试，但是效果只能作为一个参考。

## 衡量实时性方法

1. 衡量实时性可以从理论上进行，给出一个前提假设，然后证明在这个前提下，如果满足某些关系，这个系统是一定可以完成调度的；
   - 某个伯克利的课程上是可以通过硬件分析方法，确定代码和硬件结合做出来的系统是符合硬实时的标准；但是这种系统必然不能承担很复杂的任务；
2. 也可以从实验上进行，通过让系统处于高负荷，长时间的运行状态；
   - 从理论上验证太复杂了，现在的各个进程大都互相联系，而理论上验证的方法都有一些苛刻的前提，所以我们很难像上古时代给出一些严格的理论证明。而只好从实验的结果上给出一个验证；
   - 所以我们现在的硬实时操作系统定义是从响应时间上来说的，并没有给出一个理论上的证明；
   - 在实验时，需要额外注意的是控制变量，排除硬件对os的影响，同时应该对参与比较的系统非常熟悉，这样才可以做到公平对比；
3. 现在对复杂系统的的主流可行方法还是后者，我们也采用这种方法；

### 实验方法的细节

1. 实时性评估首先应该了解有哪些应用场景，也就是需要如何触发这些任务；
2. 然后应该这个场景下知道有哪些指标需要测量；
3. 最后需要寻找一个测量的方法；
4. 下面具体介绍这三个环节

## 实时任务的场景

1. 实时任务有其独特的场景，我们要针对不同的场景设置这个场景下的指标；
2. 介绍一下不同的场景
   - 中断触发
        ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220123211733.png)
        - 中断触发的情景下，有这些环节；
        - 这个图里面还不是很完整，缺少一个中断到达，到意识到有中断的过程；
   - 周期性时钟触发
        ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220123211645.png)
3. 我们最终选择分析中断触发的这个场景，因为这个场景更为普遍；

## 实时性指标

### 实时性指标的分类

1. 第一类指标是对于操作系统接口的测试，就是针对任务管理，内存管理和进程间通信系统接口的测试指标；
   - 这类指标比较直白，就是一个系统调用的时间，相对好测量；
   - 一般是RTOS的制作商提供；
2. 第二类指标是一个复杂情况下的系统性能；
   - 这类指标是模拟业务环境，对内核的一个整体性能进行评测；
   - 评测时主要是关注两个方面：响应速度和吞吐量；
3. 同时还有一些形成规范的标准，对现有的总结进行总结
    ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220123212650.png)
    - 图片的右侧是对os的benchmark，这个类别里面，我们有Rhealsone和Hartstone两类成熟的方法，下面是他们的具体内容；
    - ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220123213115.png)
    - ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220123213711.png)
4. 我们最终的benchmark侧重跑第二类指标，比较有现实意义；我们具体关注响应速度这个指标，出于减少难度的考虑，现阶段不会采用一个成熟的标准；

### 实时性指标内容讲解

下面通过内核对一个外部中断的响应模型具体介绍衡量实时性的指标，这个模型是一个比较普适的情况，基本涵盖了实时内核处理的各个阶段。

1. 首先先介绍一下一个中断的总体流程
    ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220123154251.png)
        
    - 时间节点
      - 中断产生
      - 内核开始处理这个中断
      - 内核处理完成
      - 完成任务
    - 可以看到这里有四个时间节点，三个时间段
      - 第一个时间段是中断延迟interrupt latency，可能影响这个时间段的因素有：
        - 中断需要CPU响应，而CPU很有可能处理关键任务，屏蔽了中断；
        - CPU需要处理相关的指令序列，寻找到处理程序，并且调整寄存器，来为处理中断做铺垫；
      - 第二个时间段是ISR的时间，这个时间段是用来处理ISR内的相关任务，具体的切换流程中断触发的小节有所展示；
        - 缓存的命中情况；
        - 中断服务程序如何完成，这个关系到指令的执行情况；
      - 第三个时间段是dispatch latency;
        - 这个过程可能首先需要完成调度，因为被唤醒的那个程序有可能不是在接受中断的这个CPU的队列上睡眠；
        - 然后进行上下文切换；
    - 下面这张图更为详细
        ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220123214325.png)
2. 我们测试的是第一个时间中断延迟时间，因为随着isr的不同，第二个时间变化很大，所以不应该测试后面的时间；
    - 我们的第一阶段是做到软实时，所以从windriver的官网上的标准来看，这个时长应该是在几百毫秒的量级，目前暂定300ms以内；
        ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220123233208.png)

## 实验测试方法


### 方法

1. 测试的方法
   - 目前采用软件的方法来测试，后续可能采用硬件的方法观察
     - 有现成的工具箱
   - 测试的配置
     ![](https://raw.githubusercontent.com/Richardhongyu/pic/main/20220124083813.png)
2. 压力的设置
   - 设置不同的周期性，非周期性触发事件；
   - 不同的运行的任务种类
   - 满负载


### 伪代码

```c
//time_interrupt_latency = time_irq - time_start;

//main.c
int main(void)
{
    generate_stress_workloads();
    register_isr(isr_function, ...);

    generate_interrupt();

    return 1;
}

//generate_interrupt funtion
int generate_interrupt()
{
    time_start = date.time();
    save_time_start(time_start);
    generate();
    return 1;
}

//isr function
int isr_function()
{
    time_irq = date.time();
    save_time_irq(time_irq);
    // before_waking_the_user_space_program();
    // time_schedule = date.time();
    // save_time_schedule(time_schedule);
    return 1;
}

//the_user_program funtion
//这个步骤目前可以省略
// int the_user_program()
// {
//     time_end = date.time();
//     save_time_end(time_end);
//     program();
//     return 1;
// }

//

```

## 注意事项

1. 各个厂家对benchmark中所涉及内容的定义其实有所差别，就比如时钟中断时，究竟设置不涉及reshedule的过程，这些内容都是需要根据具体情况一一分析，所以我们如果要做到完全公平的比较，是非常具有难度的；
2. 目前有一些比较成熟的benchmark，这些标准是可以直接拿来用的；



## 参考文献

[1] Real-time Operating Systems Book1 - The Theory. Chapter 11.
[2] https://docs.oracle.com/cd/E19455-01/806-4750/chap7rt-21297/index.html
[3] https://evlproject.org/core/benchmarks/