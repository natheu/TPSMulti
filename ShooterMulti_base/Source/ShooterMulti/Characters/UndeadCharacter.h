
#pragma once

#include "HealthCharacter.h"
#include "UndeadCharacter.generated.h"

UCLASS()
class SHOOTERMULTI_API AUndeadCharacter : public AHealthCharacter
{
	GENERATED_BODY()

private:

	bool bHasPunched;

	void PlayPunchMontage();

public:

	UPROPERTY(Category = UndeadCharacter, EditAnywhere, BlueprintReadWrite)
	float PunchCooldown = 1.5f;

	AUndeadCharacter();

	virtual void BeginPlay() override;
	void StartDisapear() override;
	void Reset() override;
	bool Punch();
};
