#ifndef _MAVLINK_COMMON_H
#define _MAVLINK_COMMON_H

#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <stdio.h>
#include "MAVLinkPayload.h"
#include "CRC.h"
#include "MAVLinkMessageBase.h"

typedef struct
{
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

	unsigned char is_receive_packet;

	MAVLinkPayload mavLinkPayload;

	CRC crc;

}MAVLinkPacket;

#endif
