#include "MAVLinkMessageCommandLong.h"

static  int MAVLINK_MSG_LENGTH = 33;

static MAVLinkPacket SendPacket;

MAVLinkPacket pack_CommandLong(MAVLinkMessageCommandLong *mavLinkMessageCommandLong)
 {
	SendPacket.len = MAVLINK_MSG_LENGTH;
	SendPacket.sysid = 255;
	SendPacket.compid = 190;
	SendPacket.msgid = MAVLINK_MSG_ID_COMMAND_LONG;
	putFloat(mavLinkMessageCommandLong->param1, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->param2, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->param3, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->param4, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->param5, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->param6, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->param7, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->command, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->target_system, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->target_component, &SendPacket.mavLinkPayload);
	putFloat(mavLinkMessageCommandLong->confirmation, &SendPacket.mavLinkPayload);

	 return SendPacket;
 }

/**
* Decode a command_long message into this class fields
*
* @param payload
*            The message to decode
*/
MAVLinkMessageCommandLong* unpack_CommandLong(MAVLinkPacket *mavLinkPacket)
{
	
	mavLinkMessageCommandLong.mavLinkMessageBase.sysid = mavLinkPacket->sysid;
	mavLinkMessageCommandLong.mavLinkMessageBase.compid = mavLinkPacket->compid;
	mavLinkMessageCommandLong.mavLinkMessageBase.msgid = MAVLINK_MSG_ID_COMMAND_LONG;
	resetIndex(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.param1 = getFloat(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.param2 = getFloat(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.param3 = getFloat(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.param4 = getFloat(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.param5 = getFloat(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.param6 = getFloat(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.param7 = getFloat(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.command = getShort(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.target_system = getByte(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.target_component = getByte(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageCommandLong.confirmation = getByte(&mavLinkPacket->mavLinkPayload);
	return (&mavLinkMessageCommandLong);

}