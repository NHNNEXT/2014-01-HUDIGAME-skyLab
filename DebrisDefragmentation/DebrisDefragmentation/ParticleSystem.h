﻿#pragma once
#include "ClientObject.h"
#include "CollisionBox.h"
#include "GameOption.h"

struct Particle
{
	D3DXVECTOR3 _position;
	D3DCOLOR    _color;
	static const DWORD FVF;
};

struct Attribute
{
	Attribute()
	{
		_lifeTime = 0.0f;
		_age = 0.0f;
		_isAlive = true;
	}

	D3DXVECTOR3 _position;
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _acceleration;
	float       _lifeTime;     // how long the particle lives for before dying  
	float       _age;          // current age of the particle  
	D3DXCOLOR   _color;        // current color of the particle   
	D3DXCOLOR   _colorFade;    // how the color fades with respect to time
	bool        _isAlive;
};

class ParticleSystem : public ClientObject
{
public:
	ParticleSystem();
	virtual ~ParticleSystem();
	
	virtual bool init( IDirect3DDevice9* device, LPCWSTR texFileName );
	virtual void reset();

	// sometimes we don't want to free the memory of a dead particle,
	// but rather respawn it instead.
	virtual void resetParticle( Attribute* attribute ) = 0;
	virtual void addParticle();

	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }

	virtual void preRender();
	//virtual void render();
	virtual void postRender();
	virtual void RenderItSelf();

	bool isEmpty();
	bool isDead();

protected:
	virtual void removeDeadParticles();
	float	GetRandomFloat( float lowBound, float highBound );
	void	GetRandomVector( D3DXVECTOR3* out,	D3DXVECTOR3* min, D3DXVECTOR3* max );
	DWORD	FtoDw( float f );

protected:
	IDirect3DDevice9*       m_Device;
	D3DXVECTOR3             m_Origin;
	CollisionBox	        m_BoundingBox;
	float                   m_EmitRate;   // rate new particles are added to system
	float                   m_Size;       // size of particles
	IDirect3DTexture9*      m_Tex;
	IDirect3DVertexBuffer9* m_VB;
	std::list<Attribute>    m_Particles;
	int                     m_MaxParticles; // max allowed particles system can have
	
	D3DXVECTOR3				m_DirectionMin;
	D3DXVECTOR3				m_DirectionMax;
	float					m_LifeTime;
	ColorRange				m_Color;
	//
	// Following three data elements used for rendering the p-system efficiently
	//

	DWORD m_VBSize;      // size of vb
	DWORD m_VBOffset;    // offset in vb to lock   
	DWORD m_VBBatchSize; // number of vertices to lock starting at _vbOffset

};

class Firework : public ParticleSystem
{
public:
	Firework();
	CREATE_OBJECT( Firework );

	void SetParticles( D3DXVECTOR3 origin, ColorRange color, D3DXVECTOR3 directionMin, D3DXVECTOR3 directionMax, float lifetime, int numParticles );
	void PlayEffect( D3DXVECTOR3 origin );
	void resetParticle( Attribute* attribute );
	void UpdateItSelf( float timeDelta );
	void preRender();
	void postRender();
};