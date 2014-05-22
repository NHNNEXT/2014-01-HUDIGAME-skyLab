#include "stdafx.h"
#include "SpaceMine.h"
#include "ObjectTable.h"
#include "ActorManager.h"

SpaceMine::~SpaceMine()
{
}

void SpaceMine::Install()
{

}

bool SpaceMine::React()
{
	bool reactFlag = false;
	std::map<int, D3DXVECTOR3> targetList;

	for ( int i = 0; i < MAX_PLAYER_NUM; ++i )
	{
		// 일단 각 플레이어와의 거리 확인
		if ( GObjectTable->GetInstance<Character>( i ) == nullptr )
			continue;

		D3DXVECTOR3 relativeDirection = m_Transform.GetPosition() - GObjectTable->GetInstance<Transform>( i )->GetPosition();
		float distance = D3DXVec3Length( &relativeDirection );
		
		if ( distance <= SPACE_MINE_RANGE )
		{
			// 범위 안이면 일단 추가
			targetList.insert( std::map<int, D3DXVECTOR3>::value_type( i, relativeDirection ) );

			// 만약 다른 팀원이면 발동!
			if ( m_Team != GObjectTable->GetInstance<Character>( i )->GetTeam() )
				reactFlag = true;
		}
	}

	// 발동되었다!
	// 발동 조건은 상대방 팀에 한정이지만 발동 후 효과 적용은 전체
	if ( reactFlag )
	{
		printf_s( "react!!\n" );
		for ( std::map<int, D3DXVECTOR3>::const_iterator it = targetList.begin(); it != targetList.end(); ++it )
		{
			// 밀려나는 방향 및 세기 결정
			D3DXVECTOR3 force;
			D3DXVec3Normalize( &force, &it->second );
			force *= -SPACE_MINE_FORCE;

			// 적용 및 방송
			GObjectTable->GetInstance<Character>( it->first )->Move( force );
			GObjectTable->GetActorManager()->BroadcastCharacterChange( it->first, ChangeType::KINETIC_STATE );
		}
	}

	return reactFlag;
}