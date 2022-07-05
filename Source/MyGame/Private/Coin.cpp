// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundBase.h"
#include "kismet/GameplayStatics.h"

// Sets default values
ACoin::ACoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	CoinMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMeshComp"));
	RootComponent = CoinMeshComp;

	CoinBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CoinSpereComp"));
	CoinBoxComp->SetupAttachment(CoinMeshComp);
	CoinBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACoin::BeginOverlap);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();	
}

void ACoin::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Server ACoin::BeginOverlap"));
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Client ACoin::BeginOverlap"));
		UGameplayStatics::PlaySound2D(GetWorld(), SoundClass);
	}
}