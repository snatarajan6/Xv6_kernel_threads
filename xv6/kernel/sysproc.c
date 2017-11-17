#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_cv_signal(void)
{
 int cv;
 if(argint(0, &cv) < 0)
	return -1;
 return cv_signal((cond_t *)cv);

}

int
sys_cv_wait(void)
{
 int cv, lock;
 if(argint(0, &cv) < 0)
	return -1;
 if(argint(1, &lock) < 0)
	return -1;
 return cv_wait((cond_t *)cv, (lock_t *)lock);
}
int
sys_cv_init(void)
{
 int cv;
 if(argint(0, &cv) < 0)
	return -1;
 return cv_init((cond_t *)cv);
}

int
sys_clone(void)
{
  int fn, arg, stack;

  if(argint(0, &fn) < 0)
    return -1;
  if(argint(1, &arg) < 0)
    return -1;
  if(argint(2, &stack) < 0)
    return -1;

  return clone((void*)fn, (void *)arg, (void*)stack);
}

int
sys_join(void)
{
  int stack;
  if(argint(0, &stack) < 0)
	return -1;

  return join((void **)stack);
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
