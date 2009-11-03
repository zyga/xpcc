// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2009, Roboterclub Aachen e.V.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
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
 * $Id: communication.hpp 76 2009-10-14 23:29:28Z dergraaf $
 */
// ----------------------------------------------------------------------------

#ifndef	XPCC_RESPONSE_CALLBACK_HPP
#define	XPCC_RESPONSE_CALLBACK_HPP

#include "backend/backend_interface.hpp"
#include "abstract_component.hpp"

namespace xpcc
{

	/**
	 * @ingroup		communication
	 * @brief 		Parameter of the Callbackfunction
	 */
	class ResponseMessage// todo, has maybe to be defined somewhere else (other name), for use with requests too
	{
	public:

		ResponseMessage(const Header& header, const uint8_t *payload, uint8_t payloadSize);
		
		const Header& header;
		const uint8_t * const payload;
		const uint8_t payloadSize;
	};
	
	/**
	 * @ingroup		communication
	 * @brief 		Callback type, which has to be passed to communication during
	 *				actioncall in order to be able to recieve a response.
	 */
	class ResponseCallback
	{
	public:
		typedef void (AbstractComponent::*CallbackFunction)(ResponseMessage& message);

		ResponseCallback(AbstractComponent *object, CallbackFunction callbackFunction);
		
		void
		handleResponse(const BackendInterface * const backend);
		
		AbstractComponent *object;
		CallbackFunction callbackFunction;
	};
	
}

#endif // XPCC_RESPONSE_CALLBACK_HPP