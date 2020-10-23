#pragma once

#include "GameFramework/PlayerState.h"
#include "PlayerGI.h"
#include "../Enum/EnumTeam.h"
#include "ShooterPS.generated.h"

UCLASS()
class SHOOTERMULTI_API AShooterPS : public APlayerState
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(Replicated, BlueprintReadOnly)
	int NbKill;
	UPROPERTY(Replicated, BlueprintReadOnly)
	int NbDeath;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FString UserName;

	// Used to copy properties from the current PlayerState to the passed one
	virtual void CopyProperties(class APlayerState* PlayerState);
	// Used to override the current PlayerState with the properties of the passed one
	virtual void OverrideWith(class APlayerState* PlayerState);

	UFUNCTION()
	void Reset();
};
