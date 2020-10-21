#pragma once

#include "ObjectPool.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct FLaserWeaponData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintInternalUseOnly)
	FTransform LookTransform;
	UPROPERTY(BlueprintInternalUseOnly)
	FTransform MuzzleTransform;

	UPROPERTY(BlueprintInternalUseOnly)
	float Damages;
	UPROPERTY(BlueprintInternalUseOnly)
	float Knockback;
	UPROPERTY(BlueprintInternalUseOnly)
	float Spread = 0.f;
	UPROPERTY(BlueprintInternalUseOnly)
	float MaxDistance = 10000.f;
};

UCLASS()
class SHOOTERMULTI_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

private:

	// Weapon Utility.

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter|Weapon")
	bool ShootLaser(AActor* Causer, FHitResult& HitResult, const FLaserWeaponData& WeaponData);

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter|Weapon")
	void MakeImpactDecal(	const FHitResult& FromHit,
							UMaterialInterface* ImpactDecalMaterial,
							float ImpactDecalSizeMin,
							float ImpactDecalSizeMax);

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter|Weapon")
	void MakeLaserBeam(	FVector Start,
						FVector End,
						UParticleSystem* BeamParticles,
						float InBeamIntensity,
						FLinearColor Color,
						UCurveFloat* InBeamIntensityCurve);

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter|Weapon")
	void MakeImpactParticles(UParticleSystem* ImpactParticles, const FHitResult& FromHit, float Scale = 1.f);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	class UParticleSystem* ImpactParticle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	class UParticleSystem* BeamParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	USoundBase* ShotSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	USoundBase* ShotEmptySound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	UMaterial* ImpactDecalMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	class UCurveFloat* BeamIntensityCurve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	class UParticleSystem* MuzzleSmokeParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	TSubclassOf<class UCameraShake> ShootShake;

	float ShootTimer = 0.0f;

	ObjectPool<class ABeamLight> LightPool;

	void SpawnEmitterAtLocation(UParticleSystem* EmitterTemplate,
								const FTransform& SpawnTransform,
								const FVector& Source = FVector::ZeroVector,
								const FVector& Target = FVector::ZeroVector);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon", meta = (ClampMin = "0"))
	int MaxAmmo = 50;

	UFUNCTION()
	void OnRep_CheckAmmo();
	UPROPERTY(ReplicatedUsing = OnRep_CheckAmmo, BlueprintReadOnly, EditAnywhere, Category = "Character|Shooter|Weapon", meta = (ClampMin = "0"))
	int AmmoCount = 50;

	UFUNCTION()
	void OnRep_CheckLoadedAmmo();
	UPROPERTY(ReplicatedUsing = OnRep_CheckLoadedAmmo, Transient, BlueprintReadOnly, Category = "Character|Shooter|Weapon")
	int LoadedAmmo;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "Character|Shooter|Weapon", meta = (ClampMin = "0"))
	int WeaponMagazineSize = 20;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon", meta = (ClampMin = "0"))
	float FireRate = 0.24f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float ImpactDecalLifeSpan = 30.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float ImpactDecalSize = 10.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float BeamIntensity = 3000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float WeaponDamage = 15.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float WeaponPunchDamage = 30.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float WeaponKnockback = 300000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float WeaponMinSpreadAim = 2.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float WeaponMinSpreadWalk = 4.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float WeaponMaxSpread = 15.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float WeaponSpreadPerShot = 4.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter|Weapon")
	float WeaponSpreadRecoveryRate = 1.5f;

	UPROPERTY(BlueprintReadOnly, Category = "Character|Shooter|Weapon")
	float CurrentSpread = 0.0f;

	void BeginPlay() override;

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool Shot();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastFxSoundShoot(FVector_NetQuantize ImpactPoint ,FLaserWeaponData WeaponData);
	void MulticastFxSoundShoot_Implementation(FVector_NetQuantize ImpactPoint ,FLaserWeaponData WeaponData);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastFxSoundSuccessShoot(FVector_NetQuantize ImpactPoint, FVector_NetQuantizeNormal ImpactNormal, FVector_NetQuantizeNormal Normal);
	void MulticastFxSoundSuccessShoot_Implementation(FVector_NetQuantize ImpactPoint, FVector_NetQuantizeNormal ImpactNormal, FVector_NetQuantizeNormal Normal);

	void Reload();

	void GetAmmo(int Count);

};
