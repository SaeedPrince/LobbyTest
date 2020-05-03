#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Base class
#include "GameFramework/PlayerController.h"

// Libraries
#include "Structures.h"

// Generated
#include "PlctStart.generated.h"

UCLASS()
class APlctStart : public APlayerController
{
	GENERATED_BODY()
	
public:

	// Constructors
	APlctStart();

	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		FString GetReplicatedPlayerName();

protected:

	// Properties
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Replicated")
		FString PlayerName;


};
