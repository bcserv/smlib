#if defined _smlib_games_nmrih_included
	#endinput
#endif
#define _smlib_games_nmrih_included


//Buttons in Nmrih
#define IN_SHOVE			( 1 << 27 )		// Shoves away zombies (+shove)
#define IN_MAGLITE			( 1 << 28 ) 	// Brings up the maglite if owned and using a one handed weapon (+maglite)
#define IN_INVENTORY 		( 1 << 29 )		// Opens weapon inventory (+inventory)
#define IN_AMMOINV 			( 1 << 30 )		// Opens ammunition inventory (+ammoinv)


//Game modes in Nmrih
enum Nmrih_GameType 
{
	Nmrih_GameType_Unknown = -1,
	Nmrih_GameType_Objective = 0,
	Nmrih_GameType_Survial,
	
	Nmrih_Num_GameTypes
}

/**
 * Checks if the client can sprint.
 * 
 * @param client		Client Index.
 * @return				True if client can sprint, false otherwise.
 */
stock bool:Nmrih_Client_IsSprintEnabled(client)
{
	return bool:GetEntProp(client, Prop_Send, "m_bSprintEnabled");
}
/**
 * Enable or disable sprinting for the given client.
 * 
 * @param client			Client Index.
 * @param isSprintEnabled	True client can sprint, false client can't sprint.
 */
stock Nmrih_Client_SetSprintEnabled(client, bool:isSprintEnabled)
{
	SetEntProp(client, Prop_Send, "m_bSprintEnabled", isSprintEnabled, 1);
}

/**
 * Gets the clients crarried weight.
 * Note#1: Only weapons count as weight (beta 1.04).
 * Note#2: 10.0 Is the maximum a client can carry.
 * 
 * @param client		Client Index.
 * @return				Carried weight points.
 */
stock Float:Nmrih_Client_GetCarriedWeight(client)
{
	return GetEntPropFloat(client, Prop_Send, "m_flCarriedWeight");
}
/**
 * Sets the clients crarried weight.
 * Note#1: Only weapons count as weight (beta 1.04).
 * Note#2: 10.0 Is the maximum a client can carry.
 * 
 * @param client			Client Index.
 * @param carriedWeight		Number of tokens.
 * @noreturn
 */
stock Nmrih_Client_SetCarriedWeight(client, Float:carriedWeight)
{
	SetEntPropFloat(client, Prop_Send, "m_flCarriedWeight", carriedWeight);
}

/**
 * Checks if the client died while infected.
 * Note: The clients dead body will come back to life as a dead npc zombie.
 * 
 * @param client		Client Index.
 * @return				True if client was infected, false otherwise.
 */
stock bool:Nmrih_Client_IsDiedWhileInfected(client)
{
	return bool:GetEntProp(client, Prop_Send, "m_bDiedWhileInfected");
}
/**
 * Sets if the client died while infected or not.
 * 
 * @param client				Client Index.
 * @param isDiedWhileInfected	True client was infected, false client wasn't infected.
 */
stock Nmrih_Client_SetDiedWhileInfected(client, bool:isDiedWhileInfected)
{
	SetEntProp(client, Prop_Send, "m_bDiedWhileInfected", isDiedWhileInfected, 1);
}

/**
 * Checks if the client is grabbed by a zombie.
 * 
 * @param client		Client Index.
 * @return				True if client is grabbed, false otherwise.
 */
stock bool:Nmrih_Client_IsGrabbed(client)
{
	return bool:GetEntProp(client, Prop_Send, "m_bGrabbed");
}
/**
 * Sets if the client is grabbed.
 * 
 * @param client			Client Index.
 * @param isGrabbed			True client is grabbed, false client isn't grabbed.
 */
stock Nmrih_Client_SetGrabbed(client, bool:isGrabbed)
{
	SetEntProp(client, Prop_Send, "m_bGrabbed", isGrabbed, 1);
}

/**
 * Checks if the client has pills.
 * 
 * @param client		Client Index.
 * @return				True if client has pills, false otherwise.
 */
stock bool:Nmrih_Client_HasPills(client)
{
	return bool:GetEntProp(client, Prop_Send, "m_bHasPills");
}
/**
 * Sets if the client has pills.
 * 
 * @param client			Client Index.
 * @param isGrabbed			True client has pills, false client hasn't pills.
 */
stock Nmrih_Client_SetPills(client, bool:hasPills)
{
	SetEntProp(client, Prop_Send, "m_bHasPills", hasPills, 1);
}

/**
 * Checks if the client owns a walkie talkie.
 * 
 * @param client		Client Index.
 * @return				True if client owns a walkie talkie, false otherwise.
 */
stock bool:Nmrih_Client_HasWalkieTalkie(client)
{
	return bool:GetEntProp(client, Prop_Send, "m_bHasWalkieTalkie");
}
/**
 * Sets if the client owns a walkie talkie.
 * 
 * @param client			Client Index.
 * @param isGrabbed			True client owns a walkie talkie, false client doesn't.
 */
stock Nmrih_Client_SetWalkieTalkie(client, bool:hasWalkieTalkie)
{
	SetEntProp(client, Prop_Send, "m_bHasWalkieTalkie", hasWalkieTalkie, 1);
}

/**
 * Checks if the client is talking via walkie talkie.
 * 
 * @param client		Client Index.
 * @return				True if client is talking via walkie talkie, false otherwise.
 */
stock bool:Nmrih_Client_IsTalkingViaWalkieTalkie(client)
{
	return bool:GetEntProp(client, Prop_Send, "m_bTalkingWalkie");
}
/**
 * Sets if the client is talking via the walkie talkie.
 * 
 * @param client			Client Index.
 * @param isTalkingWalkie	True client is talking via walkie talkie, false client isn't.
 */
