// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainProjectile.generated.h"

UCLASS()
class TEST8_API AMainProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//���������������ײ
	UPROPERTY(VisibleDefaultsOnly,Category="Sphere")
	class USphereComponent * SphereComp;


	//��������
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class UProjectileMovementComponent * ProjectileMovementComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//���䣨��ʼ�ٶ��Ѿ�֪���ˣ����������Ҫ�ƶ�����㣩
	void FireInDirection(const FVector& Direction);
};
