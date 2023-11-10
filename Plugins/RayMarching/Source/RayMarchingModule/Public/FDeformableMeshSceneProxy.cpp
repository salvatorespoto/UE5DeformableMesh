#include "FDeformableMeshSceneProxy.h"
#include "UDeformableMeshComponent.h"


FDeformableMeshSceneProxy::FDeformableMeshSceneProxy(UDeformableMeshComponent* FDeformableMeshComponent)
: FPrimitiveSceneProxy(FDeformableMeshComponent)
// Material relevence ??
{

	// Init sections
	for(int32 i=0; i<FDeformableMeshComponent->NumSections; i++)
	{
		 Sections.Add(new FDeformableSectionSceneProxy());
		 	
	}
}