// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerPawn.h"

// Sets default values
AMyPlayerPawn::AMyPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

