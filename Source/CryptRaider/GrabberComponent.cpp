// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr) {
		return;
	}
	if (physicsHandle->GetGrabbedComponent() != nullptr) {
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
		physicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}

}

void UGrabberComponent::GrabForward()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr) {
		return;
	}
	FHitResult hitResult;
	bool hit = GetGrababbleInReach(hitResult);
	if (hit) {
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->SetSimulatePhysics(true);
		hitComponent->WakeAllRigidBodies();
		AActor* hitActor = hitResult.GetActor();
		hitActor->Tags.Add("Grabbed");
		hitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Blue, false, 2);
		physicsHandle->GrabComponentAtLocationWithRotation(
			hitComponent,
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabberComponent::Release()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr) {
		return;
	}
	if (physicsHandle->GetGrabbedComponent() != nullptr) {
		AActor* grabbedActor = physicsHandle->GetGrabbedComponent()->GetOwner();
		grabbedActor->Tags.Remove("Grabbed");
		physicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Unable to retrieve physics handle"));
	}
	return physicsHandle;
}

bool UGrabberComponent::GetGrababbleInReach(FHitResult& outHitResult) const
{
	FVector lineStart = GetComponentLocation();
	FVector lineEnd = lineStart + GetForwardVector() * this->maxGrabDistance;

	// DrawDebugLine(GetWorld(), lineStart, lineEnd, FColor::Red);
	FCollisionShape sphere = FCollisionShape::MakeSphere(this->grabRadius);
	return GetWorld()->SweepSingleByChannel(
		outHitResult,
		lineStart,
		lineEnd, FQuat::Identity,
		ECC_GameTraceChannel2,
		sphere
	);
}
