struct appdata
{
    float4 pos : POSITION;
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
    int4 SPLIT;
    int4 UV_POS;
}

cbuffer CB_COLOR : register(b4)
{
    float4 COLOR;
}

v2p VS(appdata v)
{
    v2p o;
	
    // World
    o.pos = mul(v.pos, MATRIX_W);
    // Projection
    o.pos = mul(o.pos, MATRIX_P);
    
    // UV_Split
    o.uv.x = v.uv.x / SPLIT.x;
    o.uv.y = v.uv.y / SPLIT.y;
    o.uv.x += (1.0f / SPLIT.x) * UV_POS.x;
    o.uv.y += (1.0f / SPLIT.y) * UV_POS.y;
	
    return o;
}

Texture2D diffuse : register(t0);
SamplerState samplerDiffuse : register(s0);

float4 PS(v2p i) : SV_Target0
{
    float4 col;
	
    col = diffuse.Sample(samplerDiffuse, i.uv);
    col *= COLOR;
	
    return col;
}
