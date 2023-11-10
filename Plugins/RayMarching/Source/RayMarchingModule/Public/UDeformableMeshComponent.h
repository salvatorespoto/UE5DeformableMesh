#pragma once

// Forward declarations
class FDeformableMeshSceneProxy;

/**
 * A deformable mesh section
 */
USTRUCT()
struct FDeformableMeshSection
{
	GENERATED_BODY()

public:
	
	/** This section transform in world coordinates */
	UPROPERTY()
		FMatrix Transform;

	/** Is this section visible ? */
	UPROPERTY()
		bool bIsVisible;
	
	/** Reset this section values */
	void Reset()
	{
		bIsVisible = true;	
	}
};

/**
 * A deformable mesh component.
 * Vertices could be moved, added and removed. 
 */
UCLASS()
class UDeformableMeshComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
	
public:
	
	/*** BEGIN UPrimitive Component Interface ***/
	
	/**
	 * Creates a proxy to represent the deformable mesh to the scene manager in the rendering thread.
	 * @return The deformable mesh proxy object.
	 */
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	/*** END UPrimitive Component Interface ***/

	/**
	 * Get the number of sections in this mesh.
	 * @return The number of sections.
	 */
	int32 GetNumSection() const { return Sections.Num(); };
	
	/**
	 * Add a new section
	 * @param Section The new section to add
	 */
	void AddSection(FDeformableMeshSection* Section) { Sections.Add(Section); }

	/**
	 * Get a section
	 * @param Index The section index
	 * @return The section with index Index
	 */
	FDeformableMeshSection* GetSection(int32 Index) { return  Sections[Index]; }

private:

	/** The deformable mesh sections */
	UPROPERTY()
	TArray<FDeformableMeshSection*> Sections;

	/** The deformable mesh scene proxy */
	FDeformableMeshSceneProxy* SceneProxy;

	/*** The FDeformableMeshSceneProxy has to access UDeformableMeshComponent to mirror its properties to the rendering thread ***/
	friend class FDeformableMeshSceneProxy;
};