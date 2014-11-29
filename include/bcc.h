/*bbcc - libbcc header file - libbcc.h
 *
 * Copyright 2014 Oliver Springer
 *
 * This file is part of libbcc.
 *
 *  libbcc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3 of the License.

 * libbcc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with libbcc.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <json/json.h>

#ifndef _BCC_H_
#define _BCC_H_
#define BCCVERSION "1.0"

struct BccMessage
{
	char bccVersion[6];
	char nick[26];
	char ipAddr[40];
	char *msg;
};

int parseMessage(char* data, struct BccMessage* bccmsg);
struct BccMessage* createMessage(char *inNick, char *inIpAddr, char *inMessage);
char* encodeMessage(struct BccMessage *bccmsg);

#endif

