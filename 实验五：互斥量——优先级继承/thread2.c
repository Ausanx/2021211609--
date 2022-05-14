static void thread2_entry(void *parameter) {
rt_err_t result;
rt_kprintf("the priority of thread2 is: %d\n", tid2->current_priority);
/* 先 让 低 优 先 级 线 程 运 行 */
rt_thread_mdelay(50);
/** 试 图 持 有 互 斥 锁， 此 时 thread3 持 有， 应 把 thread3 的 优 先 级 提 升 * 到 thread2 相 同 的 优 先 级
*/
result = rt_mutex_take(mutex, RT_WAITING_FOREVER);
if (result == RT_EOK) {
/* 释 放 互 斥 锁 */
rt_mutex_release(mutex);
} }tid2 = rt_thread_create("thread2",
thread2_entry,
RT_NULL,
THREAD_STACK_SIZE,
THREAD_PRIORITY, THREAD_TIMESLICE);
if (tid2 != RT_NULL)
rt_thread_startup(tid2);