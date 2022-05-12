#include <rtthread.h>
/* 定 时 器 的 控 制 块 */
static rt_timer_t timer1;
static rt_timer_t timer2;
static int cnt = 0;
static void timeout1(void *parameter) {
rt_kprintf("periodic timer is timeout %d\n", cnt);
/* 运 行 第 10 次， 停 止 周 期 定 时 器 */
if (cnt++>= 9)
{
rt_timer_stop(timer1);
rt_kprintf("periodic timer was stopped! \n");
} 
}
static void timeout2(void *parameter) {
rt_kprintf("one shot timer is timeout\n");
}
int timer_sample(void) {
/* 创 建 定 时 器 1 周 期 定 时 器 */
timer1 = rt_timer_create("timer1", timeout1,
RT_NULL, 10,
RT_TIMER_FLAG_PERIODIC);
/* 启 动 定 时 器 1 */
if (timer1 != RT_NULL)
rt_timer_start(timer1);
 return 0；
}
MSH_CMD_EXPORT(timer_sample, timer sample);