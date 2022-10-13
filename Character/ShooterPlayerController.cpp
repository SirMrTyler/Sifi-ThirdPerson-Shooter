// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"



void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    HUD->RemoveFromViewport();
    
    if (bIsWinner) {
        UUserWidget *WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr) {
            WinScreen->AddToViewport();
        }
        GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
    }

    else {
        UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr) {
            LoseScreen->AddToViewport();
        }
        GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);        
    }

}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);
    HUD->AddToViewport();

}
