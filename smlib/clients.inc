#if defined _smlib_client_included
	#endinput
#endif
#define _smlib_client_included

#include <smlib>
#include <_smlib/general>
#include <_smlib/teams>
#include <_smlib/weapons>

// Hud Element hiding flags (possibly outdated)
#define	HIDEHUD_WEAPONSELECTION		( 1<<0 )	// Hide ammo count & weapon selection
#define	HIDEHUD_FLASHLIGHT			( 1<<1 )
#define	HIDEHUD_ALL					( 1<<2 )
#define HIDEHUD_HEALTH				( 1<<3 )	// Hide health & armor / suit battery
#define HIDEHUD_PLAYERDEAD			( 1<<4 )	// Hide when local player's dead
#define HIDEHUD_NEEDSUIT			( 1<<5 )	// Hide when the local player doesn't have the HEV suit
#define HIDEHUD_MISCSTATUS			( 1<<6 )	// Hide miscellaneous status elements (trains, pickup history, death notices, etc)
#define HIDEHUD_CHAT				( 1<<7 )	// Hide all communication elements (saytext, voice icon, etc)
#define	HIDEHUD_CROSSHAIR			( 1<<8 )	// Hide crosshairs
#define	HIDEHUD_VEHICLE_CROSSHAIR	( 1<<9 )	// Hide vehicle crosshair
#define HIDEHUD_INVEHICLE			( 1<<10 )
#define HIDEHUD_BONUS_PROGRESS		( 1<<11 )	// Hide bonus progress display (for bonus map challenges)

/**
* Sets the Hud flags of a client
*
* @param client		Client index.
* @param flags		Flag to set, use one of the HIDEHUD_ hiding constants
* @noreturn
*/
stock Client_SetHud(client, flags)
{
	SetEntProp(client, Prop_Send, "m_iHideHUD", flags);
}

/**
* Checks if the specified index is a player and connected.
*
* @param entity				An entity index.
* @param checkConnected		Set to false to skip the IsClientConnected check
* @return					Returns true if the specified entity index is a player connected, false otherwise.
*/
stock bool:Client_IsValid(client, bool:checkConnected=true)
{
	if (client > 4096) {
		client = EntRefToEntIndex(client);
	}

	if (client < 1 || client > MaxClients) {
		return false;
	}

	if (checkConnected && !IsClientConnected(client)) {
		return false;
	}
	
	return true;
}

/**
* Checks if the specified index is a player and ingame.
*
* @param entity		An entity index.
* @return			Returns true if the specified index is a player and ingame, false otherwise.
*/
stock bool:Client_IsIngame(client)
{
	if (!Client_IsValid(client, false)) {
		return false;
	}

	if (!IsClientInGame(client)) {
		return false;
	}

	return true;
}

/**
* Checks if the specified index is a player, ingame and authorized.
*
* @param entity		An entity index.
* @return			Returns true if the specified index is a player, ingame and authed, false otherwise.
*/
stock bool:Client_IsIngameAuthorized(client)
{
	if (!Client_IsIngame(client, false)) {
		return false;
	}

	if (!IsClientAuthorized(client)) {
		return false;
	}

	return true;
}

#define MAX_STEAMAUTH_LENGTH 21

/**
* Finds a player by his SteamID
*
* @param auth			SteamID to search for
* @return				Client Index or -1
*/
stock Client_FindBySteamId(const String:auth[])
{
	new String:clientAuth[MAX_STEAMAUTH_LENGTH];
	for (new client=1; client <= MaxClients; client++) {
		if (!IsClientAuthorized(client)) {
			continue;
		}
		
		GetClientAuthString(client, clientAuth, sizeof(clientAuth));

		if (StrEqual(auth, clientAuth)) {
			return client;
		}
	}
	
	return -1;
}

/**
* Finds a player by his name.
* Only returns the first matching player.
*
* @param name			Name to search for.
* @param partOfName		Whether to search for the part of a name or compare the full name.
* @param caseSensitive	If true, comparison is case sensitive. If false (default), comparison is case insensitive.
* @return				Client Index or -1
*/
stock Client_FindByName(const String:name[], bool:partOfName=true, bool:caseSensitive=false)
{
	new String:clientName[MAX_STEAMAUTH_LENGTH];
	for (new client=1; client <= MaxClients; client++) {
		if (!IsClientAuthorized(client)) {
			continue;
		}
		
		GetClientName(client, clientName, sizeof(clientName));

		if (partOfName) {
			if (StrContains(clientName, name, caseSensitive) != -1) {
				return client;
			}
		}
		else if (StrEqual(name, clientName, caseSensitive)) {
			return client;
		}
	}
	
	return -1;
}

// Spectator Movement modes
enum Obs_Mode
{
	OBS_MODE_NONE = 0,	// not in spectator mode
	OBS_MODE_DEATHCAM,	// special mode for death cam animation
	OBS_MODE_FREEZECAM,	// zooms to a target, and freeze-frames on them
	OBS_MODE_FIXED,		// view from a fixed camera position
	OBS_MODE_IN_EYE,	// follow a player in first person view
	OBS_MODE_CHASE,		// follow a player in third person view
	OBS_MODE_ROAMING,	// free roaming

	NUM_OBSERVER_MODES
};

// Force Camera Restrictions with mp_forcecamera
enum Obs_Allow
{
	OBS_ALLOW_ALL = 0,	// allow all modes, all targets
	OBS_ALLOW_TEAM,		// allow only own team & first person, no PIP
	OBS_ALLOW_NONE,		// don't allow any spectating after death (fixed & fade to black)

	OBS_ALLOW_NUM_MODES,
};

/**
 * Gets the client's  observer mode (Obs_Mode).
 * 
 * @param client		Client Index.
 * @return				The current observer mode (ObsMode).
 */
stock Obs_Mode:Client_GetObserverMode(client)
{
	return Obs_Mode:GetEntProp(client, Prop_Send, "m_iObserverMode");
}


/**
 * Sets the client's observer mode.
 * Use a value of the Obs_Mode enum.
 * This is a rewrite of CBasePlayer::SetObserverMode().
 * 
 * @param client		Client Index.
 * @param mode			New Observer mode value (Obs_Mode).
 * @noreturn
 */
