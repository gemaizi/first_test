
#include "Parser.h"

MAV_states state = MAVLINK_PARSE_STATE_UNINIT;

static unsigned char msg_received;

/**
 * This is a convenience function which handles the complete MAVLink
 * parsing. the function will parse one byte at a time and return the
 * complete packet once it could be successfully decoded. Checksum and other
 * failures will be silently ignored.
 * 
 * @param c
 *            The char to parse
 */

MAVLinkPacket mavlink_parse_char(int c)
{
	msg_received = 0;

	switch (state)
	{
	case MAVLINK_PARSE_STATE_UNINIT:
	case MAVLINK_PARSE_STATE_IDLE:

		if (c == MAVLINK_STX)
		{
			state = MAVLINK_PARSE_STATE_GOT_STX;
			InitMAVLinkPacket(m);
		}
		break;

	case MAVLINK_PARSE_STATE_GOT_STX:
		if (msg_received)
		{
			msg_received = 0;
			state = MAVLINK_PARSE_STATE_IDLE;
		} else
		{
			m.len = c;
			state = MAVLINK_PARSE_STATE_GOT_LENGTH;
		}
		break;

	case MAVLINK_PARSE_STATE_GOT_LENGTH:
		m.seq = c;
		state = MAVLINK_PARSE_STATE_GOT_SEQ;
		break;

	case MAVLINK_PARSE_STATE_GOT_SEQ:
		m.sysid = c;
		state = MAVLINK_PARSE_STATE_GOT_SYSID;
		break;

	case MAVLINK_PARSE_STATE_GOT_SYSID:
		m.compid = c;
		state = MAVLINK_PARSE_STATE_GOT_COMPID;
		break;

	case MAVLINK_PARSE_STATE_GOT_COMPID:
		m.msgid = c;
		if (m.len == 0)
		{
			state = MAVLINK_PARSE_STATE_GOT_PAYLOAD;
		} else
		{
			state = MAVLINK_PARSE_STATE_GOT_MSGID;
		}
		break;

	case MAVLINK_PARSE_STATE_GOT_MSGID:
		add((char)c,m.mavLinkPayload);
		if (payloadIsFilled(m))
		{
			state = MAVLINK_PARSE_STATE_GOT_PAYLOAD;
		}
		break;

	case MAVLINK_PARSE_STATE_GOT_PAYLOAD:
		generateCRC(m);
		// Check first checksum byte
		if (c != getLSB(m.crc))
		{
			msg_received = 0;
			state = MAVLINK_PARSE_STATE_IDLE;
			if (c == MAVLINK_STX)
			{
				state = MAVLINK_PARSE_STATE_GOT_STX;
				start_checksum(m.crc);
			}
			printf("crc error!\n");
		} else
		{
			state = MAVLINK_PARSE_STATE_GOT_CRC1;
		}
		break;

	case MAVLINK_PARSE_STATE_GOT_CRC1:
		// Check second checksum byte
		if (c != getMSB(m.crc))
		{
			msg_received = 0;
			state = MAVLINK_PARSE_STATE_IDLE;
			if (c == MAVLINK_STX)
			{
				state = MAVLINK_PARSE_STATE_GOT_STX;
				start_checksum(m.crc);
			}
			printf("crc error!\n");
		} else
		{ // Successfully received the message
			
			msg_received = 1;
			state = MAVLINK_PARSE_STATE_IDLE;
		}

		break;

	}
	if (msg_received)
	{
		return m;
	} else
	{
		return null;
	}
}





