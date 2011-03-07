#if defined _smlib_server_included
	#endinput
#endif
#define _smlib_server_included

#include <smlib>

/*
 * Gets the server's IP address.
 *
 * @param buffer			String buffer.
 * @param size			String buffer size.
 * @return				True on success, false otherwise.
 */
stock bool:Server_GetIP(String:buffer[], size)
{	
	new Handle:cvarHostip = FindConVar("hostip");

	if (cvarHostip == INVALID_HANDLE) {
		buffer[0] = '\0';
		return false;
	}

	new ip = GetConVarInt(cvarHostip);
	
	Format(buffer, size, "%d.%d.%d.%d",
		(ip >> 24)	& 0xFF,
		(ip >> 16)	& 0xFF,
		(ip >> 8 )	& 0xFF,
		ip        	& 0xFF
	);
	
	CloseHandle(cvarHostip);

	return true;
}

/*
 * Gets the server's Port.
 *
 * @noparam
 * @return			The server's port, 0 if there is no port.
 */
stock Server_GetPort()
{
	new Handle:cvarHostport = FindConVar("hostport");

	if (cvarHostport == INVALID_HANDLE) {
		return 0;
	}

	new port = GetConVarInt(cvarHostport);
	CloseHandle(cvarHostport);

	return port;
}

/*
 * Gets the server's hostname
 *
 * @param hostname		String buffer
 * @param size			String buffer size
 * @return				True on success, false otherwise.
 */
stock bool:Server_GetHostName(String:buffer[], size)
{	
	new Handle:cvarHostname = FindConVar("hostname");

	if (cvarHostname == INVALID_HANDLE) {
		buffer[0] = '\0';
		return false;
	}

	GetConVarString(cvarHostname, buffer, size);
	CloseHandle(cvarHostname);
	
	return true;
}