stock bool:Client_SetObserverMode(client, Obs_Mode:mode)
{
	if (mode < OBS_MODE_NONE || mode >= NUM_OBSERVER_MODES) {
		return false;
	}
	
	// check mp_forcecamera settings for dead players
	if (mode > OBS_MODE_FIXED && GetClientTeam(client) > TEAM_SPECTATOR)
	{
		new Handle:mp_forcecamera = FindConVar("mp_forcecamera");

		if (mp_forcecamera != INVALID_HANDLE) {
			switch (GetConVarInt(mp_forcecamera))
			{
				case OBS_ALLOW_TEAM: {
					mode = OBS_MODE_IN_EYE;
				}
				case OBS_ALLOW_NONE: {
					mode = OBS_MODE_FIXED; // don't allow anything
				}
			}
		}
	}

	new Obs_Mode:observerMode = Client_GetObserverMode(client);
	if (observerMode > OBS_MODE_DEATHCAM) {
		// remember mode if we were really spectating before
		Client_SetObserverLastMode(client, observerMode);
	}

	SetEntProp(client, Prop_Send, "m_iObserverMode", _:mode);

	switch (mode) {
		case OBS_MODE_NONE, OBS_MODE_FIXED, OBS_MODE_DEATHCAM: {
			Client_SetFOV(client, 0);	// Reset FOV
			SetEntityMoveType(client, MOVETYPE_NONE);
		}
		case OBS_MODE_CHASE, OBS_MODE_IN_EYE: {
			// udpate FOV and viewmodels
			Client_SetViewOffset(client, NULL_VECTOR);
			SetEntityMoveType(client, MOVETYPE_OBSERVER);
		}
		case OBS_MODE_ROAMING: {
			Client_SetFOV(client, 0);	// Reset FOV
			Client_SetViewOffset(client, NULL_VECTOR);
			SetEntityMoveType(client, MOVETYPE_OBSERVER);
		}
	}

	return true;
}

/**
 * Gets the client's last oberserver mode
 * 
 * @param client		Client Index.
 * @return				Last Observer mode
 */
stock Obs_mode:Client_GetObserverLastMode(client)
{
	return Obs_mode:GetEntProp(client, Prop_Data, "m_iObserverLastMode");
}

/**
 * Sets the client's last oberserver mode
 * 
 * @param client		Client Index.
 * @param mode			Last Observer mode
 * @noreturn
 */
stock Client_SetObserverLastMode(client, Obs_Mode:mode)
{
	SetEntProp(client, Prop_Data, "m_iObserverLastMode", _:mode);
}

/**
 * Gets the client's view offset.
 * This is the position relative to the client itself.
 * 
 * @param client		Client Index.
 * @param vec			Vector Buffer.
 * @noreturn
 */
stock Client_GetViewOffset(client, Float:vec[3])
{
	GetEntPropVector(client, Prop_Data, "m_vecViewOffset", vec);
}

/**
 * Sets the client's view offset.
 * This is the position relative to the client itself.
 * 
 * @param client		Client Index.
 * @param vec			Vector buffer.
 * @noreturn
 */
stock Client_SetViewOffset(client, Float:vec[3])
{
	SetEntPropVector(client, Prop_Data, "m_vecViewOffset", vec);
}

/**
 * Gets the client's current observer target entity.
 * 
 * @param client		Client Index.
 * @return				Observed Entity Index.
 */
stock Client_GetObserverTarget(client)
{
	return GetEntPropEnt(client, Prop_Send, "m_hObserverTarget");
}

/**
 * Sets the client's current observer target entity.
 * 
 * @param client		Client Index.
 * @param entity		Observed Entity Index.
 * @param resetFOV		If to reset the client's field of view.
 * @noreturn
 */
stock Client_SetObserverTarget(client, entity, bool:resetFOV=true)
{
	SetEntPropEnt(client, Prop_Send, "m_hObserverTarget", entity);
	
	if (resetFOV) {
		Client_SetFOV(client, 0);
	}
}

/**
 * Gets the client's Field Of View.
 * 
 * @param client		Client Index.
 * @return				Field Of View
 */
stock Client_GetFOV(client)
{
	return GetEntProp(client, Prop_Send, "m_iFOV");
}

/**
 * Sets the client's Field Of View.
 * 
 * @param client		Client Index.
 * @param value			Field Of View
 * @noreturn
 */
stock Client_SetFOV(client, value)
{
	SetEntProp(client, Prop_Send, "m_iFOV", value);
}

/**
 * Checks if the client's View Model is drawn for the client.
 * 
 * @param client		Client Index.
 * @return				True if the viewmodel is drawn, false otherwise.
 */
stock bool:Client_DrawViewModel(client)
{
	return bool:GetEntProp(client, Prop_Send, "m_bDrawViewmodel");
}

/**
 * Sets if to draw the client's view model for the client.
 * 
 * @param client		Client Index.
 * @param drawViewModel	Set to true if to draw, false otherwise.
 * @noreturn
 */
stock Client_SetDrawViewModel(client, bool:drawViewModel)
{
	SetEntProp(client, Prop_Send, "m_bDrawViewmodel", drawViewModel);
}

/**
 * Puts the specified client into thirdperson or back to firstperson when false
 * This doesn't work correctly in all games, it works in CS:S and DOD:S and some other games.
 * Todo: Enhance this
 *
 * @param client 		Client Index.
 * @param enable			If set to true, the client will be put into thirdperson mode,
 * 						if false the client will be put in firstperson mode.
 * @noreturn
 */
stock Client_SetThirdPersonMode(client, enable=true)
{
	if (enable) {
		Client_SetObserverTarget(client, 0);
		Client_SetObserverMode(client, OBS_MODE_DEATHCAM);
		Client_SetDrawViewModel(client, false);
		Client_SetFOV(client, 120);
	}
	else {
		Client_SetObserverTarget(client, -1);
		Client_SetObserverMode(client, OBS_MODE_NONE);
		Client_SetDrawViewModel(client, true);
		Client_SetFOV(client, 90);
	}
}

/**
* Checks if the client is in thirdperson mode
*
* @param client		client index
* @return			true if the client is currently in thirdperson mode, false otherwise
*/
stock Client_IsInThirdPersonMode(client)
{
	return GetEntProp(client, Prop_Data, "m_iObserverMode");
}

#define FFADE_IN			0x0001		// Just here so we don't pass 0 into the function
#define FFADE_OUT			0x0002		// Fade out (not in)
#define FFADE_MODULATE		0x0004		// Modulate (don't blend)
#define FFADE_STAYOUT		0x0008		// ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_PURGE			0x0010		// Purges all other fades, replacing them with this one

