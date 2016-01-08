#ifndef _MAVLINK_PACKET_H
#define _MAVLINK_PACKET_H

#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <stdio.h>

#include "MAVLinkPayload.h"
#include "CRC.h"

struct MAVLinkPacket{
/**
 * Message length. NOT counting STX, LENGTH, SEQ, SYSID, COMPID, MSGID, CRC1
 * and CRC2
 */
 int len;
/**
 * Message sequence
 */
 int seq;
/**
 * ID of the SENDING system. Allows to differentiate different MAVs on the
 * same network.
 */
 int sysid;
/**
 * ID of the SENDING component. Allows to differentiate different components
 * of the same system, e.g. the IMU and the autopilot.
 */
 int compid;
/**
 * ID of the message - the id defines what the payload means and how it
 * should be correctly decoded.
 */
 int msgid;

 MAVLinkPayload mavLinkPayload;

 CRC crc;

};

#define MAVLINK_STX  254

void InitMAVLinkPacket(MAVLinkPacket mavLinkPacket);
unsigned char payloadIsFilled(MAVLinkPacket mavLinkPacket);
void generateCRC(MAVLinkPacket mavLinkPacket);
void encodePacket(MAVLinkPacket mavLinkPacket,char *buffer);


#endif

