struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 nor : NORMAL;
};

cbuffer ConstantBuffer
{
    float4x4 World; // ワールド変換行列
    float4x4 View; // ビュー変換行列
    float4x4 Projection; // 透視射影変換行列
    float4 LightVector; // ライト方向
    float4 LightColor; // ライトカラー
    float4 MaterialAmbient; // アンビエント
    float4 MaterialDiffuse; // ディフューズ
    float4 MaterialSpecular; // スペキュラー
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

    float4 ambient_color = MaterialAmbient * ambient_power;
    float4 diffuse_color = (LightColor * MaterialDiffuse * input.nor) * diffuse_power;

	// アンビエントカラー + ディフューズカラー
    float4 out_color = ambient_color + diffuse_color;

    return out_color;
}
