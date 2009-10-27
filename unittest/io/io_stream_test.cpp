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

#include "io_stream_test.hpp"

// ----------------------------------------------------------------------------
// simple IODevice which stores all data in a memory buffer
// used for testing the output of an IOStream

class MemoryWriter : public xpcc::IODevice
{
public:
	MemoryWriter() :
		bytesWritten(0) {}
	
	virtual void
	put(char c)
	{
		buffer[bytesWritten] = c;
		bytesWritten++;
	}
	
	using xpcc::IODevice::put;
	
	virtual void
	flush()
	{
		// TODO
		put('\b');
	}
	
	virtual bool
	get(char& /*c*/)
	{
		return false;
	}
	
	void
	clear()
	{
		bytesWritten = 0;
	}
	
	char buffer[20];
	int bytesWritten;
};

// ----------------------------------------------------------------------------
static MemoryWriter device;

void
IoStreamTest::setUp()
{
	device.clear();
	stream = new xpcc::IOStream(device);
}

void
IoStreamTest::tearDown()
{
	delete stream;
}

// ----------------------------------------------------------------------------
void
IoStreamTest::testString()
{
	char string[] = "abc";
	
	(*stream) << string;
	
	TEST_ASSERT_EQUALS_ARRAY(string, device.buffer, 0, 3);
	TEST_ASSERT_EQUALS(device.bytesWritten, 3);
}

FLASH_STRING(flashString) = "abc";

void
IoStreamTest::testFlashString()
{
	char string[] = "abc";
	
	(*stream) << xpcc::Flash(flashString);
	
	TEST_ASSERT_EQUALS_ARRAY(string, device.buffer, 0, 3);
	TEST_ASSERT_EQUALS(device.bytesWritten, 3);
}

void
IoStreamTest::testShortInteger()
{
	char string[] = "123";
	
	(*stream) << 123;
	
	TEST_ASSERT_EQUALS_ARRAY(string, device.buffer, 0, 3);
	TEST_ASSERT_EQUALS(device.bytesWritten, 3);
}

void
IoStreamTest::testInteger()
{
	char string[] = "1234567";
	
	(*stream) << 1234567;
	
	TEST_ASSERT_EQUALS_ARRAY(string, device.buffer, 0, 7);
	TEST_ASSERT_EQUALS(device.bytesWritten, 7);
}

void
IoStreamTest::testFloat()
{
	char string[] = "1.230000e+00";
	
	(*stream) << 1.23f;
	
	TEST_ASSERT_EQUALS_ARRAY(string, device.buffer, 0, 12);
	TEST_ASSERT_EQUALS(device.bytesWritten, 12);
}