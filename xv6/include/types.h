#ifndef _TYPES_H_
#define _TYPES_H_

// Type definitions

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
typedef struct __lock_t { volatile uint flag;} lock_t;
typedef struct __q_t {int front, rear, capacity; int q[8]; } q_t;
typedef struct __cond_t { q_t queue; lock_t qlock; } cond_t;
#ifndef NULL
#define NULL (0)
#endif

#endif //_TYPES_H_
