#include "ShooterController.h"
#include "../Characters/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void AShooterController::BeginPlayingState()
{
	Super::BeginPlayingState();

	ShooterCharacter = Cast<AShooterCharacter>(GetPawn());
	ShooterCharacter->InitPlayer();
}

void AShooterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AShooterController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AShooterController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AShooterController::LookUp);
	InputComponent->BindAxis("Turn", this, &AShooterController::Turn);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &AShooterController::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AShooterController::EndSprint);
	InputComponent->BindAction("Aim", IE_Pressed, this, &AShooterController::StartAim);
	InputComponent->BindAction("Aim", IE_Released, this, &AShooterController::EndAim);
	InputComponent->BindAction("Reload", IE_Pressed, this, &AShooterController::StartReload);
	InputComponent->BindAction("Punch", IE_Pressed, this, &AShooterController::Punch);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AShooterController::StartJump);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AShooterController::StartShoot);
	InputComponent->BindAction("Shoot", IE_Released, this, &AShooterController::EndShoot);
	InputComponent->BindAction("PushButton", IE_Pressed, this, &AShooterController::PushButton);
}

void AShooterController::MoveForward(float Value)
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead() && ShooterCharacter->GetState() != EShooterCharacterState::PushButton)
	{
		if (ShooterCharacter->GetState() == EShooterCharacterState::Sprint && Value <= 0.0f)
			EndSprint();

		FRotator Rotation = GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		ShooterCharacter->AddMovementInput(Value * Rotation.GetNormalized().Vector());
	}

}
void AShooterController::MoveRight(float Value)
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead()	&& ShooterCharacter->GetState() != EShooterCharacterState::Sprint
																	&& ShooterCharacter->GetState() != EShooterCharacterState::PushButton)
	{
		FRotator Rotation = GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		ShooterCharacter->AddMovementInput(Value * Rotation.GetNormalized().RotateVector(FVector::RightVector));
	}
}

void AShooterController::LookUp(float Value)
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead() && ShooterCharacter->GetState() != EShooterCharacterState::PushButton)
	{
		AddPitchInput(Value);
	}
}
void AShooterController::Turn(float Value)
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead() && ShooterCharacter->GetState() != EShooterCharacterState::PushButton)
	{
		AddYawInput(Value);
	}
}

void AShooterController::StartSprint()
{
	/*if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->StartSprint();*/
	ServerStartSprint();

}

void AShooterController::ServerStartSprint_Implementation()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->MulticastStartSprint();
}

void AShooterController::EndSprint()
{
	ServerEndSprint();
	/*if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->EndSprint();*/
}

void AShooterController::ServerEndSprint_Implementation()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->MulticastEndSprint();
}
void AShooterController::StartJump()
{
	ServerStartJump();
}

void AShooterController::ServerStartJump_Implementation()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->MulticastStartJump();
}

void AShooterController::EndJump()
{
	if (GetPawn()->GetLocalRole() == ENetRole::ROLE_Authority)
		if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
			ShooterCharacter->MulticastEndJump();
}


void AShooterController::StartAim()
{
	ServerStartAim();
}

void AShooterController::ServerStartAim_Implementation()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->MulticastStartAim();
}

void AShooterController::EndAim()
{
	ServerEndAim();
}

void AShooterController::ServerEndAim_Implementation()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->MulticastEndAim();
}


void AShooterController::StartShoot()
{
	ServerStartShoot();
}

void AShooterController::ServerStartShoot_Implementation()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->MulticastStartShoot();
}


void AShooterController::EndShoot()
{
	ServerEndShoot();
}

void AShooterController::ServerEndShoot_Implementation()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->MulticastEndShoot();
}

void AShooterController::StartReload()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->StartReload();
}

void AShooterController::EndReload()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->EndReload();
}

void AShooterController::PushButton()
{
	ServerPushButton();
}

void AShooterController::ServerPushButton_Implementation()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->MulticastPushButton();
}

void AShooterController::Punch()
{
	ServerPunch();
	/*if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->Punch();*/
}

void AShooterController::ServerPunch_Implementation()
{
	if (IsValid(ShooterCharacter) && !ShooterCharacter->IsDead())
		ShooterCharacter->MulticastPunch();
}

void AShooterController::DisableInput(APlayerController* PlayerController)
{
	Super::DisableInput(PlayerController);
	
	EndSprint();
	EndAim();
	EndShoot();
}