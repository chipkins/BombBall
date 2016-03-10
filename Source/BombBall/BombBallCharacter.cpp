// Fill out your copyright notice in the Description page of Project Settings.

#include "BombBall.h"
#include "BombBallCharacter.h"
#include "BombBallProjectile.h"

// Sets default values
ABombBallCharacter::ABombBallCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

ABombBallCharacter::ABombBallCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	FPGun = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FPGun"));
	FPGun->SetOnlyOwnerSee(true);
	FPGun->AttachParent = FirstPersonMesh;
	FPGun->bCastDynamicShadow = false;
	FPGun->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);

	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABombBallCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("We are using BoomBallCharacter!"));
	}
}

// Called every frame
void ABombBallCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABombBallCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ABombBallCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABombBallCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &ABombBallCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ABombBallCharacter::AddControllerPitchInput);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ABombBallCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABombBallCharacter::OnStopJump);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ABombBallCharacter::OnFire);
}

void ABombBallCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		FRotator Rotation = Controller->GetControlRotation();

		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}

		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void ABombBallCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		AddMovementInput(Direction, value);
	}
}

void ABombBallCharacter::OnStartJump()
{
	bPressedJump = true;
}

void ABombBallCharacter::OnStopJump()
{
	bPressedJump = false;
}

void ABombBallCharacter::OnFire()
{
	if (ProjectileClass != NULL)
	{
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);

		FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			ABombBallProjectile* const Projectile = World->SpawnActor<ABombBallProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector const LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}

