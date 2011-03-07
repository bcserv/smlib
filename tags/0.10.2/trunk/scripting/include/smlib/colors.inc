#if defined _smlib_colors_included
	#endinput
#endif
#define _smlib_colors_included

#include <sourcemod>
#include <smlib/arrays>
#include <smlib/teams>

#define CHATCOLOR_NOSUBJECT -2
#define SMLIB_COLORS_GAMEDATAFILE "smlib_colors.games"

enum ChatColorSubjectType
{
	ChatColorSubjectType_none		= -3,

	// Subject/Team colors
	ChatColorSubjectType_player		= -2,
	ChatColorSubjectType_undefined	= -1,
	ChatColorSubjectType_world		= 0
	// Anything higher is a specific team
}

enum ChatColorInfo
{
	ChatColorInfo_Code,
	ChatColorInfo_Alternative,
	bool:ChatColorInfo_Supported,
	ChatColorSubjectType:ChatColorInfo_SubjectType
};

enum ChatColor
{
	ChatColor_Normal,
	ChatColor_Orange,
	ChatColor_Red,
	ChatColor_RedBlue,
	ChatColor_Blue,
	ChatColor_BlueRed,
	ChatColor_Team,
	ChatColor_Lightgreen,
	ChatColor_Gray,
	ChatColor_Green,
	ChatColor_Olivegreen,
	ChatColor_Black
}

static String:chatColorTags[][] = {
	"N",	// Normal
	"O",	// Orange
	"R",	// Red
	"RB",	// Red, Blue
	"B",	// Blue
	"BR",	// Blue, Red
	"T",	// Team
	"L",	// Light green
	"GRA",	// GRAy 
	"G",	// Green
	"OG",	// Olive green
	"BLA"	// BLAck
};

static String:chatColorNames[][] = {
	"normal",		// Normal
	"orange",		// Orange
	"red",			// Red
	"redblue",		// Red, Blue
	"blue",			// Blue
	"bluered",		// Blue, Red
	"team",			// Team
	"lightgreen",	// Light green
	"gray",			// GRAy 
	"green",		// Green
	"olivegreen",	// Olive green
	"black"			// BLAck
};

static chatColorInfo[][ChatColorInfo] =
{
	// Code , alternative	, Is Supported?	Chat color subject type 		   Color name
	{ '\x01', -1/* None	 */	, true,			ChatColorSubjectType_none,	},	// Normal
	{ '\x01', 0	/* None	 */	, true,			ChatColorSubjectType_none,	},	// Orange
	{ '\x03', 9	/* Green */	, true,			ChatColorSubjectType:2		},	// Red
	{ '\x03', 4	/* Blue	 */	, true,			ChatColorSubjectType:2		},	// Red, Blue
	{ '\x03', 9	/* Green */	, true,			ChatColorSubjectType:3		},	// Blue
	{ '\x03', 2	/* Red	 */	, true,			ChatColorSubjectType:3		},	// Blue, Red
	{ '\x03', 9	/* Green */	, true,			ChatColorSubjectType_player	},	// Team
	{ '\x03', 9	/* Green */	, true,			ChatColorSubjectType_world	},	// Light green
	{ '\x03', 9	/* Green */	, true,			ChatColorSubjectType_undefined},// GRAy 
	{ '\x04', 0	/* Normal*/	, true,			ChatColorSubjectType_none	},	// Green
	{ '\x05', 9	/* Green */	, true,			ChatColorSubjectType_none	},	// Olive green
	{ '\x06', 9	/* Green */	, true,			ChatColorSubjectType_none	}	// BLAck
};

static bool:checkTeamPlay			= false;
static Handle:mp_teamplay			= INVALID_HANDLE;
static bool:isSayText2_supported	= true;
static chatSubject					= CHATCOLOR_NOSUBJECT;

/**
 * Sets the subject (a client) for the chat color parser.
 * Call this before Color_ParseChatText() or Client_PrintToChat().
 *
 * @param client			Client Index/Subject
 * @noreturn
 */
stock Color_ChatSetSubject(client)
{
	chatSubject = client;
}

/**
 * Clears the subject used for the chat color parser.
 * Call this after Color_ParseChatText().
 *
 * @noreturn
 */
stock Color_ChatClearSubject()
{
	chatSubject = CHATCOLOR_NOSUBJECT;
}

/**
 * Parses a chat string and converts all color tags to color codes.
 * This is a very powerful function that works recursively over the color information
 * table. The support colors are hardcoded, but can be overriden for each game by
 * creating the file gamedata/smlib_colors.games.txt.
 *
 * @param str				Chat String.
 * @param subject			Output Buffer
 * @param size				Output Buffer size
 * return
 */