/**
* Fades a client's screen to a specified color
*
* @param client			player for which to fade the screen
* @param duration		duration in seconds the effect stays
* @param mode			fade mode, see FFADE_ defines
* @param holdtime		holdtime in seconds
* @param r				red amount
* @param g				green amount
* @param b				blue amount
* @param a				transparency
* @return				True on success, false otherwise
*/
stock bool:Client_ScreenFade(client, duration, mode, holdtime=-1, r=0, g=0, b=0, a=255, bool:reliable=true)
{
	new Handle:msg = StartMessageOne("Fade", client, (reliable?USERMSG_RELIABLE:0));
	
	if (fade == INVALID_MESSAGE_ID) {
		return false;
	}
	
	BfWriteShort(msg, duration);	// Fade duration
	BfWriteShort(msg, holdtime);	// Fade hold time
	BfWriteShort(msg, mode);		// What to do
	BfWriteByte(msg, r);			// Color R
	BfWriteByte(msg, g);			// Color G
	BfWriteByte(msg, b);			// Color B
	BfWriteByte(msg, a);			// Color Alpha
	EndMessage();
	
	return true;
}

/**
* This function retrieves an array that holds all clones of a client by IP check.
*
* @param client			Client index.
* @param closelist		An array that holds all clones of a client.
* @return				Returns how many clones a client has.
*/
stock Client_GetClones(client, clonelist[])
{
	new x=0;
	decl String:ip_client[16], String:ip_player[16];
	
	GetClientIP(client, ip_client, sizeof(client));
	
	for (new player=1; player <= MaxClients; player++) {
		
		if (IsClientInGame(player)) {
			GetClientIP(player, ip_player, sizeof(ip_player));
			
			if (StrEqual(ip_client, ip_player, false)) {
				cloneList[x++] = player;
			}
		}
	}

	return x;
}

/*
* This function returns true if the client is at a ladder..
*
* @param client			Client index.
* @return				Returns true if the client is on a ladder other wise false.
*/
stock bool:Client_IsOnLadder(client)
{	
	new MoveType:movetype = GetEntityMoveType(client);
	
	if (movetype == MOVETYPE_LADDER) {
		return true;
	}
	else{	
		return false;
	}
}

enum Water_level
{
	WATER_LEVEL_NOT_IN_WATER = 0,
	WATER_LEVEL_FEET_IN_WATER,
	WATER_LEVEL_WAIST_IN_WATER,
	WATER_LEVEL_HEAD_IN_WATER
};

/*
* This function returns how deep a client is in water.
*
* @param client			Client index.
* @return				Returns 0 if not in water. 1 if feets are in water. 2 if waist is in water. 3 if head is in water.
*/
stock Water_Level:Client_GetWaterLevel(client)
{	
	return Water_Level:GetEntProp(client, Prop_Send, "m_nWaterLevel");
}

/*
* Returns how much suit sprint power a client has left in percent.
*
* @param client			Client index.
* @return				returns the actual power left in percent.
*/
stock Float:Client_GetSuitSprintPower(client)
{
	return GetEntPropFloat(client, Prop_Send, "m_flSuitPower");
}

/*
* Sets a client suit sprint power in percent.
*
* @param client			Client index.
* @param power			power (0.0 to 100.0)
* @noreturn
*/
stock Client_SetSuitSprintPower(client, Float:power)
{	
	SetEntPropFloat(client, Prop_Send, "m_flSuitPower", power);
}

/*
* Returns the client count put in the server. 
*
* @param inGameOnly		If false connecting players are also counted.
* @param countBots		If true bots will be counted too.
* @return				Client count in the server.
*/
stock Client_GetCount(bool:countInGameOnly=true, bool:countFakeClients=false)
{
	new numClients = 0;
	
	for (new client=1; client <= MaxClients; client++) {
		
		if (!IsClientConnected(client)) {
			continue;
		}
		
		if (countInGameOnly && !IsClientInGame(client)) {
			continue;
		}
		
		if (!countFakeClients && IsFakeClient(client)) {
			continue;
		}
		
		numClients++;
	}

	return numClients;
}

/*
* Returns the ping of a client like it is displayed in the scoreboard.
* The weird calculation formula is taken from Valve's SDK
* hl2sdk\game\server\util.cpp: UTIL_GetPlayerConnectionInfo()
* The Scoreboard uses the goldSource corrected Ping, the net_graph doesn't
* For Fake Clients 0 is returned.
*
* @param inGameOnly		Wether players not ingame yet are also counted
* @param countBots		If true bots will be counted too.
* @return				Client's ping or 0 for fake clients
*/
stock Client_GetFakePing(client, bool:goldSource=true)
{
	if (IsFakeClient(client)) {
		return 0;
	}

	new ping;
	new Float:latency = GetClientLatency(client, NetFlow_Outgoing); // in seconds
		
	// that should be the correct latency, we assume that cmdrate is higher 
	// then updaterate, what is the case for default settings
	decl String:cl_cmdrate[4];
	GetClientInfo(client, "cl_cmdrate", cl_cmdrate, sizeof(cl_cmdrate));

	new Float:tickRate = GetTickInterval();
	latency -= (0.5 / StringToInt(cl_cmdrate)) + TICKS_TO_TIME(1.0); // correct latency

	if (goldSource) {
		// in GoldSrc we had a different, not fixed tickrate. so we have to adjust
		// Source pings by half a tick to match the old GoldSrc pings.
		latency -= tickRate * 0.5;
	}

	ping = RoundFloat(latency * 1000.0); // as msecs
	ping = Math_Clamp(ping, 5, 1000); // set bounds, dont show pings under 5 msecs
	
	return ping;
}

/**
 * Searches for the closest client in relation to the given client.
 *
 * @param client		Client index
 * @return				The closest client or -1
 */
stock Client_GetClosestToClient(client)
{
	return Edict_GetClosestToEdict(client, true);
}

/**
 * Gets the name of the last place (if set by the game)
 *
 * @param entity			Entity index.
 * @param buffer			String buffer
 * @param size				Size of the String buffer
 * @noreturn
 */
stock Client_GetLastPlaceName(client, String:buffer[], size)
{
	SetEntPropString(client, Prop_Send, "m_szLastPlaceName", buffer);
}

