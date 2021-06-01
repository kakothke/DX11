struct VS_INPUT
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD1;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
	
    output.pos.xyz = input.pos.xyz;
    output.pos.w = 1.0f;
    output.uv = input.uv;
	
    return output;
}

Texture2D diffuse : register(t0);
SamplerState samplerDiffuse : register(s0);

float4 PS(VS_OUTPUT input) : SV_Target0
{
    float4 output;
	
    float4 tex = diffuse.Sample(samplerDiffuse, input.uv);
    //output = input.col * tex;
	
    return output;
}
