+/* 线 程 入 口 */
static void thread_entry(void* parameter) 
{
    rt_uint32_t value;
    rt_uint32_t count = 0;
    value = (rt_uint32_t)parameter;
    while (1)
    {
        if(0 == (count % 5))
        {
            rt_kprintf("thread %d is running ,thread %d count = %d\n", value , value, count);
            if(count> 200) return;
        }
        count++;
    }
}



/*--------------------------------------线程2代码-------------------------------*/
    /* 创 建 线 程 2 */
    tid = rt_thread_create("thread2",
                           thread_entry, (void*)2,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY, THREAD_TIMESLICE-5);
    if (tid != RT_NULL)
        rt_thread_startup(tid);