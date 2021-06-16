#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
#include <string>
#include <codecvt>
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
	if (!std::ifstream(aFileName)) {
		MessageBox(nullptr, TEXT("�ǂݍ������Ƃ��Ă���hlsl�����݂��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
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

	HRESULT hr;
	hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, &blob, nullptr);
	if (FAILED(hr)) {
		return false;
	}
	static auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &mShaderData[aFileName].vs);
	if (FAILED(hr)) {
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
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring fileName = cv.from_bytes(aFileName);

	HRESULT hr;
	ID3DBlob* blob = nullptr;
	hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, &blob, nullptr);
	if (FAILED(hr)) {
		return false;
	}

	ID3D11ShaderReflection* reflection = nullptr;
	hr = D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection);
	if (FAILED(hr)) {
		return false;
	}

	D3D11_SHADER_DESC shaderDesc;
	reflection->GetDesc(&shaderDesc);

	// ���t���N�V�������璸�_���C�A�E�g�쐬
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (UINT i = 0; i < shaderDesc.InputParameters; i++) {
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		reflection->GetInputParameterDesc(i, &paramDesc);

		D3D11_INPUT_ELEMENT_DESC elementDesc = {
			paramDesc.SemanticName,
			paramDesc.SemanticIndex,
			getDxgiFormat(paramDesc),
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		};
		inputLayoutDesc.push_back(elementDesc);
	}
	reflection->Release();
	reflection = nullptr;

	// ���_���C�A�E�g�쐬
	static auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreateInputLayout(
		&inputLayoutDesc[0],
		inputLayoutDesc.size(),
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&mShaderData[aFileName].inputLayout
	);
	if (FAILED(hr)) {
		return false;
	}

	blob->Release();
	blob = nullptr;

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���t���N�V��������DXGIFormat����������
DXGI_FORMAT ShaderLoader::getDxgiFormat(D3D11_SIGNATURE_PARAMETER_DESC aParamDesc)
{
	if (aParamDesc.Mask == 1) {
		switch (aParamDesc.ComponentType) {
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			return DXGI_FORMAT_R32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32_FLOAT;
		}
	} else if (aParamDesc.Mask <= 3) {
		switch (aParamDesc.ComponentType) {
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			return DXGI_FORMAT_R32G32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32_FLOAT;
		}
	} else if (aParamDesc.Mask <= 7) {
		switch (aParamDesc.ComponentType) {
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32B32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			return DXGI_FORMAT_R32G32B32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		}
	} else if (aParamDesc.Mask <= 15) {
		switch (aParamDesc.ComponentType) {
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32B32A32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:
			return DXGI_FORMAT_R32G32B32A32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			std::string sementicName = aParamDesc.SemanticName;
			if (sementicName == "POSITION" || sementicName == "NORMAL") {
				return DXGI_FORMAT_R32G32B32_FLOAT;
			} else {
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
		}
	}

	MessageBox(nullptr, TEXT("���̓��C�A�E�g�̍쐬�����֐��̒ǋL���K�v�ł��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return DXGI_FORMAT_UNKNOWN;
}

//-------------------------------------------------------------------------------------------------
/// �s�N�Z���V�F�[�_�[�쐬
bool ShaderLoader::createPixelShader(const char* const aFileName)
{
	ID3DBlob* blob = nullptr;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring fileName = cv.from_bytes(aFileName);

	HRESULT hr;
	hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, &blob, nullptr);
	if (FAILED(hr)) {
		return false;
	}
	static auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &mShaderData[aFileName].ps);
	if (FAILED(hr)) {
		return false;
	}

	blob->Release();
	blob = nullptr;

	return true;
}

} // namespace
// EOF