/**
 * Returns the client's Score. 
 *
 * @param client			Client's index.
 * @return					Score.
 */
stock Client_GetScore(client)
{
	return GetClientFrags(client);
}

/**
 * Sets the client's Score.
 *
 * @param client			Client's index.
 * @param value				Score.
 * @noreturn
 */
stock Client_SetScore(client, value)
{
	SetEntProp(client, Prop_Data, "m_iFrags", value);
}

/**
 * Returns the client's Death count
 *
 * @param client			Client's index.
 * @return					Death count
 */
stock Client_GetDeaths(client)
{
	return GetEntProp(client, Prop_Data, "m_iDeaths");
}

/**
 * Sets the client's Death count.
 *
 * @param client			Client's index.
 * @param value				Death count
 * @noreturn
 */
stock Client_SetDeaths(client, value)
{
	SetEntProp(client, Prop_Data, "m_iDeaths", value);
}

/**
 * Returns the client's Armor
 *
 * @param client			Client's index.
 * @return					Armor value
 */
stock Client_GetArmor(client)
{
	return GetEntProp(client, Prop_Data, "m_ArmorValue");
}

/**
 * Sets the client's Armor.
 *
 * @param client			Client's index.
 * @param value				Armor value
 * @noreturn
 */
stock Client_SetArmor(client, value)
{
	SetEntProp(client, Prop_Data, "m_ArmorValue", value);
}

/**
 * Returns the client's Suitpower
 *
 * @param client			Client's index.
 * @return					Suitpower
 */
stock Client_GetSuitPower(client)
{
	return GetEntPropFloat(client, Prop_Data, "m_flSuitPower");
}

/**
 * Sets the client's Suitpower
 *
 * @param client			Client's index.
 * @param value				Suitpower
 * @noreturn
 */
stock Client_SetSuitPower(client, value)
{
	SetEntPropFloat(client, Prop_Data, "m_flSuitPower", value);
}

// suit usage bits
#define bits_SUIT_DEVICE_SPRINT		0x00000001
#define bits_SUIT_DEVICE_FLASHLIGHT	0x00000002
#define bits_SUIT_DEVICE_BREATHER	0x00000004
#define MAX_SUIT_DEVICES			3

/**
 * Returns the client's active devices (Max MAX_SUIT_DEVICES)
 * The return is a bitwise value with bits_SUIT_DEVICE_SPRINT,
 * bits_SUIT_DEVICE_FLASHLIGHT and/or bits_SUIT_DEVICE_BREATHER set.
 *
 * @param client			Client's index.
 * @return					The active devices (bitwise value)
 */
stock Client_GetActiveDevices(client)
{
	return GetEntProp(client, Prop_Send, "m_bitsActiveDevices");
}

/**
 * Returns the time when the client is allowed to spray
 * a decal again.
 *
 * @param client			Client's index.
 * @return					Next decal time
 */
stock Float:Client_GetNextDecalTime(client)
{
	return GetEntPropFloat(client, Prop_Data, "m_flNextDecalTime");
}

/**
 * Returns whether the client is allowed to spray a decal or not.
 *
 * @param client			Client's index.
 * @return					True if he is allowed to spray a decal, false otherwise
 */
stock bool:Client_CanSprayDecal(client)
{
	return Client_GetNextDecalTime <= GetGameTime();
}

/**
 * Returns the vehicle the client is in, if the client
 * isn't in a vehicle, -1 is returned.
 *
 * @param client			Client's index.
 * @return					Vehicle index, -1 if the client isn't in a vehicle.
 */
stock Client_GetVehicle(client)
{
	new m_hVehicle = GetEntPropEnt(client, Prop_Send, "m_hVehicle");

	return m_hVehicle;
}

/**
 * Returns whether the client is in a vehicle or not.
 *
 * @param client			Client's index.
 * @return					True if he is in a vehicle, false otherwise
 */
stock bool:Client_IsInVehicle(client)
{
	return !(Client_GetVehicle(client) == -1);
}

/**
 * Removes all decals for a client
 *
 * @param client			Client's index.
 * @noreturn
 */
stock Client_RemoveAllDecals(client)
{
	ClientCommand(client, "r_cleardecals");
}

/**
 * Let's the client exit the vehicle
 *
 * @param vehicle			Client index.
 * @return					True on success, false otherwise.
 */
stock bool:Client_ExitVehicle(client)
{
	new vehicle = Client_GetVehicle(client);

	if (vehicle == -1) {
		return false;
	}
	
	return AcceptEntityInput(vehicle, "ExitVehicle");
}

/**
 * Plays a soundfile as if the player is using voicecomm for a single client.
 * The voiceindicator is shown on the right, as if the players is talking.
 * Thanks to Peace-Maker for the function.
 *
 * @param client		For whom to play the sound.
 * @param emitter		Player/Entity the voice stream comes from.
 * @param soundfile		Path to the soundfile relative to the sound folder.
 * @param length        Length in seconds how long the hud "voiceindicator" is shown.
 * @param pitch			The pitch of the audiofile.
 * @return				True on success, false on failure.
 */
stock bool:Client_RawAudio(client, const emitter, const String:soundfile[], Float:length = 0.0, pitch = 100)
{
    new Handle:message = StartMessageOne("RawAudio", client);

    if (message == INVALID_HANDLE) {
		return false;
	}

	BfWriteByte(message,	pitch);
	BfWriteByte(message,	emitter);
	BfWriteFloat(message,	length);
	BfWriteString(message,	soundfile);
	EndMessage();

    return true;
}

/**
 * Plays a soundfile as if the player is using voicecomm for all players.
 * The voiceindicator is shown on the right, as if the players is talking.
 * Thanks to Peace-Maker for the function.
 *
 * @param emitter		Player/Entity the voice stream comes from.
 * @param soundfile		Path to the soundfile relative to the sound folder.
 * @param length        Length in seconds how long the hud "voiceindicator" is shown.
 * @param pitch			The pitch of the audiofile.
 * @return				True on success, false on failure.
 */
stock bool:Client_RawAudioToAll(const emitter, const String:soundfile[], Float:length = 0.0, pitch = 100)
{
    new Handle:message = StartMessageAll("RawAudio");

    if (message == INVALID_HANDLE) {
		return false;
	}

	BfWriteByte(message,	pitch);
	BfWriteByte(message,	emitter);
	BfWriteFloat(message,	length);
	BfWriteString(message,	soundfile);
	EndMessage();

    return true;
}

