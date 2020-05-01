#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Base class
#include "Engine/GameInstance.h"

// Interfaces
#include "Interfaces/OnlineSessionInterface.h"

// Generated
#include "GmInstMain.generated.h"

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

	FPlayerInfo()
	{
		bHost = false;
		bReady = false;
		PlayerName = FText::FromString("");
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
		virtual void SearchServer();

	UFUNCTION(BlueprintCallable, Category = "Events")
		virtual void JoinServer(const FText& inServerName);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		FName ServerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		FString MapLobbyString;

	UPROPERTY(BlueprintReadWrite, Category = "Servers")
		TArray<FServerInfo> Servers;

	UPROPERTY(BlueprintReadWrite, Category = "Servers")
		TArray<FPlayerInfo> Players;

};
