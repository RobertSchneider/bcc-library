/*
 * libbcc - automated test 1 - test1.cpp
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
#include <stdio.h>
#include <json/json.h>
#include "../include/bcc.h"

// Define the strings used for testing
#define NICK "This is a testnick"
#define IPADDR "2001:0db8:85a3:08d3:1319:8a2e:0370:7344"
#define MSG "This is a test message!"

int main(void)
{
	bool bPassedVersion = 0;
	bool bPassedNick = 0;
	bool bPassedIp = 0;
	bool bPassedMsg = 0;
	std::string bccString;

	try
	{
		BccMessage bcc(NICK, IPADDR, MSG);
		bccString = bcc.encodeMessage();
	} catch (BccMessageInitException e) {
		std::cerr << "CAUGHT EXCEPTION: " << e.getEID() << std::endl;
		return 1;
	}

	// Check if the output matches the desired output

	try
	{
		BccMessage bcc(bccString);
		if(strcmp(bcc.getBccVersion(), BCCVERSION) == 0)
			bPassedVersion = 1;
		if(strcmp(bcc.getNick(), NICK) == 0)
			bPassedNick = 1;
		if(strcmp(bcc.getIp(), IPADDR) == 0)
			bPassedIp = 1;
		if(strcmp(bcc.getMsg().c_str(), MSG) == 0)
			bPassedMsg = 1;

		if( (bPassedVersion && bPassedNick) && (bPassedIp && bPassedMsg) )
		{
			std::cout << "LIBBCC PASSED ALL TESTS." << std::endl;
		} else {
			if(!bPassedVersion)
				std::cerr << "LIBBCC FAILED THE VERSION CHECK." << std::endl;
			if(!bPassedNick)
				std::cerr << "LIBBCC FAILED THE NICK CHECK." << std::endl;
			if(!bPassedIp)
				std::cerr << "LIBBCC FAILED THE IP CHECK." << std::endl;
			if(!bPassedMsg)
				std::cerr << "LIBBCC FAILED THE MESSAGE CHECK." << std::endl;
			return -1;
		}
	} catch (BccMessageInitException e) {
		std::cerr << "CAUGHT EXCEPTION: " << e.getEID() << std::endl;
		return 1;
	}
	
	return 0;
}
