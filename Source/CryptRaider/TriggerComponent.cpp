// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UnlockDoor();
}

void UTriggerComponent::UnlockDoor()
{
	AActor* actor = GetAcceptableActor();
	if (actor != nullptr)
	{
		auto component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
		if (component != nullptr)
		{
			component->SetSimulatePhysics(false);
		}
		actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		this->SetShouldMove(true);
	} else {
		this->SetShouldMove(false);
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (auto actor : Actors)
	{
		if (actor->ActorHasTag(unlockTag) && !actor->ActorHasTag("Grabbed"))
		{
			return actor;
		}
	}
	return nullptr;
}

void UTriggerComponent::SetMover(UMoverComponent* newMover)
{
	this->mMover = newMover;
}

void UTriggerComponent::SetShouldMove(bool shouldMove)
{
	if (this->mMover == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to set shouldMove but mover is empty"));
		return;
	} else {
		this->mMover->SetShouldMove(shouldMove);
	}
}