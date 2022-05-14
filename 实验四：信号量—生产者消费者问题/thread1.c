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