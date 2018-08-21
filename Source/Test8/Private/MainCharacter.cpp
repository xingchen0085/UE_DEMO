// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/MainCharacter.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Engine/Classes/GameFramework/Character.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//初始化两个摄像机
	CameraOne = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraOne"));
	CameraTwo = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraTwo"));

	//附加到胶囊体中
	CameraOne->AttachTo(GetCapsuleComponent());
	CameraTwo->AttachTo(GetCapsuleComponent());
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

	//前后左右移动+鼠标控制
	PlayerInputComponent->BindAxis("MoveForward",this,&AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	//跳跃
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
}

void AMainCharacter::MoveForward(float Value)
{
	//添加向前移动的输入：Actor前方向量，加上Value
	AddMovementInput(GetActorForwardVector(),Value);
}

void AMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(),Value);
}
