// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class SIMPLESHOOTER_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// virtual void EndPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class AShooterPlayerController *Shooter;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* WeaponRootComponent;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* MuzzleFlashParticle;

	UPROPERTY(EditAnywhere)
	USoundBase *MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase *ImpactSound;
	
	FTimerHandle HitMarkTimerHandle;
	
	UPROPERTY(EditAnywhere)
	float HitMarkDelay = -1.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HitMarkClass;
	
	UPROPERTY()
	UUserWidget *HitMarkWidget;

	void CreateHitMark();
	void DeleteHitMark();

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* BulletImpactParticle;

	UPROPERTY(EditAnywhere)
	float Damage;

	bool WeaponTrace(FHitResult &Hit, FVector &ShotDirection);

	AController *GetOwnerController() const;
};
