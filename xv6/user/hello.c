#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void fn(void *arg){

printf(1, "Hello from the function %d", (int *)arg);

}


int
main(int argc, char *argv[])
{
//int* arg = 2; 
int pid = thread_create(fn, 0);  


int join_pid = thread_join();
//if(pid == 0) { printf(1, "In the thread"); }
//else { printf(1, "in parent");	}

exit();

}
