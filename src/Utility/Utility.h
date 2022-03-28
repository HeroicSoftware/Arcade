/*
 * Utility.h
 *
 *  Created on: Nov 27, 2021
 *      Author: Jordan
 */

#ifndef UTILITY_UTILITY_H_
#define UTILITY_UTILITY_H_

const float PI = 3.14159;
const float TWO_PI = 2.0f * PI;
static const float EPSILON = 0.0001f;
bool IsEqual(float x, float y);
bool IsGreaterThanOrEqual(float x, float y);
bool IsLessThanOrEqual(float x, float y);
float MillisecondsToSeconds(unsigned int milliseconds);
#endif /* UTILITY_UTILITY_H_ */
