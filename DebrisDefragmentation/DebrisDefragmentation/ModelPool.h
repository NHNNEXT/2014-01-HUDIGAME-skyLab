#pragma once
#include "DDModel.h"

class ModelPool
{
public:
	ModelPool();
	~ModelPool();

	bool			InitModel( ModelType modelType, std::wstring path, bool isAnimation = false );
	MeshInfo*		GetModel( ModelType );
	SkinnedMesh*	GetAnimationModel( ModelType );
	void			ClearModelPool();

private:
	bool		SetNormalVector( MeshInfo* mi );
	void		AddModel( ModelType mt, MeshInfo* mi );
	bool		Cleanup( MeshInfo* mi );
	
	std::unordered_map<ModelType, MeshInfo*> m_ObjectMap;
	std::unordered_map<ModelType, SkinnedMesh*> m_AnimationObjectMap;
};

