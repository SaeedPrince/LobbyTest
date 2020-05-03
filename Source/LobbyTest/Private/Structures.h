#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Library
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Generated
#include "Structures.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "Player Info")
		FText PlayerName;

	UPROPERTY(BlueprintReadWrite, Category = "Player Info")
		bool bHost;

	UPROPERTY(BlueprintReadWrite, Category = "Player Info")
		bool bReady;

	UPROPERTY(BlueprintReadWrite, Category = "Player Info")
		class APlayerController* inPlctCtrl;

	FPlayerInfo()
	{
		bHost = false;
		bReady = false;
		PlayerName = FText::FromString("");
		inPlctCtrl = nullptr;
	}
};

USTRUCT(BlueprintType)
struct FServerInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Server Info")
		bool bUsePass;

	UPROPERTY(BlueprintReadWrite, Category = "Server Info")
		FString ServerMap;

	UPROPERTY(BlueprintReadWrite, Category = "Server Info")
		FText ServerName;

	UPROPERTY(BlueprintReadWrite, Category = "Server Info")
		FText ServerPassword;

	UPROPERTY(BlueprintReadWrite, Category = "Server Info")
		int32 MaxPlayers;

	FServerInfo()
	{
		bUsePass = false;
		ServerName = FText::FromString("");
		ServerPassword = FText::FromString("");
		ServerMap = "MapPrototype";
		MaxPlayers = 4;
	}
};

