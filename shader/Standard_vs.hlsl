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

VS_OUT main(VS_IN input)
{
    VS_OUT output;

	// ���[�J�����W * ���[���h���W�ϊ��s��
    output.pos = mul(input.pos, World);
	// ���[���h���W * �r���[���W�ϊ��s��
    output.pos = mul(output.pos, View);
	// �r���[���W * �v���W�F�N�V�������W�ϊ��s��
    output.pos = mul(output.pos, Projection);

    float4 normal;
	// �ړ����v�Z�ɔ��f�����Ȃ�
    input.nor.w = 0.0;
	// ���_�̖@���Ƀ��[���h�s����|�����킹��
	// ���[���h���W��ł̖@���̌����ɕϊ�����
    normal = mul(input.nor, World).xyzw;
    normal = normalize(normal);
	// saturate => �����Ŏw�肵���l��0�`1�Ԃł͈̔͂Ɏ��߂�
	// dot => ���όv�Z
    output.nor = saturate(dot(normal, LightVector));

    return output;
}
