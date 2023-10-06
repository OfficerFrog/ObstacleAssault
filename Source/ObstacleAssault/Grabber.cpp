// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* Physicshandle = GetPhysicsHandle();
	
	if(Physicshandle && Physicshandle->GetGrabbedComponent())
	{
		FVector Targetloc = GetComponentLocation() + GetForwardVector() * Holddist;
		Physicshandle -> SetTargetLocationAndRotation(Targetloc, GetComponentRotation());
	}
	}
	

void UGrabber::Release()
{
	UPhysicsHandleComponent* Physicshandle = GetPhysicsHandle();
	
	if(Physicshandle && Physicshandle->GetGrabbedComponent())
	{
		AActor* Grabbedactor = Physicshandle->GetGrabbedComponent()->GetOwner();
		Grabbedactor->Tags.Remove("Grabbed");
		Physicshandle->ReleaseComponent();
	}
}

void UGrabber::Grab()
{

	UPhysicsHandleComponent* Physicshandle = GetPhysicsHandle();
	if(Physicshandle == nullptr){
		return;
	}
			
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * Maxgrabdist;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(Grabradius);
	FHitResult Hitresult;
	bool Hashit = GetWorld() -> SweepSingleByChannel(Hitresult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, Sphere);

	if(Hashit) {
		UPrimitiveComponent* Hitcomponent = Hitresult.GetComponent();
		Hitcomponent -> WakeAllRigidBodies();
		Hitresult.GetActor()->Tags.Add("Grabbed");
		Physicshandle->GrabComponentAtLocationWithRotation(Hitcomponent, NAME_None, Hitresult.ImpactPoint, GetComponentRotation());
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
		UPhysicsHandleComponent* Result = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
		if(Result == nullptr)
			UE_LOG(LogTemp, Display, TEXT("Grabber requires UPhysicsHandle"));
		return Result;
}
