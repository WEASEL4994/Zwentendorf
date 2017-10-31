// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponCannon.h"

#include "ProjectileCannon.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

AWeaponCannon::AWeaponCannon()
	: AWeaponModule()
{
	InitializeMesh();

	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/Audio/Weapon/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Weapon
	FireRate = 0.25f;
	bCanFire = true;
}

void AWeaponCannon::InitializeMesh()
{
	if (MeshComponent == nullptr)
	{
		UE_LOG(LogActor, Warning, TEXT("AWeaponCannon"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Meshes/Character/Tasis/WEA_Cannon.WEA_Cannon"));
		// Create the mesh component
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		RootComponent = MeshComponent;
		MeshComponent->SetStaticMesh(Mesh.Object);

		MeshComponent->SetSimulatePhysics(true);
		MeshComponent->SetEnableGravity(true);
	}
}

void AWeaponCannon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponCannon::Activate()
{
	UE_LOG(LogActor, Warning, TEXT("Fire"));

	// If we it's ok to fire again
	if (bCanFire == true)
	{
		// Spawn projectile at an offset using cannon dir vector
		const UStaticMeshSocket* fireDirectionSocket = GetMeshComponent()->GetSocketByName("DIR_ProjectilSpawn"); //JV-TODO: Correct this name in the mesh, also account for the radius of the projectile in the mesh file. If you re-export shooting will be broken again...
		FTransform socketTransform;
		fireDirectionSocket->GetSocketTransform(socketTransform, GetMeshComponent());
		const FVector SpawnLocation = socketTransform.GetLocation();
		const FRotator FireRotation = socketTransform.GetRotation().Rotator();

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile
			World->SpawnActor<AProjectileCannon>(SpawnLocation, FireRotation);
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AWeaponCannon::ShotTimerExpired, FireRate);

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		bCanFire = false;
	}
}

void AWeaponCannon::ShotTimerExpired()
{
	bCanFire = true;
}