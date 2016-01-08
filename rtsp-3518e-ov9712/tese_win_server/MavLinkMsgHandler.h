#ifndef _MAVLINK_MSG_HANDLE_H
#define _MAVLINK_MSG_HANDLE_H

#include "Common.h"
#include "MAVLinkMessageCommandLong.h"
#include "MAVLinkMessageHeartbeat.h"

void receiveData(MAVLinkMessageBase *msg);

#endif