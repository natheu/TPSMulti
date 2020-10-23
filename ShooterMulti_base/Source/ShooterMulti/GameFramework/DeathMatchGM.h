#pragma once

#include "../AI/UndeadDirector.h"
#include "GameFramework/GameModeBase.h"
#include "../Enum/EnumTeam.h"
#include "DeathMatchGM.generated.h"

UCLASS()
class SHOOTERMULTI_API ADeathMatchGM : public AGameModeBase
{
	GENERATED_BODY()

protected:
	AUndeadDirector* undeadDirector;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float InvincibilityTime = 3.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 GameTime = 300;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxKill = 20;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxAIPerPlayer = 10;

	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Respawn(APlayerController* PlayerController);

	AUndeadDirector* GetUndeadDirector() { return undeadDirector; }

	void Quit();
};
