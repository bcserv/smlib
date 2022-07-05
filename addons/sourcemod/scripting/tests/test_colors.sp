
// enforce semicolons after each code statement
#pragma semicolon 1
#pragma newdecls required

#include <sourcemod>
#include <sdktools>
#include <smlib>

#define PLUGIN_VERSION "0.1"



/*****************************************************************


		P L U G I N   I N F O


*****************************************************************/

public Plugin myinfo = {
	name = "smlib - color tests",
	author = "Berni",
	description = "",
	version = PLUGIN_VERSION,
	url = "http://www.sourcemodplugins.org"
}



/*****************************************************************


		G L O B A L   V A R S


*****************************************************************/

// ConVar Handles

// Misc



/*****************************************************************


		F O R W A R D   P U B L I C S


*****************************************************************/

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
    MarkNativeAsOptional("GetUserMessageType");
    return APLRes_Success;
}

public void OnPluginStart()
{
	Client_PrintToChatAll(false, "Loading plugin test-colors compiled on %s %s", __DATE__, __TIME__);
	RegAdminCmd("sm_testcolors", Command_TestColors, ADMFLAG_ROOT);
}



/****************************************************************


		C A L L B A C K   F U N C T I O N S


****************************************************************/

public Action Command_TestColors(int client, int args)
{
	char arguments[255];

	GetCmdArgString(arguments, sizeof(arguments));
	Client_PrintToChat(client, true, "%s", arguments);

	return Plugin_Handled;
}



/*****************************************************************


		P L U G I N   F U N C T I O N S


*****************************************************************/