stock Nmrih_Client_SetTalkingViaWalkieTalkie(client, bool:isTalkingWalkie)
{
	SetEntProp(client, Prop_Send, "m_bTalkingWalkie", isTalkingWalkie, 1);
}

/**
 * Gets how many tokens the client has left.
 * Note: Tokens mean in this game extra lifes. When a client dies and still has tokens left the client can respawn.
 * 
 * @param client		Client Index.
 * @return				Number of tokens.
 */
stock Nmrih_Client_GetTokens(client)
{
	return GetEntProp(client, Prop_Send, "m_iTokens");
}
/**
 * Sets how many tokens the client has left.
 * Note: Tokens mean in this game extra lifes. When a client dies and still has tokens left the client can respawn.
 * 
 * @param client		Client Index.
 * @param tokens		Number of tokens.
 * @noreturn
 */
stock Nmrih_Client_SetTokens(client, tokens)
{
	SetEntProp(client, Prop_Send, "m_iTokens", tokens);
}


/**
 * Returns the game time when the client will die of an infection.
 * Note: You can subtract GetGameTime() from this to get the number of seconds left.
 * 		 This value is always in the future, it normally depends on sv_infectionlength.
 * 
 * @param client		Client Index.
 * @return				Game time when the player dies.
 */
stock Float:Nmrih_Client_GetInfectionDeathTime(client)
{
	return GetEntPropFloat(client, Prop_Send, "m_flInfectionDeathTime");
}
/**
 * Sets the game time, when a client dies because of an infection.
 * Note: You can use GetGameTime() to calculate this value.
 * 		 This value should always be in the future, it normally depends on sv_infectionlength.
 * 
 * @param client				Client Index.
 * @param infectionDeathTime	Game time when the will player die.
 * @noreturn
 */
stock Nmrih_Client_SetInfectionDeathTime(client, Float:infectionDeathTime)
{
	SetEntPropFloat(client, Prop_Send, "m_flInfectionDeathTime", infectionDeathTime);
}


/**
 * Returns the game time when the client was infected.
 * Note: You can subtract this from GetGameTime() to get the number of seconds since infection.
 * 
 * @param client		Client Index.
 * @return				Game time when the infection happened.
 */
stock Float:Nmrih_Client_GetInfectionTime(client)
{
	return GetEntPropFloat(client, Prop_Send, "m_flInfectionTime");
}
/**
 * Sets when the given client was infected.
 * 
 * @param client				Client Index.
 * @param infectionTime			Game time when the will player die.
 * @noreturn
 */
stock Nmrih_Client_SetInfectionTime(client, Float:infectionTime)
{
	SetEntPropFloat(client, Prop_Send, "m_flInfectionTime", infectionTime);
}

/**
 * Checks if the client is infected.
 * 
 * @param client		Client Index.
 * @return				True if poisoned, false otherwise.
 */
stock bool:Nmrih_Client_IsInfected(client)
{
	return bool:(Nmrih_Client_GetInfectionTime(client) != -1.0);
}

enum Nmrih_Zombie_Type
{
	
	Nmrih_Zombie_None = -1,
	
	Nmrih_Zombie_Shambler,
	Nmrih_Zombie_Runner,
	Nmrih_Zombie_Kid,
	
	Nmrih_Zombie_All
}

/*new String:Nmrih_Zombie_Type_ClassNames[][] =
{
	
	"npc_nmrih_shamblerzombie",
	"npc_nmrih_runnerzombie",
	"npc_nmrih_kidzombie"
};*/

/**
 * Returns how many valid zombies of specified type are on the map.
 * 
 * @param type			The filter type, only matching zombies will count.
 * @return				Number of zombies.
 */
stock Nmrih_Zombie_GetCount(Nmrih_Zombie_Type:type=Nmrih_Zombie_All)
{
	new count = 0;
	new maxEntities = GetMaxEntities();
	
	for (new entity=0; entity<maxEntities; entity++) {
		
		if (Nmrih_Zombie_IsValid(entity)) {
			
			if (type == Nmrih_Zombie_All) {
				
				count++;
			}
			else if (type == Nmrih_Zombie_GetType(entity)) {
				
				count++;
			}
		}
	}
	return count;
}

/**
 * Returns the type of a zombie.
 * Note: Use Nmrih_Zombie_Type to differentiate the different types.
 * 
 * @param entity		Entity index.
 * @return				Type of zombie.
 */
stock Nmrih_Zombie_Type:Nmrih_Zombie_GetType(entity)
{
	decl String:className[MAX_NAME_LENGTH];
	Entity_GetClassName(entity,className,sizeof(className));
	
	if (StrContains(className,"npc_nmrih_",false) == 0) {
		
		//npc_nmrih_shamblerzombie
		if (className[10] == 's' || className[10] == 'S') {
			return Nmrih_Zombie_Shambler;
		}
		//npc_nmrih_runnerzombie
		else if (className[10] == 'r' || className[10] == 'R') {
			return Nmrih_Zombie_Runner;
		}
		//npc_nmrih_kidzombie
		else if (className[10] == 'k' || className[10] == 'K') {
			return Nmrih_Zombie_Kid;
		}
		
		return Nmrih_Zombie_All;
	}
	return Nmrih_Zombie_None;
}
/**
 * Returns true when the given entity is valid and a zombie.
 * 
 * @param entity		Entity index.
 * @return				True if entity is valid and is a zombie, otherwise false.
 */
stock bool:Nmrih_Zombie_IsValid(entity)
{
	if (!Entity_IsValid(entity)) {
		return false;
	}
	
	if (Nmrih_Zombie_GetType(entity) == Nmrih_Zombie_None) {
		return false;
	}
	
	return true;
}


