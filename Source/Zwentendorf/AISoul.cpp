// Fill out your copyright notice in the Description page of Project Settings.
#include "AISoul.h"

#include "Projectile.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

AAISoul::AAISoul()
{
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/Audio/Weapon/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Weapon
	FireRate = 0.25f;
	bCanFire = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	MeshComponent->SetupAttachment(SceneComponent);
}

void AAISoul::Attack()
{
	// If we it's ok to fire again
	if (bCanFire == true)
	{
		if (GetMeshComponent())
		{
			// Spawn projectile at an offset using cannon dir vector
			const UStaticMeshSocket* fireDirectionSocket = GetMeshComponent()->GetSocketByName("DIR_ProjectileSpawn");
			FTransform socketTransform;
			bool success = fireDirectionSocket->GetSocketTransform(socketTransform, GetMeshComponent());
			
			 
			UWorld* const World = GetWorld();

			const FVector SpawnLocation = socketTransform.GetLocation();
			const FRotator FireRotation = socketTransform.GetRotation().Rotator();

			if (World != NULL)
			{
				// spawn the projectile
				World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AAISoul::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

		}
	}

}

void AAISoul::OnDeath()
{
	Destroy();
}

const float AAISoul::GetHealthPoints()
{
	return Health;
}

float AAISoul::ApplyDamage(const float damage)
{
	return Health - damage;
}

void AAISoul::ShotTimerExpired()
{
	bCanFire = true;
}

