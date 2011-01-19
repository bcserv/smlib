#include <smlib>

#if defined _smlib_teams_included
	#endinput
#endif
#define _smlib_teams_included

// Team Defines
#define	TEAM_INVALID	-1
#define TEAM_UNASSIGNED	0
#define TEAM_SPECTATOR	1
#define TEAM_ONE		2
#define TEAM_TWO		3
#define TEAM_THREE		4
#define TEAM_FOUR		5

/*
 * If one team is empty its assumed single team mode is enabled.
 *
 * @noparam
 * @return			True if one team is empty, false otherwise.			
 */
stock bool:Team_HaveAllPlayers(bool:countFakeClients=true) {

	new teamCount = GetTeamCount();
	for (new i=2; i < teamCount; i++) {

		if (Team_GetClientCount(i, countFakeClients) == 0) {
			return false;
		}
	}
	
	return true;
}

/*
* Returns the client count of the players in a team
*
* @param inGameOnly		If false connecting players are also counted.
* @param countBots		If true bots will be counted too.
* @return				Client count in the server.
*/
stock Team_GetClientCount(team, bool:countFakeClients=true)
{
	new numClients = 0;
	
	for (new client=1; client <= MaxClients; client++) {
		
		if (!IsClientInGame(client)) {
			continue;
		}
		
		if (!countFakeClients && IsFakeClient(client)) {
			continue;
		}
		
		if (GetClientTeam(client) == team) {
			numClients++;
		}
	}

	return numClients;
}

/*
* Gets the name of a team.
* Don't call this before OnMapStart()
*
* @param index			Team Index.
* @param str			String buffer
* @param size			String Buffer Size
* @return				True on success, false otherwise
*/
stock bool:Team_GetName(index, String:str[], size)
{
	new edict = Team_GetEdict(index);
	
	if (edict == -1) {
		str[0] = '\0';
		return false;
	}

	GetEntPropString(edict, Prop_Send, "m_szTeamname", str, size);
	
	return true;
}

/*
* Changes a team's name.
* Use this carefully !
* Only set the teamname OnMapStart() or OnEntityCreated()
* when no players are ingame, otherwise it can crash the server.
*
* @param index			Team Index.
* @param name			New Name String
* @return				True on success, false otherwise
*/
stock bool:Team_SetName(index, const String:name[])
{
	new edict = Team_GetEdict(index);
	
	if (edict == -1) {
		return false;
	}

	SetEntPropString(edict, Prop_Send, "m_szTeamname", name);
	ChangeEdictState(edict, GetEntSendPropOffs(edict, "m_szTeamname", true));
	
	return true;
}

/*
* Changes a team's score.
* Don't use this before OnMapStart().
*
* @param index			Team Index.
* @param score			Score value.
* @return				Team Score or -1 if the team is not valid.
*/
stock bool:Team_GetScore(index, score)
{
	new edict = Team_GetEdict(index);
	
	if (edict == -1) {
		return -1;
	}

	return GetEntProp(edict, Prop_Send, "m_iScore");
}

/*
* Changes a team's score.
* Don't use this before OnMapStart().
*
* @param index			Team Index.
* @param score			Score value.
* @return				True on success, false otherwise
*/
stock bool:Team_SetScore(index, score)
{
	new edict = Team_GetEdict(index);
	
	if (edict == -1) {
		return false;
	}

	SetEntProp(edict, Prop_Send, "m_iScore", score);
	ChangeEdictState(edict, GetEntSendPropOffs(edict, "m_iScore", true));
	
	return true;
}

/*
* Gets a team's edict (*team_manager) Team Index.
* Don't call this before OnMapStart()
*
* @param edict			Edict
* @return				Team Index
*/
stock Team_EdictGetNum(edict)
{
	return GetEntProp(edict, Prop_Send, "m_iTeamNum");
}

/*
* Check's whether the index is a valid team index or not.
* Don't call this before OnMapStart()
*
* @param index			Index.
* @return				True if the Index is a valid team, false otherwise.
*/
stock bool:Team_IsValid(index)
{
	return (Team_GetEdict(index) != -1);
}

/*
* Gets a team's edict (team_manager) Team Index.
* Don't call this before OnMapStart()
*
* @param index			Edict
* @return				Team Index
*/
stock Team_EdictIsValid(edict)
{
	return GetEntProp(edict, Prop_Send, "m_iTeamNum");
}

/*
* Gets a team's edict (team_manager)
* Don't call this before OnMapStart()
*
* @param index			Team Index.
* @return				Team edict or -1 if not found
*/
stock Team_GetEdict(index)
{
	new maxEntities = GetMaxEntities();
	for (new entity=MaxClients+1; entity < maxEntities; entity++) {
		
		if (!IsValidEntity(entity)) {
			continue;
		}
		
		if (!Entity_ClassNameMatches(entity, "team_manager", true)) {
			return -1;
		}
		
		if (Team_EdictGetNum(entity) == index) {
			return entity;
		}
	}
	
	return -1;
}
