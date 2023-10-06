// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent1.h"

UTriggerComponent1::UTriggerComponent1()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent1::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("trigger"));
}

void UTriggerComponent1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

   AActor* Actor = GetAcceptableActor();
   if(Actor != nullptr)
   {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if(Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
   }
   else
   {
        Mover->SetShouldMove(false);
   }
    
}

void UTriggerComponent1::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}

AActor* UTriggerComponent1::GetAcceptableActor() const
{
    TArray<AActor*> Actors;

    GetOverlappingActors(Actors);

    for (AActor* Actor : Actors)
    {
        if(Actor -> ActorHasTag(AcceptableActorTag) && !Actor->ActorHasTag("Grabbed"))
        {
            return Actor;
        }
        
    }
    return nullptr;
}