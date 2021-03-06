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

#ifndef XPCC_STM32F3__CLOCK_HPP
#define XPCC_STM32F3__CLOCK_HPP

#include <stdint.h>

namespace xpcc
{
	namespace stm32
	{
		/**
		 * Clock management.
		 * 
		 * For using the internal clock (which is 8 MHz) use:
		 * \code
		 * typedef xpcc::stm32::Clock C;
		 * enablePll(C::PllSource::PLL_HSI, 8, 72);	// for STM32Fxxx
		 * switchToPll();
		 * \endcode
		 * 
		 * For using an external crystal with 8 MHz use:
		 * \code
		 * typedef xpcc::stm32::Clock C;
		 * if (enableHse(C::HseConfig::HSE_CRYSTAL))
		 * {
		 *     enablePll(C::PllSource::PLL_HSE, 4, 72);	// for STM32F3xx
		 *     switchToPll();
		 * }
		 * \endcode
		 *
		 * For using an external oscillator with 25 MHz use:
		 * \code
		 * if (enableHse(HSE_BYPASS))
		 * {
		 *     enablePll(PLL_HSE, TODO, TODO);	// for STM32F3xx
		 *     switchToPll();
		 * }
		 * \endcode
		 * 
		 * \ingroup	stm32f3
		 */
		class Clock
		{
		public:
			enum class HseConfig
			{
				HSE_CRYSTAL,	///< Use a crystal to generate a clock
				HSE_BYPASS,		///< Use an external clock (e.g. a crystal oscillator)
			};
			
			enum class PllSource
			{
				// It is known that HSI does not work yet.
//				PLL_HSI,		///< High speed internal clock (8 MHz)
				PLL_HSE,		///< High speed external clock (see HseConfig)
			};
			
			enum class PllMul
			{
				MUL_2   = RCC_CFGR_PLLMULL2, 		/*!< PLL input clock*2 */
				MUL_3   = RCC_CFGR_PLLMULL3, 		/*!< PLL input clock*3 */
				MUL_4   = RCC_CFGR_PLLMULL4, 		/*!< PLL input clock*4 */
				MUL_5   = RCC_CFGR_PLLMULL5, 		/*!< PLL input clock*5 */
				MUL_6   = RCC_CFGR_PLLMULL6, 		/*!< PLL input clock*6 */
				MUL_7   = RCC_CFGR_PLLMULL7, 		/*!< PLL input clock*7 */
				MUL_8   = RCC_CFGR_PLLMULL8, 		/*!< PLL input clock*8 */
				MUL_9   = RCC_CFGR_PLLMULL9, 		/*!< PLL input clock*9 */
				MUL_10  = RCC_CFGR_PLLMULL10, 		/*!< PLL input clock*10 */
				MUL_11  = RCC_CFGR_PLLMULL11, 		/*!< PLL input clock*11 */
				MUL_12  = RCC_CFGR_PLLMULL12, 		/*!< PLL input clock*12 */
				MUL_13  = RCC_CFGR_PLLMULL13, 		/*!< PLL input clock*13 */
				MUL_14  = RCC_CFGR_PLLMULL14, 		/*!< PLL input clock*14 */
				MUL_15  = RCC_CFGR_PLLMULL15, 		/*!< PLL input clock*15 */
				MUL_16  = RCC_CFGR_PLLMULL16, 		/*!< PLL input clock*16 */
			};

		public:
			static bool
			enableHse(const HseConfig config, const uint32_t waitCycles = 1500);
			
			/**
			 * Enable PLL.
			 * 
			 * \param	source 
			 * 		Source select for PLL. If you are using
			 * 		HSE you must enable it first (see enableHse()).
			 *
			 * \param	pllM
			 * 		Division factor for the main PLL (PLL).
			 * 		The PLL must run between 16 and 72 MHz.
			 * 
			 * Example:
			 * 
			 */
			static void
			enablePll(const PllSource source, const PllMul pllM);

			/**
			 * Switch the core to the clock generated by the PLL
			 */
			static bool
			switchToPll(const uint32_t waitCycles = 1500);

			/**
			 * Switch the core to the high speed clock.
			 */
			static bool
			switchToHse(const uint32_t waitCycles = 1500);
		};
	}
}

#endif	//  XPCC_STM32F3__CLOCK_HPP
