// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2009, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
// ----------------------------------------------------------------------------

#ifndef XPCC__CAN_CONNECTOR_HPP
	#error	"Don't include this file directly, use 'can.hpp' instead!"
#endif

#include <xpcc/math/utils/bit_operation.hpp>
#include <xpcc/driver/can/can.hpp>

#include <xpcc/debug/logger.hpp>

// -----------------------------------------------------------------------------
template<typename Driver>
xpcc::CanConnector<Driver>::~CanConnector()
{
}

// -----------------------------------------------------------------------------
template<typename Driver>
void
xpcc::CanConnector<Driver>::sendPacket(const Header &header, SmartPointer payload)
{
	bool successfull = false;
	if (payload.getSize() <= 8 && Driver::canSend()) {
		// try to send the message directly
		successfull = this->sendCanMessage(
				header, payload.getPointer(), payload.getSize(), false);
	}

	if (!successfull)
	{
		// append the message to the list of waiting messages
		this->sendList.append(SendListItem(header, payload));
	}
}

// -----------------------------------------------------------------------------
template<typename Driver>
void
xpcc::CanConnector<Driver>::dropPacket()
{
	this->receivedMessages.removeFront();
}

// -----------------------------------------------------------------------------
template<typename Driver>
void
xpcc::CanConnector<Driver>::update()
{
	this->checkAndReceiveMessages();
	this->sendWaitingMessages();
}

// ----------------------------------------------------------------------------
// protected
// ----------------------------------------------------------------------------
template<typename Driver>
uint32_t
xpcc::CanConnector<Driver>::convertToIdentifier(const Header & header, bool fragmentated)
{
	uint32_t identifier;
	
	switch (header.type){
		case xpcc::Header::REQUEST:
			identifier = 0;
			break;
		case xpcc::Header::RESPONSE:
			identifier = 1;
			break;
		case xpcc::Header::NEGATIVE_RESPONSE:
			identifier = 2;
			break;
		default:
			identifier = 0;
	}
	identifier = identifier << 1;
	if (header.isAcknowledge){
		identifier |= 1;
	}
	identifier = identifier << 1;
	// Message counter
	identifier = identifier << 1;
	
	if (fragmentated){
		identifier |= 1;
	}
	identifier = identifier << 8;
	identifier |= header.destination;
	identifier = identifier << 8;
	identifier |= header.source;
	identifier = identifier << 8;
	identifier |= header.packetIdentifier;
	
	return identifier;
}

template<typename Driver>
bool
xpcc::CanConnector<Driver>::convertToHeader(
		const uint32_t & identifier_, xpcc::Header & header)
{
	uint32_t identifier = identifier_;
	
	header.packetIdentifier = 0x000000FF & identifier;
	identifier	= identifier >> 8;
	header.source 			= 0x000000FF & identifier;
	identifier	= identifier >> 8;
	header.destination 		= 0x000000FF & identifier;
	identifier 	= identifier >> 8;

	bool isFragment = false;
	if (identifier & 0x01) {
		isFragment = true;
	}
	identifier = identifier >> 1;

	// todo counter
	identifier = identifier >> 1;

	if( identifier & 0x01 ) {
		header.isAcknowledge = true;
	}
	else {
		header.isAcknowledge = false;
	}
	identifier = identifier >> 1;

	switch (identifier & 0x03)
	{
		case 0:
			header.type = xpcc::Header::REQUEST;
			break;
		case 1:
			header.type = xpcc::Header::RESPONSE;
			break;
		case 2:
			header.type = xpcc::Header::NEGATIVE_RESPONSE;
			break;
		default:
			// unknown type
			//XPCC_LOG_ERROR << "Unknown Type" << xpcc::flush;
			header.type = xpcc::Header::REQUEST;
	}
	
	return isFragment;
}

template<typename Driver>
bool
xpcc::CanConnector<Driver>::sendCanMessage(const Header &header,
		const uint8_t *data, uint8_t size, bool fragmentated)
{
	xpcc::Can::Message message(
			convertToIdentifier(header, fragmentated),
			size);
	
	memcpy(message.data, data, size);
	
	return Driver::sendMessage( message );
}

