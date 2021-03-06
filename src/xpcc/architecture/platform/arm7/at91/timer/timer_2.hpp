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
/*
 * WARNING: This file is generated automatically, do not edit!
 * Please modify the corresponding *.in file instead and rebuild this file. 
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_AT91__TIMER_2_HPP
#define XPCC_AT91__TIMER_2_HPP

#include "../timer.hpp"

namespace xpcc
{
	namespace at91
	{
		/**
		 * @brief		Three-channel 16-bit Timer/Counter Channel 0 (TC)
		 *
		 * Each channel is organized around a 16-bit counter. The value of the
		 * counter is incremented at each positive edge of the selected clock.
		 * 
		 * Each channel can independently operate in two different modes:
		 * - Capture Mode provides measurement on signals.
 	 	 * - Waveform Mode provides wave generation.
 	 	 * 
		 * In Capture Mode, TIOA and TIOB are configured as inputs.
		 * In Waveform Mode, TIOA is always configured to be an output and
		 * TIOB is an output if it is not selected to be the external trigger.
		 * 
		 * @attention	Not yet implemented!
		 * 
		 * @ingroup		at91
		 * @author		Fabian Greif
		 */
		class Timer2 : public Timer
		{
		public:
			/**
			 * @brief	Enable Clock
			 */
			static void
			enable();
			
			/**
			 * @brief	Disable Clock
			 */
			static void
			disable();
		};
	}
}

#endif // XPCC_AT91__TIMER_2_HPP