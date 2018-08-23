// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/MainProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
// ������
AMainProjectile::AMainProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->InitSphereRadius(15.0f);//�뾶
	SetRootComponent(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->SetUpdatedComponent(SphereComp);
	ProjectileMovementComp->InitialSpeed = 3000.0f;//��ʼ�ٶ�
	ProjectileMovementComp->MaxSpeed = 3000.0f;//����ٶ�
	ProjectileMovementComp->bRotationFollowsVelocity = true;//�õ������ת������ÿ��֡��ƥ�����ٶȷ���
	ProjectileMovementComp->bShouldBounce = true;//ģ��򵥷���
	ProjectileMovementComp->Bounciness = 0.3f;//�ڳ�����������򣨻ָ�ϵ�����󱣳��ٶȵİٷֱ� 0-1
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
	//���亯��
	ProjectileMovementComp->Velocity = Direction * ProjectileMovementComp->InitialSpeed;
}


