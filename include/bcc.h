/*
 * libbcc - libbcc header file - libbcc.h
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

#ifndef _BCC_H_
#define _BCC_H_
#define BCCVERSION "1.0"

class BccMessage
{
	private:
		char bccVersion[6];
		char nick[26];
		char ipAddr[40];
		std::string msg;
	public:
		BccMessage(std::string input);
		BccMessage(const char *inNick, const char *inIpAddr, const std::string inMessage);
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
