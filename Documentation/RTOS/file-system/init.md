# evl入口

## start_kernel

1. 在/init/main.c下的start_kernel新增了5个函数，分别是
   - stall_inband_nocheck
   - local_irq_disable_full
   <!-- - irq_pipeline_init_early -->
   - irq_pipeline_init
   - local_irq_enable_full


## device_initcall

1. 同时通过device_initcall加载了内核
   - 加载位置在/kernel/evl/init.c
   - 加载的函数是evl_init