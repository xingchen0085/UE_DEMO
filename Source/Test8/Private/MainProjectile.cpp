// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/MainProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
// 发射物
AMainProjectile::AMainProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->InitSphereRadius(15.0f);//半径
	SetRootComponent(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->SetUpdatedComponent(SphereComp);
	ProjectileMovementComp->InitialSpeed = 3000.0f;//初始速度
	ProjectileMovementComp->MaxSpeed = 3000.0f;//最大速度
	ProjectileMovementComp->bRotationFollowsVelocity = true;//该弹丸的旋转将更新每个帧以匹配其速度方向。
	ProjectileMovementComp->bShouldBounce = true;//模拟简单反弹
	ProjectileMovementComp->Bounciness = 0.3f;//在冲击的正常方向（恢复系数）后保持速度的百分比 0-1
}

// Called when the game starts or when spawned
void AMainProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMainProjectile::FireInDirection(const FVector& Direction)
{
	//发射函数
	ProjectileMovementComp->Velocity = Direction * ProjectileMovementComp->InitialSpeed;
}


