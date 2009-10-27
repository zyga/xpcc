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
 * $Id: lock.hpp 94 2009-10-19 18:44:57Z dergraaf $
 */
// ----------------------------------------------------------------------------

#ifndef	XPCC_ATOMIC__LOCK_HPP
#define	XPCC_ATOMIC__LOCK_HPP

#include <stdint.h>

namespace xpcc
{
	namespace atomic
	{
		/// \ingroup	atomic
		/// \brief		Critical section
		///  
		/// Typical usage:
		/// \code
		/// function()
		/// {
		///     // some code with interrupts enabled
		///     
		///     {
		///         atomic::Lock lock;
		///         
		///         // code which should be executed with disabled interrupts.
		///         
		///         // with the end of this block the lock object is destroyed
		///         // and the interrupts are reenabled.
		///     }
		///     
		///     // other code with interrupts enabled
		/// }
		/// \endcode
		/// 
		/// \warning	Interrupts should be disabled the shortest possible time!
		///
		class Lock
		{
		public:
			Lock();
			~Lock();
			
			/// \brief	Reenable interrupts
			///
			/// \warning	Don't use this function without a very good reason!
			void
			reenableInterrupts();
			
			/// \brief	Disable interrupts
			///
			/// Could be used together with reenableInterrupts() to create a
			/// nested block with interrupts enabled inside a block with
			/// interrupts disabled.
			///
			/// \warning	Don't use this function without a very good reason!
			void
			disableInterrupts();

		private:
			uint8_t sreg;
		}; 
	}
}

#ifdef __AVR__

#include <avr/interrupt.h>

xpcc::atomic::Lock::Lock() :
	sreg(SREG)
{
	cli();
}

xpcc::atomic::Lock::~Lock()
{
	SREG = sreg;
	__asm__ volatile ("" ::: "memory");
}

void
xpcc::atomic::Lock::reenableInterrupts()
{
	sei();
	__asm__ volatile ("" ::: "memory");		// TODO needed here?
}

void
xpcc::atomic::Lock::disableInterrupts()
{
	cli();
	__asm__ volatile ("" ::: "memory");		// TODO needed here?
}

#else

// TODO: usefull implementation for any non AVR targets
xpcc::atomic::Lock::Lock()
{
}

xpcc::atomic::Lock::~Lock()
{
}

#endif

#endif	// XPCC_ATOMIC__LOCK_HPP