// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/MainCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Public/MainProjectile.h"

// ���
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��ʼ�������
	CameraOne = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraOne"));
	//�������׷�ӵ�������
	CameraOne->AttachTo(GetCapsuleComponent());
	//��������õ��۾��Ϸ�50cm
	CameraOne->SetRelativeLocation(FVector(0.0f,0.0f,BaseEyeHeight+50.0f));
	//�������������ת
	CameraOne->bUsePawnControlRotation=true;

	//������һ�˳�ģ��
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSMesh"));
	FPSMesh->AttachTo(CameraOne);
	//������ҿɼ�
	FPSMesh->SetOnlyOwnerSee(true);
	//��ֹ��Ӱ
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//��һ�˳�ʱ�޷������Լ� USkeletalMeshComponent
	GetMesh()->SetOwnerNoSee(true);

	MuzzleOffset = FVector(100.0f, 0, 0);//��ǰ��100cm
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
	//��Ծ
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&AMainCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJump);

	//Fire
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);
}


void AMainCharacter::Fire() {
	UE_LOG(LogTemp,Warning,TEXT("Fire.."));
	if (ProjectileClass) {
		//��õ�ǰ�����λ��
		FVector CameraLocation;
		FRotator CameraRotation;

		GetActorEyesViewPoint(CameraLocation,CameraRotation);

		//���ɵ�
		FVector MuzzLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzRotation = CameraRotation;

		MuzzRotation.Pitch += 10.0f;//׼����̧10

		//���world
		UWorld * World =  GetWorld();
		if (World) {

			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Owner = this;
			ActorSpawnParameters.Instigator = Instigator;
			//����
			AMainProjectile * Projectile = World->SpawnActor<AMainProjectile>(ProjectileClass,MuzzLocation,MuzzRotation, ActorSpawnParameters);
			if (Projectile) {
				//����ɹ����ɣ�����
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


