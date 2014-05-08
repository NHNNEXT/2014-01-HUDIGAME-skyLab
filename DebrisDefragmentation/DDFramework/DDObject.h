#pragma once
#include "DDConfig.h"
#include "DDMacro.h"
#include "DDRenderer.h"

// 전방선언
//class DDRenderer;

class DDObject
{
public:
	DDObject();
	virtual ~DDObject();

	// 클래스 생성 및 소멸
	CREATE_OBJECT(DDObject);
	static void DeleteAlignedClass( DDObject* object );
	virtual void Release( );
	
	// 노드 계층 구조 관련
	const DDObject* GetParent() { return m_pParent; }
	const std::list<std::shared_ptr<DDObject>>& GetChildList() { return m_NormalChildList; }		
	void AddChild( DDObject* object, int alphaIndex = 0 ); // alpha 값이 있을 경우 내림차순 정렬을 해서 알파가 제일 큰 놈을 list의 가장 앞에 오도록 함
	void RemoveChild( DDObject* object );

	// world matrix
	D3DXMATRIXA16 GetMatrix() const { return m_Matrix; }

	// local position 관련
	const DDVECTOR3 GetPosition() { return m_Position; }
	const float GetPositionX() const { return m_Position.x; }
	const float GetPositionY() const { return m_Position.y; }
	const float GetPositionZ() const { return m_Position.z; }
	void IncreasePosition( DDVECTOR3 position ) { m_Position += position; }
	void IncreasePositionX( float x ) { m_Position.x += x; }
	void IncreasePositionY( float y ) { m_Position.y += y; }
	void IncreasePositionZ( float z ) { m_Position.z += z; }
	void SetPosition( DDVECTOR3 position ) { m_Position = position; }
	void SetPosition( float x, float y, float z ) { m_Position = DDVECTOR3( x, y, z ); }
	
	// local rotation 관련
	const DDVECTOR3 GetRotation() const { return m_Rotation; }
	const float GetRotationX() const { return m_Rotation.x; }
	const float GetRotationY() const { return m_Rotation.y; }
	const float GetRotationZ() const { return m_Rotation.z; }
	void IncreaseRotation( DDVECTOR3 rotation ) { m_Rotation += rotation; }
	void IncreaseRotationX( float x ) { m_Rotation.x += x; }
	void IncreaseRotationY( float y ) { m_Rotation.y += y; }
	void IncreaseRotationZ( float z ) { m_Rotation.z += z; }
	void SetRotation( DDVECTOR3 rotation ) { m_Rotation = rotation; }
	void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_Rotation = DDVECTOR3( rotationX, rotationY, rotationZ ); }
	
	// local scale 관련
	const DDVECTOR3 GetScale() { return m_Scale; }
	const float GetScaleX() const { return m_Scale.x; }
	const float GetScaleY() const { return m_Scale.y; }
	const float GetScaleZ() const { return m_Scale.z; }
	void IncreaseScale(DDVECTOR3 scale) { m_Scale += scale; }
	void IncreaseScaleX(float x) { m_Scale.x += x; }
	void IncreaseScaleY(float y) { m_Scale.y += y; }
	void IncreaseScaleZ( float z ) { m_Scale.z += z; }
	void SetScale( DDVECTOR3 scale ) { m_Scale = scale; }
	void SetScale( float scaleX, float scaleY, float scaleZ ) { m_Scale = DDVECTOR3( scaleX, scaleY, scaleZ ); }
	
	// update 및 visible
	bool IsVisible() const { return m_VisibleFlag; }
	void SetVisible( bool visible ) { m_VisibleFlag = visible; }
	bool IsUpdatable() const { return m_UpdatableFlag; }
	void SetUpdatable( bool updatable ) { m_UpdatableFlag = updatable; }	

	// alpha값이 있는 물체의 그리기 순서를 get set함
	int GetAlphaIndex() const { return m_AlphaIndex; }
	void SetAlphaIndex( int val ) { m_AlphaIndex = val; }

	// z축 방향 벡터를 월드 좌표계 기준으로 반환
	DDVECTOR3 GetViewDirection() const;
	DDVECTOR3 GetAxisX();

	// NVI Wrapper (비가상 인터페이스)
	void Render();
	void Update( float dTime );

protected:
	void SetParent( DDObject* object ) { m_pParent = object; }
	
	// NVI virtual function
	virtual void AffineTransfrom();
	virtual void RenderItSelf() {}
	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }

	// node구조
	std::list<std::shared_ptr<DDObject>>	m_NormalChildList;
	std::list<std::shared_ptr<DDObject>>	m_AhphaChildList;
	DDObject*		m_pParent = nullptr;	
	int				m_AlphaIndex = 0;	// alpha값이 있는 물체들을 그릴때 순서를 정해주기위해 사용
	
	// visible updatable 
	bool			m_VisibleFlag = true;
	bool			m_UpdatableFlag = true;			

	// local coordinate
	DDVECTOR3		m_Position{ .0f, .0f, .0f };	// c++11에서 나온 균일한 중괄호 초기화라함.
	DDVECTOR3		m_Rotation{ .0f, .0f, .0f };
	DDVECTOR3		m_Scale{ 1.0f, 1.0f, 1.0f };

	// update주기 체크용 임시
	long long		m_UpdateCycles = 0;

	// world coordinate
	D3DXMATRIXA16	m_Matrix;


private : 
	// NVI 함수 내용
	void RenderChildNodes();
	void UpdateChildNodes( float dTime );

};