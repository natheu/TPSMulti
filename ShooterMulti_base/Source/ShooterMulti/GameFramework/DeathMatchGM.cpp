#include "DeathMatchGM.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ShooterPS.h"
#include "DeathMatchGS.h"


void ADeathMatchGM::BeginPlay()
{
	Super::BeginPlay();
	/*if (GetLocalRole() == ENetRole::ROLE_Authority)
		undeadDirector = Cast<AUndeadDirector>(GetWorld()->SpawnActor(AUndeadDirector::StaticClass()));*/
}
void ADeathMatchGM::Respawn(APlayerController* PlayerController)
{
	RestartPlayerAtPlayerStart(PlayerController, ChoosePlayerStart(PlayerController));
}

void ADeathMatchGM::Quit()
{
	FGenericPlatformMisc::RequestExit(false);
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void ADeathMatchGM::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{
	UE_LOG(LogTemp, Warning, TEXT("GetSeamlessTravelActorList custom"));

	ActorList.Add(GetWorld()->GetGameState());

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator++)
	{
		APlayerController* PlayerController = Iterator->Get();
		ActorList.Add(PlayerController->GetPlayerState<AShooterPS>());
	}

	Super::GetSeamlessTravelActorList(bToTransition, ActorList);
}

void ADeathMatchGM::CheckPlayersAreReady()
{
	UE_LOG(LogTemp, Warning, TEXT("CheckPlayersAreReady"));

	ADeathMatchGS* MyGameState = GetGameState<ADeathMatchGS>();
	if (MyGameState != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyGameState ok"));

		if (MyGameState->ArePlayersReady())
		{
			UE_LOG(LogTemp, Warning, TEXT("ServerTravel to Game map"));

			bUseSeamlessTravel = true;
			DisplayShooterHUD();
			GetWorld()->ServerTravel("Highrise");
		}
	}
}