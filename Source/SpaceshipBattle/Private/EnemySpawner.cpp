// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Public/SpaceShip.h"
#include "Engine/World.h"
#include "Public/Enemy.h"
#include "TimerManager.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
	SpawnInterval = 2.0f;
	MaxEnemyNum = 30;
	CurrentEnemyCount = 0;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();	
	SpaceShip=Cast<ASpaceShip>( UGameplayStatics::GetPlayerPawn(this,0));
	GetWorldTimerManager().SetTimer(TimerHandle_Spawn,this,&AEnemySpawner::SpawnEnemy,SpawnInterval,true,0.0f);
}

FVector AEnemySpawner::GetGenerateLocation()
{
	float Distance=0;
	FVector Location;
	while (Distance<MinimumDistanceToPlayer)
	{
		Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin, SpawnArea->Bounds.BoxExtent);
		Distance = (Location - SpaceShip->GetActorLocation()).Size();
	}

	return Location;
}

void AEnemySpawner::SpawnEnemy()
{
	if (SpaceShip->GetBDead() == false&&CurrentEnemyCount<MaxEnemyNum)
	{
		FActorSpawnParameters SpawnParameters;
		GetWorld()->SpawnActor<AEnemy>(Enemy, GetGenerateLocation(), FRotator::ZeroRotator, SpawnParameters);
		CurrentEnemyCount++;
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::DecreaseEnemyCount()
{
	if (CurrentEnemyCount > 0)
	{
		CurrentEnemyCount--;
		UE_LOG(LogTemp,Warning,TEXT("%s"),*FString::SanitizeFloat(CurrentEnemyCount));
	}
}

