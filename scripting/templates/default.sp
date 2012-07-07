/***************************************************************************************

	Copyright (C) 2012 BCServ (plugins@bcserv.eu)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
***************************************************************************************/

/***************************************************************************************


	C O M P I L E   O P T I O N S


***************************************************************************************/
// enforce semicolons after each code statement
#pragma semicolon 1

/***************************************************************************************


	P L U G I N   I N C L U D E S


***************************************************************************************/
#include <sourcemod>
#include <sdktools>
#include <smlib>
#include <smlib/pluginmanager>


/***************************************************************************************


	P L U G I N   I N F O


***************************************************************************************/
public Plugin:myinfo = {
	name 						= "",
	author 						= "BCServ",
	description 				= "",
	version 					= "1.0",
	url 						= "http://bcserv.eu/"
}

/***************************************************************************************


	P L U G I N   D E F I N E S


***************************************************************************************/


/***************************************************************************************


	G L O B A L   V A R S


***************************************************************************************/
// Server Variables


// Plugin Internal Variables


// Console Variables
// new Handle:g_cvarEnable 					= INVALID_HANDLE;


// Console Variables: Runtime Optimizers
// new g_iPlugin_Enable 					= 1;


// Timers


// Library Load Checks


// Game Variables


// Map Variables


// Client Variables


// M i s c


/***************************************************************************************


	F O R W A R D   P U B L I C S


***************************************************************************************/
public OnPluginStart()
{
	// Initialization for SMLib
	PluginManager_Initialize("", "[SM] ");
	
	// Translations
	// LoadTranslations("common.phrases");
	
	
	// Command Hooks (AddCommandListener) (If the command already exists, like the command kill, then hook it!)
	
	
	// Register New Commands (PluginManager_RegConsoleCmd) (If the command doesn't exist, hook it here)
	
	
	// Register Admin Commands (PluginManager_RegAdminCmd)
	
	
	// Cvars: Create a global handle variable.
	// g_cvarEnable = PluginManager_CreateConVar("enable", "1", "Enables or disables this plugin");
	
	
	// Hook ConVar Change
	// HookConVarChange(g_cvarEnable, ConVarChange_Enable);
	
	
	// Event Hooks
	
	
	// Library
	
	
	/* Features
	if(CanTestFeatures()){
		
	}
	*/
	
	// Create ADT Arrays
	
	
	// Timers
	
	
}

public OnMapStart()
{
	// hax against valvefail (thx psychonic for fix)
	if (GuessSDKVersion() == SOURCE_SDK_EPISODE2VALVE) {
		SetConVarString(Plugin_VersionCvar, Plugin_Version);
	}
}

public OnConfigsExecuted()
{
	// Set your ConVar runtime optimizers here
	// g_iPlugin_Enable = GetConVarInt(g_cvarEnable);
	
	// Mind: this is only here for late load, since on map change or server start, there isn't any client.
	// Remove it if you don't need it.
	Client_InitializeAll();
}

public OnClientPutInServer(client)
{
	Client_Initialize(client);
}

public OnClientPostAdminCheck(client)
{
	Client_Initialize(client);
}

/**************************************************************************************


	C A L L B A C K   F U N C T I O N S


**************************************************************************************/
/**************************************************************************************

	C O N  V A R  C H A N G E

**************************************************************************************/
/* Example Callback Con Var Change
public ConVarChange_Enable(Handle:cvar, const String:oldVal[], const String:newVal[])
{
	g_iPlugin_Enable = StringToInt(newVal);
}
*/


/**************************************************************************************

	C O M M A N D S

**************************************************************************************/
/* Example Command Callback
public Action:Command_(client, args)
{
	
	return Plugin_Handled;
}
*/


/**************************************************************************************

	E V E N T S

**************************************************************************************/
/* Example Callback Event
public Action:Event_Example(Handle:event, const String:name[], bool:dontBroadcast)
{

}
*/


/***************************************************************************************


	P L U G I N   F U N C T I O N S


***************************************************************************************/



/***************************************************************************************

	S T O C K

***************************************************************************************/
stock Client_InitializeAll()
{
	LOOP_CLIENTS (client, CLIENTFILTER_ALL) {
		
		Client_Initialize(client);
	}
}

stock Client_Initialize(client)
{
	// Variables
	Client_InitializeVariables(client);
	
	
	// Functions
	
	
	/* Functions where the player needs to be in game 
	if(!IsClientInGame(client)){
		return;
	}
	*/
}

stock Client_InitializeVariables(client)
{
	// Client Variables
	
}


