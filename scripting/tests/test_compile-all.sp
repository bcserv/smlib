/**************************************************
 *
 *            SMLIB Testing Suite
 *
 * ************************************************
 *
 * Warning: This plugin is only for testing if all
 * function stocks are compile-able without any
 * errors/warnings, do not load this on a production
 * server or it will likely crash it.
 *
 */

// enforce semicolons after each code statement
#pragma semicolon 1
// enforce transitional syntax
#pragma newdecls required

#include <sourcemod>
#include <smlib>

#define PLUGIN_VERSION "1.0"



/*****************************************************************


		P L U G I N   I N F O


*****************************************************************/

public Plugin myinfo = {
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

public void OnPluginStart() {

	int arr[1], arr_4[4];
	char arr_str[1][1];
	float vec[3];
	char buf[1], buf_10[10], twoDimStrArr[1][1];
	int variable;
	Handle handle;

	// File: arrays.inc
	Array_FindValue(arr, sizeof(arr), 1);
	Array_FindString(arr_str, sizeof(arr_str), "");
	Array_FindLowestValue(arr, sizeof(arr));
	Array_FindHighestValue(arr, sizeof(arr));
	Array_Fill(arr, sizeof(arr), 0);
	Array_Copy(arr, arr, 1);

	// File: clients.inc
	Client_SetHideHud(0, 0);
	Client_IsValid(0);
	Client_IsIngame(0);
	Client_IsIngameAuthorized(0);
	Client_FindBySteamId("");
	Client_FindByName("");
	Client_GetObserverMode(0);
	Client_SetObserverMode(0, view_as<Obs_Mode>(0));
	Client_GetObserverLastMode(0);
	Client_SetObserverLastMode(0, view_as<Obs_Mode>(0));
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
	Client_GetWeaponPlayerAmmoEx(0, 0);
	Client_SetWeaponPlayerAmmo(0, "");
	Client_SetWeaponPlayerAmmoEx(0, 0);
	Client_SetWeaponAmmo(0, "");
	Client_GetNextWeapon(0, variable);
	Client_PrintHintText(0, "");
	Client_PrintHintTextToAll("");
	Client_PrintKeyHintText(0, "");
	Client_PrintKeyHintTextToAll("");
	Client_PrintToChatRaw(0, "");
	Client_PrintToChat(0, false, "");
	Client_PrintToChatAll(false, "");
	Client_PrintToChatEx({ 0 }, 0, false, "");
	Client_Shake(0);
	Client_IsAdmin(0);
	Client_HasAdminFlags(0);
	Client_IsInAdminGroup(0, "");
	Client_IsLookingAtWall(0);
	Client_GetClass(0);
	Client_SetClass(0, 0);
	Client_GetButtons(0);
	Client_SetButtons(0, 0);
	Client_AddButtons(0, 0);
	Client_RemoveButtons(0, 0);
	Client_ClearButtons(0);
	Client_HasButtons(0, 0);
	Client_GetChangedButtons(0);
	Client_SetMaxSpeed(0, 0.0);
	Client_SetScreenOverlay(0, "");
	Client_SetScreenOverlayForAll("");
	Client_Mute(0);
	Client_UnMute(0);
	Client_IsMuted(0);
	Client_PrintToConsole(0, "");
	Client_Print(0, view_as<ClientHudPrint>(0), "");
	Client_PrintToChatExclude(0);
	Client_Reply(0, "");
	Client_MatchesFilter(0, 0);
	Client_Get({ 0 }, 0);
	Client_GetRandom(0);
	Client_GetNext(0);
	Client_GetMapTime(0);
	Client_GetMoney(0);
	Client_SetMoney(0, 0);
	Client_GetObservers(0, { 0 });
	Client_GetPlayersInRadius(0, arr, 0.0);
	Client_GetNextObserver(0);
	Client_GetPlayerManager();
	Client_SetPing(0, 0);
	Client_PrintToTopExclude(0);
	Client_PrintToTopRaw(0,0,0,0,0,0.0,"");
	Client_PrintToTop(0,0,0,0,0,0.0,"");
	Client_PrintToTopAll(0,0,0,0,0.0,"");
	Client_PrintToTopEx({ 0 },1,0,0,0,0,0.0,"");
	Client_ShowScoreboard(0);

	// File: colors.inc
	Color_ChatSetSubject(0);
	Color_ChatGetSubject();
	Color_ChatClearSubject();
	Color_ParseChatText("", "", 0);
	Color_TagToCode("", variable, buf_10);
	Color_StripFromChatText("", "", 0);

	// File: convars.inc
	ConCommand_HasFlags("", 0);
	ConCommand_AddFlags("", 0);
	ConCommand_RemoveFlags("", 0);

	// File: convars.inc
	Convar_HasFlags(null, 0);
	Convar_AddFlags(null, 0);
	Convar_RemoveFlags(null, 0);
	Convar_IsValidName("");

	// File: crypt.inc
	Crypt_Base64Encode("", buf, sizeof(buf));
	Crypt_Base64Decode("", buf, sizeof(buf));
	Crypt_Base64MimeToUrl("", buf, sizeof(buf));
	Crypt_Base64UrlToMime("", buf, sizeof(buf));
	Crypt_MD5("", buf, sizeof(buf));
	Crypt_RC4Encode("", "", buf, sizeof(buf));
	Crypt_RC4EncodeBinary("", 0, "", buf, sizeof(buf));

	// File: debug.inc
	Debug_FloatArray(vec);

	// File: dynarrays.inc
	DynArray_GetBool(null, 0);

	// File: edicts.inc
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
	Effect_DrawBeamBox(arr, 1, NULL_VECTOR, NULL_VECTOR, 0, 0);
	Effect_DrawBeamBoxToAll(NULL_VECTOR, NULL_VECTOR, 0, 0);
	Effect_DrawBeamBoxToClient(0, NULL_VECTOR, NULL_VECTOR, 0, 0);
	Effect_DrawBeamBoxRotatableToClient(0, NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, 0, 0);
	Effect_DrawBeamBoxRotatableToAll(NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, 0, 0);
	Effect_DrawBeamBoxRotatable(arr, 1, NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, 0, 0);
	Effect_DrawAxisOfRotationToClient(0, NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, 0, 0);
	Effect_DrawAxisOfRotationToAll(NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, 0, 0);
	Effect_DrawAxisOfRotation(arr, 1, NULL_VECTOR, NULL_VECTOR, NULL_VECTOR, 0, 0);
	Effect_EnvSprite(NULL_VECTOR,0);

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
	Entity_SetEFlags(0, view_as<Entity_Flags>(0));
	Entity_AddEFlags(0, view_as<Entity_Flags>(0));
	Entity_RemoveEFlags(0, view_as<Entity_Flags>(0));
	Entity_HasEFlags(0, view_as<Entity_Flags>(0));
	Entity_MarkSurrBoundsDirty(0);
	Entity_GetFlags(0);
	Entity_SetFlags(0, 0);
	Entity_AddFlags(0, 0);
	Entity_RemoveFlags(0, 0);
	Entity_ToggleFlag(0, 0);
	Entity_ClearFlags(0);
	Entity_GetSolidFlags(0);
	Entity_SetSolidFlags(0, view_as<SolidFlags_t>(0));
	Entity_AddSolidFlags(0, view_as<SolidFlags_t>(0));
	Entity_RemoveSolidFlags(0, view_as<SolidFlags_t>(0));
	Entity_ClearSolidFlags(0);
	Entity_SolidFlagsSet(0, view_as<SolidFlags_t>(0));
	Entity_GetSolidType(0);
	Entity_SetSolidType(0, view_as<SolidType_t>(0));
	Entity_IsSolid(0);
	Entity_GetModel(0, buf, sizeof(buf));
	Entity_SetModel(0, "");
	Entity_GetModelIndex(0);
	Entity_SetModelIndex(0, 0);
	Entity_SetMaxSpeed(0, 0.0);
	Entity_GetCollisionGroup(0);
	Entity_SetCollisionGroup(0, view_as<Collision_Group_t>(0));
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
	Entity_GetDistance(0, 0);
	Entity_GetDistanceOrigin(0, vec);
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
	Entity_ClearParent(0);
	Entity_SetParent(0, 0);
	Entity_ChangeOverTime(0, 0.1, INVALID_FUNCTION);
	Entity_GetNextChild(0);
	Entity_GetMoveDirection(0,NULL_VECTOR);
	Entity_SetMoveDirection(0,NULL_VECTOR);
	Entity_GetForceClose(0);
	Entity_SetForceClose(0,true);
	Entity_GetSpeed(0);
	Entity_SetSpeed(0,0.0);
	Entity_GetBlockDamage(0);
	Entity_SetBlockDamage(0,0.0);
	Entity_IsDisabled(0);
	Entity_Disable(0);
	Entity_Enable(0);
	Entity_SetTakeDamage(0,0);
	Entity_GetTakeDamage(0);
	Entity_SetMinHealthDamage(0,0);
	Entity_GetMinHealthDamage(0);
	Entity_GetRenderColor(0, arr_4);
	Entity_SetRenderColor(0, 0, 0, 0, 0);
	Entity_AddOutput(0, "");
	Entity_TakeHealth(0, 0);

	// File: files.inc
	File_GetBaseName("", buf, sizeof(buf));
	File_GetDirName("", buf, sizeof(buf));
	File_GetFileName("", buf, sizeof(buf));
	File_GetExtension("", buf, sizeof(buf));
	File_AddToDownloadsTable("");
	File_ReadDownloadList("");
	File_LoadTranslations("");
	File_ToString("", "", 0);
	File_StringToFile("", "");
	File_Copy("", "");
	File_CopyRecursive("", "");

	// File: game.inc
	Game_End();
	Game_EndRound();

	// File: general.inc
	PrecacheMaterial("");
	IsMaterialPrecached("");
	PrecacheParticleSystem("");
	IsParticleSystemPrecached("");
	FindStringIndexByTableName("", "");
	FindStringIndex2(0, "");
	LongToIP(0, buf, sizeof(buf));
	IPToLong("");
	IsIPLocal(0);
	ClearHandle(handle);

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
	Math_UnitsToMeters(0.0);
	Math_UnitsToFeet(0.0);
	Math_UnitsToCentimeters(0.0);
	Math_UnitsToKilometers(0.0);
	Math_UnitsToMiles(0.0);
	Math_RotateVector(vec, vec, vec);
	Math_MakeVector(0.0, 0.0, 0.0, vec);
	Math_Overflow(0, 0, 0);

	// File: menus.inc
	Menu_AddIntItem(null, 0, "");
	Menu_GetIntItem(null, 0);

	// File: server.inc
	Server_GetIP();
	Server_GetIPString(buf, sizeof(buf));
	Server_GetPort();
	Server_GetHostName(buf, sizeof(buf));

	// File: sql.inc
	SQL_TQueryF(null, INVALID_FUNCTION, 0, DBPrio_Normal, "");
	SQL_FetchIntByName(null, "");
	SQL_FetchBoolByName(null, "");
	SQL_FetchFloatByName(null, "");
	SQL_FetchStringByName(null, "", buf, sizeof(buf));

	// File: strings.inc
	String_IsNumeric("");
	String_Trim("", buf, sizeof(buf));
	String_RemoveList(buf, twoDimStrArr, sizeof(twoDimStrArr));
	String_ToLower(buf, buf, sizeof(buf));
	String_ToUpper(buf, buf, sizeof(buf));
	String_GetRandom(buf, sizeof(buf));
	String_StartsWith("", "");
	String_EndsWith("", "");

	// File: teams.inc
	Team_HaveAllPlayers();
	Team_GetClientCount(0);
	Team_GetClientCounts(variable, variable);
	Team_GetName(0, buf, sizeof(buf));
	Team_SetName(0, "");
	Team_GetScore(0);
	Team_SetScore(0, 0);
	Team_EdictGetNum(0);
	Team_IsValid(0);
	Team_EdictIsValid(0);
	Team_GetEdict(0);
	Team_GetAnyClient(0);

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
	Weapon_GetSubType(0);
	Weapon_IsReloading(0);
	Weapon_GetState(0);
	Weapon_FiresUnderWater(0);
	Weapon_SetFiresUnderWater(0);
	Weapon_FiresUnderWaterAlt(0);
	Weapon_SetFiresUnderWaterAlt(0);
	Weapon_GetPrimaryAmmoType(0);
	Weapon_GetSecondaryAmmoType(0);
	Weapon_SetSecondaryAmmoType(0,0);
	Weapon_SetPrimaryAmmoType(0,0);
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
