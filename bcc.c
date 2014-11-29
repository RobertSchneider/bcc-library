/*bbcc - libbcc main source file - libbcc.cpp
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
#include <string.h>
#include "include/bcc.h"
#include <stdio.h>

int parseMessage(char* data, struct BccMessage* bccmsg)
{
	char header[5];

	// Sanity check, input must be longer than the header!
	if(strlen(data) < 5) return 1;
	// Check if the message header is valid
	if (strncmp(data, "-BCC-", 5) != 0) return 1;
	if(bccmsg == NULL)  return 1;

	json_object *json = json_tokener_parse(data + 5);
	json_object_object_foreach(json, key, val)
	{
		// Copy the payload into the objects variables
		if(strncmp(key, "version", 7) == 0)
		{
			strncpy(bccmsg->bccVersion, json_object_get_string(val), 5);
			bccmsg->bccVersion[5] = '\0';
		} else if (strncmp(key, "nick", 4) == 0) {
			strncpy(bccmsg->nick, json_object_get_string(val), 25);
			bccmsg->nick[25] = '\0';
		} else if (strncmp(key, "sender", 6) == 0) {
			strncpy(bccmsg->ipAddr, json_object_get_string(val), 39);
			bccmsg->ipAddr[39] = '\0';
		} else if (strncmp(key, "message", 7) == 0) {
			const char *msg = json_object_get_string(val);
			bccmsg->msg = malloc(strlen(msg)+1);
			strncpy(bccmsg->msg, msg, strlen(msg));
			bccmsg->msg[strlen(msg)] = '\0';
		}
	}
	// Destroy the json object
	json_object_put	(json);
	return 0;
}

// Create a BCC message object from nick, IP and a message
struct BccMessage* createMessage(char *inNick, char *inIpAddr, char *inMessage)
{
	struct BccMessage *msg = malloc(sizeof(struct BccMessage));
	strcpy(msg->bccVersion, BCCVERSION);
	msg->bccVersion[5] = '\0';

	if(inNick != NULL) 
	{
		strcpy(msg->nick, inNick);
		msg->nick[25] = '\0';
	}
	if(inIpAddr != NULL) 
	{
		strcpy(msg->ipAddr, inIpAddr);
		msg->ipAddr[39] = '\0';
	}
	if(inMessage != NULL) 
	{
		msg->msg = malloc(strlen(inMessage)+1);
		strncpy(msg->msg, inMessage, strlen(inMessage));
		msg->msg[strlen(inMessage)] = '\0';
	}
	return msg;
}

// Build a bcc message string from the message object. All variables should be set.
char* encodeMessage(struct BccMessage *bccmsg)
{
	json_object *json = json_object_new_object();
	json_object_object_add(json, "version", json_object_new_string(bccmsg->bccVersion));
	json_object_object_add(json, "nick", json_object_new_string(bccmsg->nick));
	json_object_object_add(json, "sender", json_object_new_string(bccmsg->ipAddr));
	json_object_object_add(json, "message", json_object_new_string(bccmsg->msg));
	const char *pckt = json_object_to_json_string(json);

	char *ret = malloc(strlen(pckt)+5+1);
	strncpy(ret, "-BCC-", 5);
	strncpy(ret+5, pckt, strlen(pckt));
	ret[strlen(pckt)+5] = '\0';

	// Destroy the json object
	json_object_put	(json);

	return ret;
}
