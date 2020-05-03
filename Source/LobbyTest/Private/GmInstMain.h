#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Base class
#include "Engine/GameInstance.h"

// Libraries
#include "Structures.h"

// Interfaces
#include "Interfaces/OnlineSessionInterface.h"

// Generated
#include "GmInstMain.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerListUpdated, const TArray<FServerInfo>&, inServers);

UCLASS()
class UGmInstMain : public UGameInstance
{
	GENERATED_BODY()
	
public:

	// Constructor
	UGmInstMain(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Events")
		virtual void CreateServer(const FServerInfo& inServerInfo, const FText& inPlayerName);

	UFUNCTION(BlueprintCallable, Category = "Events")
		virtual void JoinServer(const FText& inServerName, const FText& inPlayerName);

	UFUNCTION(BlueprintCallable, Category = "Events")
		virtual void SearchServer();

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Server")
		FServerListUpdated OnServerListUpdated;

protected:

	virtual void Init() override;
	virtual void OnCreateSessionComplete(FName inServerName, bool Success);
	virtual void OnFindSessionComplete(bool Success);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Log")
		void PrintOnLog(const FString& String1, const FString& String2 = "", bool bScreen = true, bool bLog = true, FColor Color = FColor::White, float Time = 5.0f);


	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	UPROPERTY(BlueprintReadWrite, Category = "Names")
		FName ServerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		FString MapLobbyString;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
		FText PlayerName;

	UPROPERTY(BlueprintReadWrite, Category = "Servers")
		TArray<FServerInfo> Servers;

};
