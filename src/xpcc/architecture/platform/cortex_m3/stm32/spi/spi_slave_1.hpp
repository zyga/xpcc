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

#ifndef XPCC_STM32__SPI_SLAVE_1_HPP
#define XPCC_STM32__SPI_SLAVE_1_HPP

#include <stdint.h>
#include "../device.h"

namespace xpcc
{
	namespace stm32
	{
		/**
		 * @brief		Serial peripheral interface (SPI1)
		 * 
		 * Simple unbuffered implementation.
		 * 
		 * STM32F10x:
		 * - SPI1 (APB2) at 72MHz
		 * - SPI2 and SPI3 (APB1) at 36MHz.
		 * 
		 * STM32F2:
		 * - TODO
		 * 
		 * STM32F4xx:
		 * - SPI1 (APB2) at 84MHz
		 * - SPI2, SPI3 (APB1) at 42MHz
		 * 
		 * @ingroup		stm32
		 */
		class SpiSlave1
		{
		public:
			enum Mode
			{
				MODE_0 = 0,								///< SCK normal, sample on rising edge
				MODE_1 = SPI_CR1_CPHA,					///< SCK normal, sample on falling edge
				MODE_2 = SPI_CR1_CPOL,					///< SCK inverted, sample on falling edge
				MODE_3 = SPI_CR1_CPOL | SPI_CR1_CPHA,	///< SCK inverted, sample on rising edge
			};
			
			enum DataSize
			{
				DATA_8_BIT = 0,
				DATA_16_BIT = SPI_CR1_DFF,
			};
			
			enum Mapping
			{
#if defined(STM32F2XX) || defined(STM32F4XX)
				REMAP_PA4_PA5_PA6_PA7,		///< NSS/PA4,  SCK/PA5,  MISO/PA6,  MOSI/PA7,  NSS/PA4 
				REMAP_PA15_PB3_PB4_PB5,		///< NSS/PA15, SCK/PB3,  MISO/PB4,  MOSI/PB5,  NSS/PA15
#else
				REMAP_PA5_PA6_PA7 = 0,							///< SCK/PA5, MISO/PA6, MOSI/PA7, NSS/PA4 
				REMAP_PB3_PB4_PB5 = AFIO_MAPR_SPI1_REMAP,		///< SCK/PB3, MISO/PB4, MOSI/PB5, NSS/PA15
#endif
			};
			
			/**
			 * Configure the IO Pins for SPI1
			 * 
			 * \warning	NSS is not configured and has to be handled
			 * 			by the user!
			 */
			static void
			configurePins(Mapping mapping);
			
		public:
			/**
			 * @brief	Initialize SPI module
			 */
			static void
			initialize(Mode mode = MODE_0, DataSize datasize = DATA_16_BIT);
			
			static uint16_t
			read();
			
			
			static void
			enableInterruptVector(bool enable, uint32_t priority);
			
//			static uint8_t
//			write(uint8_t data);
			
//			static bool
//			setBuffer(uint16_t length,
//					  uint8_t* transmit=0, uint8_t* receive=0,
//					  BufferIncrease bufferIncrease=BUFFER_INCR_BOTH);
//			
//			static bool
//			transfer(TransferOptions options=TRANSFER_SEND_BUFFER_SAVE_RECEIVE);
//			
//			static ALWAYS_INLINE bool
//			transferSync(TransferOptions options=TRANSFER_SEND_BUFFER_SAVE_RECEIVE);
			
//			static bool
//			isFinished();
		};
	}
}

#endif // XPCC_STM32__SPI_1_HPP