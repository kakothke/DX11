struct VS_IN
{
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
};
 
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
};
 
cbuffer ConstantBuffer
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
}

VS_OUT main(VS_IN input)
{
    VS_OUT output;
    
    output.pos = mul(input.pos, World);
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);
    
    output.col = (1, 1, 1, 1);

    return output;
}
