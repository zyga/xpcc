// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2009, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *	 * Redistributions of source code must retain the above copyright
 *	   notice, this list of conditions and the following disclaimer.
 *	 * Redistributions in binary form must reproduce the above copyright
 *	   notice, this list of conditions and the following disclaimer in the
 *	   documentation and/or other materials provided with the distribution.
 *	 * Neither the name of the Roboterclub Aachen e.V. nor the
 *	   names of its contributors may be used to endorse or promote products
 *	   derived from this software without specific prior written permission.
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

#ifndef XPCC__S_CURVE_CONTROLLER_HPP
	#error	"Don't include this file directly, use 's_curve_controller.hpp' instead!"
#endif

// ----------------------------------------------------------------------------

template<typename T>
xpcc::SCurveController<T>::Parameter::Parameter(
		const T& targetArea, const T& kp, const T& increment, const T& decreaseFactor,
		const T& secondaryMaximum, const T& secondaryMinimum) :
	targetArea(targetArea), kp(kp), increment(increment), decreaseFactor(decreaseFactor),
	secondaryMaximum(secondaryMaximum), secondaryMinimum(secondaryMinimum)
{
}			

// ----------------------------------------------------------------------------

template<typename T>
xpcc::SCurveController<T>::SCurveController(const Parameter& parameter) :
	target(), output(), targetReached(false), parameter(parameter)
{
}

// ----------------------------------------------------------------------------

template<typename T>
void
xpcc::SCurveController<T>::setTarget(const T& primary)
{
	this->target = primary;
	targetReached = false;
}

template<typename T>
bool
xpcc::SCurveController<T>::isTargetReached() const
{
	return targetReached;
}

// ----------------------------------------------------------------------------

template<typename T>
void
xpcc::SCurveController<T>::update(const T& primary, const T& secondary)
{
	T error = target - primary;
	
	// adjust sign to be always positive
	bool invert = false;
	T currentValue = secondary;
	if (error < 0)
	{
		invert = true;
		error = -error;
		currentValue = -currentValue;
	}
	
	T outputIncrement = currentValue + parameter.increment;
	T outputDecrement;
	if (error <= parameter.targetArea)
	{
		targetReached = true;
		outputDecrement = error * parameter.kp;
	}
	else {
		outputDecrement = std::sqrt((error - parameter.targetArea) * \
									parameter.decreaseFactor);
	}
	
	output = std::min(outputIncrement, outputDecrement);
	output = std::min(output, parameter.secondaryMaximum);
	
	if (output < parameter.secondaryMinimum) {
		output = parameter.secondaryMinimum;
	}
	
	// revert sign
	if (invert) {
		output = -output;
	}
}

template<typename T>
inline const T&
xpcc::SCurveController<T>::getValue() const
{
	return output;
}