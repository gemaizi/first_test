#ifndef _MAVLINK_PLAYLOAD_H
#define _MAVLINK_PLAYLOAD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>

#define  MAX_PAYLOAD_SIZE  512

typedef struct 
{

  char payload[MAX_PAYLOAD_SIZE];
  int read_index;
  int write_index;
}MAVLinkPayload;

void InitMAVLinkPayload(MAVLinkPayload *mavLinkPayload);
char* getData(MAVLinkPayload *mavLinkPayload);
int sizeofpayload(MAVLinkPayload *mavLinkPayload);
void add(char c,MAVLinkPayload *mavLinkPayload);
void resetIndex(MAVLinkPayload *mavLinkPayload);
void reset_writeIndex(MAVLinkPayload *mavLinkPayload);
int floatToIntBits(float value);
float intBitsToFloat(int value);
char getByte(MAVLinkPayload *mavLinkPayload);
short getShort(MAVLinkPayload *mavLinkPayload);
int getInt(MAVLinkPayload *mavLinkPayload);
long getLong(MAVLinkPayload *mavLinkPayload);
long getLongReverse(MAVLinkPayload *mavLinkPayload);
float getFloat(MAVLinkPayload *mavLinkPayload);
void putByte(char data,MAVLinkPayload *mavLinkPayload);
void putShort(short data,MAVLinkPayload *mavLinkPayload);
void putInt(int data,MAVLinkPayload *mavLinkPayload);
void putLong(long data,MAVLinkPayload *mavLinkPayload);
void putFloat(float data,MAVLinkPayload *mavLinkPayload);

#endif

