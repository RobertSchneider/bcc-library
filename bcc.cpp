/*
 * libbcc - libbcc main source file - libbcc.cpp
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

#include <iostream>
#include <cstring>
#include <json/json.h>
#include "include/bcc.h"

BccMessage::BccMessage(std::string input)
{
	char header[5];

	// Sanity check, input must be longer than the header!
	if(sizeof(input) < 5)
		throw BccMessageInitException(1);
	// Check if the message header is valid
	if (strncmp(input.c_str(), "-BCC-", 5) != 0)
		throw BccMessageInitException(2);
	json_object *json = json_tokener_parse(input.substr(5).c_str());
	json_object_object_foreach(json, key, val)
	{
		// Copy the payload into the objects variables
		if(strncmp(key, "version", 7) == 0)
		{
			strncpy(bccVersion, json_object_get_string(val), 5);
			bccVersion[6] = '\0';
		} else if (strncmp(key, "nick", 4) == 0) {
			strncpy(nick, json_object_get_string(val), 25);
			nick[26] = '\0';
		} else if (strncmp(key, "sender", 6) == 0) {
			strncpy(ipAddr, json_object_get_string(val), 39);
			ipAddr[39] = '\0';
		} else if (strncmp(key, "message", 7) == 0) {
			msg = json_object_get_string(val);
		}
	}

	// Destroy the json object
	json_object_put	(json);
}

// Create a BCC message object from nick, IP and a message
BccMessage::BccMessage(const char *inNick, const char *inIpAddr, const std::string inMessage)
{
	strncpy(bccVersion, BCCVERSION, 5);
	bccVersion[6] = '\0';
	strncpy(nick, inNick, 25);
	nick[26] = '\0';
	strncpy(ipAddr, inIpAddr, 39);
	ipAddr[39] = '\0';
	msg = inMessage;
}

char* BccMessage::getBccVersion()
{
	return bccVersion;
}
char* BccMessage::getNick()
{
	return nick;
}
char* BccMessage::getIp()
{
	return ipAddr;
}
std::string BccMessage::getMsg()
{
	return msg;
}
// Build a bcc message string from the message object. All variables should be set.
std::string BccMessage::encodeMessage()
{
	std::string ret = "-BCC-";

	json_object *json = json_object_new_object();
	json_object_object_add(json, "version", json_object_new_string(bccVersion));
	json_object_object_add(json, "nick", json_object_new_string(nick));
	json_object_object_add(json, "sender", json_object_new_string(ipAddr));
	json_object_object_add(json, "message", json_object_new_string(msg.c_str()));
	
	ret.append(json_object_to_json_string(json));

	// Destroy the json object
	json_object_put	(json);

	return ret;
}

// Initialization exception.
// 1 = received string is too short
// 2 = received string has a bad header
BccMessageInitException::BccMessageInitException(int input)
{
	eID = input;
}
int BccMessageInitException::getEID()
{
	return eID;
}
