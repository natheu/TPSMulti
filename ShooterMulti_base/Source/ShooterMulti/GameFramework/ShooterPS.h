#pragma once

#include "GameFramework/PlayerState.h"
#include "PlayerGI.h"
#include "../Enum/EnumTeam.h"
#include "ShooterPS.generated.h"

USTRUCT(BlueprintType)
struct FSPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		ETeam Team;
	UPROPERTY(BlueprintReadWrite)
		FString Name;
};

UCLASS()
class SHOOTERMULTI_API AShooterPS : public APlayerState
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;

public:

	UPROPERTY(Replicated, BlueprintReadOnly)
	int NbKill;
	UPROPERTY(Replicated, BlueprintReadOnly)
	int NbDeath;

	// Used to copy properties from the current PlayerState to the passed one
	virtual void CopyProperties(class APlayerState* PlayerState) override;
	// Used to override the current PlayerState with the properties of the passed one
	virtual void OverrideWith(class APlayerState* PlayerState);

	UFUNCTION()
	void Reset();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void Server_SelectBlueTeam(const FString& Name);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void Server_SelectRedTeam(const FString& Name);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastSelectBlueTeam(const FString& Name);
	void MulticastSelectBlueTeam_Implementation(const FString& Name);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastSelectRedTeam(const FString& Name);
	void MulticastSelectRedTeam_Implementation(const FString& Name);

	UFUNCTION(BlueprintNativeEvent)
		void Event_TeamUpdateBlue(const FString& Name);
	virtual void Event_TeamUpdateBlue_Implementation(const FString& Name) {};

	UFUNCTION(BlueprintNativeEvent)
		void Event_TeamUpdateRed(const FString& Name);
	virtual void Event_TeamUpdateRed_Implementation(const FString& Name) {};


	//	-	-	-	PlayerIsReady	-	-	-

	UPROPERTY(Replicated, BlueprintReadOnly)
		bool bIsPlayerReady = false;

	UPROPERTY(Replicated, BlueprintReadOnly)
		FString UserName;

	UPROPERTY(Replicated, BlueprintReadOnly)
		ETeam CurrentTeam = ETeam::None;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
		void Server_PlayerIsReady(const FSPlayerInfo& PlayerInfo);

	UFUNCTION(BlueprintNativeEvent)
		void OnPlayerReady();

	UFUNCTION(Client, Reliable)
		void Client_OnPlayerReady();
};
