#include "stdafx.h"
#include "ParticleSystem.h"
#include "DDMacro.h"
#include "GameOption.h"
#include "DDMath.h"

const DWORD Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

ParticleSystem::ParticleSystem()
{
	m_Device = 0;
	m_VB = 0;
	m_Tex = 0;
}


ParticleSystem::~ParticleSystem()
{
	SafeRelease<LPDIRECT3DVERTEXBUFFER9>( m_VB );
	SafeRelease<IDirect3DTexture9*>( m_Tex );
}


bool ParticleSystem::init( IDirect3DDevice9* device, LPCWSTR texFileName )
{
	// vertex buffer's size does not equal the number of particles in our system.  We
	// use the vertex buffer to draw a portion of our particles at a time.  The arbitrary
	// size we choose for the vertex buffer is specified by the _vbSize variable.

	m_Device = device; // save a ptr to the device

	HRESULT hr = 0;

	hr = device->CreateVertexBuffer(
		m_VBSize * sizeof( Particle ),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		Particle::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
		&m_VB,
		0 );

	if ( FAILED( hr ) )
	{
		//::MessageBox(0, "CreateVertexBuffer() - FAILED", "ParticleSystem", 0);
		return false;
	}
	std::wstring imgPath = L".\\Resources\\3DModel\\";
	imgPath.append( texFileName );

	hr = D3DXCreateTextureFromFileW(
		device,
		imgPath.c_str(),
		&m_Tex );

	if ( FAILED( hr ) )
	{
		::MessageBox( 0, L"D3DXCreateTextureFromFile() - FAILED", L"ParticleSystem", 0 );
		return false;
	}

	return true;
}

void ParticleSystem::reset()
{
	std::list<Attribute>::iterator i;
	for ( i = m_Particles.begin(); i != m_Particles.end(); i++ )
	{
		resetParticle( &( *i ) , 0.0f);
	}
}

void ParticleSystem::addParticle()
{
	Attribute attribute;

	resetParticle( &attribute, m_LifeTime );

	m_Particles.push_back( attribute );
}

void ParticleSystem::preRender()
{
	m_Device->SetRenderState( D3DRS_LIGHTING, false );
	m_Device->SetRenderState( D3DRS_POINTSPRITEENABLE, true );
	m_Device->SetRenderState( D3DRS_POINTSCALEENABLE, true );
	m_Device->SetRenderState( D3DRS_POINTSIZE, DDMath::FtoDw( m_Size ) );
	m_Device->SetRenderState( D3DRS_POINTSIZE_MIN, DDMath::FtoDw( 0.0f ) );

	// control the size of the particle relative to distance
	m_Device->SetRenderState( D3DRS_POINTSCALE_A, DDMath::FtoDw( 0.0f ) );
	m_Device->SetRenderState( D3DRS_POINTSCALE_B, DDMath::FtoDw( 0.0f ) );
	m_Device->SetRenderState( D3DRS_POINTSCALE_C, DDMath::FtoDw( 1.0f ) );

	// use alpha from texture
	m_Device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	m_Device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );

	m_Device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	m_Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}

void ParticleSystem::postRender()
{
	m_Device->SetRenderState( D3DRS_LIGHTING, true );
	m_Device->SetRenderState( D3DRS_POINTSPRITEENABLE, false );
	m_Device->SetRenderState( D3DRS_POINTSCALEENABLE, false );
	m_Device->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
}

