// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	Originalloc = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(Shouldmove) {
		FVector Currentloc = GetOwner()->GetActorLocation();
		FVector Targetloc = Originalloc + Moveoffset;
		float Speed = FVector::Distance(Originalloc, Targetloc) / Movetime;
		FVector Newloc = FMath::VInterpConstantTo(Currentloc, Targetloc, DeltaTime, Speed);
		GetOwner()->SetActorLocation(Newloc);
	}
}

void UMover::SetShouldMove(bool NewShouldmove)
{
	Shouldmove = NewShouldmove;
}

