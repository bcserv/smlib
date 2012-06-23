#if defined _smlib_pluginmanager_included
	#endinput
#endif
#define _smlib_pluginmanager_included

#include <sourcemod>
#include <smlib/files>

stock
	Handle:Plugin_Handle = INVALID_HANDLE,
	String:Plugin_Name[256],
	String:Plugin_Author[256],
	String:Plugin_Description[256],
	String:Plugin_Version[256],
	String:Plugin_VersionDescription[256],
	Handle:Plugin_VersionCvar,
	String:Plugin_EnableDescription[256],
	String:Plugin_Url[256],
	String:Plugin_Tag[256],
	String:Plugin_Prefix[256],
	String:Plugin_FileName[PLATFORM_MAX_PATH];

stock PluginManager_Initialize(const String:prefix[], const String:tag[], bool:loadTranslations=false, bool:autoConfig=true)
{
	Plugin_Handle = GetMyHandle();
	GetPluginInfo(Plugin_Handle, PlInfo_Name, Plugin_Name,			sizeof(Plugin_Name));
	GetPluginInfo(Plugin_Handle, PlInfo_Name, Plugin_Author,		sizeof(Plugin_Author));
	GetPluginInfo(Plugin_Handle, PlInfo_Name, Plugin_Description,	sizeof(Plugin_Description));
	GetPluginInfo(Plugin_Handle, PlInfo_Name, Plugin_Version,		sizeof(Plugin_Version));
	Format(
		Plugin_VersionDescription,
		sizeof(Plugin_VersionDescription),
		"\n  || %s ('%s') v%s\n  || Builddate:'%s - %s'\n  || Author(s):'%s'\n  || URL:'%s'\n  || Description:'%s'\n",
		Plugin_Name,
		Plugin_FileName,
		Plugin_Version,
		__TIME__,
		__DATE__,
		Plugin_Author,
		Plugin_Url,
		Plugin_Description
	);
	GetPluginInfo(Plugin_Handle, PlInfo_Name, Plugin_Url,			sizeof(Plugin_Url));
	strcopy(Plugin_Prefix,sizeof(Plugin_Prefix),prefix);
	strcopy(Plugin_Tag,sizeof(Plugin_Tag),tag);
	GetPluginFilename(Plugin_Handle, Plugin_FileName,				sizeof(Plugin_FileName));

	if (loadTranslations) {
		decl String:path[PLATFORM_MAX_PATH];
		Format(path, sizeof(path), "%s.phrases", prefix);
		File_LoadTranslations(path, true);
	}

	if (autoConfig) {
		AutoExecConfig(true);
	}
	
	Plugin_VersionCvar = PluginManager_CreateConvar("version", Plugin_Version, Plugin_VersionDescription, FCVAR_PLUGIN|FCVAR_DONTRECORD|FCVAR_NOTIFY);
	//override old cvar in case of late load (this is needed to kick the engine in the ass, so it'll broadcast its value again)
	SetConVarString(Plugin_VersionCvar,Plugin_Version);
}

stock Handle:PluginManager_CreateConvar(const String:name[], const String:defaultValue[], const String:description[]="", flags=0, bool:hasMin=false, Float:min=0.0, bool:hasMax=false, Float:max=0.0)
{
	flags |= FCVAR_PLUGIN;

	decl String:conVarName[256];
	Format(conVarName, sizeof(conVarName), "%s_%S", Plugin_Prefix, name);

	return CreateConVar(conVarName, defaultValue, description, flags, hasMin, min, hasMax, max);
}

stock PluginManager_RegServerCmd(const String:name[], SrvCmd:callback, const String:description[]="", minArgs=0, const String:usage[]="", flags=0)
{
	flags |= FCVAR_PLUGIN;

	RegAdminCmd(name, callback, description, flags);
}

stock PluginManager_RegConsoleCmd(const String:name[], ConCmd:callback, const String:description[]="", minArgs=0, const String:usage[]="", flags=0)
{
	flags |= FCVAR_PLUGIN;

	RegAdminCmd(name, callback, description, flags);
}

stock PluginManager_RegAdminCmd(const String:name[], ConCmd:callback, adminflags, const String:description[]="", minArgs=0, const String:usage[]="", const String:group[]="", flags=0)
{
	flags |= FCVAR_PLUGIN;

	RegAdminCmd(name, callback, description, groups, flags);
}
