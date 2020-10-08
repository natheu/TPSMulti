#pragma once

#include "GameFramework/Character.h"
#include "../GameFramework/ShooterPS.h"
#include "../GameFramework/Resetable.h"
#include "HealthCharacter.generated.h"

UCLASS()
class SHOOTERMULTI_API AHealthCharacter : public ACharacter, public IResetable
{
	GENERATED_BODY()

protected:

	float DisapearTimer;
	bool bIsDisapearing;
	TArray<UMaterialInstanceDynamic*> DissolveMaterials;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ETeam Team;

	UPROPERTY(EditAnywhere, Category = "Character|Health", meta = (ClampMin = "0.0"))
	float MaxHealth = 100.f;

	float Health = MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Character|Health", meta = (ClampMin = "0.0"))
	float DisapearingDelay = 10.f;

	UPROPERTY(EditAnywhere, Category = "Character|Health", meta = (ClampMin = "0.0"))
	float DisapearingDuration = 3.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Health")
	USoundBase* HitSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Health")
	USoundBase* HeadshotHitSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Health")
	USoundBase* PunchHitSound;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character")
	class USphereComponent* PunchCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character", meta = (ClampMin = "0"))
	float PunchDuration = 1.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character", meta = (ClampMin = "0"))
	float PunchDamage = 10.f;

	void InitRagdoll();
	void ActivateRagdoll();

public:

	DECLARE_EVENT(AHealthCharacter, TeamSwitchEvent)
	TeamSwitchEvent OnTeamSwitch;
 
	AHealthCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintPure, Category = "Character|Health")
	bool IsDead();

	UFUNCTION(BlueprintCallable, Category = "Character|Health")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Health")
	float GetHealth() const;

	ETeam GetTeam() const;

	void SetTeam(ETeam InTeam);

	UFUNCTION(BlueprintCallable, Category = "Character|Health")
	virtual float	TakeDamage	(float					DamageAmount,
								 FDamageEvent const&	DamageEvent,
								 class AController*		EventInstigator,
								 AActor*				DamageCauser) override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastUpdateTakeDamage(const FVector_NetQuantize& PointDamageEvent, USoundBase* CrtHitSound, float TotalDamage);
	void MulticastUpdateTakeDamage_Implementation(const FVector_NetQuantize& PointDamageEvent, USoundBase* CrtHitSound, float TotalDamage);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastUpdateDeath();
	void MulticastUpdateDeath_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Character|Health")
	float GainHealth(float Amount);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastGainHealth(float GainAmount);
	void MulticastGainHealth_Implementation(float GainAmount);

	UFUNCTION(BlueprintCallable, Category = "Character|Health")
	void ResetHealth();

	UFUNCTION(BlueprintCallable, Category = "Character|Health")
	void InflictPunch();

	void UpdateSkinColor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Reset() override;

	virtual void StartDisapear();
	virtual void UpdateDisapear();
	virtual void FinishDisapear();
};
