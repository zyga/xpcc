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

#ifndef	XPCC__FLASH_HPP
#define	XPCC__FLASH_HPP

#include "../../utils/misc.hpp"
#include "flash_reader.hpp"

namespace xpcc
{
	/**
	 * \brief	Pointer to flash memory
	 * 
	 * This tepmplate can mostly be used like a regular pointer, but operates
	 * on flash memory. It will automatically read the data from flash when
	 * dereferenced.
	 * 
	 * Based on a implementation of Rolf Magnus, see
	 * http://www.mikrocontroller.net/topic/78610#656695
	 * 
	 * \author	Fabian Greif <fabian.greif@rwth-aachen.de>
	 */
	template<typename T>
	class FlashPointer
	{
	public:
		ALWAYS_INLINE
		explicit FlashPointer(const T* address = 0) : address(address) {
		}
		
		template <typename U>
		ALWAYS_INLINE
		explicit FlashPointer(const FlashPointer<U>& rhs)
		: address((T*)rhs.address) {
		}
		
		ALWAYS_INLINE
		const T
		operator *() const {
			return FlashReader<T, sizeof(T)>::read(address);
		}
		
		ALWAYS_INLINE
		const T
		operator [](size_t index) const {
			return FlashReader<T, sizeof(T)>::read(address + index);
		}
		
		ALWAYS_INLINE
		FlashPointer&
		operator++()
		{
			*this += 1;
			return *this;
		}

		ALWAYS_INLINE
		FlashPointer
		operator++(int)
		{
			FlashPointer ret = *this;
			++*this;
			return ret;
		}

		ALWAYS_INLINE
		FlashPointer&
		operator--()
		{
			*this -= 1;
			return *this;
		}

		ALWAYS_INLINE
		FlashPointer&
		operator--(int)
		{
			FlashPointer ret = *this;
			--*this;
			return ret;
		}
		
		ALWAYS_INLINE
		FlashPointer&
		operator+=(size_t rhs)
		{
			address += rhs;
			return *this;
		}
		
		ALWAYS_INLINE
		FlashPointer&
		operator-=(size_t rhs)
		{
			address -= rhs;
			return *this;
		}
		
		ALWAYS_INLINE
		const T*
		getPointer() const {
			return address;
		}
	
	private:
		const T* address;
	};
	
	template<typename T>
	ALWAYS_INLINE
	FlashPointer<T>
	Flash(const T* ptr)
	{
		return FlashPointer<T>(ptr);
	}
}

#endif	// XPCC__FLASH_HPP