// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPickup.h"
#include "../Characters/ShooterCharacter.h"

void AHealthPickup::NotifyActorBeginOverlap(AActor * OtherActor)
{
	AShooterCharacter* Player = Cast<AShooterCharacter>(OtherActor);

	if (!Player || Player->GetHealth() >= Player->GetMaxHealth())
		return;
	if(GetLocalRole() == ENetRole::ROLE_Authority)
		Player->GainHealth(Health);

	// After because of Destroy
	Super::NotifyActorBeginOverlap(OtherActor);
}