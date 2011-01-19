#if defined _smlib_game_included
	#endinput
#endif
#define _smlib_game_included

/*
* End's the game and displays the scoreboard with intermission time.
*
* @noparam
* @return				True on success, false otherwise
*/
stock bool:Game_End()
{
	new game_end = FindEntityByClassname(-1, "game_end");
	
	if (game_end == -1) {
		game_end = CreateEntityByName("game_end");
		
		if (game_end == -1) {
			ThrowError("Unable to find or create entity \"game_end\"");
		}
	}

	return AcceptEntityInput(game_end, "EndGame");
}
