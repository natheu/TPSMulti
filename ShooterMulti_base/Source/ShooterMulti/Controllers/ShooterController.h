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

	void EndSprint();
	void StartJump();
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerStartJump();
	void ServerStartJump_Implementation();
	bool ServerStartJump_Validate() { return true; }
	UFUNCTION(NetMulticast, Reliable)
		void MulticastStartJump();
	void MulticastStartJump_Implementation();

	void StartAim();
	void EndAim();

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
	void Punch();
	

public:
	void DisableInput(APlayerController* PlayerController) override;

	UFUNCTION(BlueprintCallable, Category = "Shooter|PlayerController")
	void EndJump();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastEndJump();
	void MulticastEndJump_Implementation();


	UFUNCTION(BlueprintCallable, Category = "Shooter|PlayerController")
		void EndReload();
};