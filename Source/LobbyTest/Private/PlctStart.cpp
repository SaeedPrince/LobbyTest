#include "PlctStart.h"
#include "Net/UnrealNetwork.h"

APlctStart::APlctStart()
{
	bReplicates = true;
}

void APlctStart::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(APlctStart, PlayerName);
}

FString APlctStart::GetReplicatedPlayerName()
{
	return PlayerName;
}