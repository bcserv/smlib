#if defined _smlib_effects_included
	#endinput
#endif
#define _smlib_effects_included

#include <sourcemod>
#include <sdktools_entinput>
#include <smlib/effects>
#include <smlib/entities>

// Entity Dissolve types
enum DissolveType
{
	DISSOLVE_NORMAL = 0,
	DISSOLVE_ELECTRICAL,
	DISSOLVE_ELECTRICAL_LIGHT,
	DISSOLVE_CORE
};

/**
 * Dissolves a player
 *
 * @param client		Client Index.
 * @param dissolveType	Dissolve Type, use the DissolveType enum.
 * @return				True on success, otherwise false.
 */
stock bool:Effect_DissolveEntity(entity, DissolveType:dissolveType=DISSOLVE_NORMAL)
{
	new env_entity_dissolver = CreateEntityByName("env_entity_dissolver");

	if (env_entity_dissolver == -1) {
		return false;
	}
	
	Entity_PointAtTarget(env_entity_dissolver, entity);
	SetEntProp(env_entity_dissolver, Prop_Send, "m_nDissolveType", _:dissolveType);
	AcceptEntityInput(env_entity_dissolver,	"Dissolve");
	Entity_Kill(env_entity_dissolver);

	return true;
}

/**
 * Dissolves a player's Ragdoll
 *
 * @param client		Client Index.
 * @param dissolveType	Dissolve Type, use the DissolveType enum.
 * @return				True on success, otherwise false.
 */
stock bool:Effect_DissolvePlayerRagDoll(client, DissolveType:dissolveType=DISSOLVE_NORMAL)
{    
	new m_hRagdoll = GetEntPropEnt(client, Prop_Send, "m_hRagdoll");

	if (m_hRagdoll == -1) {
		return false;
	}
	
	return Effect_DissolveEntity(m_hRagdoll, dissolveType);
}

functag EffectCallback public(entity, any:data);

/**
 * Fades an entity in our out.
 * You can specifiy a callback function which will get called
 * when the fade is finished.
 * Important: The callback will be called if it is passed,
 * no matter if the entity is still valid or not. That means you
 * have to check if the entity is valid yourself.
 *
 * @param entity		Entity Index.
 * @param fadeOut		Optional: Fade the entity out (true) or in (false).
 * @param kill			Optional: If to kill the entity when the fade is finished.
 * @param fast			Optional: Fade the entity fast (~0.7 secs) or slow (~3 secs)
 * @param callback		Optional: You can specify a callback Function that will get called when the fade is finished.
 * @param data			Optional: You can pass any data to the callback.
 * @return				True on success, otherwise false.
 */
stock Effect_Fade(entity, fadeOut=true, kill=false, fast=true, EffectCallback:callback=INVALID_FUNCTION, any:data=0)
{
	new Float:timerTime = 0.0;
	
	if (fast) {
		timerTime = 0.6;

		if (fadeOut) {
			SetEntityRenderFx(entity, RENDERFX_FADE_FAST);
		}
		else {
			SetEntityRenderFx(entity, RENDERFX_SOLID_FAST);
		}
	}
	else {
		timerTime = 3.0;

		if (fadeOut) {
			SetEntityRenderFx(entity, RENDERFX_FADE_SLOW);
		}
		else {
			SetEntityRenderFx(entity, RENDERFX_SOLID_SLOW);
		}
	}

	ChangeEdictState(entity, GetEntSendPropOffs(entity, "m_nRenderFX", true));

	if (kill || callback != INVALID_FUNCTION) {
		new Handle:dataPack = INVALID_HANDLE;
		CreateDataTimer(timerTime, _smlib_Timer_Effect_Fade, dataPack, TIMER_FLAG_NO_MAPCHANGE | TIMER_DATA_HNDL_CLOSE);
		
		WritePackCell(dataPack, EntIndexToEntRef(entity));
		WritePackCell(dataPack, kill);
		WritePackCell(dataPack, _:callback);
		WritePackCell(dataPack, data);
		ResetPack(dataPack);
	}
}

/**
 * Fades the entity in.
 *  A wrapper function around Effect_Fade().
 *
 * @param entity		Entity Index.
 * @param fadeOut		Optional: Fade the entity out (true) or in (false).
 * @param fast			Optional: Fade the entity fast (~0.7 secs) or slow (~3 secs)
 * @param callback		Optional: You can specify a callback Function that will get called when the fade is finished.
 * @param data			Optional: You can pass any data to the callback.
 * @return				True on success, otherwise false.
 */
stock Effect_FadeIn(entity, fast=true, EffectCallback:callback=INVALID_FUNCTION, any:data=0)
{
	Effect_Fade(entity, false, fast, callback, data);
}
	
/**
 * Fades the entity out.
 * A wrapper function around Effect_Fade().
 *
 * @param entity		Entity Index.
 * @param fadeOut		Optional: Fade the entity out (true) or in (false).
 * @param kill			Optional: If to kill the entity when the fade is finished.
 * @param fast			Optional: Fade the entity fast (~0.7 secs) or slow (~3 secs)
 * @param callback		Optional: You can specify a callback Function that will get called when the fade is finished.
 * @param data			Optional: You can pass any data to the callback.
 * @return				True on success, otherwise false.
 */
stock Effect_FadeOut(entity, kill=false, fast=true, EffectCallback:callback=INVALID_FUNCTION, any:data=0)
{
	Effect_Fade(entity, true, kill, fast, callback, data);
}

public Action:_smlib_Timer_Effect_Fade(Handle:Timer, Handle:dataPack)
{
	new entity = ReadPackCell(dataPack);
	new kill = ReadPackCell(dataPack);
	new EffectCallback:callback = EffectCallback:ReadPackCell(dataPack);
	new any:data = any:ReadPackCell(dataPack);
	
	if (callback != INVALID_FUNCTION) {
		Call_StartFunction(INVALID_HANDLE, callback);
		Call_PushCell(entity);
		Call_PushCell(data);
		Call_Finish();
	}

	if (kill && IsValidEntity(entity)) {
		Entity_Kill(entity);
	}

	return Plugin_Stop;
}
