#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/cred.h>
#include<linux/sched/signal.h>
#include<linux/moduleparam.h>
#include<linux/sched.h>

static char *P="";
module_param(P,charp,0660);
//Loading Module in kernel
static int __init proc_init(void)
{
	printk("\n");
	printk("_________---Module added successfull---________\n");
	struct task_struct *task;
	const struct cred *cred;
	for_each_process(task){
		cred= current_cred();
		if (strcmp(P,task->comm)==0){
			printk(KERN_INFO " pid=%d userid=%d groupid=%d Comm=%s, \n", task->pid,cred->uid,cred->gid,task->comm);
			return 0;
		}
	}
	return 0;
}
///Unloading module form kernel
static void __exit proc_cleanup(void)
{
	printk(" MODULE DELETED SUCCESSFULLY\n");
}

module_init(proc_init);
module_exit(proc_cleanup);
MODULE_LICENSE("GPL");