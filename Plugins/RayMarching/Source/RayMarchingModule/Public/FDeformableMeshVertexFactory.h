#pragma once

#include "LocalVertexFactory.h"

#include "MaterialDomain.h"
#include "MeshMaterialShader.h"


class FDeformableMeshSceneProxy;

/**
 * Deformable Mesh Vertex Factory.
 * Mesh vertex factories provide vertices info from the CPU to the GPU.
 */
class FDeformableMeshVertexFactory : public FLocalVertexFactory
{
	DECLARE_VERTEX_FACTORY_TYPE_API(FDeformableMeshVertexFactory);
	
public:

	FDeformableMeshVertexFactory(ERHIFeatureLevel::Type InFeatureLevel)
		: FLocalVertexFactory(InFeatureLevel, "FDeformableMeshVertexFactory")
		, SceneProxy(nullptr)
	{}

	/** Specify which shader permutation to compile */
	static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);

	/** Modify the compilation environment to control which parts of the shader file are taken in consideration by the shader compiler */
	static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);

	
	/*** Begin FRenderResource interface. ***/
	
	/**
	 * Initialize RHI resources used from this resource.
	 * Define the streams and the vertex declaration
	 */
	virtual void InitRHI(FRHICommandListBase& RHICmdList) override;

	/*** No need to override the ReleaseRHI() method, since we're not crearting any additional resources respect the LocalVertexFactory class ***/

	/*** End FRenderResource interface. ***/

	
	void SetTransformIndex(uint16 Index) { TransformIndex = Index; }
	void SetSceneProxy(FDeformableMeshSceneProxy* Proxy) { SceneProxy = Proxy; }

private:

	/** TODO what is this ? */
	uint16 TransformIndex;
	
	/** The Scene Proxy holds all the section scene proxy for a mesh */ 
	FDeformableMeshSceneProxy* SceneProxy;
	
	/**
	 * Resources needed by the vertex factory to initialize its RHI resources.
	 */
	FStaticMeshDataType Data;
};
