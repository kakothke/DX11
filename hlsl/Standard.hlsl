struct VS_IN
{
    float4 pos : POSITION0;
    float2 uv : TEXTURE0;
    float4 nor : NORMAL0;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXTURE0;
    float4 nor : NORMAL;
};

cbuffer CB_MATRIX : register(b0)
{
    float4x4 MATRIX_W;
    float4x4 MATRIX_V;
    float4x4 MATRIX_P;
}

cbuffer CB_DLIGHT : register(b3)
{
    float4 LIGHT_VEC;
    float4 LIGHT_COL;
};

cbuffer CB_COLOR : register(b4)
{
    float4 COLOR;
}

VS_OUT VS(VS_IN input)
{
    VS_OUT output;
    
    output.pos = mul(input.pos, MATRIX_W);
    output.pos = mul(output.pos, MATRIX_V);
    output.pos = mul(output.pos, MATRIX_P);
    
    output.uv = input.uv;

    float4 normal;
    input.nor.w = 0.0;
    normal = mul(input.nor, MATRIX_W).xyzw;
    normal = normalize(normal);
    output.nor = saturate(dot(normal, LIGHT_VEC));

    return output;
}

Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);

cbuffer CB_MATERIAL : register(b5)
{
    float4 MATERIAL_A;
    float4 MATERIAL_D;
    float4 MATERIAL_S;
}

float4 PS(VS_OUT input) : SV_Target
{
    float4 col;
    
    col = (LIGHT_COL * MATERIAL_D * input.nor);
    col += Texture.Sample(Sampler, input.uv);
    col *= COLOR;

    return col;
}
