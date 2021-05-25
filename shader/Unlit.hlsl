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
 
cbuffer CB_MATRIX : register(b0)
{
    float4x4 MATRIX_W;
    float4x4 MATRIX_V;
    float4x4 MATRIX_P;
}

VS_OUT VS(VS_IN input)
{
    VS_OUT output;
    
    output.pos = mul(input.pos, MATRIX_W);
    output.pos = mul(output.pos, MATRIX_V);
    output.pos = mul(output.pos, MATRIX_P);
    
    output.col = float4(1, 1, 1, 1);

    return output;
}
 
float4 PS(VS_OUT input) : SV_Target
{
    return input.col;
}
