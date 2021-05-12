#include "VertexShader.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
VertexShader::VertexShader()
	: mInterface(nullptr)
	, mInputLayout(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
VertexShader::~VertexShader()
{
	if (mInterface) {
		mInterface->Release();
		mInterface = nullptr;
	}
	if (mInputLayout) {
		mInputLayout->Release();
		mInputLayout = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_���쐬����
/// @param aFileName �w�肳�ꂽ�t�@�C���̃V�F�[�_���쐬����
/// @return �쐬���� ����(true)
bool VertexShader::create(const char* aFileName)
{
	// �V�F�[�_�̓ǂݍ���
	if (!load(aFileName)) {
		return false;
	}

	// �V�F�[�_�̍쐬
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateVertexShader(
		mData,
		mSize,
		nullptr,
		&mInterface
	))) {
		return false;
	}

	// ���̓��C�A�E�g�̍쐬
	if (!createInputLayout()) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���̓��C�A�E�g���쐬����
/// @detail �i�Ƃ肠�����蓮�ō쐬���邪�A��X�����쐬�o����l�ɂ��������j
/// @return �쐬���� ����(true)
bool VertexShader::createInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	if (FAILED(Direct3D11::getInst()->getDevice()->CreateInputLayout(
		vertexDesc,
		ARRAYSIZE(vertexDesc),
		mData,
		mSize,
		&mInputLayout
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
const ID3D11VertexShader* VertexShader::shaderInterface() const
{
	return mInterface;
}

//-------------------------------------------------------------------------------------------------
const ID3D11InputLayout* VertexShader::inputLayout() const
{
	return mInputLayout;
}

} // namespace
// EOF
