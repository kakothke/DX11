#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
#include <string>
#include "ShaderFileName.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
ShaderLoader::ShaderLoader()
	: mShaderData()
{
	mShaderData.clear();
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
ShaderLoader::~ShaderLoader()
{
	if (!mShaderData.empty()) {
		mShaderData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[��ǂݍ���
/// @param aFileName �ǂݍ��݂����V�F�[�_�[�̃t�@�C���p�X
/// @return �쐬���� ����(true)
bool ShaderLoader::load(const char* aFileName)
{
	if (mShaderData.count(aFileName)) {
		MessageBox(nullptr, TEXT("�V�F�[�_�[�t�@�C���̓�d�ǂݍ��݁B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	std::string fileName;
	// ���_�V�F�[�_�[���쐬����
	fileName = aFileName;
	fileName += "_vs.cso";
	if (!mShaderData[aFileName].vs.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("���_�V�F�[�_�[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �s�N�Z���V�F�[�_�[���쐬����
	fileName = aFileName;
	fileName += "_ps.cso";
	if (!mShaderData[aFileName].ps.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("�s�N�Z���V�F�[�_�[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[�f�[�^���擾����
ShaderData* ShaderLoader::getShaderData(const char* aFileName)
{
	if (mShaderData.count(aFileName)) {
		return &mShaderData[aFileName];
	}
	MessageBox(nullptr, TEXT("���݂��Ȃ��V�F�[�_�[�f�[�^���擾���悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

} // namespace
// EOF
