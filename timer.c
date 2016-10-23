#include <linux/module.h> 
#include <linux/printk.h> 
#include <linux/kobject.h> 
#include <linux/sysfs.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/string.h>
#include <linux/kmod.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <asm/param.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nastya Gurskaya");
MODULE_VERSION("1");


static void print_hello(unsigned long data)
{
		printk(KERN_INFO "Hello, world!\n");	
}

static ssize_t timer_read(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", times_left);
}

static ssize_t timer_write(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	sscanf(buf, "%du", &times_left);
	return count;
}

static int timer_init(void)
{
	
	return 0;
}

static void timer_exit(void)
{	
	kobject_put(mytimer_kobject);
	del_timer(&my_timer);
}

module_init(timer_init);
module_exit(timer_exit);
