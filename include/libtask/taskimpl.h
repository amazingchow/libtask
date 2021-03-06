#define USE_UCONTEXT 1

#include <assert.h>
#include <errno.h>
#include <sched.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#if USE_UCONTEXT
#	include <ucontext.h>
#endif
#include "task.h"

#include <inttypes.h>
#include <sys/utsname.h>

#define nil ((void*)0)
#define nelem(x) (sizeof(x) / sizeof((x)[0]))

#define ulong task_ulong
#define uint task_uint
#define uchar task_uchar
#define ushort task_ushort
#define uvlong task_uvlong
#define vlong task_vlong

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long long uvlong;
typedef long long vlong;

#define print task_print
#define fprint task_fprint
#define snprint task_snprint
#define seprint task_seprint
#define vprint task_vprint
#define vfprint task_vfprint
#define vsnprint task_vsnprint
#define vseprint task_vseprint
#define strecpy task_strecpy

int print(char*, ...);
int fprint(int, char*, ...);
char* snprint(char*, uint, char*, ...);
char* seprint(char*, char*, char*, ...);
int vprint(char*, va_list);
int vfprint(int, char*, va_list);
char* vsnprint(char*, uint, char*, va_list);
char* vseprint(char*, char*, char*, va_list);
char* strecpy(char*, char*, char*);

typedef struct Context Context;

enum {
	STACK = 8192
};

struct Context {
	ucontext_t uc;
};

struct Task {
	char name[256];   // offset known to acid
	char state[256];
	Task* next;
	Task* prev;
	Task* allnext;
	Task* allprev;
	Context context;
	uvlong alarmtime;
	uint id;
	uchar* stk;
	uint stksize;
	int exiting;
	int alltaskslot;
	int system;
	int ready;
	void (*startfn)(void*);
	void* startarg;
	void* udata;
};

void taskready(Task*);
void taskswitch(void);

void addtask(Tasklist*, Task*);
void deltask(Tasklist*, Task*);

extern Task* taskrunning;
extern int taskcount;
