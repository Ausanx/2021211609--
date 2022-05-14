#include <rtthread.h>
/* 指 向 线 程 控 制 块 的 指 针 */
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
static rt_thread_t tid3 = RT_NULL;
static rt_mutex_t mutex = RT_NULL; #define THREAD_PRIORITY 10
#define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5
/* 线 程 1 入 口 */
static void thread1_entry(void *parameter) {
/* 先 让 低 优 先 级 线 程 运 行 */
rt_thread_mdelay(100);
/* 此 时 thread3 持 有 mutex， 并 且 thread2 等 待 持 有 mutex */
/* 检 查 天 thread2 与 thread3 的 优 先 级 情 况 */
if (tid2->current_priority != tid3->current_priority) {
/* 优 先 级 不 相 同， 测 试 失 败 */
rt_kprintf("the priority of thread2 is: %d\n", tid2->current_priority);
rt_kprintf("the priority of thread3 is: %d\n", tid3->current_priority);
rt_kprintf("test failed.\n");
return; }
else
{
rt_kprintf("the priority of thread2 is: %d\n", tid2->current_priority);
rt_kprintf("the priority of thread3 is: %d\n", tid3->current_priority);
rt_kprintf("test OK.\n");
} }
int pri_inversion(void) {
/* 创 建 互 斥 锁 */
mutex = rt_mutex_create("mutex", RT_IPC_FLAG_FIFO);
if (mutex == RT_NULL) {
rt_kprintf("create dynamic mutex failed.\n");
return -1;
}
tid1 = rt_thread_create("thread1",
thread1_entry,
RT_NULL,
THREAD_STACK_SIZE,
THREAD_PRIORITY - 1, THREAD_TIMESLICE);
if (tid1 != RT_NULL)
rt_thread_startup(tid1);}
MSH_CMD_EXPORT(pri_inversion, pri_inversion sample);