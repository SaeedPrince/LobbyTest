#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Base class
#include "GameFramework/GameModeBase.h"

// Libraries
#include "Structures.h"

// Generated
#include "GmmdLobby.generated.h"

UCLASS()
class AGmmdLobby : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	// Constructor
	AGmmdLobby();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		TArray<FPlayerInfo> GetPlayers();

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Events")
		void AddPlayer(const FPlayerInfo& inPlayerInfo);

	UFUNCTION(BlueprintCallable, Category = "Events")
		void RemoveAllPlayers();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void RemovePlayer(const FText& inPlayerName);

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Servers")
		TArray<FPlayerInfo> Players;

private:

	// Functions
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Internal Getter", meta = (AllowPrivateAccess = "true"))
		int32 _GetPlayerIndex(const FText& inPlayerName);

};
