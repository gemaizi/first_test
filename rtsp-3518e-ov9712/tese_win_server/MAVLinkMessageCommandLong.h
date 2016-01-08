#ifndef _MAVLINK_MESSAGE_COMMAND_LONG_H
#define _MAVLINK_MESSAGE_COMMAND_LONG_H

#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <stdio.h>
#include "Common.h"

#define  MAVLINK_MSG_ID_COMMAND_LONG 76
typedef struct {
	
	MAVLinkMessageBase mavLinkMessageBase;
	 /**
	 * Parameter 1, as defined by MAV_CMD enum.
	 */
	 float param1;
	 /**
	 * Parameter 2, as defined by MAV_CMD enum.
	 */
	 float param2;
	 /**
	 * Parameter 3, as defined by MAV_CMD enum.
	 */
	 float param3;
	 /**
	 * Parameter 4, as defined by MAV_CMD enum.
	 */
	 float param4;
	 /**
	 * Parameter 5, as defined by MAV_CMD enum.
	 */
	 float param5;
	 /**
	 * Parameter 6, as defined by MAV_CMD enum.
	 */
	 float param6;
	 /**
	 * Parameter 7, as defined by MAV_CMD enum.
	 */
	 float param7;
	 /**
	 * Command ID, as defined by MAV_CMD enum.
	 */
	 short command;
	 /**
	 * System which should execute the command
	 */
	 char target_system;
	 /**
	 * Component which should execute the command, 0 for all components
	 */
	 char target_component;
	 /**
	 * 0: First transmission of this command. 1-255: Confirmation transmissions
	 * (e.g. for kill command)
	 */
	 char confirmation;
}MAVLinkMessageCommandLong;

 MAVLinkMessageCommandLong mavLinkMessageCommandLong;

 MAVLinkPacket pack_CommandLong(MAVLinkMessageCommandLong *mavLinkMessageCommandLong);
 MAVLinkMessageCommandLong* unpack_CommandLong(MAVLinkPacket *mavLinkPacket);

#endif

