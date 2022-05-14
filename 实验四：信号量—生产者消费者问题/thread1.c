#include <rtthread.h>
#define THREAD_PRIORITY 6 #define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5
/* 定 义 最 大 5 个 元 素 能 够 被 产 生 */
#define MAXSEM 5
/* 用 于 放 置 生 产 的 整 数 数 组 */
rt_uint32_t array[MAXSEM];
/* 指 向 生 产 者、 消 费 者 在 array 数 组 中 的 读 写 位 置 */
static rt_uint32_t set, get;
/* 指 向 线 程 控 制 块 的 指 针 */
static rt_thread_t producer_tid = RT_NULL;
static rt_thread_t consumer_tid = RT_NULL;
struct rt_semaphore sem_lock;
struct rt_semaphore sem_empty, sem_full;
/* 生 产 者 线 程 入 口 */
void producer_thread_entry(void *parameter) {
int cnt = 0;
/* 运 行 10 次 */
while (cnt < 10)
{
/* 获 取 一 个 空 位 */
rt_sem_take(&sem_empty, RT_WAITING_FOREVER);
/* 修 改 array 内 容， 上 锁 */
rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
array[set % MAXSEM] = cnt + 1;
rt_kprintf("the producer generates a number: %d\n", array[set % MAXSEM]);
set++;
rt_sem_release(&sem_lock);
/* 发 布 一 个 满 位 */
rt_sem_release(&sem_full);
cnt++;
/* 暂 停 一 段 时 间 */
rt_thread_mdelay(20);
}
rt_kprintf("the producer exit!\n");
}
int producer_consumer(void) {
set = 0;
get = 0;
/* 初 始 化 3 个 信 号 量 */
rt_sem_init(&sem_lock, "lock", 1, RT_IPC_FLAG_FIFO);
rt_sem_init(&sem_empty, "empty", MAXSEM, RT_IPC_FLAG_FIFO);
rt_sem_init(&sem_full, "full", 0, RT_IPC_FLAG_FIFO);
/* 创 建 生 产 者 线 程 */
producer_tid = rt_thread_create("producer",producer_thread_entry, RT_NULL,
THREAD_STACK_SIZE,
THREAD_PRIORITY - 1, THREAD_TIMESLICE);
if (producer_tid != RT_NULL)
rt_thread_startup(producer_tid);}
MSH_CMD_EXPORT(producer_consumer, producer_consumer sample);