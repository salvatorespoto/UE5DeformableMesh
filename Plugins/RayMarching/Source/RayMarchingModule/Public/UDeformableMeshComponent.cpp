#include "UDeformableMeshComponent.h"

#include "FDeformableMeshSceneProxy.h"



FPrimitiveSceneProxy* UDeformableMeshComponent::CreateSceneProxy()
{
	return SceneProxy;
}
