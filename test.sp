
// enforce semicolons after each code statement
#pragma semicolon 1

#include <sourcemod>
#include <smlib>

#define PLUGIN_VERSION "0.1"



/*****************************************************************


		P L U G I N   I N F O


*****************************************************************/

public Plugin:myinfo = {
	name = "smlib Testing Suite",
	author = "Berni, Chanz",
	description = "Plugin by Berni",
	version = PLUGIN_VERSION,
	url = ""
}



/*****************************************************************


		G L O B A L   V A R S


*****************************************************************/

// ConVar Handles

// Misc



/*****************************************************************


		F O R W A R D   P U B L I C S


*****************************************************************/

public OnPluginStart() {
	
	new arr[1], String:arr_str[1][1];
	decl Float:vec[3];
	decl String:buf[1], String:twoDimStrArr[1][1];

	// File: arrays.inc
	Array_FindValue(arr, sizeof(arr), 1);
	Array_FindString(arr_str, sizeof(arr_str), "");
	Array_FindLowestValue(arr, sizeof(arr));
	Array_FindHighestValue(arr, sizeof(arr));
	Array_Fill(arr, sizeof(arr), 0);

	// File: 0s.inc
	Client_SetHud(0, 0);
	Client_IsValid(0);
	Client_IsIngame(0);
	Client_IsIngameAuthorized(0);
	Client_FindBySteamId("");
	Client_FindByName("");
	Client_GetObserverMode(0);
	Client_SetObserverMode(0, Obs_Mode:0);
	Client_GetObserverLastMode(0);
	Client_SetObserverLastMode(0, Obs_Mode:0);
	Client_GetViewOffset(0, vec);
	Client_SetViewOffset(0, vec);
	Client_GetObserverTarget(0);
	Client_SetObserverTarget(0, 0);
	Client_GetFOV(0);
	Client_SetFOV(0, 0);
	Client_DrawViewModel(0);
	Client_SetDrawViewModel(0, true);
	Client_SetThirdPersonMode(0);
	Client_IsInThirdPersonMode(0);
	Client_ScreenFade(0, 0, 0);
	Client_GetClones(0, arr);
	Client_IsOnLadder(0);
	Client_GetWaterLevel(0);
	Client_GetSuitSprintPower(0);
	Client_SetSuitSprintPower(0, 0.0);
	Client_GetCount();
	Client_GetFakePing(0);
	Client_GetClosestToClient(0);
	Client_GetLastPlaceName(0, buf, sizeof(buf));
	Client_GetScore(0);
	Client_SetScore(0, 0);
	Client_GetDeaths(0);
	Client_SetDeaths(0, 0);
	Client_GetArmor(0);
	Client_SetArmor(0, 0);
	Client_GetSuitPower(0);
	Client_SetSuitPower(0, 0.0);
	Client_GetActiveDevices(0);
	Client_GetNextDecalTime(0);
	Client_CanSprayDecal(0);
	Client_GetVehicle(0);
	Client_IsInVehicle(0);
	Client_RemoveAllDecals(0);
	Client_ExitVehicle(0);
	Client_RawAudio(0, 0, "");
	Client_RawAudioToAll(0, "");
	Client_Impulse(0, 0);
	Client_GetWeaponsOffset(0);
	Client_GetActiveWeapon(0);
	Client_GetActiveWeaponName(0, buf, sizeof(buf));
	Client_SetActiveWeapon(0, 0);
	Client_ChangeWeapon(0, "");
	Client_ChangeToLastWeapon(0);
	Client_GetLastActiveWeapon(0);
	Client_GetLastActiveWeaponName(0, buf, sizeof(buf));
	Client_SetLastActiveWeapon(0, 0);
	Client_EquipWeapon(0, 0);
	Client_DetachWeapon(0, 0);
	Client_GiveWeapon(0, "");
	Client_GiveWeaponAndAmmo(0, "");
	Client_RemoveWeapon(0, "");
	Client_RemoveAllWeapons(0, "");
	Client_HasWeapon(0, "");
	Client_GetWeapon(0, "");
	Client_GetWeaponBySlot(0, 0);
	Client_GetDefaultWeapon(0);
	Client_GetDefaultWeaponName(0, buf, sizeof(buf));
	Client_GetFirstWeapon(0);
	Client_GetWeaponCount(0);
	Client_IsReloading(0);
	Client_SetWeaponClipAmmo(0, "");
	Client_GetWeaponPlayerAmmo(0, "");
	Client_SetWeaponPlayerAmmo(0, "");
	Client_SetWeaponPlayerAmmoEx(0, 0);
	Client_SetWeaponAmmo(0, "");
	Client_PrintHintText(0, "");
	Client_PrintHintTextToAll("");
	Client_PrintKeyHintText(0, "");
	Client_PrintKeyHintTextToAll("");
	Client_Shake(0);
	Client_IsAdmin(0);
	Client_IsLookingAtWall(0);
	Client_GetClass(0);
	Client_SetClass(0, 0);

	// File: debug.inc
	Debug_FloatArray(vec);

	// File: dynarrays.inc
	DynArray_GetBool(INVALID_HANDLE, 0);

	// File: 0s.inc
	Edict_FindByName("");
	Edict_FindByHammerId(0);
	Edict_GetClosest(vec);
	Edict_GetClosestToEdict(0);

	// File: effects.inc
	Effect_DissolveEntity(0);
	Effect_DissolvePlayerRagDoll(0);
	Effect_Fade(0);
	Effect_FadeIn(0);
	Effect_FadeOut(0);

	// File: entities.inc
	Entity_IsValid(0);
	Entity_FindByName("");
	Entity_FindByHammerId(0);
	Entity_FindByClassName(0, "");
	Entity_ClassNameMatches(0, "");
	Entity_NameMatches(0, "");
	Entity_GetName(0, buf, sizeof(buf));
	Entity_SetName(0, "");
	Entity_GetClassName(0, buf, sizeof(buf));
	Entity_SetClassName(0, "");
	Entity_GetTargetName(0, buf, sizeof(buf));
	Entity_SetTargetName(0, "");
	Entity_GetGlobalName(0, buf, sizeof(buf));
	Entity_SetGlobalName(0, "");
	Entity_GetParentName(0, buf, sizeof(buf));
	Entity_SetParentName(0, "");
	Entity_GetHammerId(0);
	Entity_GetRadius(0);
	Entity_SetRadius(0, 0.0);
	Entity_GetMinSize(0, vec);
	Entity_SetMinSize(0, vec);
	Entity_GetMaxSize(0, vec);
	Entity_SetMaxSize(0, vec);
	Entity_SetMinMaxSize(0, vec, vec);
	Entity_GetSpawnFlags(0);
	Entity_SetSpawnFlags(0, 0);
	Entity_AddSpawnFlags(0, 0);
	Entity_RemoveSpawnFlags(0, 0);
	Entity_ClearSpawnFlags(0);
	Entity_HasSpawnFlags(0, 0);
	Entity_GetEFlags(0);
	Entity_SetEFlags(0, Entity_Flags:0);
	Entity_AddEFlags(0, Entity_Flags:0);
	Entity_RemoveEFlags(0, Entity_Flags:0);
	Entity_HasEFlags(0, Entity_Flags:0);
	Entity_MarkSurrBoundsDirty(0);
	Entity_GetFlags(0);
	Entity_SetFlags(0, 0);
	Entity_AddFlags(0, 0);
	Entity_RemoveFlags(0, 0);
	Entity_ToggleFlag(0, 0);
	Entity_ClearFlags(0);
	Entity_GetSolidFlags(0);
	Entity_SetSolidFlags(0, SolidFlags_t:0);
	Entity_AddSolidFlags(0, SolidFlags_t:0);
	Entity_RemoveSolidFlags(0, SolidFlags_t:0);
	Entity_ClearSolidFlags(0);
	Entity_SolidFlagsSet(0, SolidFlags_t:0);
	Entity_GetSolidType(0);
	Entity_SetSolidType(0, SolidType_t:0);
	Entity_IsSolid(0);
	Entity_GetModel(0, buf, sizeof(buf));
	Entity_SetModel(0, "");
	Entity_GetModelIndex(0);
	Entity_SetModelIndex(0, 0);
	Client_SetMaxSpeed(0, 0.0);
	Entity_GetCollisionGroup(0);
	Entity_SetCollisionGroup(0, Collision_Group_t:0);
	Entity_GetAbsOrigin(0, vec);
	Entity_SetAbsOrigin(0, vec);
	Entity_GetAbsAngles(0, vec);
	Entity_SetAbsAngles(0, vec);
	Entity_GetLocalVelocity(0, vec);
	Entity_SetLocalVelocity(0, vec);
	Entity_GetBaseVelocity(0, vec);
	Entity_SetBaseVelocity(0, vec);
	Entity_GetAbsVelocity(0, vec);
	Entity_SetAbsVelocity(0, vec);
	Entity_IsLocked(0);
	Entity_Lock(0);
	Entity_UnLock(0);
	Entity_GetHealth(0);
	Entity_SetHealth(0, 0);
	Entity_GetMaxHealth(0);
	Entity_SetMaxHealth(0, 0);
	Entity_AddHealth(0, 0);
	Entity_InRange(0, 0, 0.0);
	Entity_EnableMotion(0);
	Entity_DisableMotion(0);
	Entity_Freeze(0);
	Entity_UnFreeze(0);
	Entity_PointAtTarget(0, 0);
	Entity_PointHurtAtTarget(0, 0);
	Entity_IsPlayer(0);
	Entity_Create("");
	Entity_Kill(0);
	Entity_KillAllByClassName("");
	Entity_GetOwner(0);
	Entity_SetOwner(0, 0);
	Entity_GetGroundEntity(0);
	Entity_Hurt(0, 0);
	Entity_GetParent(0);
	Entity_RemoveParent(0);
	Entity_SetParent(0, 0);

	// File: files.inc
	File_GetBaseName("", buf, sizeof(buf));
	File_GetDirName("", buf, sizeof(buf));
	File_GetFileName("", buf, sizeof(buf));
	File_GetExtension("", buf, sizeof(buf));
	File_AddToDownloadsTable("");
	File_ReadDownloadList("");
	File_LoadTranslations("");

	// File: game.inc
	Game_End();

	// File: general.inc
	PrecacheMaterial("");
	IsMaterialPrecached("");
	PrecacheParticleSystem("");
	IsParticleSystemPrecached("");
	FindStringIndexByTableName("", "");
	FindStringIndex2(0, "");

	// File: math.inc
	Math_Abs(0);
	Math_VectorsEqual(vec, vec);
	Math_Min(0, 0);
	Math_Max(0, 0);
	Math_Clamp(0, 0, 0);
	Math_IsInBounds(0, 0, 0);
	Math_GetRandomInt(0, 0);
	Math_GetRandomFloat(0.0, 0.0);
	Math_GetPercentage(0, 0);
	Math_GetPercentageFloat(0.0, 0.0);
	Math_MoveVector(vec, vec, 0.0, vec);

	// File: server.inc
	Server_GetIP(buf, sizeof(buf));
	Server_GetPort();
	Server_GetHostName(buf, sizeof(buf));

	// File: sql.inc
	SQL_TQueryF(INVALID_HANDLE, SQLTCallback:0, 0, DBPrio_Normal, "");
	SQL_FetchIntByName(INVALID_HANDLE, "");
	SQL_FetchBoolByName(INVALID_HANDLE, "");
	SQL_FetchFloatByName(INVALID_HANDLE, "");
	SQL_FetchStringByName(INVALID_HANDLE, "", buf, sizeof(buf));

	// File: strings.inc
	String_IsNumeric("");
	String_Trim("", buf, sizeof(buf));
	String_RemoveList(buf, twoDimStrArr, sizeof(twoDimStrArr));
	String_ToLower(buf, buf, sizeof(buf));
	String_ToUpper(buf, buf, sizeof(buf));
	String_StripChatColors(buf, buf, sizeof(buf));

	// File: teams.inc
	Team_HaveAllPlayers();
	Team_GetClientCount(0);
	Team_GetName(0, buf, sizeof(buf));
	Team_SetName(0, "");
	Team_GetScore(0);
	Team_SetScore(0, 0);
	Team_EdictGetNum(0);
	Team_IsValid(0);
	Team_EdictIsValid(0);
	Team_GetEdict(0);

	// File: 0s.inc
	Vehicle_GetDriver(0);
	Vehicle_HasDriver(0);
	Vehicle_ExitDriver(0);
	Vehicle_TurnOn(0);
	Vehicle_TurnOff(0);
	Vehicle_Lock(0);
	Vehicle_Unlock(0);
	Vehicle_IsValid(0);
	Vehicle_GetScript(0, buf, sizeof(buf));
	Vehicle_SetScript(0, "");

	// File: 0s.inc
	Weapon_GetOwner(0);
	Weapon_SetOwner(0, 0);
	Weapon_IsValid(0);
	Weapon_Create("", vec, vec);
	Weapon_CreateForOwner(0, "");
	Weapon_GetSubType(0, 0);
	Weapon_IsReloading(0);
	Weapon_GetState(0);
	Weapon_FiresUnderWater(0);
	Weapon_SetFiresUnderWater(0);
	Weapon_FiresUnderWaterAlt(0);
	Weapon_SetFiresUnderWaterAlt(0);
	Weapon_GetPrimaryAmmoType(0);
	Weapon_GetSecondaryAmmoType(0);
	Weapon_GetPrimaryClip(0);
	Weapon_SetPrimaryClip(0, 0);
	Weapon_GetSecondaryClip(0);
	Weapon_SetSecondaryClip(0, 0);
	Weapon_SetClips(0, 0, 0);
	Weapon_GetPrimaryAmmoCount(0);
	Weapon_SetPrimaryAmmoCount(0, 0);
	Weapon_GetSecondaryAmmoCount(0);
	Weapon_SetSecondaryAmmoCount(0, 0);
	Weapon_SetAmmoCounts(0, 0, 0);
	Weapon_GetViewModelIndex(0);
	Weapon_SetViewModelIndex(0, 0);

	// File: world.inc
	World_GetMaxs(vec);
}



/****************************************************************


		C A L L B A C K   F U N C T I O N S


****************************************************************/





/*****************************************************************


		P L U G I N   F U N C T I O N S


*****************************************************************/

