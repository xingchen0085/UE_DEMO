// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/MainCharacter.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Engine/Classes/GameFramework/Character.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//ǰ�������ƶ�+������
	PlayerInputComponent->BindAxis("MoveForward",this,&AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	//��Ծ
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
}

void AMainCharacter::MoveForward(float Value)
{
	//�����ǰ�ƶ������룺Actorǰ������������Value
	AddMovementInput(GetActorForwardVector(),Value);
}

void AMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(),Value);
}
