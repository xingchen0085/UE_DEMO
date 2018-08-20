// Fill out your copyright notice in the Description page of Project Settings.

#include "Test8GameModeBase.h"
#include "Engine/Classes/Engine/Engine.h"
#include "Core/Public/Math/Color.h"

void ATest8GameModeBase::StartPlay() {
	UE_LOG(LogTemp,Warning,TEXT("GameModebase::StartPaly"));

	if (GEngine) {
		//输出日志信息
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Yellow,TEXT("Hello World!!"));
	}
}


