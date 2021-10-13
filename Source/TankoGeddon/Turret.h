// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <UObject/ConstructorHelpers.h>
#include "Turret.generated.h"

UCLASS()
class TANKOGEDDON_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

	template <typename TResourceClass>
	static FORCEINLINE TResourceClass* LoadObjectFromGamePath(const FString& GamePath)
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> finder(*GamePath);
		//UE_LOG(LogTankoGeddon, Log, TEXT("bodyFoundTemp.Object: %p"), bodyFoundTemp.Object);
		return finder.Object ? finder.Object : nullptr;
	}

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* CannonSetupPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* HitCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<class ACannon> CannonClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float TargetingRange = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float TargetingSpeed = .1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float TargetingRate = .005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	float Accuracy = 10.f;

	const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/CopyForFix_SM_CSC_Tower1.CopyForFix_SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();

	//TEMPLATE Load Obj From Path
	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FString& Path)
	{
		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path));
	}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class ACannon* Cannon;

	UPROPERTY()
	class APawn* PlayerPawn;
};
