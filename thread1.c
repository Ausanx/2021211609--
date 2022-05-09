#include <rtthread.h>
#define THREAD_STACK_SIZE 1024
#define THREAD_PRIORITY 20
#define THREAD_TIMESLICE 10
static void thread_entry(void* parameter)
{
rt_uint32_t value;
rt_uint32_t count = 0;
value = (rt_uint32_t)parameter;
while (1)
{
	if(0 == (count % 5))
  {
	rt_kprintf("thread %d is running ,thread %d count = %d\n", value , value
			, count);
			if(count> 200)
				return;			
		}
			count++;
	}
	}
int timeslice_sample(void) 
{
rt_thread_t tid = RT_NULL;

tid = rt_thread_create("thread1",
thread_entry, (void*)1,
THREAD_STACK_SIZE,
THREAD_PRIORITY, THREAD_TIMESLICE);
if (tid != RT_NULL)
rt_thread_startup(tid);
}
MSH_CMD_EXPORT(timeslice_sample, timeslice sample);