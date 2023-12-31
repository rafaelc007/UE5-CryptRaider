// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "MoverComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BluePrintCallable)
	void SetShouldMove(bool shouldMove);

	UFUNCTION(BluePrintCallable)
	void SetMoveOffset(FVector moveOffset);

private:
	FVector moveOffset;

	UPROPERTY(EditAnywhere)
	float moveTime = 4;

	UPROPERTY(EditAnywhere)
	bool shouldMove = false;

	FVector startLocation;
	AActor * uOwner;

	void MoveOwner(FVector targetLocation, float DeltaTime);

		
};