void ParticleSystem::RenderItSelf()
{
	//
	// Remarks:  The render method works by filling a section of the vertex buffer with data,
	//           then we render that section.  While that section is rendering we lock a new
	//           section and begin to fill that section.  Once that sections filled we render it.
	//           This process continues until all the particles have been drawn.  The benifit
	//           of this method is that we keep the video card and the CPU busy.  

	if ( !m_Particles.empty() )
	{
		//
		// set render states
		//

		preRender();

		m_Device->SetTexture( 0, m_Tex );
		m_Device->SetFVF( Particle::FVF );
		m_Device->SetStreamSource( 0, m_VB, 0, sizeof( Particle ) );

		//
		// render batches one by one
		//

		// start at beginning if we're at the end of the vb
		if ( m_VBOffset >= m_VBSize )
			m_VBOffset = 0;

		Particle* v = 0;

		m_VB->Lock(
			m_VBOffset    * sizeof( Particle ),
			m_VBBatchSize * sizeof( Particle ),
			(void**)&v,
			m_VBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD );

		DWORD numParticlesInBatch = 0;

		//
		// Until all particles have been rendered.
		//
		std::list<Attribute>::iterator i;
		for ( i = m_Particles.begin(); i != m_Particles.end(); i++ )
		{
			if ( i->_isAlive )
			{
				//
				// Copy a batch of the living particles to the
				// next vertex buffer segment
				//
				v->_position = i->_position;
				v->_color = (D3DCOLOR)i->_color;
				v++; // next element;

				numParticlesInBatch++; //increase batch counter

				// if this batch full?
				if ( numParticlesInBatch == m_VBBatchSize )
				{
					//
					// Draw the last batch of particles that was
					// copied to the vertex buffer. 
					//
					m_VB->Unlock();

					m_Device->DrawPrimitive(
						D3DPT_POINTLIST,
						m_VBOffset,
						m_VBBatchSize );

					//
					// While that batch is drawing, start filling the
					// next batch with particles.
					//

					// move the offset to the start of the next batch
					m_VBOffset += m_VBBatchSize;

					// don't offset into memory thats outside the vb's range.
					// If we're at the end, start at the beginning.
					if ( m_VBOffset >= m_VBSize )
						m_VBOffset = 0;

					m_VB->Lock(
						m_VBOffset    * sizeof( Particle ),
						m_VBBatchSize * sizeof( Particle ),
						(void**)&v,
						m_VBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD );

					numParticlesInBatch = 0; // reset for new batch
				}
			}
		}

		m_VB->Unlock();

		// its possible that the LAST batch being filled never 
		// got rendered because the condition 
		// (numParticlesInBatch == _vbBatchSize) would not have
		// been satisfied.  We draw the last partially filled batch now.

		if ( numParticlesInBatch )
		{
			m_Device->DrawPrimitive(
				D3DPT_POINTLIST,
				m_VBOffset,
				numParticlesInBatch );
		}

		// next block
		m_VBOffset += m_VBBatchSize;

		//
		// reset render states
		//

		postRender();
	}
}

bool ParticleSystem::isEmpty()
{
	return m_Particles.empty();
}

bool ParticleSystem::isDead()
{
	std::list<Attribute>::iterator i;
	for ( i = m_Particles.begin(); i != m_Particles.end(); i++ )
	{
		// is there at least one living particle?  If yes,
		// the system is not dead.
		if ( i->_isAlive )
			return false;
	}
	// no living particles found, the system must be dead.
	return true;
}

void ParticleSystem::removeDeadParticles()
{
	std::list<Attribute>::iterator i;

	i = m_Particles.begin();

	while ( i != m_Particles.end() )
	{
		if ( i->_isAlive == false )
		{
			// erase returns the next iterator, so no need to
			// incrememnt to the next one ourselves.
			i = m_Particles.erase( i );
		}
		else
		{
			i++; // next in list
		}
	}
}


//*****************************************************************************
// Explosion System
//********************

Firework::Firework(  )
{	
	m_Size = FIREWORK_SIZE;
	m_VBSize = 2048;
	m_VBOffset = 0;
	m_VBBatchSize = 512;
}

void Firework::SetParticles( D3DXVECTOR3 origin, ColorRange color, D3DXVECTOR3 directionMin, D3DXVECTOR3 directionMax, float lifetime,  int numParticles, int velocity )
{
	m_Origin = origin;
	m_Color = color;
	m_DirectionMax = directionMax;
	m_DirectionMin = directionMin;
	m_LifeTime = lifetime;
	m_Velocity = velocity;

	for ( int i = 0; i < numParticles; i++ )
		addParticle();
}


void Firework::resetParticle( Attribute* attribute, float age )
{
	attribute->_isAlive = true;
	D3DXVECTOR3 originRange;
	D3DXVECTOR3 originMin{ -1.0f, -1.0f, -1.0f };
	D3DXVECTOR3 originMax{ 1.0f, 1.0f, 1.0f };
	DDMath::GetRandomVector( &originRange, &originMin, &originMax );
	
	attribute->_position = m_Origin + originRange;

//	D3DXVECTOR3 min = D3DXVECTOR3( -1.0f, -1.0f, -1.0f );
//	D3DXVECTOR3 max = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

// 	GetRandomVector(
// 		&attribute->_velocity,
// 		&min,
// 		&max );
	
	DDMath::GetRandomVector( &attribute->_velocity, &m_DirectionMin, &m_DirectionMax );

	// normalize to make spherical
	D3DXVec3Normalize(
		&attribute->_velocity,
		&attribute->_velocity );

	attribute->_velocity *= m_Velocity;

	attribute->_color = D3DXCOLOR(
		DDMath::GetRandomFloat( m_Color.m_RMin, m_Color.m_RMax ),
		DDMath::GetRandomFloat( m_Color.m_GMin, m_Color.m_GMax ),
		DDMath::GetRandomFloat( m_Color.m_BMin, m_Color.m_BMax ),
		m_Color.m_Alpha );

	attribute->_age = age;
	attribute->_lifeTime = m_LifeTime; 
}

