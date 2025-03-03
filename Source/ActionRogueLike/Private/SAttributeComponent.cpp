// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values
ASAttributeComponent::ASAttributeComponent()
{
	Health = 100;
}

bool ASAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	
	return true;
}
