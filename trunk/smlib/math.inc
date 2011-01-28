#if defined _smlib_math_included
	#endinput
#endif
#define _smlib_math_included

#include <smlib>

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

/**
 * Sets the given value to min
 * if the value is smaller than the given.
 * 
 * @param value			Value
 * @param min			Min Value used as lower border
 * @return				Correct value not lower than min
 */
stock any:Math_Min(any:value, any:min)
{
	if (value < min) {
		value = min;
	}
	
	return value;
}

/**
 * Sets the given value to max
 * if the value is greater than the given.
 * 
 * @param value			Value
 * @param max			Max Value used as upper border
 * @return				Correct value not upper than max
 */
stock any:Math_Max(any:value, any:max)
{	
	if (value > max) {
		value = max;
	}
	
	return value;
}

/**
 * Makes sure a value is within a certain range.
 * 
 * @param value			Value
 * @param min			Min value used as lower border
 * @param max			Max value used as upper border
 * @return				Correct value not lower than min and not greater than max.
 */
stock any:Math_Clamp(any:value, any:min, any:max)
{
	value = Math_Min(value, min);
	value = Math_Max(value, max);

	return value;
}

/* 
 * Checks if the value is within the given bounds (min & max).
 * 
 * @param value		The value you want to check.
 * @param min		The lower border.
 * @param max		The upper border.
 * @return			True if the value is within bounds (bigger or equal min / smaller or equal max), false otherwise.
 */
stock bool:Math_IsInBounds(any:value, any:min, any:max)
{
	if (value < min || value > max) {
		return false;
	}
	
	return true;
}

/**
 * Returns a random Integer number in the specified range.
 * This is safe to use multiple times in a function.
 * The seed is set automatically for each plugin.
 * 
 * @param value			Value
 * @param min			Min value used as lower border
 * @param max			Max value used as upper border
 * @return				Random Integer number between min and max
 */
stock Math_GetRandomInt(min, max)
{
	new Float:_max = max + 0.9999999999;
	return RoundToFloor(Math_GetRandomFloat(float(min), _max));
}

/**
 * Returns a random Float number in the specified range.
 * This is safe to use multiple times in a function.
 * The seed is set automatically for each plugin.
 * 
 * @param value			Value
 * @param min			Min value used as lower border
 * @param max			Max value used as upper border
 * @return				Random Float number between min and max
 */
stock Float:Math_GetRandomFloat(Float:min, Float:max)
{
	new Float:rand = GetURandomFloat();
	rand = (rand * (max  - min)) + min;
	
	return rand;
}

/**
 * Gets the percentage of amount in all as Integer where
 * amount and all are numbers and amount usually
 * is a subset of all.
 * 
 * @param value			Integer value
 * @param all			Integer value
 * @return				An Integer value between 0 and 100 (inclusive).
 */
stock Math_GetPercentage(value, all) {
	return RoundToNearest((float(value) / float(all)) * 100.0);
}

/**
 * Gets the percentage of amount in all as Float where
 * amount and all are numbers and amount usually
 * is a subset of all.
 * 
 * @param value			Float value
 * @param all			Float value
 * @return				A Float value between 0.0 and 100.0 (inclusive).
 */
stock Float:Math_GetPercentageFloat(Float:value, Float:all) {
	return (value / all) * 100.0;
}
