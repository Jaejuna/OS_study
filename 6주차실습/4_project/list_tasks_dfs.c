#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/init_task.h>

void dfs(struct task_struct *task) {
    struct task_struct *cursor;
    printk(KERN_INFO "COMM: %-20s STATE: %ld\tPID: %d\n", task->comm, task->state, task->pid);

    /* list_for_each_entry 사용할 경우 */
    list_for_each_entry(cursor, &task->children, sibling) { 
        dfs(cursor); 
    }
}

static int __init list_task_init(void) {

    printk(KERN_INFO "INSTALL: list_tasks_dfs\n");

    dfs(&init_task); // 깊이 우선 탐색을 통해 init 프로세스를 기점으로 모든 자식노드들의 프로세스를 탐색한다.
    return 0;
}

static void __exit list_task_exit(void) {
    printk(KERN_INFO "REMOVE: list_tasks_dfs\n");
}

module_init(list_task_init);
module_exit(list_task_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("list tasks by dfs");
MODULE_AUTHOR("OS2019");
