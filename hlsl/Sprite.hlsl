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
	
    // World
    o.pos = mul(v.pos, MATRIX_W);
    // Projection
    o.pos = mul(o.pos, MATRIX_P);
    
    // zŽ²‚ð-1~1‚ÌŠÔ‚ÉŽû‚ß‚é
    float nearZ = 0.3f;
    float farZ = 1000;
    o.pos.z = (o.pos.z - nearZ) / (farZ - nearZ);
    float minZ = -1;
    float maxZ = 1;
    o.pos.z = o.pos.z * (maxZ - minZ) + minZ;
    
    // UV_Split
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