/**
 * Sets an Impulse value for a client (eg: "impulse 100" for flashlight, value would be 100).
 * See: http://developer.valvesoftware.com/wiki/Impulse
 * 
 * @param client		Client Index
 * @param value			The impulse command value.
 * @return				True on success, false on failure.
 */
stock Client_Impulse(client, value)
{
	SetEntProp(client, Prop_Data, "m_nImpulse", value);
}

/**
 * Gets the offset for a client's weapon list (m_hMyWeapons).
 * The offset will saved globally for optimization.
 *
 * @param client		Client Index.
 * @return				Weapon list offset or -1 on failure.
 */
stock Client_GetWeaponsOffset(client)
{
	static offset = -1;

	if (offset == -1) {
		offset = FindDataMapOffs(client, "m_hMyWeapons");
	}
	
	return offset;
}

/**
 * Gets the current/active weapon of a client
 *
 * @param client		Client Index.
 * @return				Weapon Index or INVALID_ENT_REFERENCE if the client has no active weapon.
 */
stock Client_GetActiveWeapon(client)
{
	new weapon =  GetEntPropEnt(client, Prop_Data, "m_hActiveWeapon");
	
	if (!Entity_IsValid(weapon)) {
		return INVALID_ENT_REFERENCE;
	}
	
	return weapon;
}

/**
 * Gets the classname of the current/active weapon of a client.
 *
 * @param client		Client Index.
 * @param buffer		String Buffer to store the weapon's classname.
 * @param size			Max size of String: buffer.
 * @return				True on success or false otherwise.
 */
stock bool:Client_GetActiveWeaponName(client, String:buffer[], size)
{
	new weapon = Client_GetActiveWeapon(client);
	
	if (weapon == INVALID_ENT_REFERENCE) {
		buffer[0] = '\0';
		return false;
	}
	
	Entity_GetClassName(weapon, buffer, size);
	
	return true;
}

/**
 * Changes the active/current weapon of a player by Index.
 * Note: No changing animation will be played !
 *
 * @param client		Client Index.
 * @param weapon		Index of a valid weapon.
 * @noreturn
 */
stock Client_SetActiveWeapon(client, weapon)
{
	SetEntPropEnt(client, Prop_Data, "m_hActiveWeapon", weapon);
	ChangeEdictState(client, FindDataMapOffs(client, "m_hActiveWeapon"));
}

/**
 * Changes the active weapon the client is holding.
 * Note: No changing animation will be played !
 *
 * @param client		Client Index.
 * @param className		Weapon Classname.
 * @return				True on success, false on failure.
 */
stock bool: Client_ChangeWeapon(client, const String:className[])
{
	new weapon = Client_GetWeapon(client, className);
	
	if (weapon == INVALID_ENT_REFERENCE) {
		return false;
	}

	Client_SetActiveWeapon(client,weapon);
	
	return true;
}

/**
 * Changes the active weapon to the last.
 * If the last active weapon can't be found, the default weapon is taken.
 * If the default weapon can't be found, the first weapon in the list is taken.
 * If the first weapon can't be found, INVALID_ENT_REFERENCEE is returned.
 *
 * @param client 		Client Index.	
 * @return				Entity Index or, INVALID_ENT_REFERENCE.
 */
stock Client_ChangeToLastWeapon(client)
{
	new weapon = Client_GetLastActiveWeapon(client);
	
	if (weapon == INVALID_ENT_REFERENCE) {
		weapon = Client_GetDefaultWeapon(client);
		
		if (weapon == INVALID_ENT_REFERENCE) {
			weapon = Client_GetFirstWeapon(client);
			
			if (weapon == INVALID_ENT_REFERENCE) {
				return INVALID_ENT_REFERENCE;
			}
		}
	}
	
	Client_SetActiveWeapon(client, weapon);
	
	return weapon;
}

/**
 * Gets the last active weapon of a client.
 *
 * @param client		Client Index.
 * @return				Entity Index of the weapon on success, INVALID_ENT_REFERENCE on failure.
 */
stock Client_GetLastActiveWeapon(client)
{
	new weapon = GetEntPropEnt(client, Prop_Data, "m_hLastWeapon");
	
	if (!Entity_IsValid(weapon)) {
		return INVALID_ENT_REFERENCE;
	}
	
	return weapon;
}

/**
 * Gets the classname of the last active weapon of a client.
 *
 * @param client		Client Index.
 * @param buffer		Buffer to store the weapon classname.
 * @param size			Max size of String: buffer.
 * @return				True on success, false on failure.
 */
stock bool:Client_GetLastActiveWeaponName(client, String:buffer[], size)
{
	new weapon = Client_GetLastActiveWeapon(client);
	
	if (weapon == INVALID_ENT_REFERENCE) {
		buffer[0] = '\0';
		return false;
	}
	
	Entity_GetClassName(weapon, buffer, size);
	
	return true;
}

/**
 * Sets the last active weapon of a client.
 *
 * @param client		Client Index.
 * @param weapon		Entity Index of a weapon.
 * @noreturn
 */
stock Client_SetLastActiveWeapon(client, weapon)
{
	SetEntPropEnt(client, Prop_Data, "m_hLastWeapon", weapon);
	ChangeEdictState(client, FindDataMapOffs(client, "m_hLastWeapon"));
}

/**
 * Equips (attaches) a weapon to a client.
 *
 * @param client		Client Index.
 * @param weapon		Entity Index of the weapon.
 * @param switchTo		If true, the client will switch to that weapon (make it active).
 * @noreturn
 */
stock Client_EquipWeapon(client, weapon, bool:switchTo=false)
{
	EquipPlayerWeapon(client, weapon);
	
	if (switchTo) {
		Client_SetActiveWeapon(client, weapon);
	}
}

/**
 * Savly detaches a clients weapon, to remove it as example.
 * The client will select his last weapon when detached.
 *
 * @param client 		Client Index.	
 * @param weapon		Entity Index of the weapon, you'd like to detach.
 * @return				True on success, false otherwise.
 */
stock bool:Client_DetachWeapon(client, weapon)
{
	if (!RemovePlayerItem(client, weapon)) {
		return false;
	}
	
	if (Client_GetActiveWeapon(client) == INVALID_ENT_REFERENCE) {
		Client_ChangeToLastWeapon(client);
	}
	
	return true;
}

