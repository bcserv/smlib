#include <smlib>

#if defined _smlib_math_included
  #endinput
#endif
#define _smlib_math_included

enum VecAngle
{
	ANG_ALPHA,
	ANG_BETA,
	ANG_GAMMA
}

/**
 * Makes a negative integer number to a positive integer number.
 *
 * @param number		A number that can be positive or negative.
 * @return				Positive number.
 */
stock any:Math_Abs(any:number)
{	
	if (number >= 0) {
		return number;
	}

	return (number * -1);
}

/**
 * Checks if 2 vectors are equal.
 * You can specfiy a tolerance.
 *
 * @param vec1			First vector (3 dim array)
 * @param vec2			Second vector (3 dim array)
 * @param tolerance 	If you want to check that those vectors are somewhat even. 0.0 means they are 100% even if this function returns true.
 * @return				True if vectors are equal, false otherwise.
 */
stock bool:Math_VectorsEqual(Float:vec1[3], Float:vec2[3], Float:tolerance=0.0)
{	
	new Float:distance = GetVectorDistance(vec1, vec2);
	
	return distance <= tolerance;
}

stock any:Math_Min(any:value, any:min)
{
	if (value < min) {
		value = min;
	}
	
	return value;
}

stock any:Math_Max(any:value, any:max)
{	
	if (value > max) {
		value = max;
	}
	
	return value;
}

stock any:Math_Clamp(any:value, any:min, any:max)
{
	value = Math_Min(value, min);
	value = Math_Max(value, max);

	return value;
}
