// Fill out your copyright notice in the Description page of Project Settings.

#include "Module.h"


AModule::AModule()
{
}

void AModule::LinkSoul(APawn *soul)
{
	m_Soul = soul;
}

float AModule::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float HealthPoints = 0;

	if (m_Soul != NULL)
	{
		HealthPoints = m_Soul->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
	else
	{
		//JV-TODO: Log error msg;
		HealthPoints = -1.0f;
	}

	return HealthPoints;
}