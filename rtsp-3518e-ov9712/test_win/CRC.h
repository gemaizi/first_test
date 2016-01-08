#ifndef __CRC_H__
#define __CRC_H__

#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <stdio.h>

typedef struct {
 	int CRCvalue;
}CRC;

void update_checksum(int data);
void finish_checksum(int msgid);
void start_checksum();
int getMSB();
int getLSB();


#endif

