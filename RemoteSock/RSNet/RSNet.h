#pragma once

#include <cstdint>
#include <iostream>

namespace RSNet
{
	enum class MESSAGE_TYPE 
	{
		DEFAULT,
		BROADCAST,
		KICK,
		BAN,
		PLAYERUPDATE,
		GAMEUPDATE
	};

	struct Packet
	{
		uint8_t header;
		// guaranteed 1024 bytes
		char body[1024];
		uint16_t body_length;
		// so we can track what we've actually used, it will be easier when tx, rx.
		
		/*void printBody()
		{
			std::cout << static_cast()
		}*/
		
		/*
		* We want 2 overloaded operators.
		* packet1 << "some string". Packs string into body.
		* std::cout << packet1. Outputs packet1 like: "header: body".
		* 
		* 
		* 
		* A nice to have would be a third operator:
		* packet1 << MESSAGE_TYPE. Packs message type enum into header.
		*/ 

		Packet& operator<<(const std::string& contents) 
		{ 

			if (contents.size() >= sizeof(body))
			{
				throw std::runtime_error("Body exceeds buffer.");
			}

			this->body_length = contents.size();

			// note: std::string.data() guarantees null terminator {for >= c++17, which ive set}
			std::memcpy(body, contents.data(), contents.size());
			header = static_cast<uint8_t>(MESSAGE_TYPE::DEFAULT);
			return *this;
		}

		friend std::ostream operator<<(std::ostream& os, const Packet& p);
		
	};
}

// Overload ostream insertion operator so we can easily log packet bodies.

std::ostream& operator<<(std::ostream& os, const RSNet::Packet& p)
{
	os << "Packet length: " << p.body_length << " body: \n";
	os.write(p.body, p.body_length);
	os << "\n";
	return os;
}