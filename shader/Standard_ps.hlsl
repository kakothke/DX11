struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 nor : NORMAL;
};

cbuffer CB_LIGHT : register(b2)
{
    float4 LIGHT_VEC;
    float4 LIGHT_COL;
};

cbuffer CB_MATERIAL : register(b3)
{
    float4 MATERIAL_A;
    float4 MATERIAL_D;
    float4 MATERIAL_S;
}

float4 main(PS_IN input) : SV_Target
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
