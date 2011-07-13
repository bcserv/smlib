#if defined _smlib_files_included
	#endinput
#endif
#define _smlib_files_included

#include <sourcemod>
#include <sdktools_stringtables>
#include <smlib/arrays>

/**
 * Gets the Base name of a path.
 * Examples:
 * blub.txt -> "blub.txt"
 * /sourcemod/extensions/example.ext.so -> "example.ext.so"
 *
 * @param path			File path
 * @param buffer		String buffer array
 * @param size			Size of string buffer
 * @noreturn
 */
stock bool:File_GetBaseName(const String:path[], String:buffer[], size)
{	
	if (path[0] == '\0') {
		buffer[0] = '\0';
		return;
	}
	
	new pos_start = FindCharInString(path, '/', true);
	
	if (pos_start == -1) {
		pos_start = FindCharInString(path, '\\', true);
	}
	
	pos_start++;
	
	strcopy(buffer, size, path[pos_start]);
}

/**
 * Gets the Directory of a path (without the file name).
 * Does not work with "." as the path.
 * Examples:
 * blub.txt -> "blub.txt"
 * /sourcemod/extensions/example.ext.so -> "example.ext.so"
 *
 * @param path			File path
 * @param buffer		String buffer array
 * @param size			Size of string buffer
 * @noreturn
 */
stock bool:File_GetDirName(const String:path[], String:buffer[], size)
{	
	if (path[0] == '\0') {
		buffer[0] = '\0';
		return;
	}
	
	new pos_start = FindCharInString(path, '/', true);
	
	if (pos_start == -1) {
		pos_start = FindCharInString(path, '\\', true);
		
		if (pos_start == -1) {
			buffer[0] = '\0';
			return;
		}
	}
	
	strcopy(buffer, size, path);
	buffer[pos_start] = '\0';
}

/**
 * Gets the File name of a path.
 * blub.txt -> "blub"
 * /sourcemod/extensions/example.ext.so -> "example.ext"
 *
 * @param path			File path
 * @param buffer		String buffer array
 * @param size			Size of string buffer
 * @noreturn
 */
stock bool:File_GetFileName(const String:path[], String:buffer[], size)
{	
	if (path[0] == '\0') {
		buffer[0] = '\0';
		return;
	}
	
	File_GetBaseName(path, buffer, size);
	
	new pos_ext = FindCharInString(buffer, '.', true);

	if (pos_ext != -1) {
		buffer[pos_ext] = '\0';
	}
}

/**
 * Gets the Extension of a file.
 * Examples:
 * blub.inc.txt -> "txt"
 * /sourcemod/extensions/example.ext.so -> "so"
 *
 * @param path			Path String
 * @param buffer		String buffer array
 * @param size			Max length of string buffer
 * @noreturn
 */
stock File_GetExtension(const String:path[], String:buffer[], size)
{
	new extpos = FindCharInString(path, '.', true);
	
	if (extpos == -1) {
		buffer[0] = '\0';
		return;
	}

	strcopy(buffer, size, path[++extpos]);
}

/**
 * Adds a path to the downloadables network string table.
 * This can be a file or directory and also works recursed.
 * You can optionally specify file extensions that should be ignored.
 * Bz2 and ztmp are automatically ignored.
 * It only adds files that actually exist.
 * You can also specify a wildcard * after the ., very useful for models.
 * This forces a client to download the file if they do not already have it.
 *
 * @param path			Path String
 * @param recursive		Whether to do recursion or not.
 * @param ignoreExts	Optional: 2 dimensional String array.You can define it like this: new String:ignore[][] = { ".ext1", ".ext2" };
 * @param size			This should be set to the number of file extensions in the ignoreExts array (sizeof(ignore) for the example above)
 * @noreturn
 */

// Damn you SourcePawn :( I didn't want to
new String:_smlib_empty_twodimstring_array[][] = { { '\0' } };
stock File_AddToDownloadsTable(const String:path[], bool:recursive=true, const String:ignoreExts[][]=_smlib_empty_twodimstring_array, size=0)
{
	if (path[0] == '\0') {
		return;
	}

	if (FileExists(path)) {
		
		new String:fileExtension[4];
		File_GetExtension(path, fileExtension, sizeof(fileExtension));
		
		if (StrEqual(fileExtension, "bz2", false) || StrEqual(fileExtension, "ztmp", false)) {
			return;
		}
		
		if (Array_FindString(ignoreExts, size, fileExtension) != -1) {
			return;
		}

		decl String:path_new[PLATFORM_MAX_PATH];
		strcopy(path_new, sizeof(path_new), path);
		ReplaceString(path_new, sizeof(path_new), "//", "/");

		AddFileToDownloadsTable(path_new);
	}
	else if (recursive && DirExists(path)) {

		decl String:dirEntry[PLATFORM_MAX_PATH];
		new Handle:__dir = OpenDirectory(path);

		while (ReadDirEntry(__dir, dirEntry, sizeof(dirEntry))) {

			if (StrEqual(dirEntry, ".") || StrEqual(dirEntry, "..")) {
				continue;
			}
			
			Format(dirEntry, sizeof(dirEntry), "%s/%s", path, dirEntry);
			File_AddToDownloadsTable(dirEntry, recursive, ignoreExts, size);
		}
		
		CloseHandle(__dir);
	}
	else if (FindCharInString(path, '*', true)) {
		
		new String:fileExtension[4];
		File_GetExtension(path, fileExtension, sizeof(fileExtension));

		if (StrEqual(fileExtension, "*")) {

			decl
				String:dirName[PLATFORM_MAX_PATH],
				String:fileName[PLATFORM_MAX_PATH],
				String:dirEntry[PLATFORM_MAX_PATH];

			File_GetDirName(path, dirName, sizeof(dirName));
			File_GetFileName(path, fileName, sizeof(fileName));
			StrCat(fileName, sizeof(fileName), ".");

			new Handle:__dir = OpenDirectory(dirName);
			while (ReadDirEntry(__dir, dirEntry, sizeof(dirEntry))) {

				if (StrEqual(dirEntry, ".") || StrEqual(dirEntry, "..")) {
					continue;
				}

				if (strncmp(dirEntry, fileName, strlen(fileName)) == 0) {
					Format(dirEntry, sizeof(dirEntry), "%s/%s", dirName, dirEntry);
					File_AddToDownloadsTable(dirEntry, recursive, ignoreExts, size);
				}
			}

			CloseHandle(__dir);
		}
	}

	return;
}


