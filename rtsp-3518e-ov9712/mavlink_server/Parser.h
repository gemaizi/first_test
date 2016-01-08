#ifndef _PARSER_H
#define _PARSER_H

#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <stdio.h>
#include "MAVLinkPacket.h"

/**
 * States from the parsing state machine
 */
enum MAV_states
{
	MAVLINK_PARSE_STATE_UNINIT, MAVLINK_PARSE_STATE_IDLE, MAVLINK_PARSE_STATE_GOT_STX, MAVLINK_PARSE_STATE_GOT_LENGTH, MAVLINK_PARSE_STATE_GOT_SEQ, MAVLINK_PARSE_STATE_GOT_SYSID, MAVLINK_PARSE_STATE_GOT_COMPID, MAVLINK_PARSE_STATE_GOT_MSGID, MAVLINK_PARSE_STATE_GOT_CRC1, MAVLINK_PARSE_STATE_GOT_PAYLOAD
}

MAVLinkPacket m;
MAVLinkPacket mavlink_parse_char(int c)

#endif