stock Color_ParseChatText(const String:str[], String:buffer[], size)
{
	new
		bool:inBracket = false,
		x = 0, x_buf = 0, x_tag = 0,
		currentColor = '\x01', // Initialize with normal color
		code = -1,
		subject = CHATCOLOR_NOSUBJECT;

	decl String:sTag[4] = "";

	size--;
	buffer[x_buf++] = '\x01';

	while (str[x] != '\0') {

		if (size == x_buf) {
			break;
		}

		new char = str[x++];
		
		if (inBracket) {
			if (char == '}' || x_tag > 2) {
				inBracket = false;
				sTag[x_tag] = '\0';
				x_tag = 0;
				
				if (char == '}') {
					code = Color_TagToCode(sTag, subject);
					if (code == 0) {
						buffer[x_buf+1] = '\0';
						x_buf = Format(buffer, size, "%s{%s}", buffer, sTag);
						continue;
					}
					else if (code != currentColor) {
						buffer[x_buf++] = code;
						currentColor = code;
					}
				}
				else {
					buffer[x_buf+1] = '\0';
					x_buf = Format(buffer, size, "%s{%s%c", buffer, sTag, char);
				}
			}
			else if (char == '{' && !x_tag) {
				buffer[x_buf++] = '{';
				inBracket = false;
			}
			else {
				sTag[x_tag++] = char;
			}
		}
		else if (char == '{') {
			inBracket = true;
		}
		else {
			buffer[x_buf++] = char;
		}
	}

	buffer[x_buf] = '\0';
	
	return subject;
}

/**
 * Converts a chat color tag to its code character.
 *
 * @param tag				Color Tag String.
 * @param subject			Subject variable to pass
 * @return					Chat Color Code char or 0 if the tag couldn't be found.
 */
stock Color_TagToCode(const String:tag[], &subject=-1){
	new n = Array_FindString(chatColorTags, sizeof(chatColorTags), tag);

	if (n == -1) {
		return 0;
	}

	Color_GetChatColorInfo(n, subject);

	return chatColorInfo[n][ChatColorInfo_Code];
}

/**
 * Strips all color control characters in a string.
 * The Output buffer can be the same as the input buffer.
 * Original code by Psychonic, thanks.
 *
 * @param input				Input String.
 * @param output			Output String.
 * @param size				Max Size of the Output string
 * @noreturn
 */
stock Color_StripFromChatText(const String:input[], String:output[], size)
{
	new x = 0;
	for (new i=0; input[i] != '\0'; i++) {
	
		if (x+1 == size) {
			break;
		}

		new char = input[i];
		
		if (char > 0x08) {
			output[x++] = char;
		}
	}
	
	output[x] = '\0';
}

