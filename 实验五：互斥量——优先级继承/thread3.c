/* 线 程 3 入 口 */
static void thread3_entry(void *parameter) {
rt_tick_t tick;
rt_err_t result;
rt_kprintf("the priority of thread3 is: %d\n", tid3->current_priority);
result = rt_mutex_take(mutex, RT_WAITING_FOREVER);
if (result != RT_EOK) {
rt_kprintf("thread3 take a mutex, failed.\n");
}
/* 做 一 个 长 时 间 的 循 环，500ms */
tick = rt_tick_get();
while (rt_tick_get() - tick < (RT_TICK_PER_SECOND / 2)) ;
rt_mutex_release(mutex);
}/* 创 建 线 程 3 */
tid3 = rt_thread_create("thread3",
thread3_entry,
RT_NULL,
THREAD_STACK_SIZE,
THREAD_PRIORITY + 1, THREAD_TIMESLICE);
if (tid3 != RT_NULL)
rt_thread_startup(tid3);
return 0;