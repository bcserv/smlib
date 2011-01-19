#include <smlib>

#if defined _smlib_weapons_included
  #endinput
#endif
#define _smlib_weapons_included

#define MAX_WEAPON_OFFSET 64

/**
 * Gives a player a weapon and sets the ammunition values as followed: primary, pripary player, secondary, secondary player ammunition.
 * IMPORTANT: If he already has that weapon this function won't give him then another but change ammunition
 * 
 * @param client			Client index of the player you want to give the weapon.
 * @param 
 * @noreturn
 */
stock Weapon_GiveAndSetAmmo(client,String:classname[],primary=-1,primaryPlayer=0,secondary=0,secondaryPlayer=0){
	
	Weapon_Give(client,classname);
	
	Weapon_SetPrimaryAmmo(client,classname,primary);
	Weapon_SetPrimaryPlayerAmmo(client,classname,primaryPlayer);
	Weapon_SetSecondaryAmmo(client,classname,secondary);
	Weapon_SetSecondaryPlayerAmmo(client,classname,secondaryPlayer);
}

/**
 * Removed all weapons from a player.
 *
 * @param 			Client index of the player you want to remove all weapons.
 * @return			Returns how many weapons have been taken.
 */
stock Weapon_RemoveAll(client) {
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_hMyWeapons");
	
	if(offset < 0){
		return offset;
	}
	
	new entity;
	new removedweapons = 0;
	new bool:success;
	
	for (new offset_add=0;offset_add<128;offset_add+=4){
		
		entity = GetEntDataEnt2(client, offset+offset_add);
		
		if (IsValidEdict(entity)){
			
			success = RemovePlayerItem(client,entity);
			if(!success){continue;}
			RemoveEdict(entity);
			removedweapons++;
		}
	}
	
	return removedweapons;
}

/**
 * Removed all weapons from a player.
 *
 * @param 			Client index of the player you want to remode all weapons.
 * @return			Returns how many weapons have been taken.
 */
stock Weapon_Remove(client,String:weaponClassname[]) {
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_hMyWeapons");
	
	if(offset < 0){
		return offset;
	}
	
	new entity;
	new removedweapons = 0;
	new bool:success;
	new String:classname[32];
	
	for (new offset_add=0;offset_add<128;offset_add+=4){
		
		entity = GetEntDataEnt2(client, offset+offset_add);
		
		if (IsValidEdict(entity)){
			
			GetEdictClassname(entity,classname,sizeof(classname));
			
			if(!StrEqual(weaponClassname,classname,false)) {
				continue;
			}
			
			success = RemovePlayerItem(client,entity);
			if(!success){continue;}
			RemoveEdict(entity);
			removedweapons++;
		}
	}
	
	return removedweapons;
}

/**
 * Sets the primary ammunition (m_iClip1) to the weapon of the client.
 *
 * @param client			Client index.
 * @param weaponClassname	The weapon's classname you want to change the ammunition.
 * @param amount			Set the amount of ammunition.
 * @return					On fail -1 (can't get the right offset or SetEntData failed.
 */
stock Weapon_SetPrimaryAmmo(client,String:weaponClassname[],amount){
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_hMyWeapons");
	
	if(offset < 0){
		return offset;
	}
	
	new entity = -1;
	new String:classname[32];
	
	for(new offset_add=0;offset_add<MAX_WEAPON_OFFSET;offset_add+=4) {
		
		entity = Weapon_GetClassname(client,offset_add,classname,sizeof(classname));
		
		if((entity < 1) || !IsValidEdict(entity)){
			continue;
		}
		
		if(StrEqual(weaponClassname,classname,false)){
			
			SetEntProp(entity, Prop_Data, "m_iClip1", amount);
			return entity;
		}
	}
	
	return -1;
}

/**
 * Sets the secondary ammunition (m_iClip2) to the weapon of the client.
 *
 * @param client			Client index.
 * @param weaponClassname	The weapon's classname you want to change the ammunition.
 * @param amount			Set the amount of ammunition.
 * @return					On fail -1 (can't get the right offset or SetEntData failed.
 */
stock Weapon_SetSecondaryAmmo(client,String:weaponClassname[],amount){
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_hMyWeapons");
	
	if(offset < 0){
		return offset;
	}
	
	new entity = -1;
	new String:classname[32];
	
	for(new offset_add=0;offset_add<MAX_WEAPON_OFFSET;offset_add+=4) {
		
		entity = Weapon_GetClassname(client,offset_add,classname,sizeof(classname));
		
		if((entity < 1) || !IsValidEdict(entity)){
			continue;
		}
		
		if(StrEqual(weaponClassname,classname,false)){
			
			SetEntProp(entity, Prop_Data, "m_iClip2", amount);
			return entity;
		}
	}
	
	return -1;
}

/**
 * Sets the primary player ammunition (m_iAmmo) to the weapon of the client.
 *
 * @param client			Client index.
 * @param weaponClassname	The weapon's classname you want to change the ammunition.
 * @param amount			Set the amount of ammunition.
 * @return					On fail -1 (can't get the right offset or SetEntData failed.
 */
