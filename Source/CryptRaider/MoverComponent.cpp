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

	if (this->shouldMove) {
		this->MoveOwner(DeltaTime);
	}
	// ...
}

void UMoverComponent::MoveOwner(float DeltaTime) {
	FVector currentLocation = uOwner->GetActorLocation();
	FVector targetLocation = this->startLocation + this->moveOffset;
	float speed = FVector::Distance(startLocation, targetLocation) / this->moveTime;

	auto newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, speed);

	this->uOwner->SetActorLocation(newLocation);
}