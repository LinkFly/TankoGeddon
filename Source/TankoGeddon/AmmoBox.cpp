// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"
#include <Components/StaticMeshComponent.h>
#include "TankPawn.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshBeginOverlap);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAmmoBox::OnMeshBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3, FColor::Orange, TEXT("PICK"));
	ATankPawn* playerTank = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank == OtherActor) {
		playerTank->SetupCannon(CannonClass);
		Destroy();
	}
}

