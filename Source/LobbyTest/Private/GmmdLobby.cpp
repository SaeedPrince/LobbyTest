#include "GmmdLobby.h"

AGmmdLobby::AGmmdLobby()
{

}

TArray<FPlayerInfo> AGmmdLobby::GetPlayers()
{
	return Players;
}

void AGmmdLobby::AddPlayer(const FPlayerInfo& inPlayerInfo)
{
	Players.Add(inPlayerInfo);
}

void AGmmdLobby::RemoveAllPlayers()
{
	Players.Empty();
}

void AGmmdLobby::RemovePlayer(const FText& inPlayerName)
{
	int32 i = _GetPlayerIndex(inPlayerName);
	if (i != -1)
	{
		Players.RemoveAt(i);
	}
}

int32 AGmmdLobby::_GetPlayerIndex(const FText& inPlayerName)
{
	int32 retVal = -1;
	for (int32 i = 0; i < Players.Num(); i++)
	{
		if (Players[i].PlayerName.EqualTo(inPlayerName))
		{
			retVal = i;
			break;
		}
	}
	return retVal;
}
