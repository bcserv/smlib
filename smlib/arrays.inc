#include <smlib>

#if defined _smlib_array_included
  #endinput
#endif
#define _smlib_array_included

/**
 * Returns the index for the first occurance of the given value.
 * If the value cannot be found, -1 will be returned.
 *
 * @param array			Static Array.
 * @param size			Size of the Array.
 * @param value			Value to search for.
 * @return				Array index, or if the value couldn't be found.
 */
stock Array_FindValue(any:array[], size, any:value)
{	
	for (new i=0; i < size; i++) {

		if (array[i] == value) {
			return i;
		}
	}
	
	return -1;
}

/**
 * Searchs for the first occurance of a string in the array.
 * If the value cannot be located, -1 will be returned.
 *
 * @param array			Static Array.
 * @param size			Size of the Array.
 * @param value			String to search for.
 * @return				Array index, or if the value couldn't be found.
 */
stock Array_FindString(const String:array[][], size, const String:str[], bool:caseSensitive=true)
{	
	for (new i=0; i < size; i++) {

		if (StrEqual(array[i], str, caseSensitive)) {
			return i;
		}
	}
	
	return -1;
}

/**
 * Returns the index for the Lowest value in the array
 *
 * @param array			Static Array.
 * @param size			Size of the Array.
 * @return				Array index.
 */
stock Array_FindLowestValue(any:array[], size)
{
	new any:value = array[0];
	new any:tempValue;
	new x = 0;
	
	for (new i=0; i < size; i++) {
		
		tempValue = array[i];
		
		if (tempValue < value) {
			value = tempValue;
			x = i;
		}
		
	}
	
	return x;
}

/**
 * Returns the index for the Highest value in the array
 *
 * @param array			Static Array.
 * @param size			Size of the Array.
 * @return				Array index.
 */
stock Array_FindHighestValue(any:array[], size)
{
	new any:value = array[0];
	new any:tempValue;
	new x = 0;
	
	for (new i=1; i < size; i++) {
		
		tempValue = array[i];
		
		if (tempValue > value) {
			value = tempValue;
			x = i;
		}
		
	}
	
	return x;
}

/**
 * Fills an array with a given value in a 1 dimensional static array.
 * You can specify the amount of cells to be written.
 *
 * @param array			Static Array.
 * @param size			Size of the Array.
 * @param value			Fill value.
 * @param num			Max number of cells to write
 * @noreturn
 */
stock Array_Fill(any:array[], size, any:value, num=-1)
{
	for (new i=0; i<size; i++) {
		
		if (num != -1 && i >= num) {
			break;
		}

		array[i] = value;
	}
}
