// Fill out your copyright notice in the Description page of Project Settings.

#include "BombBall.h"
#include "BombBallProjectile.h"


// Sets default values
ABombBallProjectile::ABombBallProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

ABombBallProjectile::ABombBallProjectile(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("BombBallProjectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABombBallProjectile::OnHit);
	CollisionComp->InitSphereRadius(15.0f);
	RootComponent = CollisionComp;

	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 5000.0f;
	ProjectileMovement->MaxSpeed = 5000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ABombBallProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABombBallProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ABombBallProjectile::InitVelocity(const FVector& ShootDirection)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}

void ABombBallProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		OtherComp->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);
	}
}