void Firework::UpdateItSelf( float timeDelta )
{
	std::list<Attribute>::iterator i;

	for ( i = m_Particles.begin(); i != m_Particles.end(); i++ )
	{
		// only update living particles
		if ( i->_isAlive )
		{
			i->_position += i->_velocity * timeDelta;

			i->_age += timeDelta;

			if ( i->_age > i->_lifeTime ) // kill 
				i->_isAlive = false;
		}
	}
}

void Firework::preRender()
{
	ParticleSystem::preRender();

	m_Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
	m_Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

	// read, but don't write particles to z-buffer
	m_Device->SetRenderState( D3DRS_ZWRITEENABLE, false );
}

void Firework::postRender()
{
	ParticleSystem::postRender();

	m_Device->SetRenderState( D3DRS_ZWRITEENABLE, true );
}

void Firework::PlayEffect( D3DXVECTOR3 origin )
{
	m_Origin = origin;
	reset();
}


//*****************************************************************************
// Snow System
//***************

Snow::Snow()
{	
	m_Size = 10.25f;
	m_VBSize = 2048;
	m_VBOffset = 0;
	m_VBBatchSize = 512;
}

void Snow::SetParticles( D3DXVECTOR3 origin, ColorRange color, D3DXVECTOR3 direction, D3DXVECTOR3 originMin, D3DXVECTOR3 originMax, float lifetime, int numParticles, int velocity )
{
	m_Origin = origin;
	m_Color = color;
	m_DirectionMax = direction;
	m_DirectionMin = ZERO_VECTOR3;
	m_LifeTime = lifetime;
	m_Velocity = velocity;
	m_OriginMin = originMin;
	m_OriginMax = originMax;

	for ( int i = 0; i < numParticles; i++ )
		addParticle();
}


void Snow::PlayEffect( D3DXVECTOR3 direction, float remainTime )
{
	m_DirectionMax = direction;
	m_LifeTime = remainTime;
	reset();
}


void Snow::resetParticle( Attribute* attribute, float age )
{
	attribute->_isAlive = true;
	
	// get random x, z coordinate for the position of the snow flake.

	D3DXVECTOR3 originRange;
// 	D3DXVECTOR3 originMin{ -10.0f, -10.0f, -10.0f };
// 	D3DXVECTOR3 originMax{ 10.0f, 10.0f, 10.0f };

	DDMath::GetRandomVector( &originRange, &m_OriginMin, &m_OriginMax );
	attribute->_position = originRange;
// 
// 	DDMath::GetRandomVector(
// 		&attribute->_position, 
// 		&m_DirectionMin,
// 		&m_DirectionMax);

	//DDMath::GetRandomVector( &attribute->_velocity, &m_DirectionMin, &m_DirectionMax );
	attribute->_velocity = m_DirectionMax;
	
	// normalize to make spherical
	D3DXVec3Normalize(
		&attribute->_velocity,
		&attribute->_velocity );

	attribute->_velocity *= m_Velocity;
		
	attribute->_color = D3DXCOLOR(
		DDMath::GetRandomFloat( m_Color.m_RMin, m_Color.m_RMax ),
		DDMath::GetRandomFloat( m_Color.m_GMin, m_Color.m_GMax ),
		DDMath::GetRandomFloat( m_Color.m_BMin, m_Color.m_BMax ),
		m_Color.m_Alpha );

	attribute->_age = age;	
	attribute->_lifeTime = m_LifeTime; 
}

void Snow::UpdateItSelf( float timeDelta )
{	
	std::list<Attribute>::iterator i;
	for ( i = m_Particles.begin(); i != m_Particles.end(); i++ )
	{
		if ( i == m_Particles.begin() )
			printf_s( "%f\n", i->_age );

		if ( i->_isAlive )
		{
			i->_position += i->_velocity * timeDelta;

			i->_age += timeDelta;
			if ( i->_age > i->_lifeTime ) // kill 
			{
				i->_isAlive = false;
				continue;
			}
			// is the point outside bounds?
			if ( m_OriginMin.x > i->_position.x || m_OriginMax.x < i->_position.x || m_OriginMin.z > i->_position.z || m_OriginMax.z < i->_position.z )
			{
				// nope so kill it, but we want to recycle dead 
				// particles, so respawn it instead.
				resetParticle( &( *i ), i->_age );
			}
		}		
	}
}
