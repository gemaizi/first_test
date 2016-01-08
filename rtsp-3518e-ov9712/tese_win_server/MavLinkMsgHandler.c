#include "MavLinkMsgHandler.h"


void receiveData(MAVLinkMessageBase *msg)
{
	
	MAVLinkMessageCommandLong* m_comm_long;
	MAVLinkMessageHeartbeat* msg_heart;

	// drone.getWaypointManager().processMessage(msg);
	switch (msg->msgid)
	{
	case MAVLINK_MSG_ID_COMMAND_LONG:

		m_comm_long = (MAVLinkMessageCommandLong*)msg;
		printf("the command is %d\n", m_comm_long->command);
		break;

	case MAVLINK_MSG_ID_HEARTBEAT:
		/*if (!drone.isDataStreamInit())
		{
			drone.setDataStreamInit(true);
		}
		msg_heart = (MAVLinkMessageHeartbeat*)msg
		drone.getState()
			.setIsFlying(
			((msg_heartbeat)msg).system_status == MAV_STATE.MAV_STATE_ACTIVE);
		processState(msg_heart);
		drone.onHeartbeat(msg_heart);*/

		break;

	default:
		break;
	}
}