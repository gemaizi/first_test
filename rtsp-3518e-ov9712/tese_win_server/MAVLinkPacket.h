#ifndef _MAVLINK_PACKET_H
#define _MAVLINK_PACKET_H
 
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <stdio.h>

#include "Common.h"
#include "MAVLinkMessageCommandLong.h"
#include "MAVLinkMessageHeartbeat.h"

#define MAVLINK_STX  254


void InitMAVLinkPacket(MAVLinkPacket *mavLinkPacket);
unsigned char payloadIsFilled(MAVLinkPacket *mavLinkPacket);
void generateCRC(MAVLinkPacket *mavLinkPacket);
void encodePacket(MAVLinkPacket *mavLinkPacket,char *buffer);
MAVLinkMessageBase* unpack(MAVLinkPacket *mavLinkPacket);

#endif

