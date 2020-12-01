#pragma once

#include "HealthCharacter.h"
#include "../Weapons/WeaponComponent.h"
#include "PlayerCameraComponent.h"
#include "ShooterCharacter.generated.h"

UENUM(BlueprintType)
enum class EShooterCharacterState : uint8
{
	IdleRun,
	Aim,
	Sprint,
	Reload,
	Jump,
	Falling,
	Punch,
	Dead,
	PushButton
};

UCLASS()
class SHOOTERMULTI_API AShooterCharacter : public AHealthCharacter
{
	GENERATED_BODY()

private:

	UFUNCTION(NetMulticast, Reliable)
	void MulticastEndReload();
	void MulticastEndReload_Implementation();

	void UpdateVariableStartReaload();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartReload();
	void MulticastStartReload_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastAbortReload();
	void MulticastAbortReload_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerInitTeam(ETeam InTeam);
	void ServerInitTeam_Implementation(ETeam InTeam);
	bool ServerInitTeam_Validate(ETeam InTeam) { return true; }

protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character|Shooter")
	UWeaponComponent* Weapon;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character|Shooter")
	UPlayerCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, Category = "Character|Shooter")
	EShooterCharacterState State;
	EShooterCharacterState PrevState;

	UPROPERTY(Replicated, BlueprintReadOnly)
	float AimPitch;

	UPROPERTY(Replicated, BlueprintReadOnly)
	float AimYaw;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void UpdateAimOffsets(float Pitch, float Yaw);

	void PlayPushButtonAnim();

	void PlayPunchAnim();

	void Falling() override;

	void BeginPlay() override;

	void Invincibility(float Duration);

	UFUNCTION(BlueprintNativeEvent, Category = "Character|Shooter")
	void InvincibilityFX(float Duration);
	void InvincibilityFX_Implementation(float Duration) {};

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerUpdateAimOffsets(float Pitch, float Yaw);
	void ServerUpdateAimOffsets_Implementation(float Pitch, float Yaw);
	bool ServerUpdateAimOffsets_Validate(float Pitch, float Yaw) { return true; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString pseudo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ready{ false };

public:

	bool bIsShooting = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter")
	float SprintSpeed = 1000.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter")
	float AimWalkSpeed = 180.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter")
	float ReloadWalkSpeed = 200.f;

	UPROPERTY(BlueprintReadOnly)
	float RunSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character|Shooter", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MinSprintMagnitude = .3f;

	AShooterCharacter();

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	EShooterCharacterState GetState() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void SetState(EShooterCharacterState InState);

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	UWeaponComponent* GetWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	UPlayerCameraComponent* GetCameraComponent();

	void InitPlayer();

	void InitTeamColor(ETeam InTeam);

	void Tick(float DeltaTime) override;

	UFUNCTION()
	void StartSprint();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartSprint();
	void MulticastStartSprint_Implementation();

	UFUNCTION()
	void EndSprint();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastEndSprint();
	void MulticastEndSprint_Implementation();

	UFUNCTION()
	void StartJump();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartJump();
	void MulticastStartJump_Implementation();
	UFUNCTION()

	void EndJump();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastEndJump();
	void MulticastEndJump_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void StartAim();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartAim();
	void MulticastStartAim_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void EndAim();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastEndAim();
	void MulticastEndAim_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void StartShoot();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartShoot();
	void MulticastStartShoot_Implementation();
	
	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void EndShoot();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastEndShoot();
	void MulticastEndShoot_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void StartReload();
	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void EndReload();
	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void AbortReload();

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void PushButton();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastPushButton();
	void MulticastPushButton_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void InflictPushButton();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastInflictPushButton();
	void MulticastInflictPushButton_Implementation();
	
	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
	void Punch();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastPunch();
	void MulticastPunch_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Character|Shooter")
	void RefreshTeamHUD(ETeam InTeam);
	void RefreshTeamHUD_Implementation(ETeam InTeam) {};

	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
		FString Pseudo() { return pseudo; }
	UFUNCTION(BlueprintCallable, Category = "Character|Shooter")
		bool Ready() { return ready; }

	void StartDisapear() override;
	void FinishDisapear() override;
};