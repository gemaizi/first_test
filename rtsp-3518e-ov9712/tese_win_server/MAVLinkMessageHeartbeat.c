#include "MAVLinkMessageHeartbeat.h"

static int MAVLINK_MSG_LENGTH = 9;

static MAVLinkPacket SendPacket;

MAVLinkPacket pack_Heartbeat(MAVLinkMessageHeartbeat *mavLinkMessageHeartbeat)
{
	SendPacket.len = MAVLINK_MSG_LENGTH;
	SendPacket.sysid = 255;
	SendPacket.compid = 190;
	SendPacket.msgid = MAVLINK_MSG_ID_HEARTBEAT;

	putInt(mavLinkMessageHeartbeat->custom_mode, &SendPacket.mavLinkPayload);
	putByte(mavLinkMessageHeartbeat->type, &SendPacket.mavLinkPayload);
	putByte(mavLinkMessageHeartbeat->autopilot, &SendPacket.mavLinkPayload);
	putByte(mavLinkMessageHeartbeat->base_mode, &SendPacket.mavLinkPayload);
	putByte(mavLinkMessageHeartbeat->system_status, &SendPacket.mavLinkPayload);
	putByte(mavLinkMessageHeartbeat->mavlink_version, &SendPacket.mavLinkPayload);

	return SendPacket;
}

/**
* Decode a command_long message into this class fields
*
* @param payload
*            The message to decode
*/
MAVLinkMessageHeartbeat* unpack_Heartbeat(MAVLinkPacket *mavLinkPacket)
{

	mavLinkMessageHeartbeat.mavLinkMessageBase.sysid = mavLinkPacket->sysid;
	mavLinkMessageHeartbeat.mavLinkMessageBase.compid = mavLinkPacket->compid;
	mavLinkMessageHeartbeat.mavLinkMessageBase.msgid = MAVLINK_MSG_ID_HEARTBEAT;
	resetIndex(&mavLinkPacket->mavLinkPayload);

	mavLinkMessageHeartbeat.custom_mode = getInt(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageHeartbeat.type = getByte(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageHeartbeat.autopilot = getByte(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageHeartbeat.base_mode = getByte(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageHeartbeat.system_status = getByte(&mavLinkPacket->mavLinkPayload);
	mavLinkMessageHeartbeat.mavlink_version = getByte(&mavLinkPacket->mavLinkPayload);
	return (&mavLinkMessageHeartbeat);

}