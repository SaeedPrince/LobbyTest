#include "GmInstMain.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"

UGmInstMain::UGmInstMain(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MapLobbyString = "MapLobby";
	ServerName = FName("ServerName");
}

void UGmInstMain::Init()
{
	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get())
	{
		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGmInstMain::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UGmInstMain::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UGmInstMain::OnJoinSessionComplete);
		}
	}
}

void UGmInstMain::OnCreateSessionComplete(FName inServerName, bool Success)
{
	if (Success)
	{
		FString str1 = "/Game/Maps/";
		FString str2 = UKismetStringLibrary::Concat_StrStr(str1, MapLobbyString);
		FString str3 = "?listen";
		FString str4 = UKismetStringLibrary::Concat_StrStr(str2, str3);
		GetWorld()->ServerTravel(str4);
		PrintOnLog("Create Session Successful.");
	}
	else
	{
		PrintOnLog("Create Session Failed.");
	}
}

void UGmInstMain::OnFindSessionComplete(bool Success)
{
	Servers.Empty();
	if (Success)
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		if (SearchResults.Num() > 0)
		{
			for (FOnlineSessionSearchResult Result : SearchResults)
			{
				if (Result.IsValid())
				{
					FOnlineSession onlSession = Result.Session;
					FOnlineSessionSettings settings = onlSession.SessionSettings;
					FString srvString;
					if (settings.Get(ServerName, srvString))
					{
						FServerInfo info = FServerInfo();
						info.ServerName = FText::FromString(srvString);
						Servers.Add(info);
					}
				}
			}
			OnServerListUpdated.Broadcast(Servers);
		}
	}
}

void UGmInstMain::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAddress;
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (JoinAddress != "")
		{
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
			/*
			FPlayerInfo plInfo = FPlayerInfo();
			APlayerState* plState = PController->PlayerState;
			if (IsValid(plState))
			{
				plInfo.PlayerName = FText::FromString(plState->GetPlayerName());
				Players.Add(plInfo);
			}
			*/
		}
		/*
		FOnlineSessionSettings* onlSess = SessionInterface->GetSessionSettings(SessionName);
		FString PlayerName;
		if (onlSess->Get(FName("PlayerName"), PlayerName))
		{
			PrintOnLog("PlayerName=", PlayerName);
		}
		*/
	}
}

void UGmInstMain::CreateServer(const FServerInfo& inServerInfo, const FText& inPlayerName)
{
	Players.Empty();
	if (SessionInterface.IsValid())
	{
		FString srvString = inServerInfo.ServerName.ToString();
		FName srvName = UKismetStringLibrary::Conv_StringToName(srvString);
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bIsDedicated = false;
		SessionSettings.bIsLANMatch = false;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.NumPublicConnections = 9;
		SessionSettings.Set<FString>(ServerName, srvString, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionInterface->CreateSession(0, srvName, SessionSettings);
		/*
		FPlayerInfo plInfo = FPlayerInfo();
		plInfo.PlayerName = inPlayerName;
		plInfo.bHost = true;
		plInfo.bReady = true;
		Players.Add(plInfo);
		*/
	}
	else
	{
		PrintOnLog("SessionInterface invalid.");
	}
}

void UGmInstMain::SearchServer()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = false;
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UGmInstMain::JoinServer(const FText& inServerName)
{
	TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
	for (int32 i = 0; i < Servers.Num(); i++)
	{
		FText srvName = Servers[i].ServerName;
		if (srvName.EqualTo(inServerName))
		{
			//SearchResults[i].Session.SessionSettings.Set<FString>(FName("PlayerName"), "AAA", EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
			SessionInterface->JoinSession(0, UKismetStringLibrary::Conv_StringToName(inServerName.ToString()), SearchResults[i]);
			break;
		}
	}
}