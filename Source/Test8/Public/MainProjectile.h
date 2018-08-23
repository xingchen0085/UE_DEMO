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

	//球体组件，处理碰撞
	UPROPERTY(VisibleDefaultsOnly,Category="Sphere")
	class USphereComponent * SphereComp;


	//发射的组件
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class UProjectileMovementComponent * ProjectileMovementComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//发射（初始速度已经知道了，这个方法主要制定发射点）
	void FireInDirection(const FVector& Direction);
};
