#pragma once
#include "DDModel.h"
#include "GameOption.h"

class ModelPool
{
public:
	ModelPool();
	~ModelPool();

	bool			InitModel( ModelType modelType, std::wstring path, bool isAnimation = false );
	MeshInfo*		GetModel( ModelType );
//	MeshInfo*		CopyModel( ModelType );
//	SkinnedMesh*	GetAnimationModel( ModelType );
	SkinnedMesh*	GetAnimationModel( int playerID );
	void			ClearModelPool();

private:
	bool		SetNormalVector( MeshInfo* mi );
	void		AddModel( ModelType mt, MeshInfo* mi );
	bool		Cleanup( MeshInfo* mi );
	
	std::unordered_map<ModelType, MeshInfo*> m_ObjectMap;
	//std::unordered_map<ModelType, SkinnedMesh*> m_AnimationObjectMap;

	// 조심해!!
	// 일단은 애니메이션 가진게 캐릭터밖에 없으니 대충!!
	std::array<SkinnedMesh*, REAL_PLAYER_NUM> m_AnimationObjectMap;
};

