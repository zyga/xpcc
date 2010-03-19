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
 */
// ----------------------------------------------------------------------------


#include <avr/io.h>

#include <xpcc/architecture/general/gpio.hpp>

#include "spi_e1.hpp"

#ifdef USARTE1

namespace {
	GPIO__OUTPUT(XCK, E, 5);
	GPIO__INPUT(RXD, E, 6);
	GPIO__OUTPUT(TXD, E, 7);
}

// ----------------------------------------------------------------------------
void
xpcc::SpiE1::initialize()
{
	TXD::high();
	TXD::setOutput();
	
	RXD::setInput();
	
	XCK::setOutput();
	XCK::low();
	
	// TODO set bitrate
	// BSEL = f_cpu / (2 * f_baud) - 1
	//USARTE1_BAUDCTRLB = (uint8_t) (ubrr >> 8);
	//USARTE1_BAUDCTRLA = (uint8_t)  ubrr;
	
	// enable SPI master mode and disable UART interrupts
	USARTE1_CTRLA = 0;
	USARTE1_CTRLC = USART_CMODE_MSPI_gc;
	USARTE1_CTRLB = USART_RXEN_bm | USART_TXEN_bm;
}

// ----------------------------------------------------------------------------
uint8_t
xpcc::SpiE1::write(uint8_t data)
{
	// clear flags
	USARTE1_STATUS = USART_RXCIF_bm;
	
	// send byte
	USARTE1_DATA = data;
	
	// wait until the byte is transmitted
	while (!(USARTE1_STATUS & USART_RXCIF_bm))
		;
	
	return USARTE1_DATA;
}

#endif // USARTE1