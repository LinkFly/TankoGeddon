// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ActorsPull.h"
#include <GameFramework/Actor.h>
#include "TankoGeddonGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API ATankoGeddonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	/*virtual void BeginPlay() override {
		Super::BeginPlay();
	}*/

public:
	static ATankoGeddonGameModeBase* GetCurrentGameMode(AActor* LiveActor);
	ATankoGeddonGameModeBase();
	void PullFill(TSubclassOf<AActor> ActorClass);
	AActor* ReceiveActor(TSubclassOf<AActor> ActorClass,
			const FVector& Location, const FRotator& Rotation);
	bool ReturnActor(AActor* Actor);
	void ActorsPullDump();
	void PullInit(int32 SubPullsCount, int32 SubPullSize);
private:

	UPROPERTY()
	UActorsPull* Pull;


};
