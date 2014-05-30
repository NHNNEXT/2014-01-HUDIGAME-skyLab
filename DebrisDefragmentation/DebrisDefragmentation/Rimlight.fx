float4x4 g_matWVP; 
float4x4 g_matWorld; 
float4 g_camPos;
float3 g_vLightDir; 



struct VS_INPUT
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 Texcoord : TEXCOORD0;

};

struct VS_OUTPUT
{
	float4 Position : POSITION0;
	float4 Color	: COLOR0;
	float2 Texcoord : TEXCOORD0;
};

texture g_txScene;

sampler2D g_samScene =
sampler_state
{
	Texture = <g_txScene>;
	MinFilter = Point;
	MagFilter = Linear;
	MipFilter = Linear;
};

struct PS_INPUT
{
	float2 Texcoord : TEXCOORD0;
	float4 Color	: COLOR0;
};

//
float4 I_a = { 0.2f, 0.2f, 0.2f, 1.0f }; // ambient
float4 I_d = { 1.f, 1.f, 1.0f, 1.0f }; // diffuse

// 
float4 k_a = { 0.3f, 0.3f, 0.3f, 1.0f }; // ambient
float4 k_d = { 1.0f, 1.0f, 1.0f, 1.0f }; // diffuse



//////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////
VS_OUTPUT vs_main( VS_INPUT Input )
{
	VS_OUTPUT Output;

	Output.Position = mul( float4( Input.Position, 1.0 ), g_matWVP );
	Output.Texcoord = Input.Texcoord;
		
	float3 L = -g_vLightDir;
		float3 N = normalize( mul( Input.Normal, ( float3x3 )g_matWorld ) );
		Output.Color = I_a * k_a + I_d * k_d * max( 0, dot( N, L ) ); // ?뺤궛愿?


	return( Output );

}

float g_RimWidth = 0.7;
//////////////////////////////////////////////////////////////
VS_OUTPUT vs_RimLight( VS_INPUT Input )
{
	VS_OUTPUT Output;

	float4 pos = mul( float4( Input.Position, 1.0 ), g_matWorld );
	Output.Position = mul( float4( Input.Position, 1.0 ), g_matWVP );
	Output.Texcoord = Input.Texcoord;

	float4 vVertexToCam = normalize( g_camPos - pos );

	float3 N = normalize( mul( Input.Normal, g_matWorld ) );
	float4 LimColor1 = { -1.0, -1.0, -1.0, 1.0 };
	float4 LimColor2 = { 1.0, 0.0, 1.0, 1.0 };

	float fDot = smoothstep( 1.0f - saturate( g_RimWidth ), 1.0f, 1.0f - max( 0, dot( N, vVertexToCam ) ) );		//dot(N, vVertexToCam);
	Output.Color = ( fDot * LimColor2 + ( 1.0 - fDot ) * LimColor1 );

	float3 L = -g_vLightDir;
	Output.Color += ( I_a * k_a + I_d * k_d * max( 0, dot( N, L ) ) );

	return( Output );

}


//////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////
float4 ps_main( PS_INPUT Input ) : COLOR0
{
	//return tex2D( g_samScene, Input.Texcoord );
	//return Input.Color;
	return tex2D( g_samScene, Input.Texcoord ) + Input.Color;
}
//////////////////////////////////////////////////////////////
float4 ps_Sepia( PS_INPUT Input ) : COLOR
{
	float4 ColorOut = 0;
	ColorOut = tex2D( g_samScene, Input.Texcoord ) * Input.Color;

	float3 YCbCr;

	const float3 RGB2Y = { 0.29900, 0.58700, 0.11400 };
	float3x3 YCbCr2RGB = { { 1.0f, 0.00000f, +1.40200f },
	{ 1.0f, -0.34414f, -0.71414f },
	{ 1.0f, 1.77200f, 0.00000f },
	};

	float3 Color = tex2D( g_samScene, Input.Texcoord ).xyz * Input.Color; // 원본색

	YCbCr.x = dot( Color, RGB2Y );    // Y
	YCbCr.y = -0.200;               // Cb
	YCbCr.z = 0.100;               // Cr

	ColorOut.rgb = mul( YCbCr2RGB, YCbCr );// YCbCr을 RGB로


	return ColorOut;
}

technique RenderScene
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}



//////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////
float4 PS_MonoTone( PS_INPUT Input ) : COLOR0
{
	float4 Out = 0.0f;
	float4 d = float4( 0.299, 0.587, 0.114, 0 );
	float4 t = tex2D( g_samScene, Input.Texcoord );

	Out = dot( d, t );
	Out.w = 1;
	return Out;
}


technique RenderMono
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 PS_MonoTone();
	}
}



//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
float4 PS_Inverse( PS_INPUT Input ) : COLOR0
{
	float4 t = tex2D( g_samScene, Input.Texcoord );
	return 1 - t;
}

technique RenderInverse
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 PS_Inverse();
	}
}


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
technique RenderRimLight
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_RimLight();
		PixelShader = compile ps_2_0 ps_main();
	}
}
