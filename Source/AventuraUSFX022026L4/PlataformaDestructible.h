// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plataforma.h"
#include "PlataformaDestructible.generated.h"


UCLASS()
class AVENTURAUSFX022026L4_API APlataformaDestructible : public APlataforma
{
	GENERATED_BODY()

//Pinball
public:
	APlataformaDestructible();
	UFUNCTION()
		void AlRecibirImpacto(UPrimitiveComponent* ComponenteGolpeado,AActor* OtroActor,UPrimitiveComponent* OtroComponente,FVector ImpulsoNormal,const FHitResult& Hit);
	
};
