#pragma once

#include <cstdint>
#include <iostream>

namespace RSNet
{
	struct Packet
	{
		uint8_t header[32];
		// guaranteed 1024 bytes
		uint8_t body[1024];
		
		/*void printBody()
		{
			std::cout << static_cast()
		}*/
		
		/*
		* We want 2 overload operators.
		* packet1 << "some string". Packs string into body.
		* std::cout << packet1. Outputs packet1 like: "header: body".
		* 
		* 
		* 
		* A nice to have would be a third operator:
		* packet1 << MESSAGE_TYPE. Packs message type enum into header.
		*/ 
	};
}