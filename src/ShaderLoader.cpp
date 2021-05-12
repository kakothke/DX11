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
/// @param aList �쐬����V�F�[�_�[���w�肷��
/// @return �쐬���� ����(true)
bool ShaderLoader::load(ShaderList aList)
{
	std::string fileName;

	// ���_�V�F�[�_�[���쐬����
	fileName = ShaderFileName::fileName(aList);
	fileName += "_vs.cso";
	if (!mShaderData[aList].vs.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("���_�V�F�[�_�[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	// �s�N�Z���V�F�[�_�[���쐬����
	fileName = ShaderFileName::fileName(aList);
	fileName += "_ps.cso";
	if (!mShaderData[aList].ps.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("�s�N�Z���V�F�[�_�[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[�\���̂�Ԃ�
const ShaderData& ShaderLoader::shaderData(ShaderList aList)
{
	return mShaderData[aList];
}

} // namespace
// EOF
