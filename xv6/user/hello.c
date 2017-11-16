#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

cond_t c;

void fn(void *arg){

printf(1, "Hello from the function %d", (int *)arg);

}


int
main(int argc, char *argv[])
{
//int* arg = 2; 

cond_init(&c);

int pid = thread_create(fn, 0); 
printf(1, "From main : pid %d ", pid); 
int join_pid = thread_join();

if(join_pid == pid ) printf(1, "SUCCESS");


//if(pid == 0) { printf(1, "In the thread"); }
//else { printf(1, "in parent");	}

exit();

}
