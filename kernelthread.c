#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

void fun(int a)
{

printk("a=%d",a);
 }
static struct task_struct *thread_st;
// Function executed by kernel thread
static int thread_fn(void *unused)
{
    int a=10;
        printk(KERN_INFO "Thread Running\n");
        ssleep(5);
	fun(a);
    
    printk(KERN_INFO "Thread Stopping\n");
   return 0;
}
// Module Initialization
static int __init init_thread(void)
{
    printk(KERN_INFO "Creating Thread\n");
    //Create the kernel thread with name 'mythread'
    thread_st = kthread_run(thread_fn, NULL, "mythread");
    if (thread_st)
        printk(KERN_INFO "Thread Created successfully\n");
    else
        printk(KERN_ERR "Thread creation failed\n");
return 0;
}
//module exit
static void __exit cleanup_thread(void)
{
   printk(KERN_INFO "Cleaning Up\n");
     kthread_stop(thread_st);
       printk(KERN_INFO "Thread stopped");
}
module_init(init_thread);
module_exit(cleanup_thread);