template<typename Driver>
void
xpcc::CanConnector<Driver>::sendWaitingMessages()
{
	if (this->sendList.isEmpty()) {
		// no message in the queue
		return;
	}
	
	SendListItem& message = this->sendList.getFront();
	uint8_t size = message.payload.getSize();
	bool sendFinished = true;
	
	if (size > 8)
	{
		// fragmented message
		uint8_t data[8];
		
		data[0] = message.fragmentIndex;
		data[1] = size; // complete message
		
		uint8_t offset = message.fragmentIndex * 6;
		uint8_t sizeFragment = size - offset;
		if (sizeFragment > 6) {
			sizeFragment = 6;
			sendFinished = false;
		}
		// else sizeFragment is 6 or smaller, i.a. the last fragment is to be
		// sent.
		// So sendFinished

		memcpy(data + 2, message.payload.getPointer() + offset, sizeFragment);

		if (sendCanMessage(message.header, data, sizeFragment+2, true)) {
			message.fragmentIndex++;
		}
		else {
			sendFinished = false;
		}
	}
	else
	{
		if (!this->sendCanMessage(
				message.header,
				message.payload.getPointer(),
				size,
				false)) {
			sendFinished = false;
		}
	}
	
	if (sendFinished)
	{
		// message was the last fragment
		// => remove it from the list
		this->sendList.removeFront();
	}
}

template<typename Driver>
bool
xpcc::CanConnector<Driver>::retrieveCanMessage()
{
	Can::Message canMessage;
	if (Driver::getMessage(canMessage))
	{
		xpcc::Header header;
		bool isFragment = convertToHeader(canMessage.identifier, header);
		
		if (isFragment)
		{
			// find existing container otherwise create a new one
			const uint8_t fragmentIndex = canMessage.data[0];
			const uint8_t messageSize = canMessage.data[1];
			
			// calculate the number of messages need to send message_size-bytes
			div_t n = div(messageSize, 6);
			uint8_t numberOfFragments = (n.rem > 0) ? n.quot + 1 : n.quot;
			
			if (canMessage.length < 4 || messageSize > 48 || fragmentIndex >= numberOfFragments)
			{
				// illegal format: fragmented messages need to have at least 3 byte payload,
				// 				   the maximum size is 48 Bytes and the fragment number should
				//				   not be higher than the number of fragments.
				return false;
			}

			// check the length of the fragment (all fragments except the last one
			// need to have a payload-length of 6 bytes + 2 byte fragment information)
			uint8_t offset = fragmentIndex * 6;
			if (fragmentIndex + 1 == numberOfFragments)
			{
				// this one is the last fragment
				if (messageSize - offset != canMessage.length - 3)
				{
					// illegal format
					return false;
				}
			}
			else if (canMessage.length != 8)
			{
				// illegal format
				return false;
			}
			
			// Check if other parts of this message are already in the
			// list of receiving messages.
			typename ReceiveList::iterator message = xpcc::find(this->receivingMessages.begin(),
					this->receivingMessages.end(), header);
			
			if (message == this->receivingMessages.end()) {
				// message not found => first part of this message,
				// append it to the list
				this->receivingMessages.prepend(ReceiveListItem(messageSize, header));
				message = this->receivingMessages.begin();
			}
			
			// create a marker for the currently received fragment
			uint8_t currentFragment = (1 << fragmentIndex);
			
			// test if the fragment was already received
			if (currentFragment & message->receivedFragments)
			{
				// error: received fragment twice -> most likely a new message -> delete the old one
				//XPCC_LOG_WARNING << "lost fragment" << xpcc::flush;
				message->receivedFragments = 0;
			}
			message->receivedFragments |= currentFragment;
			
			std::memcpy(message->payload.getPointer() + offset,
					canMessage.data + 2,
					canMessage.length - 2);
			
			// test if this was the last segment, otherwise we have to wait for more messages
			if (xpcc::math::bitCount(message->receivedFragments) == numberOfFragments)
			{
				this->receivedMessages.append(*message);
				this->receivingMessages.erase(message);
			}
		}
		else {
			this->receivedMessages.append(ReceiveListItem(canMessage.length, header));
			
			// copy payload
			std::memcpy(this->receivedMessages.getBack().payload.getPointer(),
					canMessage.data,
					canMessage.length);
		}

		return true;
	}
	// todo Save values
	return false;
}

template<typename Driver>
void
xpcc::CanConnector<Driver>::checkAndReceiveMessages()
{
	while (Driver::isMessageAvailable())
	{
		this->retrieveCanMessage();
	}
}

