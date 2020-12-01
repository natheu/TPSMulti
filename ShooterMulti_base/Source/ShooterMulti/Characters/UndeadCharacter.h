
#pragma once

#include "HealthCharacter.h"
#include "UndeadCharacter.generated.h"

UCLASS()
class SHOOTERMULTI_API AUndeadCharacter : public AHealthCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool bHasPunched;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayPunchMontage();
	void MulticastPlayPunchMontage_Implementation();

protected:
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(Category = UndeadCharacter, EditAnywhere, BlueprintReadWrite)
	float PunchCooldown = 1.5f;

	AUndeadCharacter();

	virtual void BeginPlay() override;
	void StartDisapear() override;
	void Reset() override;
	bool Punch();
};
