#if defined _smlib_convars_included
	#endinput
#endif
#define _smlib_convars_included

#include <sourcemod>

/**
 * Checks if a ConVar has one or more flags set.
 *
 * @param	convar		ConVar Handle.
 * @param	flags		Flags to check.
 * @return				True if flags are set, false otherwise.
 */
stock bool:Convar_HasFlags(Handle:convar, flags)
{
	return bool:(GetConVarFlags(convar) & flags);
}

/**
 * Adds one or more flags to a ConVar.
 *
 * @param	convar		ConVar Handle.
 * @param	flags		Flags to add.
 * @noreturn
 */
stock Convar_AddFlags(Handle:convar, flags)
{
	new newFlags = GetConVarFlags(convar);
	newFlags |= flags;
	SetConVarFlags(convar, newFlags);
}

/**
 * Removes one ore more flags from a ConVar.
 *
 * @param	convar		ConVar Handle.
 * @param	flags		Flags to remove
 * @noreturn
 */
stock Convar_RemoveFlags(Handle:convar, flags)
{
	new newFlags = GetConVarFlags(convar);
	newFlags &= ~flags;
	SetConVarFlags(convar, newFlags);
}
