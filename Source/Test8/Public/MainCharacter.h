// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class TEST8_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void StartJump();

	void StopJump();

	UPROPERTY(EditAnywhere,Category="Camera")
	class UCameraComponent * CameraOne;

	//��һ�˳�ģ��
	UPROPERTY(EditAnywhere,Category="Mesh")
	class USkeletalMeshComponent * FPSMesh;

	//��������ӽǵ�����ƫ��
	UPROPERTY(EditAnywhere,Category="GamePlay")
	FVector MuzzleOffset;

	//������
	UPROPERTY(EditAnywhere,Category="Projectile")
	TSubclassOf<class AMainProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//��������
	void Fire();

};