/**
 * Gives a client a weapon.
 *
 * @param client		Client Index.
 * @param className		Weapon Classname String.
 * @param switchTo		If set to true, the client will switch the active weapon to the new weapon.
 * @return				Entity Index of the given weapon on success, INVALID_ENT_REFERENCE on failure.
 */
stock Client_GiveWeapon(client, const String:className[], bool:switchTo=true)
{
	new weapon = Client_GetWeapon(client, className);

	if (weapon == INVALID_ENT_REFERENCE) {
		weapon = Weapon_CreateForOwner(client, className);
		
		if (weapon == INVALID_ENT_REFERENCE) {
			return INVALID_ENT_REFERENCE;
		}
	}

	Client_EquipWeapon(client, weapon, switchTo);

	return weapon;
}

/**
 * Gives a client a weapon and ammo for that weapon.
 *
 * @param client		Client Index.
 * @param className		Weapon Classname String.
 * @param switchTo		If set to true, the client will switch the active weapon to the new weapon.
 * @param primaryAmmo	Primary ammo stock value from the client, if -1 the value is untouched.
 * @param secondaryAmmo	Secondary ammo stock value from the client, if -1 the value is untouched.
 * @param primaryClip	Primary ammo value in the weapon clip, if -1 the value is untouched.
 * @param secondaryClip	Secondary ammo value in the weapon clip, if -1 the value is untouched.
 * @return				Entity Index of the given weapon on success, INVALID_ENT_REFERENCE on failure.
 */
stock Client_GiveWeaponAndAmmo(client, const String:className[], bool:switchTo=true, primaryAmmo=-1, secondaryAmmo=-1, primaryClip=-1, secondaryClip=-1)
{
	new weapon = Client_GiveWeapon(client, className, switchTo);
	
	if (weapon == INVALID_ENT_REFERENCE) {
		return INVALID_ENT_REFERENCE;
	}

	Weapon_SetClips(weapon, primaryClip, secondaryClip);
	Client_SetWeaponPlayerAmmoEx(client, weapon, primaryAmmo, secondaryAmmo);

	return weapon;
}

/**
 * Removes a weapon from a client.
 *
 * @param client 		Client Index.
 * @param className		Weapon Classname String.
 * @param firstOnly		If false it loops trough the whole weapon list and deletes all weapons that match the specified classname.
 * @param clearAmmo		If true, the ammo the client carries for that weapon will be set to 0 (primary and secondary).
 * @return				True on success, false otherwise.
 */
stock bool:Client_RemoveWeapon(client, const String:className[], bool:firstOnly=true, bool:clearAmmo=false)
{
	new offset = Client_GetWeaponsOffset(client) - 4;

	for (new i=0; i < MAX_WEAPONS; i++) {
		offset += 4;

		new weapon = GetEntDataEnt2(client, offset);
		
		if (!Weapon_IsValid(weapon)) {
			continue;
		}
		
		if (!Entity_ClassNameMatches(weapon, className)) {
			continue;
		}
		
		if (clearAmmo) {
			Client_SetWeaponPlayerAmmoEx(client, weapon, 0, 0);
		}
		
		if (Client_GetActiveWeapon(client) == weapon) {
			Client_ChangeToLastWeapon(client);
		}
		
		if (RemovePlayerItem(client, weapon)) {
			Entity_Kill(weapon);
		}
		
		if (firstOnly) {
			return true;
		}
	}

	return false;
}

/**
 * Removes all weapons of a client.
 * You can specify a weapon it shouldn't remove and if to
 * clear the player's ammo for a weapon when it gets removed.
 *
 * @param client 		Client Index.
 * @param exclude		If not empty, this weapon won't be removed from the client.
 * @param clearAmmo		If true, the ammo the player carries for all removed weapons are set to 0 (primary and secondary).
 * @return				Number of removed weapons.
 */
stock Client_RemoveAllWeapons(client, const String:exclude[]="", bool:clearAmmo=false)
{
	new offset = Client_GetWeaponsOffset(client) - 4;
	
	new numWeaponsRemoved = 0;
	for (new i=0; i < MAX_WEAPONS; i++) {
		offset += 4;

		new weapon = GetEntDataEnt2(client, offset);
		
		if (!Weapon_IsValid(weapon)) {
			continue;
		}
		
		if (exclude[0] != '\0' && Entity_ClassNameMatches(weapon, exclude)) {
			Client_SetActiveWeapon(client, weapon);
			continue;
		}
		
		if (clearAmmo) {
			Client_SetWeaponPlayerAmmoEx(client, weapon, 0, 0);
		}

		if (RemovePlayerItem(client, weapon)) {
			Entity_Kill(weapon);
		}

		numWeaponsRemoved++;
	}
	
	return numWeaponsRemoved;
}

/**
 * Checks if a client has a specific weapon.
 *
 * @param client 		Client Index.
 * @param className		Weapon Classname.
 * @return				True if client has the weapon, otherwise false.
 */
stock Client_HasWeapon(client, const String:className[])
{
	new weapon = Client_GetWeapon(client, className);
	
	return (weapon != INVALID_ENT_REFERENCE);
}

/**
 * Gets the weapon of a client by the weapon's classname.
 *
 * @param client 		Client Index.
 * @param className		Classname of the weapon.
 * @return				Entity index on success or INVALID_ENT_REFERENCE.
 */
stock Client_GetWeapon(client, const String:className[])
{
	new offset = Client_GetWeaponsOffset(client) - 4;

	for (new i=0; i < MAX_WEAPONS; i++) {
		offset += 4;

		new weapon = GetEntDataEnt2(client, offset);
		
		if (!Weapon_IsValid(weapon)) {
			continue;
		}
		
		if (Entity_ClassNameMatches(weapon, className)) {
			return weapon;
		}
	}
	
	return INVALID_ENT_REFERENCE;
}

/**
 * Gets the weapon of a client by slot number.
 * Note: This is incompatible to games that have multiple
 * weapons in one slot (eg.: hl2dm).
 *
 * @param client 		Client Index.
 * @param slot			Slot Index.
 * @return				Entity index on success or INVALID_ENT_REFERENCE.
 */
stock Client_GetWeaponBySlot(client, slot)
{
	return GetPlayerWeaponSlot(client, slot);
}

