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

cbuffer CB_DLIGHT : register(b2)
{
    float4 LIGHT_VEC;
    float4 LIGHT_COL;
};

VS_OUT VS(VS_IN input)
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

cbuffer CB_MATERIAL : register(b3)
{
    float4 MATERIAL_A;
    float4 MATERIAL_D;
    float4 MATERIAL_S;
}

float4 PS(VS_OUT input) : SV_Target
{
    float material_ambient_power = 1.0;
    float material_diffuse_power = 1.0;
    float total_power = material_ambient_power + material_diffuse_power;

    if (total_power == 0)
    {
        total_power = 1.0;
    }

    float ambient_power = material_ambient_power / total_power;
    float diffuse_power = material_diffuse_power / total_power;

    float4 ambient_color = MATERIAL_A * ambient_power;
    float4 diffuse_color = (LIGHT_COL * MATERIAL_D * input.nor) * diffuse_power;

	// アンビエントカラー + ディフューズカラー
    float4 out_color = ambient_color + diffuse_color;

    return out_color;
}
