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

#define DELAY 3
#define TEXT "Hello, world!"

static unsigned long times_left = 0;
static unsigned char timer_exists = 0;

static int timer_init(void);
static void timer_exit(void);

static ssize_t times_write(struct kobject *, struct kobj_attribute *, char *);
static ssize_t times_read(struct kobject *, struct kobj_attribute *, const char *, size_t);

static struct kobj_attribute times_attrb =
    __ATTR(interval, 0664, timer_write, timer_read);

static struct kobject *times_obj = NULL;
static struct timer_list timer;

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
	nit_timer_on_stack(&timer);

    times_obj = kobject_create_and_add("timer", NULL);
    if (!times_obj) {
        return -ENOMEM;
    }

    if (sysfs_create_file(times_obj, &times_attrb.attr)) {
        timer_exit();
        return -EINVAL;
    }
	return 0;
}

static void timer_exit(void)
{	
     if (timer_exists) {
        del_timer(&timer);
    }

    if (times_obj) {
        kobject_put(times_obj);
    }
}

module_init(timer_init);
module_exit(timer_exit);