stock Weapon_SetPrimaryPlayerAmmo(client,String:weaponClassname[],amount){
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_iAmmo");
	
	if(offset < 0){
		return offset;
	}
	
	new offset_add = Weapon_GetPrimaryPlayerAmmoOff(client,weaponClassname);
	
	if(offset_add < 0){
		return offset_add;
	}
	
	return SetEntData(client, offset+offset_add, amount, 4, true);
}

/**
 * Sets the secondary player ammunition (m_iAmmo) to the weapon of the client.
 *
 * @param client			Client index.
 * @param weaponClassname	The weapon's classname you want to change the ammunition.
 * @param amount			Set the amount of ammunition.
 * @return					On fail -1 (can't get the right offset or SetEntData failed.
 */
stock Weapon_SetSecondaryPlayerAmmo(client,String:weaponClassname[],amount){
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_iAmmo");
	
	if(offset < 0){
		return offset;
	}
	
	new offset_add = Weapon_GetSecondaryAmmoOffset(client,weaponClassname);
	
	if(offset_add < 0){
		return offset_add;
	}
	
	return SetEntData(client, offset+offset_add, amount, 4, true);
}

/**
 * Returns how much primary ammunition (m_iClip1) the _weapon_ has left in it from a player.
 *
 * @param 	client		Client index.
 * @param 	classname	The classname of the weapon you want to retrieve.
 * @return				Returns the amount of primary ammunition the player has for the given weapon.
 */
stock Weapon_GetPrimaryAmmo(client,String:weaponClassname[]){
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_hMyWeapons");
	
	if(offset < 0){
		return -1;
	}
	
	new entity = -1;
	new String:classname[32];
	
	for(new offset_add=0;offset_add<MAX_WEAPON_OFFSET;offset_add+=4) {
		
		entity = Weapon_GetClassname(client,offset_add,classname,sizeof(classname));
		
		if((entity < 1) || !IsValidEdict(entity)){
			continue;
		}
		
		if(StrEqual(weaponClassname,classname,false)){
			
			return GetEntProp(entity, Prop_Data, "m_iClip1");
		}
	}
	
	return 0;
}

/**
 * Returns how much secondary ammunition (m_iClip2) the _weapon_ has left in it from a player.
 *
 * @param 	client		Client index.
 * @param 	classname	The classname of the weapon you want to retrieve.
 * @return				Returns the amount of primary ammunition the player has for the given weapon.
 */
stock Weapon_GetSecondaryAmmo(client,String:weaponClassname[]){
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_hMyWeapons");
	
	if(offset < 0){
		return -1;
	}
	
	new entity = -1;
	new String:classname[32];
	
	for(new offset_add=0;offset_add<MAX_WEAPON_OFFSET;offset_add+=4) {
		
		entity = Weapon_GetClassname(client,offset_add,classname,sizeof(classname));
		
		if((entity < 1) || !IsValidEdict(entity)){
			continue;
		}
		
		if(StrEqual(weaponClassname,classname,false)){
			
			return GetEntProp(entity, Prop_Data, "m_iClip2");
		}
	}
	
	return 0;
}

/**
 * Returns how much primary ammunition (m_iAmmo) the _player_ has left for the given weapon.
 *
 * @param 	client		Client index.
 * @param 	classname	The classname of the weapon you want to retrieve.
 * @return				Returns the amount of primary ammunition the player has for the given weapon.
 */
stock Weapon_GetPrimaryPlayerAmmo(client,String:weaponClassname[]){
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_iAmmo");
	
	if(offset < 0){
		return -1;
	}
	
	new offset_add = Weapon_GetPrimaryPlayerAmmoOff(client,weaponClassname);
	
	if(offset_add < 0){
		return 0;
	}
	
	return GetEntData(client, offset+offset_add);
}

/**
 * Returns how much secondary ammunition (m_iAmmo) the _player_ has left for the given weapon.
 *
 * @param 	client		Client index.
 * @param 	classname	The classname of the weapon you want to retrieve.
 * @return				Returns the amount of secondary ammunition the player has for the given weapon.
 */
stock Weapon_GetSecondaryPlayerAmmo(client,String:weaponClassname[]){
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_iAmmo");
	
	if(offset < 0){
		return -1;
	}
	
	new offset_add = Weapon_GetSecondaryAmmoOffset(client,weaponClassname);
	
	if(offset_add < 0){
		return 0;
	}
	
	return GetEntData(client, offset+offset_add);
}

/**
 * Gives a player a weapon and returns the entity index of that weapon. This function is fail save, if he already have that weapon instead only the entity index will be returned.
 * WARNING: This works for item_* entitys too, but there is no fail save for them. 
 * 
 * @param client			Client index of the player you want to give the weapon.
 * @param classname			Classname of the weapon or item you want to give. Usualy weapon_***** (example: weapon_357, weapon_awp).
 * @return					The new entity index of the given weapon.
 */
stock Weapon_Give(client, String:classname[]) {
	
	new entity = Weapon_GetEntity(client,classname);
	
	if(entity < 0){
		
		return GivePlayerItem(client, classname);
	}
	
	return entity;
}

