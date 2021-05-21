struct VS_IN
{
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 nor : NORMAL;
};

cbuffer CB_MATRIX : register(b0)
{
    float4x4 MATRIX_W;
    float4x4 MATRIX_V;
    float4x4 MATRIX_P;
}

cbuffer CB_LIGHT : register(b2)
{
    float4 LIGHT_VEC;
    float4 LIGHT_COL;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output;
    
    output.pos = mul(input.pos, MATRIX_W);
    output.pos = mul(output.pos, MATRIX_V);
    output.pos = mul(output.pos, MATRIX_P);

    float4 normal;
    input.nor.w = 0.0;
    normal = mul(input.nor, MATRIX_W).xyzw;
    normal = normalize(normal);
    output.nor = saturate(dot(normal, LIGHT_VEC));

    return output;
}
