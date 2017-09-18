// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Cannon.h"
#include "ChassisDefault.h"
#include "MobilityDefault.h"


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZwentendorfPawn.generated.h"

UCLASS(Blueprintable)
class AZwentendorfPawn : public APawn
{
	GENERATED_BODY()

		/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//Modules
	UPROPERTY(Category = Module, EditAnywhere)
		AMobilityDefault* m_Mobility;
	UPROPERTY(Category = Module, EditAnywhere)
		AChassisDefault* m_Chassis;
	UPROPERTY(Category = Module, EditAnywhere)
		ACannon* m_Cannon;
	

public:
	AZwentendorfPawn();

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;

	// Begin Actor Interface
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	/* Aim in the specified direction */
	void Aim(FVector AimDirection);

	/* Fire a shot in the direction the player is facing */
	void FireShot();

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName AimForwardBinding;
	static const FName AimRightBinding;

	// Static names for action bindings
	static const FName LeftShoulderBinding;
	static const FName RightShoulderBinding;
	static const FName LeftTriggerBinding;
	static const FName RightTriggerBinding;
	static const FName InteractBinding;
	static const FName DodgeBinding;
	static const FName AbilityXBinding;
	static const FName AbilityYBinding;

private:

	void LeftShoulder() {};
	void RightShoulder();
	void LeftTrigger() {};
	void RightTrigger() {};

	void Interact() {};
	void Dodge() {};
	void AbilityX() {};
	void AbilityY() {};

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

public:
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};

