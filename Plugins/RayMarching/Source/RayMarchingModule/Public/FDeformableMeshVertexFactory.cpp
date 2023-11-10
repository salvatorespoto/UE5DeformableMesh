#include "FDeformableMeshVertexFactory.h"

bool FDeformableMeshVertexFactory::ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters)
{
	// Compile permutation for surface unlint material, plus the default one
	if ((Parameters.MaterialParameters.MaterialDomain == MD_Surface && Parameters.MaterialParameters.ShadingModels == MSM_Unlit) ||
		Parameters.MaterialParameters.bIsDefaultMaterial)
	{
		return true;
	}
	
	return false;
}

void FDeformableMeshVertexFactory::ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);
{
	// Exclude manual vertex fetch because we don't support it
	const bool ContainsManualVertexFetch = OutEnvironment.GetDefinitions().Contains("MANUAL_VERTEX_FETCH");
	if (!ContainsManualVertexFetch)
	{
		OutEnvironment.SetDefine(TEXT("MANUAL_VERTEX_FETCH"), TEXT("0"));
	}

	OutEnvironment.SetDefine(TEXT("DEFORMABLE_MESH"), TEXT("1"));
}

void FDeformableMeshVertexFactory::InitRHI(FRHICommandListBase& RHICmdList) override 
{
	// Check that the feature level is supported
	check(HasValidFeatureLevel());
	
	const bool bCanUseGPUScene = UseGPUScene(GMaxRHIShaderPlatform, GetFeatureLevel());

	// With Manual Vertex Fetch vertex data is fetched manually (address calculated from SV_VertexID and SV_InstanceID).
	// This allows us to output a different mesh for each instance. With standard vertex buffer fetch, each instance would use the same mesh.
	// This is an important use case for custom vertex fetch.
	const bool bUseManualVertexFetch = SupportsManualVertexFetch(GetFeatureLevel());

	// Position Only /** The RHI vertex declaration used to render the factory during depth only passes. */
	{
		// FVertexDeclarationElementList is a TArray of FVertexElement that is used to create vertex declaration
		FVertexDeclarationElementList StreamElements; // Used for the default vertex stream
		// Mirrors the stream elements, creates a vertex element for a vertex stream component,
		// this is for the position stream, so access the stream comopnent and set this vertex factory PositionStream to point to it
		StreamElements.Add(AccessStreamComponent(Data.PositionComponent, 0, EVertexInputStreamType::PositionOnly));
		// Add the defined elements as primitive id streaming  ??
		AddPrimitiveIdStreamElement(EVertexInputStreamType::PositionOnly, StreamElements, 1, 8);
		// Create the declaration
		InitDeclaration(StreamElements, EVertexInputStreamType::PositionOnly);
	}

	// Position and Normals buh ?
	{
		FVertexDeclarationElementList StreamElements; // Used for the default vertex stream
		// Mirrors the stream elements, creates a vertex element for a vertex stream component,
		// this is for the position stream, so access the stream comopnent and set this vertex factory PositionStream to point to it
		StreamElements.Add(AccessStreamComponent(Data.PositionComponent, 0, EVertexInputStreamType::PositionAndNormalOnly));
		StreamElements.Add(AccessStreamComponent(Data.TangentBasisComponents[1], 2, EVertexInputStreamType::PositionAndNormalOnly));
		// Add the defined elements as primitive id streaming  ??
		AddPrimitiveIdStreamElement(EVertexInputStreamType::PositionAndNormalOnly, StreamElements, 1, 8);
		// Create the declaration
		InitDeclaration(StreamElements, EVertexInputStreamType::PositionAndNormalOnly);
	}

	// Default The RHI vertex declaration used to render the factory normally in the main render passes
	{
		FVertexDeclarationElementList StreamElements; // Used for the default vertex stream
		
		//We add all the available texcoords to the default element list, that's all what we'll need for unlit shading
		if (Data.TextureCoordinates.Num())
		{
			const int32 BaseTexCoordAttribute = 4;
			for (int32 CoordinateIndex = 0; CoordinateIndex < Data.TextureCoordinates.Num(); CoordinateIndex++)
			{
				StreamElements.Add(AccessStreamComponent(Data.TextureCoordinates[CoordinateIndex], BaseTexCoordAttribute + CoordinateIndex));
			}

			for (int32 CoordinateIndex = Data.TextureCoordinates.Num(); CoordinateIndex < MAX_STATIC_TEXCOORDS / 2; CoordinateIndex++)
			{
				StreamElements.Add(AccessStreamComponent(Data.TextureCoordinates[Data.TextureCoordinates.Num() - 1], BaseTexCoordAttribute + CoordinateIndex));
			}
		}

		check(Streams.Num() > 0);
		InitDeclaration(StreamElements);
		check(IsValidRef(GetDeclaration()));
	}
}