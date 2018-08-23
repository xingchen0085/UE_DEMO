// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/MainCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Public/MainProjectile.h"

// 玩家
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//初始化摄像机
	CameraOne = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraOne"));
	//将摄像机追加到胶囊体
	CameraOne->AttachTo(GetCapsuleComponent());
	//摄像机放置到眼睛上方50cm
	CameraOne->SetRelativeLocation(FVector(0.0f,0.0f,BaseEyeHeight+50.0f));
	//相机跟随人物旋转
	CameraOne->bUsePawnControlRotation=true;

	//创建第一人称模型
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSMesh"));
	FPSMesh->AttachTo(CameraOne);
	//仅对玩家可见
	FPSMesh->SetOnlyOwnerSee(true);
	//禁止阴影
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//第一人称时无法看到自己 USkeletalMeshComponent
	GetMesh()->SetOwnerNoSee(true);

	MuzzleOffset = FVector(100.0f, 0, 0);//正前方100cm
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

	PlayerInputComponent->BindAxis("MoveForward",this,&AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this, &AMainCharacter::AddControllerPitchInput);
	//跳跃
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&AMainCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJump);

	//Fire
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);
}


void AMainCharacter::Fire() {
	UE_LOG(LogTemp,Warning,TEXT("Fire.."));
	if (ProjectileClass) {
		//获得当前摄像机位置
		FVector CameraLocation;
		FRotator CameraRotation;

		GetActorEyesViewPoint(CameraLocation,CameraRotation);

		//生成点
		FVector MuzzLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzRotation = CameraRotation;

		MuzzRotation.Pitch += 10.0f;//准星上抬10

		//获得world
		UWorld * World =  GetWorld();
		if (World) {

			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Owner = this;
			ActorSpawnParameters.Instigator = Instigator;
			//生成
			AMainProjectile * Projectile = World->SpawnActor<AMainProjectile>(ProjectileClass,MuzzLocation,MuzzRotation, ActorSpawnParameters);
			if (Projectile) {
				//如果成功生成，发射
				Projectile->FireInDirection(MuzzRotation.Vector());
			}
		}
	}
}

void AMainCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(),Value);
}

void AMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(),Value);
}

void AMainCharacter::StartJump() {
	bPressedJump = true;
}

void AMainCharacter::StopJump() {
	bPressedJump = false;
}


