#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ssh1131");
MODULE_DESCRIPTION("Truy nguoc cay pha he tu tien trinh con ve tien trinh cha");

static int __init trace_parent_init(void)
{
    struct task_struct *task;

    pr_info("=== BAT DAU TRUY NGUOC PHA HE TIEN TRINH ===\n");
    pr_info("Tien trinh hien tai: %s [PID: %d]\n", current->comm, current->pid);

    /* 
     * Lan nguoc tu con sang cha.
     * Voi kernel 6.x tro di tren Fedora, PID 1 (systemd) co parent la chinh no hoac tro ve init_task (PID 0)
     */
    for (task = current; task != &init_task; task = task->parent) {
        pr_info("  -> Cha: %s [PID: %d]\n", task->parent->comm, task->parent->pid);

        if (task->parent == task) {
            break;
        }
    }

    return 0;
}

static void __exit trace_parent_exit(void)
{
    pr_info("=== GO MODULE: KET THUC KIEM TRA ===\n");
}

module_init(trace_parent_init);
module_exit(trace_parent_exit);