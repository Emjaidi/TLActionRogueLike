// Fill out your copyright notice in the Description page of Project Settings.

#include "SExplosiveBarrel_v2.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASExplosiveBarrel_v2::ASExplosiveBarrel_v2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASExplosiveBarrel_v2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASExplosiveBarrel_v2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

