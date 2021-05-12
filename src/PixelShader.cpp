#include "PixelShader.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
PixelShader::PixelShader()
	: mInterface(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
PixelShader::~PixelShader()
{
	if (mInterface) {
		mInterface->Release();
		mInterface = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_���쐬����
/// @param aFileName �w�肳�ꂽ�t�@�C���̃V�F�[�_���쐬����
/// @return �쐬���� ����(true)
bool PixelShader::create(const char* aFileName)
{
	// �V�F�[�_�̓ǂݍ���
	if (!load(aFileName)) {
		return false;
	}

	// �V�F�[�_�̍쐬
	if (FAILED(Direct3D11::getInst()->getDevice()->CreatePixelShader(
		mData,
		mSize,
		nullptr,
		&mInterface
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
const ID3D11PixelShader* PixelShader::shaderInterface() const
{
	return mInterface;
}

} // namespace
// EOF
