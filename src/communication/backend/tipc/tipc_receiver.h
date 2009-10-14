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
 * $Id$
 */
// ----------------------------------------------------------------------------
#ifndef TIPC_RECEIVER_H_
#define TIPC_RECEIVER_H_
 
#include <queue>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include "../icc_receiver_interface.h"

#include "tipc_receiver_socket.h"

namespace rca {
	namespace tipc {
		/**
		 * @class		Receiver
		 * @brief		Receive Packets over the TIPC and store them.
		 * 
		 * In a seperate thread the packets are taken from the TIPC and saved local.
		 *  
		 * @ingroup		tipc
		 * @version		$Id$
		 * @author		Carsten Schmitt < >
		 */
		class Receiver : public icc::ReceiverInterface {
			public:
				Receiver(	icc::TChannelId 	channelId, 
							icc::TComponentId	componentId);
			 	~Receiver();
			
				void 
				addPacketListener(	icc::TChannelId 	channelId,
									icc::TPayloadId 	payloadId);
		
			 	bool 
			 	frontHeader( icc::THeader & header );
			 	
			 	
				//! @throw	rca::icc::WrongPayloadSizeException
				bool 
				frontPayload( void * payload, size_t size );
				
				void 
				popFront();
				
				bool 
				hasPacket();
				
			private:
				typedef boost::shared_array<char>	TSharedArr;
				typedef boost::mutex				TMutex;
				typedef boost::mutex::scoped_lock	TMutexGuard;
				typedef	boost::thread::thread		TThread;
				
				typedef struct {
					icc::THeader	iccHeader;
					TSharedArr		iccPayloadPtr;
				} TPacketQueueSummary;
				
				bool 
				isAlive();
		
				void* 
				runReceiver();
				
				void 
				update();
				
				icc::TChannelId 					channelId_;
				icc::TComponentId					componentId_;
				
				tipc::ReceiverSocket				tipcReceiverSocket_;
				std::queue<TPacketQueueSummary>		packetQueue_;
				
				boost::scoped_ptr<TThread>			receiverThread_;
				TMutex								receiverSocketLock_;
				TMutex								packetQueueLock_;
				
				bool								isAlive_;
		};


	}
	
}

// -------------------------------------------------------------------------


#endif // TIPC_RECEIVER_H_

