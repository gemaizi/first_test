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

void update_checksum(int data, CRC *crc);
void finish_checksum(int msgid, CRC *crc);
void start_checksum(CRC *crc);
int getMSB(CRC *crc);
int getLSB(CRC *crc);


#endif

