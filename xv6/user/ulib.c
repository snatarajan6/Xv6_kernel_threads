#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "syscall.h"
#include "fs.h"

char*
strcpy(char *s, char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
thread_create(void (*fn)(void*), void *arg)
{
  void* stack;
  stack =(void *)malloc(4096);
  int pid ; 

  pid = clone(fn, arg, stack);

  return pid;
}

int
thread_join()
{
int pid;
void* stack;
pid = join(&stack); 

return pid;
}


int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, void *vsrc, int n)
{
  char *dst, *src;
  
  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}

void lock_init(lock_t *lock)
{
   lock->flag = 0;
}

void lock_acquire(lock_t *lock)
{
   while((xchg(&lock->flag, 1)) == 1);
}

void lock_release(lock_t *lock)
{
   lock->flag = 0;
}

void cond_init(cond_t *cv)
{

cv_init(cv);
//cv->queue.front = -1;
//cv->queue.rear = -1;
//cv->queue.capacity = 8; // NTHREADS = 8 
}



void cond_wait(cond_t *cv, lock_t *lock){

if(lock->flag == 0){
printf(2, "lock not acquired\n"); 
exit();
}
lock_acquire(&cv->qlock);
if(cv_wait(cv) == -1){
printf(2,"cv_wait failed");
lock_release(&cv->qlock);
exit();
}
lock_release(&cv->qlock);

}


