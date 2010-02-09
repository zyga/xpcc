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

#include <xpcc/math/angle.hpp>

#include "angle_test.hpp"

void
AngleTest::testConstructor()
{
	xpcc::Angle angle;
	TEST_ASSERT_EQUALS(angle, 0);
	
	xpcc::Angle angle2(1.2);
	TEST_ASSERT_EQUALS(angle2, 1.2);
}

void
AngleTest::testAssignment()
{
	xpcc::Angle angle;
	
	angle = 0.7 * M_PI;
	TEST_ASSERT_EQUALS(angle, 0.7 * M_PI);
	
	angle = -0.4 * M_PI;
	TEST_ASSERT_EQUALS(angle, -0.4 * M_PI);
}

void
AngleTest::testNormalize()
{
	xpcc::Angle angle;
	
	angle = 0.3 * M_PI;
	angle.normalize();
	TEST_ASSERT_EQUALS_FLOAT(angle, 0.3 * M_PI);
	
	angle = -0.6 * M_PI;
	angle.normalize();
	TEST_ASSERT_EQUALS_FLOAT(angle, -0.6 * M_PI);
	
	angle = 2.9 * M_PI;
	angle.normalize();
	TEST_ASSERT_EQUALS_FLOAT(angle, 0.9 * M_PI);
	
	angle = -2.9 * M_PI;
	angle.normalize();
	TEST_ASSERT_EQUALS_FLOAT(angle, -0.9 * M_PI);
	
	angle = 1.5 * M_PI;
	angle.normalize();
	TEST_ASSERT_EQUALS_FLOAT(angle, -0.5 * M_PI);
}

void
AngleTest::testReverse()
{
	xpcc::Angle angle;
	
	angle = -0.5 * M_PI;
	angle.reverse();
	TEST_ASSERT_EQUALS_FLOAT(angle, 0.5 * M_PI);
	
	angle = -0.9 * M_PI;
	angle.reverse();
	TEST_ASSERT_EQUALS_FLOAT(angle, 0.1 * M_PI);
	
	angle = 0.7 * M_PI;
	angle.reverse();
	TEST_ASSERT_EQUALS_FLOAT(angle, -0.3 * M_PI);
}

void
AngleTest::testGlobalFunctions()
{
	xpcc::Angle angle;
	
	//cos();
	//sin();
	//tan();
}