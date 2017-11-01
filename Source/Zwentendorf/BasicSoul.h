// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Soul.h"
#include "BasicSoul.generated.h"

/**
 * TEMPORARY CLASS: The purpose of this class is to provide a concrete implementation of ASoul to create BP
 */
UCLASS()
class ZWENTENDORF_API ABasicSoul : public ASoul
{
	GENERATED_BODY()
	
public:
	/* The maximum health points of the robot*/
	UPROPERTY(Category = Health, EditAnywhere, BlueprintReadWrite)
	float MaximumHealthPoints;

	/* The current health points of the robot*/
	UPROPERTY(Category = Health, EditAnywhere, BlueprintReadWrite)
	float HealthPoints;

public:
	ABasicSoul();

	virtual const float GetHealthPoints() override;

	virtual float ApplyDamage(const float damage) override;

protected:
	void OnDeath() override;
};
