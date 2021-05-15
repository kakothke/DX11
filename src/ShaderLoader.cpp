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
/// �V�F�[�_�[���쐬����
/// @param aShaderList �쐬����V�F�[�_�[���w�肷��
/// @return �쐬���� ����(true)
bool ShaderLoader::load(ShaderList aShaderList)
{
	if (mShaderData.count(aShaderList)) {
		MessageBox(nullptr, TEXT("�V�F�[�_�[�t�@�C���̓�d�ǂݍ��݁B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	std::string fileName;
	// ���_�V�F�[�_�[���쐬����
	fileName = ShaderFileName::fileName(aShaderList);
	fileName += "_vs.cso";
	if (!mShaderData[aShaderList].vs.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("���_�V�F�[�_�[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �s�N�Z���V�F�[�_�[���쐬����
	fileName = ShaderFileName::fileName(aShaderList);
	fileName += "_ps.cso";
	if (!mShaderData[aShaderList].ps.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("�s�N�Z���V�F�[�_�[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[�f�[�^��Ԃ�
ShaderData* ShaderLoader::getShaderData(ShaderList aShaderList)
{
	if (mShaderData.count(aShaderList)) {
		return &mShaderData[aShaderList];
	}
	MessageBox(nullptr, TEXT("�ǂݍ��܂�Ă��Ȃ��V�F�[�_�[�f�[�^���擾���悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

} // namespace
// EOF
