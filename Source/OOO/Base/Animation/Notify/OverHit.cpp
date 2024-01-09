
#include "OverHit.h"

#include "../../Unit/Base/Unit.h"



void UOverHit::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AUnit* ownerUnit = Cast<AUnit>(MeshComp->GetOwner());

	if (ownerUnit)
	{
		//UE_LOG(LogTemp, Error, TEXT("_____NOTE____      Step: '%s'     "), *(OwnerUnit->GetName()));

		ownerUnit->OnAnimNotify(GetNotifyName());
	}
}
