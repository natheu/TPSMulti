#include "ShooterPS.h"
#include "PlayerGI.h"
#include "../Characters/ShooterCharacter.h"
#include "DeathMatchGS.h"
#include "Net/UnrealNetwork.h"

#include "DeathMatchGM.h"
#include "Net/UnrealNetwork.h"


void AShooterPS::BeginPlay()
{
	Super::BeginPlay();

	ADeathMatchGS* GameState = GetWorld()->GetGameState<ADeathMatchGS>();
	GameState->OnResetAfterDelay.AddLambda([this]() { Reset(); });
	CurrentTeam = ETeam::Blue;
}

void AShooterPS::CopyProperties(class APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (PlayerState)
	{
		AShooterPS* ShooterPlayerState = Cast<AShooterPS>(PlayerState);
		if (ShooterPlayerState)
		{
			ShooterPlayerState->NbKill = NbKill;
			ShooterPlayerState->NbKill = NbDeath;
			ShooterPlayerState->UserName = UserName;
			ShooterPlayerState->CurrentTeam = CurrentTeam;
		}
	}
}

void AShooterPS::OverrideWith(class APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);
	if (PlayerState)
	{
		AShooterPS* ShooterPlayerState = Cast<AShooterPS>(PlayerState);

		if (ShooterPlayerState)
		{
			NbKill = ShooterPlayerState->NbKill;
			NbDeath = ShooterPlayerState->NbDeath;
			UserName = ShooterPlayerState->UserName;
		}
	}
}

void AShooterPS::Reset()
{
	NbKill = 0;
	NbDeath = 0;
}

//	-	-	-	PlayerIsReady	-	-	-

void AShooterPS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShooterPS, bIsPlayerReady);
	DOREPLIFETIME(AShooterPS, CurrentTeam);
	DOREPLIFETIME(AShooterPS, UserName);
	DOREPLIFETIME(AShooterPS, NbKill);
	DOREPLIFETIME(AShooterPS, NbDeath);
}

bool AShooterPS::Server_PlayerIsReady_Validate(const FSPlayerInfo& PlayerInfo)
{
	return true;
}

void AShooterPS::Server_PlayerIsReady_Implementation(const FSPlayerInfo& PlayerInfo)
{
	bIsPlayerReady = true;
	CurrentTeam = PlayerInfo.Team;
	UserName = PlayerInfo.Name;

	UE_LOG(LogTemp, Warning, TEXT("bIsPlayerReady = true (Server)"));
	UE_LOG(LogTemp, Warning, TEXT("PlayerName is set to %s (Server)"), *UserName);
	UE_LOG(LogTemp, Warning, TEXT("CurrentTeam is set to %d (Server)"), CurrentTeam);

	Client_OnPlayerReady();

	UE_LOG(LogTemp, Warning, TEXT("Calling RPC Client"));

	ADeathMatchGM* MyGameMode = Cast<ADeathMatchGM>(GetWorld()->GetAuthGameMode());
	if (MyGameMode != nullptr)
		MyGameMode->CheckPlayersAreReady();
}

void AShooterPS::OnPlayerReady_Implementation()
{
}

void AShooterPS::Client_OnPlayerReady_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("RPC OnPlayerReady received from Server"));
	OnPlayerReady();
}

bool AShooterPS::Server_SelectBlueTeam_Validate(const FString& Name)
{
	return true;
}

void AShooterPS::Server_SelectBlueTeam_Implementation(const FString& Name)
{
	UE_LOG(LogTemp, Warning, TEXT("%s SelectBlueTeam"), *Name);
	MulticastSelectBlueTeam(Name);
}

bool AShooterPS::Server_SelectRedTeam_Validate(const FString& Name)
{
	return true;
}

void AShooterPS::Server_SelectRedTeam_Implementation(const FString& Name)
{
	UE_LOG(LogTemp, Warning, TEXT("%s SelectRedTeam"), *Name);
	MulticastSelectRedTeam(Name);
}

void AShooterPS::MulticastSelectBlueTeam_Implementation(const FString& Name)
{
	UE_LOG(LogTemp, Warning, TEXT("%s SelectBlueTeam"), *Name);
	Event_TeamUpdateBlue(Name);
}

void AShooterPS::MulticastSelectRedTeam_Implementation(const FString& Name)
{
	UE_LOG(LogTemp, Warning, TEXT("%s SelectRedTeam"), *Name);
	Event_TeamUpdateRed(Name);
}
