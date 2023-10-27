// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabberComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float maxGrabDistance = 200;

	UPROPERTY(EditAnywhere)
	float grabRadius = 50;

	UPROPERTY(EditAnywhere)
	float holdDistance = 150;

	UFUNCTION(BlueprintCallable)
	void GrabForward();

	UFUNCTION(BlueprintCallable)
	void Release();

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrababbleInReach(FHitResult& outHitResult) const;

};
