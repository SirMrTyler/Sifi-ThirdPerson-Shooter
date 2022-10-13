// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "SimpleShooter/Character/ShooterPlayerController.h"


// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Root Component"));
	SetRootComponent(WeaponRootComponent);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	WeaponMesh->SetupAttachment(WeaponRootComponent);
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::CreateHitMark()
{
	HitMarkWidget->AddToViewport();
}

void AWeaponActor::DeleteHitMark()
{
	HitMarkWidget->RemoveFromViewport();
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
	Shooter = Cast<AShooterPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if(Shooter != nullptr) {
		HitMarkWidget = CreateWidget(Shooter, HitMarkClass);
		return;
	}
}

/*void AWeaponActor::EndPlay()
{
	
}*/

void AWeaponActor::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticle, WeaponMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, WeaponMesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;

	bool bHasHit = WeaponTrace(Hit, ShotDirection);

	if(bHasHit) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpactParticle, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		AActor* HitActor = Hit.GetActor();
		if(HitActor != nullptr) {
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController *OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			
			FString HitActorClassName = HitActor->GetClass()->GetName();
			if(HitActorClassName == "BP_EnemyCharacter_C") {
				CreateHitMark();
				GetWorldTimerManager().SetTimer(HitMarkTimerHandle, this, &AWeaponActor::DeleteHitMark, HitMarkDelay);
			}
			
		}
	}
	
}

bool AWeaponActor::WeaponTrace(FHitResult &Hit, FVector &ShotDirection)
{

	AController *OwnerController = GetOwnerController();
	if(OwnerController == nullptr)
		return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AWeaponActor::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) 
		return nullptr;
	return OwnerPawn->GetController();
}

