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

cbuffer CB_SPRITE : register(b1)
{
    float4x4 MATRIX_P;
    float4x4 MATRIX_W;
    float4 PIVOT;
    int2 SPLIT;
}

cbuffer CB_COLOR : register(b4)
{
    float4 COLOR;
}

v2p VS(appdata v)
{
    v2p o;
	
    o.pos = mul(float4(v.pos, 1.0f), MATRIX_W);
    o.pos = mul(o.pos, MATRIX_P);
    o.uv.x = v.uv.x / SPLIT.x;
    o.uv.y = v.uv.y / SPLIT.y;
	
    return o;
}

Texture2D diffuse : register(t0);
SamplerState samplerDiffuse : register(s0);

float4 PS(v2p i) : SV_Target0
{
    float4 col;
	
    col = diffuse.Sample(samplerDiffuse, i.uv);
    col.a *= COLOR;
	
    return col;
}
