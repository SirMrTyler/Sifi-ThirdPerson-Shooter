// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Controller.h"
#include "SimpleShooter/Character/ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    

    if(AIBehavior != nullptr) {
        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        AIPawn = GetPawn();

        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), AIPawn->GetActorLocation());
        
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter * ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if (ControlledCharacter != nullptr) {
        return ControlledCharacter->IsDead();
    }

    return true;
}
