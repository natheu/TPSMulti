#include "DeathMatchGM.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DeathMatchGS.h"

void ADeathMatchGM::Respawn(APlayerController* PlayerController)
{
	RestartPlayerAtPlayerStart(PlayerController, ChoosePlayerStart(PlayerController));
}

void ADeathMatchGM::Quit()
{
	FGenericPlatformMisc::RequestExit(false);
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
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
			GetWorld()->ServerTravel("Game");
		}
	}
}