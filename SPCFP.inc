/*
	SetPlayerColorForPlayer

	@author: 	hotspicytaco
	
	please love Jelly23 for helping me understand this black magic
	over Discord
*/

#if defined _SPCFP_included
    #endinput
#endif
#define _SPCFP_included

#if !defined PAWNRAKNET_INC_
	#error You must have Pawn.RakNet included to use this library
#endif

#if !defined _samp_included
	#error SPCFP depends on a_samp to function, please include it first
#endif

// native SetPlayerColorForPlayer(for_player, playerid, color);
// native ResetPlayerColorForPlayer(for_player, playerid);

// More checks to be added

static SPCFP_current_color[MAX_PLAYERS][MAX_PLAYERS];

stock SetPlayerColorForPlayer(for_player, playerid, color)
{
	new BitStream:SPCFP_bs = new BS_New();

	BS_WriteValue(
		SPCFP_bs,
		PR_UINT16, playerid,
		PR_UINT32, color
	);

	// GetPlayerColor might be affected by this RPC, just so you know... I am not sure
	// A workaround might be needed
	
	BS_RPC(SPCFP_bs, for_player, 0x48);
	BS_Delete(SPCFP_bs);

	SPCFP_current_color[playerid][for_player] = color;
	return 1;
}

stock ResetPlayerColorForPlayer(for_player, playerid)
{
	new BitStream:SPCFP_bs = new BS_New();

	BS_WriteValue(
		SPCFP_bs,
		PR_UINT16, playerid,
		PR_UINT32, GetPlayerColor(playerid)
	);

	BS_RPC(SPCFP_bs, for_player, 0x48);
	BS_Delete(SPCFP_bs);
	return 1;
}
