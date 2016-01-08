#ifndef _MAVLINK_MESSAGE_BASE_H
#define _MAVLINK_MESSAGE_BASE_H

#include <ctype.h>
#include <sys/types.h>
#include <math.h>
#include <stdio.h>

typedef struct {
	 int sysid;
	 int compid;
	 int msgid;
}MAVLinkMessageBase;

#endif

