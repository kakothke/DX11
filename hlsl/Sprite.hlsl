struct appdata
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct v2p
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD1;
};

cbuffer CB_MATRIX2D : register(b1)
{
    float4x4 PROJ_2D;
}

v2p VS(appdata v)
{
    v2p o;
	
    o.pos = mul(float4(v.pos, 1.0f), PROJ_2D);    
    o.uv = v.uv;
	
    return o;
}

Texture2D diffuse : register(t0);
SamplerState samplerDiffuse : register(s0);

float4 PS(v2p i) : SV_Target0
{
    float4 col;
	
    col = diffuse.Sample(samplerDiffuse, i.uv);
    //output = input.col * tex;
	
    return col;
}
