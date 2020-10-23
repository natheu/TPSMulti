#include "DeathMatchGM.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"


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