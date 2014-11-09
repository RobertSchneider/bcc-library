#include <iostream>
#include <cstring>
#include <json/json.h>

#ifndef _BCC_H_
#define _BCC_H_

class BccMessage
{
	private:
		char bccVersion[6];
		char nick[26];
		char ipAddr[40];
		std::string msg;
	public:
		BccMessage(std::string input);
		BccMessage(char inVersion[6], char inNick[26], char inIpAddr[40], std::string inMessage);
		char* getBccVersion();
		char* getNick();
		char* getIp();
		std::string getMsg();
		std::string encodeMessage();
};

class BccMessageInitException
{
	private:
		int eID;
	public:
		BccMessageInitException(int input);
		int getEID();
};
#endif