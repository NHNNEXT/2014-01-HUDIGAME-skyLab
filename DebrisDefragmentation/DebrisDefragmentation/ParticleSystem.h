#pragma once
#include "ClientObject.h"
#include "CollisionBox.h"

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

	virtual void UpdateItSelf( float dTime ) {};

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
	IDirect3DDevice9*       _device;
	D3DXVECTOR3             _origin;
	CollisionBox	        _boundingBox;
	float                   _emitRate;   // rate new particles are added to system
	float                   _size;       // size of particles
	IDirect3DTexture9*      _tex;
	IDirect3DVertexBuffer9* _vb;
	std::list<Attribute>    _particles;
	int                     _maxParticles; // max allowed particles system can have

	//
	// Following three data elements used for rendering the p-system efficiently
	//

	DWORD _vbSize;      // size of vb
	DWORD _vbOffset;    // offset in vb to lock   
	DWORD _vbBatchSize; // number of vertices to lock starting at _vbOffset

};

class Firework : public ParticleSystem
{
public:
	Firework();
	CREATE_OBJECT( Firework );

	void SetParticles( D3DXVECTOR3* origin, int numParticles );
	void resetParticle( Attribute* attribute );
	void UpdateItSelf( float timeDelta );
	void preRender();
	void postRender();
};
