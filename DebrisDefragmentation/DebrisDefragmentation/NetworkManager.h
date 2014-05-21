#pragma once
#include "GameOption.h"

struct DDPacketHeader;

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void Init();
	void Connect();
	void Disconnect();

	void SendAcceleration();
	void SendStop();
	void SendTurnBody();
	void SendUsingSkill( ClassSkill skilType );
	//void SendDeadRequest();
	void SendRespawnRequest(CharacterClass characterClass);

	int GetMyPlayerId() const { return m_MyPlayerId; }
	void SetMyPlayerId( int val ) { m_MyPlayerId = val; }
	bool IsPlayerLogon() { return ( m_MyPlayerId == -1 ) ? false : true; }

	void RegisterHandles();

	

	static void HandleLoginResult( DDPacketHeader& pktBase );
	static void HandleSyncResult( DDPacketHeader& pktBase );
	static void HandleNewResult( DDPacketHeader& pktBase );
	static void HandleDeadResult( DDPacketHeader& pktBase );
	static void HandleRespawnResult( DDPacketHeader& pktBase );
	static void HandleCollisionResult( DDPacketHeader& pktBase );

	static void HandleGoForwardResult( DDPacketHeader& pktBase );
	static void HandleStopResult( DDPacketHeader& pktBase );
	static void HandleTurnBodyResult( DDPacketHeader& pktBase );

	static void HandleUsingSkillResult( DDPacketHeader& pktBase );
	
	static void HandleBuildDispenserResult( DDPacketHeader& pktBase );
	static void HandleDispenserEffectResult( DDPacketHeader& pktBase );
	static void HandleGatherResult( DDPacketHeader& pktBase );
	static void HandleIssStateResult( DDPacketHeader& pktBase );
	static void HandleIssModuleStateResult( DDPacketHeader& pktBase );
	static void HandleGameResultResult( DDPacketHeader& pktBase );

	static void HandleKineticStateResult( DDPacketHeader& pktBase );
	static void HandleCharacterStateResult( DDPacketHeader& pktBase );

private:
	static int m_MyPlayerId;
	
};

extern NetworkManager* GNetworkManager;