#if defined _smlib_strings_included
	#endinput
#endif
#define _smlib_strings_included

#include <smlib>

/**
 * Checks if the string is numeric.
 * This correctly handles + - . in the String.
 *
 * @param str				String to check.
 * @return					True if the String is numeric, false otherwise..
 */
stock bool:String_IsNumeric(const String:str[])
{	
	new x=0;
	new dotsFound=0;
	new numbersFound=0;

	if (str[x] == '+' || str[x] == '-') {
		x++;
	}

	while (str[x] != '\0') {

		if (IsCharNumeric(str[x])) {
			numbersFound++;
		}
		else if (str[x] == '.') {
			dotsFound++;
			
			if (dotsFound > 1) {
				return false;
			}
		}
		else {
			return false;
		}
		
		x++;
	}
	
	if (!numbersFound) {
		return false;
	}
	
	return true;
}

/**
 * Trims a string by removing the specified chars from beginning and ending.
 * Removes all ' ', '\t', '\r', '\n' characters by default.
 * The Output String can be the same as the Input String.
 *
 * @param str				Input String.
 * @param output			Output String (Can be the as the input).
 * @param size				Size of the output String.
 * @param chars				Characters to remove.
 * @noreturn
 */
stock String_Trim(const String:str[], String:output[], size, const String:chrs[]=" \t\r\n")
{	
	new x=0;
	while (str[x] != '\0' && FindCharInString(chrs, str[x]) != -1) {
		x++;
	}
	
	x = strcopy(output, size, str[x]);
	x--;

	while (x >= 0 && FindCharInString(chrs, output[x]) != -1) {
		x--;
	}
	
	output[++x] = '\0';
}

/**
 * Removes a list of strings from a string.
 *
 * @param buffer			Input/Ourput buffer.
 * @param removeList		A list of strings which should be removed from buffer.
 * @param size				Number of Strings in the List.
 * @param caseSensitive		If true, comparison is case sensitive. If false (default), comparison is case insensitive.
 * @noreturn
 */
stock String_RemoveList(String:buffer[], String:removeList[][], size, bool:caseSensitive=false)
{	
	for (new i=0; i < size; i++) {
		ReplaceString(buffer, 2147483647, removeList[i], "", caseSensitive);
	}
}

/**
 * Converts the whole String to lower case.
 * Only works with alphabetical characters (not ÖÄÜ) because Sourcemod suxx !
 * The Output String can be the same as the Input String.
 *
 * @param input				Input String.
 * @param output			Output String.
 * @param size				Max Size of the Output string
 * @noreturn
 */
stock String_ToLower(const String:input[], String:output[], size)
{
	size--;

	new x=0;
	while (input[x] != '\0' || x < size) {
		
		if (IsCharUpper(input[x])) {
			output[x] = CharToLower(input[x]);
		}
		
		x++;
	}
	
	output[x] = '\0';
}

/**
 * Converts the whole String to upper case.
 * Only works with alphabetical characters (not öäü) because Sourcemod suxx !
 * The Output String can be the same as the Input String.
 *
 * @param input				Input String.
 * @param output			Output String.
 * @param size				Max Size of the Output string
 * @noreturn
 */
stock String_ToUpper(const String:input[], String:output[])
{
	size--;

	new x=0;
	while (input[x] != '\0') {
		
		if (IsCharLower(input[x])) {
			output[x] = CharToUpper(input[x]);
		}
		
		x++;
	}
	
	output[x] = '\0';
}

/**
 * Strips all color control characters in a string.
 * The Output buffer can be the same as the input buffer.
 * Original code by Psychonic, thanks.
 *
 * @param input				Input String.
 * @param output			Output String.
 * @param size				Max Size of the Output string
 * @noreturn
 */
stock String_StripChatColors(const String:input[], String:output[], size)
{
	new x = 0;
	for (new i=0; input[i] != '\0'; i++) {
	
		if (x+1 == size) {
			break;
		}

		new char = input[i];
		
		if (char > 0x08) {
			output[x++] = char;
		}
	}
	
	output[x] = '\0';
}
