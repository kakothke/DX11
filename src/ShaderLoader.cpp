#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
#include <string>
#include <codecvt>
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
bool ShaderLoader::load(const char* const aFileName)
{
	if (mShaderData.count(aFileName)) {
		MessageBox(nullptr, TEXT("�V�F�[�_�[�t�@�C���̓�d�ǂݍ��݁B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	if (!createVertexShader(aFileName)) {
		MessageBox(nullptr, TEXT("VertexShader�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createInputLayout(aFileName)) {
		MessageBox(nullptr, TEXT("InputLayout�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createPixelShader(aFileName)) {
		MessageBox(nullptr, TEXT("PixelShader�V�F�[�_�[�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[�f�[�^���擾����
ShaderData* ShaderLoader::getShaderData(const char* const aFileName)
{
	if (mShaderData.count(aFileName)) {
		return &mShaderData[aFileName];
	}
	MessageBox(nullptr, TEXT("���݂��Ȃ��V�F�[�_�[�f�[�^���擾���悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// ���_�V�F�[�_�[�쐬
bool ShaderLoader::createVertexShader(const char* const aFileName)
{
	ID3DBlob* blob = nullptr;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring fileName = cv.from_bytes(aFileName);

	if (FAILED(D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, &blob, nullptr))) {
		return false;
	}
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateVertexShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&mShaderData[aFileName].vs
	))) {
		return false;
	}

	blob->Release();
	blob = nullptr;

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���̓��C�A�E�g�쐬
bool ShaderLoader::createInputLayout(const char* const aFileName)
{
	ID3DBlob* blob = nullptr;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring fileName = cv.from_bytes(aFileName);

	if (FAILED(D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, &blob, nullptr))) {
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE",0, DXGI_FORMAT_R32G32_FLOAT, 0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	if (FAILED(Direct3D11::getInst()->getDevice()->CreateInputLayout(
		vertexDesc,
		ARRAYSIZE(vertexDesc),
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&mShaderData[aFileName].inputLayout
	))) {
		return false;
	}

	blob->Release();
	blob = nullptr;

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �s�N�Z���V�F�[�_�[�쐬
bool ShaderLoader::createPixelShader(const char* const aFileName)
{
	ID3DBlob* blob = nullptr;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring fileName = cv.from_bytes(aFileName);

	if (FAILED(D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, &blob, nullptr))) {
		return false;
	}
	if (FAILED(Direct3D11::getInst()->getDevice()->CreatePixelShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&mShaderData[aFileName].ps
	))) {
		return false;
	}

	blob->Release();
	blob = nullptr;

	return true;
}

} // namespace
// EOF
