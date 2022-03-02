#ifndef __COMMON_H
#define __COMMON_H

/*
 * Make this structure a certain size so that it does not
 * get passed in registers!
 */
typedef struct {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
} addable;

#endif
