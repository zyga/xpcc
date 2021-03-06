// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2011, Roboterclub Aachen e.V.
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
 */
// ----------------------------------------------------------------------------
/*
 * WARNING: This file is generated automatically, do not edit!
 * Please modify the corresponding *.in file instead and rebuild this file. 
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_ATXMEGA__TIMER_HIRES_D_HPP
#define XPCC_ATXMEGA__TIMER_HIRES_D_HPP

#include <avr/io.h>
#include <stdint.h>

#if defined(HIRESD) || defined(__DOXYGEN__)

// older versions of avr-libc provide false register names
#ifndef HIRESD_CTRLA
#	define HIRESD_CTRLA		HIRESD_CTRL
#endif

namespace xpcc
{
	namespace atxmega
	{
		/**
		 * \brief		HIgh RESolution Extension of Timer D
		 *
		 * \ingroup		atxmega_timer
		 */
		class HighResD
		{
		public:
			inline static HIRES_t&
			getHighResBase()
			{
				return HIRESD;
			}
			
			inline static void
			setHIRESEnable(HIRES_HREN_t enable)
			{
				HIRESD_CTRLA = enable;
			}
		};
	}
}

#endif // HIRESD
#endif // XPCC_ATXMEGA__TIMER_HIRES_D_HPP
