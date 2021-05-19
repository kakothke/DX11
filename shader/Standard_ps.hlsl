struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 nor : NORMAL;
};

cbuffer ConstantBuffer
{
    float4x4 World; // ���[���h�ϊ��s��
    float4x4 View; // �r���[�ϊ��s��
    float4x4 Projection; // �����ˉe�ϊ��s��
    float4 LightVector; // ���C�g����
    float4 LightColor; // ���C�g�J���[
    float4 MaterialAmbient; // �A���r�G���g
    float4 MaterialDiffuse; // �f�B�t���[�Y
    float4 MaterialSpecular; // �X�y�L�����[
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

	// �A���r�G���g�J���[ + �f�B�t���[�Y�J���[
    float4 out_color = ambient_color + diffuse_color;

    return out_color;
}
