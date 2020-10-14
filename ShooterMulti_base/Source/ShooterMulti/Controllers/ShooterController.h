#pragma once

#include "GameFramework/PlayerController.h"
#include "../GameFramework/DeathMatchGS.h"
#include "ShooterController.generated.h"

UCLASS()
class SHOOTERMULTI_API AShooterController : public APlayerController
{
	GENERATED_BODY()

protected:

	class AShooterCharacter* ShooterCharacter = nullptr;

	virtual void BeginPlayingState() override;
	virtual void SetupInputComponent() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);

	void StartSprint();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStartSprint();
	void ServerStartSprint_Implementation();
	bool ServerStartSprint_Validate() { return true; }

	void EndSprint();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEndSprint();
	void ServerEndSprint_Implementation();
	bool ServerEndSprint_Validate() { return true; }

	void StartJump();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStartJump();
	void ServerStartJump_Implementation();
	bool ServerStartJump_Validate() { return true; }
	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartJump();
	void MulticastStartJump_Implementation();

	void StartAim();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStartAim();
	void ServerStartAim_Implementation();
	bool ServerStartAim_Validate() { return true; }

	void EndAim();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEndAim();
	void ServerEndAim_Implementation();
	bool ServerEndAim_Validate() { return true; }

	void StartShoot();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStartShoot();
	void ServerStartShoot_Implementation();
	bool ServerStartShoot_Validate() { return true; }
	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartShoot();
	void MulticastStartShoot_Implementation();

	void EndShoot();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerEndShoot();
	void ServerEndShoot_Implementation();
	bool ServerEndShoot_Validate() { return true; }
	UFUNCTION(NetMulticast, Reliable)
	void MulticastEndShoot();
	void MulticastEndShoot_Implementation();

	void StartReload();

	void PushButton();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerPushButton();
	void ServerPushButton_Implementation();
	bool ServerPushButton_Validate() { return true; }


	void Punch();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerPunch();
	void ServerPunch_Implementation();
	bool ServerPunch_Validate() { return true; }
	

public:
	void DisableInput(APlayerController* PlayerController) override;

	UFUNCTION(BlueprintCallable, Category = "Shooter|PlayerController")
	void EndJump();

	UFUNCTION(BlueprintCallable, Category = "Shooter|PlayerController")
	void EndReload();
};