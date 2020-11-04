#include "EnemySpawnerButton.h"
#include "../AI/UndeadDirector.h"
#include "../GameFramework/DeathMatchGS.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"

AEnemySpawnerButton::AEnemySpawnerButton()
{
	bAlwaysRelevant = true;
	bReplicates = true;
}

void AEnemySpawnerButton::BeginPlay()
{
	Super::BeginPlay();

	if (material == nullptr)
	{
		TArray<UStaticMeshComponent*> Components;
		GetComponents<UStaticMeshComponent>(Components);
		material = Components[0]->CreateAndSetMaterialInstanceDynamic(2);
	}
}

void AEnemySpawnerButton::Activate(ETeam team)
{
	if (mTeam == team)
		return;
	
	SetTeam(team);

	auto lambda = [this]()
	{
		//auto dir = Cast<ADeathMatchGM>(GetWorld()->GetAuthGameMode())->GetUndeadDirector();
		auto dir = AUndeadDirector::GetInstance();
		dir->SpawnEnemy(GetActorLocation(), GetActorRotation(), mTeam, false);
	};
	if (GetLocalRole() == ENetRole::ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(mSpawnTimerHandle, lambda, SecondPerSpawn, true);
		FTimerHandle resetTimerButton;
		GetWorld()->GetTimerManager().SetTimer(mSpawnTimerHandle, this, &AEnemySpawnerButton::Reset, TimeResetButton, false);
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ActivateSound, GetActorLocation());
}

void AEnemySpawnerButton::SetTeam(ETeam team)
{
	mTeam = team;

	if (!material && GetLocalRole() != ENetRole::ROLE_Authority)
		return;

	FLinearColor color = team == ETeam::Blue ? FLinearColor::Blue : team == ETeam::Red ? FLinearColor::Red : FLinearColor::Green;

	MulticastUpdateTeam(team, color);
}

void AEnemySpawnerButton::MulticastUpdateTeam_Implementation(ETeam team, FLinearColor color)
{
	mTeam = team;

	if (!material)
		return;

	material->SetVectorParameterValue("ColorActive", color);
}

void AEnemySpawnerButton::Reset()
{
	SetTeam(ETeam::None);

	if (GetLocalRole() == ENetRole::ROLE_Authority)
		GetWorldTimerManager().ClearTimer(mSpawnTimerHandle);
}
