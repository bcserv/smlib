
// enforce semicolons after each code statement
#pragma semicolon 1

#include <sourcemod>
#include <sdktools>
#include <smlib>
#include <smlib/pluginmanager>

#define PLUGIN_VERSION "0.1"



/*****************************************************************


		P L U G I N   I N F O


*****************************************************************/

public Plugin:myinfo = {
	name = "",
	author = "Berni",
	description = "Plugin by Berni",
	version = PLUGIN_VERSION,
	url = "http://www.bcserv.eu"
}



/*****************************************************************


		G L O B A L   V A R S


*****************************************************************/

// ConVar Handles

// Misc



/*****************************************************************


		F O R W A R D   P U B L I C S


*****************************************************************/

public OnPluginStart()
{
	PluginManager_Initialize("smlib_example", "[SM]");
}



/****************************************************************


		C A L L B A C K   F U N C T I O N S


****************************************************************/





/*****************************************************************


		P L U G I N   F U N C T I O N S


*****************************************************************/
