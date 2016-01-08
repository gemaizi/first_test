#ifndef _MAVLINK_MESSAGE_HEARTBEAT_H
#define _MAVLINK_MESSAGE_HEARTBEAT_H

#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <stdio.h>

#include "Common.h"


#define MAVLINK_MSG_ID_HEARTBEAT  0

typedef struct
{

	MAVLinkMessageBase mavLinkMessageBase;
	/**
	* A bitfield for use for autopilot-specific flags.
	*/
	 int custom_mode;
	/**
	* Type of the MAV (quadrotor, helicopter, etc., up to 15 types, defined in
	* MAV_TYPE ENUM)
	*/
	 char type;
	/**
	* Autopilot type / class. defined in MAV_AUTOPILOT ENUM
	*/
	 char autopilot;
	/**
	* System mode bitfield, see MAV_MODE_FLAG ENUM in
	* mavlink/include/mavlink_types.h
	*/
	 char base_mode;
	/**
	* System status flag, see MAV_STATE ENUM
	*/
	 char system_status;
	/**
	* MAVLink version, not writable by user, gets added by protocol because of
	* magic data type: uint8_t_mavlink_version
	*/
	 char mavlink_version;
}MAVLinkMessageHeartbeat;

MAVLinkMessageHeartbeat mavLinkMessageHeartbeat;

MAVLinkPacket pack_Heartbeat(MAVLinkMessageHeartbeat *mavLinkMessageHeartbeat);
MAVLinkMessageHeartbeat* unpack_Heartbeat(MAVLinkPacket *mavLinkPacket);


#endif