/**
 * Gets the clients default weapon (Entity Index).
 *
 * @param client 		Client Index.
 * @return				Entity Index on success, INVALID_ENT_REFERENCE on failure.
 */
stock Client_GetDefaultWeapon(client)
{
	decl String:weaponName[MAX_WEAPON_STRING];
	if (Client_GetDefaultWeaponName(client, weaponName, sizeof(weaponName))) {
		return INVALID_ENT_REFERENCE;
	}
	
	return Client_GetWeapon(client, weaponName);
}

/**
 * Gets the clients default weapon (classname).
 * This function doesn't work in all games (maybe only works in hl2dm).
 * It will return an empty string if cl_defaultweapon doesn't exist.
 *
 * @param client 		Client Index.
 * @param buffer		Buffer to store the default weapon's classname.
 * @param size			Max size of string: buffer.
 * @return				True on success, false otherwise.
 */
stock bool:Client_GetDefaultWeaponName(client, String:buffer[], size)
{
	if (!GetClientInfo(client, "cl_defaultweapon", buffer, size)) {
		buffer[0] = '\0';
		return false;
	}
	
	return true;
}

/**
 * Gets the first weapon of the client's weapon list (m_hMyWeapons).
 * Note: This has nothing to do with weapon slots.
 *
 * @param client 		Client Index.	
 * @return				Entity Index of the weapon or INVALID_ENT_REFERENCE.
 */
stock Client_GetFirstWeapon(client)
{
	new offset = Client_GetWeaponsOffset(client) - 4;

	for (new i=0; i < MAX_WEAPONS; i++) {
		offset += 4;

		new weapon = GetEntDataEnt2(client, offset);
		
		if (!Weapon_IsValid(weapon)) {
			continue;
		}
		
		return weapon;
	}
	
	return INVALID_ENT_REFERENCE;
}

/**
 * Gets the number of weapons a client has.
 *
 * @param client 		Client Index.	
 * @return				Number of weapons.
 */
stock Client_GetWeaponCount(client)
{	
	new numWeapons = 0;
	
	new offset = Client_GetWeaponsOffset(client) - 4;

	for (new i=0; i < MAX_WEAPONS; i++) {
		offset += 4;

		new weapon = GetEntDataEnt2(client, offset);
		
		if (!Weapon_IsValid(weapon)) {
			continue;
		}
		
		numWeapons++;
	}
	
	return numWeapons;
}

/**
 * Checks whether the client is currently reloading his active weapon. 
 *
 * @param client 		Client Index.	
 * @return				True if client is reloading, false otherwise.
 */
stock bool:Client_IsReloading(client)
{
	new weapon = Client_GetActiveWeapon(client);
	
	if (weapon == INVALID_ENT_REFERENCE) {
		return false;
	}
	
	return Weapon_IsReloading(weapon);
}

/**
 * Sets the primary and secondary clip value of a weapon.
 *
 * @param client		Client Index.
 * @param classname		Classname of a weapon.
 * @param primaryClip	Primary ammo value in the weapon clip, if -1 the value is untouched.
 * @param secondaryClip	Secondary ammo value in the weapon clip, if -1 the value is untouched.
 * @return				True on success, false on failure.
 */
stock bool:Client_SetWeaponClipAmmo(client, const String:className[], primaryClip=-1, secondoaryClip=-1)
{
	new weapon = Client_GetWeapon(client, className);

	if (weapon == INVALID_ENT_REFERENCE) {
		return false;
	}

	if (primaryClip != -1) {
		Weapon_SetPrimaryClip(weapon, primaryClip);
	}

	if (secondoaryClip != -1) {
		Weapon_SetSecondaryClip(weapon, primaryClip);
	}

	return true;
}

/**
 * Gets the primary and secondary ammo the player carries for a specific weapon classname.
 *
 * @param client		Client Index.
 * @param classname		Classname of a weapon.
 * @param primaryAmmo	Primary ammo stock from the client, if -1 the value is untouched.
 * @param secondaryAmmo	Secondary ammo stock from the client, if -1 the value is untouched.
 * @return				True on success, false on failure.
 */
stock bool:Client_GetWeaponPlayerAmmo(client, const String:className[], &primaryAmmo=-1, &secondaryAmmo=-1)
{
	new weapon = Client_GetWeapon(client, className);

	if (weapon == INVALID_ENT_REFERENCE) {
		return false;
	}
	
	new offset_ammo = FindDataMapOffs(client, "m_iAmmo");
	
	if (primaryAmmo != -1) {
		new offset = offset_ammo + (Weapon_GetPrimaryAmmoType(weapon) * 4);
		primaryAmmo = GetEntData(client, offset);
	}
	
	if (secondaryAmmo != -1) {
		new offset = offset_ammo + (Weapon_GetSecondaryAmmoType(weapon) * 4);
		secondaryAmmo = GetEntData(client, offset);
	}

	return true;
}

/**
 * Sets the primary and secondary ammo the player carries for a specific weapon classname.
 *
 * @param client		Client Index.
 * @param classname		Weapon Classname String.
 * @param primaryAmmo	Primary ammo stock from the client, if -1 the value is untouched.
 * @param secondaryAmmo	Secondary ammo stock from the client, if -1 the value is untouched.
 * @return				True on success, false on failure.
 */
stock bool:Client_SetWeaponPlayerAmmo(client, const String:className[], primaryAmmo=-1, secondaryAmmo=-1)
{
	new weapon = Client_GetWeapon(client, className);

	if (weapon == INVALID_ENT_REFERENCE) {
		return false;
	}

	Client_SetWeaponPlayerAmmoEx(client, weapon, primaryAmmo, secondaryAmmo);

	return true;
}

/**
 * Sets the primary and secondary ammo the player carries for a specific weapon index.
 *
 * @param client		Client Index.
 * @param weapon		Weapon Entity Index.
 * @param primaryAmmo	Primary ammo stock value from the client, if -1 the value is untouched.
 * @param secondaryAmmo	Secondary ammo stock value from the client, if -1 the value is untouched.
 * @noreturn		
 */
stock Client_SetWeaponPlayerAmmoEx(client, weapon, primaryAmmo=-1, secondaryAmmo=-1)
{
	new offset_ammo = FindDataMapOffs(client, "m_iAmmo");

	if (primaryAmmo != -1) {
		new offset = offset_ammo + (Weapon_GetPrimaryAmmoType(weapon) * 4);
		SetEntData(client, offset, primaryAmmo, 4, true);
	}

	if (secondaryAmmo != -1) {
		new offset = offset_ammo + (Weapon_GetSecondaryAmmoType(weapon) * 4);
		SetEntData(client, offset, secondaryAmmo, 4, true);
	}
}