/*
 * Adds all files/paths in the given text file to the download table.
 * Recursive mode enabled, see File_AddToDownloadsTable()
 * Comments are allowed ! Supported comment types are ; // #
 *
 * @param path			Path to the .txt file.
 * @noreturn
 */
stock File_ReadDownloadList(const String:path[])
{
	new Handle:file = OpenFile(path, "r");
	
	if (file  == INVALID_HANDLE) {
		return;
	}

	new String:buffer[PLATFORM_MAX_PATH];
	while (!IsEndOfFile(file)) {
		ReadFileLine(file, buffer, sizeof(buffer));
		
		new pos;
		pos = StrContains(buffer, "//");
		if (pos != -1) {
			buffer[pos] = '\0';
		}
		
		pos = StrContains(buffer, "#");
		if (pos != -1) {
			buffer[pos] = '\0';
		}

		pos = StrContains(buffer, ";");
		if (pos != -1) {
			buffer[pos] = '\0';
		}
		
		TrimString(buffer);
		
		if (buffer[0] == '\0') {
			continue;
		}

		File_AddToDownloadsTable(buffer);
	}

	CloseHandle(file);
}

/*
 * Attempts to load a translation file and unloads the plugin if the file doesn't exist.
 *
 * @param file		Filename of the translations file (eg. <pluginname>.phrases).
 * @noreturn
 */
stock File_LoadTranslations(const String:file[])
{
	decl String:path[PLATFORM_MAX_PATH];
	
	Format(path,sizeof(path),"translations/%s",file);
	
	BuildPath(Path_SM, path, sizeof(path), path);
	
	if (FileExists(path)) {
		LoadTranslations(file);
		return;
	}
	
	Format(path,sizeof(path),"%s.txt",path);
	
	if (FileExists(path)) {
		LoadTranslations(file);
		return;
	}
	
	SetFailState("Unable to locate translation file (%s).",path);
}

/*
 * Reads the contents of a given file into a string buffer in binaey mode.
 *
 * @param path		Path to the file
 * @param buffer	String buffer
 * @param size		If -1, reads until a null terminator is encountered in the file.  Otherwise, read_count bytes are read into the buffer provided.  In this case the buffer is not explicitly null terminated, and the buffer will contain any null terminators read from the file.
 * @return			Number of characters written to the buffer, or -1 if an error was encountered.
 */
stock File_ToString(const String:path[], String:buffer[], size)
{
	new Handle:file = OpenFile(path, "rb");

	if (file == INVALID_HANDLE) {
		return -1;
	}

	new num_bytes_written = ReadFileString(file, buffer, size);
	CloseHandle(file);

	return num_bytes_written;
}

/*
 * Writes a string into a file in binary mode.
 *
 * @param file		Path to the file
 * @param str		String to write
 * @return			True on success, false otherwise
 */
stock bool:File_StringToFile(const String:path[], String:str[])
{
	new Handle:file = OpenFile(path, "wb");

	if (file == INVALID_HANDLE) {
		return false;
	}

	new bool:success = WriteFileString(file, str, false);
	CloseHandle(file);

	return success;
}

/*
 * Copies file source to destination
 *
 * @param source		Input file
 * @param destination	Output file
 */
stock bool:File_Copy(const String:source[], const String:destination[])
{
	new Handle:file_source = OpenFile(source, "rb");

	if (file_source == INVALID_HANDLE) {
		return false;
	}

	new Handle:file_destination = OpenFile(destination, "wb");

	if (file_destination == INVALID_HANDLE) {
		CloseHandle(file_source);
		return false;
	}

	new buffer[32];
	new cache;

	while((cache = ReadFile(file_source, buffer, 32, 1)) != -1) {
		WriteFile(file_destination, buffer, cache, 1);
	}

	CloseHandle(file_source);
	CloseHandle(file_destination);

	return true;
}
