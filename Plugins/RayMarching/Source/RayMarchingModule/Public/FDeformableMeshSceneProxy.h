#pragma once

#include "FDeformableMeshVertexFactory.h"


/**
 * Holds the data that are passed to the rendering thread.
 * Each deformable section scene proxy holds:
 * - An instance of a vertex factory that hold the mesh vertices
 * - An index buffer
 * - A material
 */ 
class FDeformableSectionSceneProxy
{
	/** Vertex factory */
	FDeformableMeshVertexFactory VertexFactory;

	/** Index buffer */
	FRawStaticIndexBuffer IndexBuffer;

	/** Material used for this section */
	UMaterialInterface* Material;

	/** The section is visible or not */
	bool bIsVisible;

	/** TODO clarify this The maximum vertex index used to render in this section */
	int32 MaxVertexIndex;
	
	FDeformableSectionSceneProxy(ERHIFeatureLevel::Type InFeatureLevel)
		: VertexFactory(InFeatureLevel)
		, Material(nullptr)
		, bIsVisible(true)
	{}
}

/**
 * Mirrors the UDeformableMeshComponent in the Render thread.
 * Scene proxies mirrors in the render thread the mesh components that are in the game thread. 
 * So this provide rendering information to the renderer when is necessary.
 */
class FDeformableMeshSceneProxy : public FPrimitiveSceneProxy
{
public:
	/** This mesh sections */
	TArray<FDeformableSectionSceneProxy*> Sections;

	/** Holds each section transform */
	TArray<FMatrix> SectionDeformTransforms;


	Material releveance ?

		DeformTransformsSB ?

			DeformTransformsSRV ?
	
	

};
