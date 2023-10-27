// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	this->uOwner = this->GetOwner();
	this->startLocation = uOwner->GetActorLocation();
	
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector targetLocation = this->startLocation;
	if (this->shouldMove) {
		targetLocation = this->startLocation + this->moveOffset;
	}
	this->MoveOwner(targetLocation, DeltaTime);
}

void UMoverComponent::MoveOwner(FVector targetLocation, float DeltaTime)
{
	FVector currentLocation = uOwner->GetActorLocation();
	float speed = moveOffset.Length() / this->moveTime;
	auto newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, speed);
	this->uOwner->SetActorLocation(newLocation);
}

void UMoverComponent::SetShouldMove(bool move)
{
	this->shouldMove = move;
}

void UMoverComponent::SetMoveOffset(FVector vec)
{
	this->moveOffset = vec;
}