static stock Color_ChatInitialize()
{
	static initialized = false;

	if (initialized) {
		return;
	}

	initialized = true;

	decl String:gameFolderName[32];
	GetGameFolderName(gameFolderName, sizeof(gameFolderName));

	chatColorInfo[ChatColor_Black][ChatColorInfo_Supported]		= false;

	if (strncmp(gameFolderName, "left4dead", 9, false) != 0 &&
		!StrEqual(gameFolderName, "cstrike", false) &&
		!StrEqual(gameFolderName, "tf", false))
	{
		chatColorInfo[ChatColor_Lightgreen][ChatColorInfo_Supported]= false;
		chatColorInfo[ChatColor_Gray][ChatColorInfo_Supported]		= false;
	}

	if (StrEqual(gameFolderName, "tf", false)) {
		chatColorInfo[ChatColor_Black][ChatColorInfo_Supported]		= true;

		chatColorInfo[ChatColor_Gray][ChatColorInfo_Code]			= '\x01';
		chatColorInfo[ChatColor_Gray][ChatColorInfo_SubjectType]	= ChatColorSubjectType_none;
	}
	else if (strncmp(gameFolderName, "left4dead", 9, false) == 0) {
		chatColorInfo[ChatColor_Red][ChatColorInfo_SubjectType]		= ChatColorSubjectType:3;
		chatColorInfo[ChatColor_RedBlue][ChatColorInfo_SubjectType]	= ChatColorSubjectType:3;
		chatColorInfo[ChatColor_Blue][ChatColorInfo_SubjectType]	= ChatColorSubjectType:2;
		chatColorInfo[ChatColor_BlueRed][ChatColorInfo_SubjectType]	= ChatColorSubjectType:2;

		chatColorInfo[ChatColor_Orange][ChatColorInfo_Code]			= '\x04';
		chatColorInfo[ChatColor_Green][ChatColorInfo_Code]			= '\x05';
	}
	else if (StrEqual(gameFolderName, "hl2mp", false)) {
		chatColorInfo[ChatColor_Red][ChatColorInfo_SubjectType]		= ChatColorSubjectType:3;
		chatColorInfo[ChatColor_RedBlue][ChatColorInfo_SubjectType]	= ChatColorSubjectType:3;
		chatColorInfo[ChatColor_Blue][ChatColorInfo_SubjectType]	= ChatColorSubjectType:2;
		chatColorInfo[ChatColor_BlueRed][ChatColorInfo_SubjectType]	= ChatColorSubjectType:2;
		chatColorInfo[ChatColor_Black][ChatColorInfo_Supported]		= true;

		checkTeamPlay												= true;
	}
	else if (StrEqual(gameFolderName, "dod", false)) {
		chatColorInfo[ChatColor_Gray][ChatColorInfo_Code]			= '\x01';
		chatColorInfo[ChatColor_Gray][ChatColorInfo_SubjectType]	= ChatColorSubjectType_none;

		chatColorInfo[ChatColor_Black][ChatColorInfo_Supported]		= true;
		chatColorInfo[ChatColor_Orange][ChatColorInfo_Supported]	= false;
	}

	if (GetUserMessageId("SayText2") == INVALID_MESSAGE_ID) {
		isSayText2_supported = false;
	}

	decl String:path_gamedata[PLATFORM_MAX_PATH];
	BuildPath(Path_SM, path_gamedata, sizeof(path_gamedata), "gamedata/%s.txt", SMLIB_COLORS_GAMEDATAFILE);

	if (FileExists(path_gamedata)) {
		new Handle:gamedata = INVALID_HANDLE;
		
		if ((gamedata = LoadGameConfigFile(SMLIB_COLORS_GAMEDATAFILE)) != INVALID_HANDLE) {

			decl String:keyName[32], String:buffer[6];
			
			for (new i=0; i < sizeof(chatColorNames); i++) {

				Format(keyName, sizeof(keyName), "%s_code",			chatColorNames[i]);
				if (GameConfGetKeyValue(gamedata, keyName, buffer, sizeof(buffer))) {
					chatColorInfo[i][ChatColorInfo_Code]			= StringToInt(buffer);
				}

				Format(keyName, sizeof(keyName), "%s_alternative",	chatColorNames[i]);
				if (GameConfGetKeyValue(gamedata, keyName, buffer, sizeof(buffer))) {
					chatColorInfo[i][ChatColorInfo_Alternative]		= buffer[0];
				}

				Format(keyName, sizeof(keyName), "%s_supported",	chatColorNames[i]);
				if (GameConfGetKeyValue(gamedata, keyName, buffer, sizeof(buffer))) {
					chatColorInfo[i][ChatColorInfo_Supported]		= StrEqual(buffer, "true");
				}

				Format(keyName, sizeof(keyName), "%s_subjecttype",	chatColorNames[i]);
				if (GameConfGetKeyValue(gamedata, keyName, buffer, sizeof(buffer))) {
					chatColorInfo[i][ChatColorInfo_SubjectType]		= ChatColorSubjectType:StringToInt(buffer);
				}
			}

			if (GameConfGetKeyValue(gamedata, "checkteamplay", buffer, sizeof(buffer))) {
				checkTeamPlay = StrEqual(buffer, "true");
			}

			CloseHandle(gamedata);
		}
	}

	mp_teamplay = FindConVar("mp_teamplay");
}

static stock Color_GetChatColorInfo(&index, &subject=CHATCOLOR_NOSUBJECT)
{
	Color_ChatInitialize();

	if (index == -1) {
		index = 0;
	}

	while (!chatColorInfo[index][ChatColorInfo_Supported]) {

		new alternative = chatColorInfo[index][ChatColorInfo_Alternative];

		if (alternative == -1) {
			index = 0;
			break;
		}

		index = alternative;
	}

	if (index == -1) {
		index = 0;
	}

	new newSubject = CHATCOLOR_NOSUBJECT;
	new ChatColorSubjectType:type = chatColorInfo[index][ChatColorInfo_SubjectType];

	switch (type) {

		case ChatColorSubjectType_none: {
		}
		case ChatColorSubjectType_player: {
			newSubject = chatSubject;
		}
		case ChatColorSubjectType_undefined: {
			newSubject = -1;
		}
		case ChatColorSubjectType_world: {
			newSubject = 0;
		}
		default: {

			if (!checkTeamPlay || GetConVarBool(mp_teamplay)) {

				if (subject > 0 && subject <= MaxClients) {

					if (GetClientTeam(subject) == _:type) {
						newSubject = subject;
					}
				}
				else if (subject == CHATCOLOR_NOSUBJECT) {
					new client = Team_GetAnyClient(_:type);

					if (client != -1) {
						newSubject = client;
					}
				}
			}
		}
	}

	if (type > ChatColorSubjectType_none &&
		((subject != CHATCOLOR_NOSUBJECT && subject != newSubject) || newSubject == CHATCOLOR_NOSUBJECT || !isSayText2_supported))
	{
		index = chatColorInfo[index][ChatColorInfo_Alternative];
		newSubject = Color_GetChatColorInfo(index, subject);
	}

	// Only set the subject if there is no subject set already.
	if (subject == CHATCOLOR_NOSUBJECT) {
		subject = newSubject;
	}
	
	return newSubject;
}
