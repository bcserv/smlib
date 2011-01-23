#if defined _smlib_world_included
	#endinput
#endif
#define _smlib_world_included

#include <smlib>

/*
 * Gets the world max size
 *
 * @param vec		Vector buffer
 * @noreturn		
 */
stock World_GetMaxs(Float:vec[3]) {
	
	GetEntPropVector(0, Prop_Data, "m_WorldMaxs", vec);
}