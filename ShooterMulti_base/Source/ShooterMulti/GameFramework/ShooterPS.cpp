#include "ShooterPS.h"
#include "PlayerGI.h"
#include "../Characters/ShooterCharacter.h"
#include "DeathMatchGS.h"
#include "Net/UnrealNetwork.h"

void AShooterPS::BeginPlay()
{
	Super::BeginPlay();

	ADeathMatchGS* GameState = GetWorld()->GetGameState<ADeathMatchGS>();
	GameState->OnResetAfterDelay.AddLambda([this]() { Reset(); });
}

void AShooterPS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShooterPS, NbKill);
	DOREPLIFETIME(AShooterPS, NbDeath);
	DOREPLIFETIME(AShooterPS, UserName);
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
