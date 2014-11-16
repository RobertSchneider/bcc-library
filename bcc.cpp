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
	// Copy the header and check if it's valid
	strncpy(header, input.c_str(), 5);
	if (strncmp(header, "-BCC-", 5) != 0)
		throw BccMessageInitException(2);
	json_object *json = json_tokener_parse(input.substr(5).c_str());
	json_object_object_foreach(json, key, val)
	{
		if (key == "version")
		{
			strncpy(bccVersion, json_object_get_string(val), 5);
			bccVersion[6] = '\0';
		} else if (key == "nick") {
			strncpy(bccVersion, json_object_get_string(val), 25);
			bccVersion[26] = '\0';
		} else if (key == "sender") {
			strncpy(ipAddr, json_object_get_string(val), 39);
			ipAddr[40] = '\0';
		} else if (key == "message") {
			msg = json_object_get_string(val);
		}
	}
}

BccMessage::BccMessage(const char *inVersion, const char *inNick, const char *inIpAddr, const std::string inMessage)
{
	strncpy(bccVersion, inVersion, 5);
	bccVersion[6] = '\0';
	strncpy(nick, inNick, 25);
	bccVersion[26] = '\0';
	strncpy(ipAddr, inIpAddr, 39);
	bccVersion[40] = '\0';
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
std::string BccMessage::encodeMessage()
{
	std::string ret = "-BCC-";

	json_object *json = json_object_new_object();
	json_object_object_add(json, "version", json_object_new_string(bccVersion));
	json_object_object_add(json, "nick", json_object_new_string(nick));
	json_object_object_add(json, "sender", json_object_new_string(ipAddr));
	json_object_object_add(json, "message", json_object_new_string(msg.c_str()));
	
	ret.append(json_object_to_json_string(json));

	return ret;
}

BccMessageInitException::BccMessageInitException(int input)
{
	eID = input;
}
int BccMessageInitException::getEID()
{
	return eID;
}