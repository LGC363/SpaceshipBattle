// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

class USphereComponent;
class UCameraComponent;
class USpringArmComponent;
class ABullet;
class USoundCue;

UCLASS()
class SPACESHIPBATTLE_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

protected:

	UPROPERTY(VisibleAnywhere,Category="Component")
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* ShipSM;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComp;

	APlayerController* PC;

	UPROPERTY(EditAnywhere,Category="Fire")
	TSubclassOf<ABullet> Bullet;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere,Category="Move")
	float Speed;

	FTimerHandle TimerHandle_BetweenShot;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float TimeBetweenShot;

	FTimerHandle TimerHandle_Restart;

	UPROPERTY(EditAnywhere,Category="Sound")
	USoundCue* GameOverCue;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* ShootCue;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UParticleSystemComponent* ThrusterParticleComp;

	UPROPERTY(EditAnywhere,Category="Particle")
	UParticleSystem* ExplosionParticle;

	bool bDead;

	bool bUpMove;
	bool bRightMove;

	void LookAtCursor();

	void MoveUp(float Value);

	void MoveRight(float Value);

	void Move();

	void Fire();

	void StartFire();

	void EndFire();

	void RestartLevel();

	void OnDeath();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FORCEINLINE bool GetBDead() {
		return bDead;
	}
	
};