/**
 * Returns the entity index of a players weapon. Example: you want from client x the entity index of his weapon_357 (hl2dm).
 *
 * @param 	client		The client index from the player you want to retrieve a weapons entity index.
 * @param 	classname	The classname of the weapon from which you want the entity index. Usualy weapon_***** (example: weapon_357, weapon_awp).
 * @return				Entity index of the weapon from the client with the given classname.
 */
stock Weapon_GetEntity(client,String:weaponClassname[]){
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_hMyWeapons");
	
	if(offset < 0){
		return offset;
	}
	
	new entity = -1;
	new String:classname[32];
	
	for(new offset_add=0;offset_add<MAX_WEAPON_OFFSET;offset_add+=4) {
		
		entity = Weapon_GetClassname(client,offset_add,classname,sizeof(classname));
		
		if(StrEqual(weaponClassname,classname,false)){
			return entity;
		}
	}
	return -1;
	
}

/**
 * Shows all infomation the SMLIB can get for weapons. A list will be printed into the console with all weapons you have on you and their values.
 *
 * @param client		The client index from who you want to get the weapon values.
 * @noreturn
 */
stock Weapon_Debug(client){
	
	PrintToConsole(client,"[SMLIB] Fatching all infomation about your weapons");
	
	new String:classname[32];
	new entity = -1;
	
	for(new offset=0;offset<MAX_WEAPON_OFFSET;offset+=4){
		
		entity = Weapon_GetClassname(client,offset,classname,sizeof(classname));
		PrintToConsole(client,"[SMLIB] offset: %d - %s - entity: %d - Weapon_GetEntity: %d (%d; %d; %d; %d)",offset,classname,entity,Weapon_GetEntity(client,classname),Weapon_GetPrimaryAmmo(client,classname),Weapon_GetPrimaryPlayerAmmo(client,classname),Weapon_GetSecondaryAmmo(client,classname), Weapon_GetSecondaryPlayerAmmo(client,classname));
	}
	
}

/**
 * Returns the entity index and retrieves the classname from a cleint and the offset_add + offset(from m_hMyWeapons).
 *
 * @param 	client			Client index.
 * @param	offset_add		The offset you want to add ontop of the offset from m_hMyWeapons (usualy +4 for each weapon - starts at 0).
 * @param 	classname		Return classname of the given offset_add. Usualy weapon_***** (example: weapon_357, weapon_awp).
 * @param	maxlen			Size of the returned classname variable.
 * @return					Entity index.
 */
stock Weapon_GetClassname(client,offset_add,String:classname[],maxlen){
	
	classname[0] = '\0';
	
	new String:clientNetClass[64];
	
	GetEntityNetClass(client,clientNetClass,sizeof(clientNetClass));
	
	new offset = FindSendPropOffs(clientNetClass, "m_hMyWeapons");
	
	if(offset < 0){
		return offset_add;
	}
	
	new entity = -1;
	
	entity = GetEntDataEnt2(client, offset+offset_add);
	
	if((entity < MaxClients) || !IsValidEdict(entity)){
		return -1;
	}
	
	GetEdictClassname(entity,classname,maxlen);
	return entity;
}

/**
 * Returns the offset m_iPrimaryAmmoType of the given classname of a weapon.
 *
 * @param 	client			Client index.
 * @param	classname		Classname of the weapon you want the offset of. Usualy weapon_***** (example: weapon_357, weapon_awp).
 * @return 					Integer - offset of the weapons m_iPrimaryAmmoType.
 */
stock Weapon_GetPrimaryPlayerAmmoOff(client,String:classname[]) {
	
	new entity = Weapon_GetEntity(client,classname);
	
	if((entity < 1) || !IsValidEntity(entity)){
		return -1;
	}
	
	new offset = GetEntProp(entity,Prop_Data,"m_iPrimaryAmmoType");
	
	if(offset < 0){
		
		return offset;
	}
	
	return (offset*4);
}

/**
 * Returns the offset m_iSecondaryAmmoType of the given classname of a weapon from a client.
 *
 * @param 	client			Client index.
 * @param	classname		Classname of the weapon you want the offset of. Usualy weapon_***** (example: weapon_357, weapon_awp).
 * @return 					Integer - offset of the weapons m_iSecondaryAmmoType.
 */
stock Weapon_GetSecondaryAmmoOffset(client,String:classname[]){
	
	new entity = Weapon_GetEntity(client,classname);
	
	if((entity < 1) || !IsValidEntity(entity)){
		return -1;
	}
	
	new offset = GetEntProp(entity,Prop_Data,"m_iSecondaryAmmoType");
	
	if(offset < 0){
		
		return offset;
	}
	
	return (offset*4);
}

/**
 * Returns the weapons owner client index.
 *
 * @param 	entity			Weapon entity.
 * @return 					Owner client index from the given weapon.
 */
stock Weapon_GetOwner(entity){
	
	new client = GetEntPropEnt(entity, Prop_Send, "m_hOwner");
	
	if(Client_IsPlayer(client)){
		
		return client;
	}
	
	return -1;
}