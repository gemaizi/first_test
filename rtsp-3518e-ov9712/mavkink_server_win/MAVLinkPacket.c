

#include "MAVLinkPacket.h"

static unsigned long serialVersionUID = 2095947771227815314L;

void InitMAVLinkPacket(MAVLinkPacket mavLinkPacket)
{
   InitMAVLinkPayload(mavLinkPacket.mavLinkPayload);
   mavLinkPacket.len=0;
   mavLinkPacket.seq=0;
   mavLinkPacket.sysid=0;
   mavLinkPacket.compi=0;
   mavLinkPacket.msgid=0;
   
}

unsigned char payloadIsFilled(MAVLinkPacket mavLinkPacket)
{
	if (mavLinkPacket.mavLinkPayload.sizeofpayload()>= MAX_PAYLOAD_SIZE - 1)
	{
		return 1;
	}
	return (mavLinkPacket.mavLinkPayload.sizeofpayload() == mavLinkPacket.len);
}

/**
 * Update CRC for this packet.
 */
 void generateCRC(MAVLinkPacket mavLinkPacket)
{
	start_checksum(mavLinkPacket.crc);
	update_checksum(mavLinkPacket.len,mavLinkPacket.crc);
	update_checksum(mavLinkPacket.seq,mavLinkPacket.crc);
	update_checksum(mavLinkPacket.sysid,mavLinkPacket.crc);
	update_checksum(mavLinkPacket.compid,mavLinkPacket.crc);
	update_checksum(mavLinkPacket.msgid,mavLinkPacket.crc);
	resetIndex(mavLinkPacket.mavLinkPayload);
	for (int i = 0; i < mavLinkPacket.mavLinkPayload.sizeofpayload(); i++)
	{
		update_checksum(getByte(mavLinkPacket.mavLinkPayload),mavLinkPacket.crc);
	}
	finish_checksum(mavLinkPacket.msgid,mavLinkPacket.crc);
}

/**
 * Encode this packet for transmission.
 * 
 * @return Array with bytes to be transmitted
 */
void encodePacket(MAVLinkPacket mavLinkPacket,char *buffer)
{
	//char[6 + len + 2] buffer;
	if(!buffer)
	{
      printf("buffer is null\n");
	  return ;
	}
	int i = 0;
	resetIndex(mavLinkPacket.mavLinkPayload);
	buffer[i++] = (char) MAVLINK_STX;
	buffer[i++] = (char) mavLinkPacket.len;
	buffer[i++] = (char) mavLinkPacket.seq;
	buffer[i++] = (char) mavLinkPacket.sysid;
	buffer[i++] = (char) mavLinkPacket.compid;
	buffer[i++] = (char) mavLinkPacket.msgid;
	for (int j = 0; j <mavLinkPacket.mavLinkPayload.sizeofpayload(); j++)
	{
		buffer[i++] = getByte(mavLinkPacket.mavLinkPayload);
	}
	generateCRC(mavLinkPacket);
	buffer[i++] = (char) (getLSB(mavLinkPacket.crc));
	buffer[i++] = (char) (getMSB(mavLinkPacket.crc));
}

/**
 * Unpack the data in this packet and return a MAVLink message
 * 
 * @return MAVLink message decoded from this packet
 */
/*	public MAVLinkMessage unpack()
{
	switch (msgid)
	{
	}
	default:
		return null;
	}
}*/

