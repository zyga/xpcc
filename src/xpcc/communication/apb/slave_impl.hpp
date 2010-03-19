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

#ifndef	XPCC_APB__SLAVE_HPP
	#error	"Don't include this file directly, use 'slave.hpp' instead!"
#endif

// ----------------------------------------------------------------------------

template <typename INTERFACE>
xpcc::apb::Slave<INTERFACE>::Slave(uint8_t address,
		xpcc::accessor::Flash<Action> actionList,
		uint8_t actionCount) : 
	ownAddress(address), actionList(actionList), actionCount(actionCount)
{
}

// ----------------------------------------------------------------------------

template <typename INTERFACE>
void
xpcc::apb::Slave<INTERFACE>::sendErrorResponse(uint8_t errorCode)
{
	uint8_t error = errorCode;
	
	INTERFACE::sendMessage(
			INTERFACE::masterAddress,
			currentCommand | INTERFACE::NACK,
			&error,
			1);
}

template <typename INTERFACE>
void
xpcc::apb::Slave<INTERFACE>::sendResponse(const uint8_t *payload, uint8_t payloadLength)
{
	INTERFACE::sendMessage(
			INTERFACE::masterAddress,
			currentCommand | INTERFACE::ACK,
			payload,
			payloadLength);
}

template <typename INTERFACE>
void
xpcc::apb::Slave<INTERFACE>::sendResponse()
{
	INTERFACE::sendMessage(
			INTERFACE::masterAddress,
			currentCommand | INTERFACE::ACK,
			NULL,
			0);
}

// ----------------------------------------------------------------------------

template <typename INTERFACE>
void
xpcc::apb::Slave<INTERFACE>::update()
{
	INTERFACE::update();
	if (INTERFACE::isMessageAvailable())
	{
		if (INTERFACE::getAddress() == this->ownAddress)
		{
			bool found = false;
			currentCommand = INTERFACE::getCommand();
			
			xpcc::accessor::Flash<Action> list = actionList;
			for (uint8_t i = 0; i < actionCount; ++i)
			{
				Action action(*list);
				
				if (currentCommand == action.command)
				{
					found = true;
					
					if (INTERFACE::getPayloadLength() == action.payloadLength)
					{
						// execute callback function
						(*action.function)(*this, INTERFACE::getPayload());
					}
					else {
						this->sendErrorResponse(INTERFACE::WRONG_PAYLOAD_SIZE);
					}
					break;
				}
				++list;
			}
			
			if (!found) {
				this->sendErrorResponse(INTERFACE::NO_ACTION);
			}
		}
		INTERFACE::dropMessage();
	}
}