#include "BaseShader.h"

//-------------------------------------------------------------------------------------------------
#include <stdio.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
BaseShader::BaseShader()
	: mSize(0)
	, mData(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
BaseShader::~BaseShader()
{
	if (mData != nullptr) {
		delete[] mData;
	}
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_��ǂݍ���
/// @param file_name �ǂݍ��ݑΏۂ̃t�@�C����
/// @return �ǂݍ��݌��� ����(true)
bool BaseShader::load(const char* file_name)
{
	FILE* fp = nullptr;
	// �g���q�`�F�b�N
	if (strstr(file_name, ".cso") == nullptr)
	{
		return false;
	}

	fopen_s(&fp, file_name, "rb");
	if (fp == nullptr)
	{
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	mSize = ftell(fp);
	if (mSize == 0)
	{
		fclose(fp);
		return false;
	}
	fseek(fp, 0, SEEK_SET);
	mData = new char[mSize];
	fread_s(mData, mSize, mSize, 1, fp);
	fclose(fp);

	return true;
}

} // namespace
// EOF