/**
 * Sets the value from primary and secondary ammo stock, of a client.
 * 
 * @param client		Client Index.
 * @param className		Classname of a weapon.
 * @param primaryAmmo	Primary ammo stock value from the client, if -1 the value is untouched.
 * @param secondaryAmmo	Secondary ammo stock value from the client, if -1 the value is untouched.
 * @param primaryClip	Primary ammo value in the weapon clip, if -1 the value is untouched.
 * @param secondaryClip	Secondary ammo value in the weapon clip, if -1 the value is untouched.
 * @return				Entity Index of the given weapon on success, INVALID_ENT_REFERENCE on failure.
 */
stock Client_SetWeaponAmmo(client, const String:className[], primaryAmmo=-1, secondaryAmmo=-1, primaryClip=-1, secondaryClip=-1)
{
	new weapon = Client_GetWeapon(client, className);
	
	if (weapon == INVALID_ENT_REFERENCE) {
		return false;
	}
	
	Weapon_SetClips(weapon, primaryClip, secondaryClip);
	Client_SetWeaponPlayerAmmoEx(client, weapon, primaryAmmo, secondaryAmmo);
	
	return true;
}

/**
 * Prints white text to the bottom center of the screen
 * for one client. Does not work in all games.
 * Line Breaks can be done with "\n".
 * 
 * @param client		Client Index.
 * @param format		Formatting rules.
 * @param ...			Variable number of format parameters.
 * @return				True on success, false if this usermessage doesn't exist.
 */
stock bool:Client_PrintHintText(client, const String:format[], ...)
{
	new Handle:userMessage = StartMessageOne("HintText", client);
	
	if (userMessage == INVALID_HANDLE) {
		return false;
	}

	decl String:buffer[254];

	SetGlobalTransTarget(client);
	VFormat(buffer, sizeof(buffer), format, 3);

	BfWriteByte(userMessage, 1); 
	BfWriteString(userMessage, buffer); 

	EndMessage();
	
	return true;
}

/**
 * Prints white text to the bottom center of the screen
 * for all clients. Does not work in all games.
 * Line Breaks can be done with "\n".
 * 
 * @param format		Formatting rules.
 * @param ...			Variable number of format parameters.
 * @noreturn
 */
stock Client_PrintHintTextToAll(const String:format[], ...)
{
	decl String:buffer[254];
	
	for (new client=1; client <= MaxClients; client++) {

		if (!IsClientInGame(client)) {
			continue;
		}

		SetGlobalTransTarget(client);
		VFormat(buffer, sizeof(buffer), format, 2);
		Client_PrintHintText(client, buffer);
	}
}

/**
 * Prints white text to the right-center side of the screen
 * for one client. Does not work in all games.
 * Line Breaks can be done with "\n".
 * 
 * @param client		Client Index.
 * @param format		Formatting rules.
 * @param ...			Variable number of format parameters.
 * @return				True on success, false if this usermessage doesn't exist.
 */
stock bool:Client_PrintKeyHintText(client, const String:format[], ...)
{
	new Handle:userMessage = StartMessageOne("KeyHintText", client);
	
	if (userMessage == INVALID_HANDLE) {
		return false;
	}

	decl String:buffer[254];

	SetGlobalTransTarget(client);
	VFormat(buffer, sizeof(buffer), format, 3);

	BfWriteByte(userMessage, 1); 
	BfWriteString(userMessage, buffer); 

	EndMessage();
	
	return true;
}

/**
 * Prints white text to the right-center side of the screen
 * for all clients. Does not work in all games.
 * Line Breaks can be done with "\n".
 * 
 * @param format		Formatting rules.
 * @param ...			Variable number of format parameters.
 * @noreturn
 */
stock Client_PrintKeyHintTextToAll(const String:format[], ...)
{
	decl String:buffer[254];
	
	for (new client=1; client <= MaxClients; client++) {

		if (!IsClientInGame(client)) {
			continue;
		}

		SetGlobalTransTarget(client);
		VFormat(buffer, sizeof(buffer), format, 2);
		Client_PrintHintText(client, buffer);
	}
}

#define	SHAKE_START					0			// Starts the screen shake for all players within the radius.
#define	SHAKE_STOP					1			// Stops the screen shake for all players within the radius.
#define	SHAKE_AMPLITUDE				2			// Modifies the amplitude of an active screen shake for all players within the radius.
#define	SHAKE_FREQUENCY				3			// Modifies the frequency of an active screen shake for all players within the radius.
#define	SHAKE_START_RUMBLEONLY		4			// Starts a shake effect that only rumbles the controller, no screen effect.
#define	SHAKE_START_NORUMBLE		5			// Starts a shake that does NOT rumble the controller.

/*
 * Shakes a client's screen with the specified amptitude,
 * frequency & duration.
 * 
 * @param client		Client Index.
 * @param command		Shake Mode, use one of the SHAKE_ definitions.
 * @param amplitude		Shake magnitude/amplitude.
 * @param frequency		Shake noise frequency.
 * @param duration		Shake lasts this long.
 * return				True on success, false otherwise.
 */
stock bool:Client_Shake(client, command=SHAKE_START, Float:amplitude=50.0, Float:frequency=150.0, Float:duration=3.0)
{
	new Handle:userMessage = StartMessageOne("Shake", client);
	
	if (userMessage == INVALID_HANDLE) {
		return false;
	}
	
	if (command == SHAKE_STOP) {
		amplitude = 0.0;
	}
	else if (amplitude <= 0.0) {
		return false;
	}
	
	BfWriteByte(userMessage,	command);	// Shake Command
	BfWriteFloat(userMessage,	amplitude);	// shake magnitude/amplitude
	BfWriteFloat(userMessage,	frequency);	// shake noise frequency
	BfWriteFloat(userMessage,	duration);	// shake lasts this long
	EndMessage();
	
	return true;
}

stock bool:Client_IsAdmin(client)
{
	new AdminId:adminId = GetUserAdmin(client);
	
	if (adminId == INVALID_ADMIN_ID) {
		return false;
	}
	
	return GetAdminFlag(adminId, Admin_Generic);
}
