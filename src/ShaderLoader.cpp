#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
#include <string>
#include <codecvt>
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
ShaderLoader::ShaderLoader()
	: mShaderData()
{
	mShaderData.clear();
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
ShaderLoader::~ShaderLoader()
{
	if (!mShaderData.empty()) {
		mShaderData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
ShaderLoader::ShaderData::~ShaderData()
{
	if (vs) {
		vs->Release();
		vs = nullptr;
	}
	if (ps) {
		ps->Release();
		ps = nullptr;
	}
	if (inputLayout) {
		inputLayout->Release();
		inputLayout = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// シェーダーを読み込む
/// @param aFileName 読み込みたいシェーダーのファイルパス
/// @return 結果 成功(true)
bool ShaderLoader::load(const LPCSTR aFileName)
{
	if (mShaderData.count(aFileName)) {
		MessageBox(nullptr, TEXT("シェーダーファイルの二重読み込み。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!std::ifstream(aFileName)) {
		MessageBox(nullptr, TEXT("読み込もうとしているhlslが存在しません。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createVertexShader(aFileName)) {
		MessageBox(nullptr, TEXT("VertexShaderの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createInputLayout(aFileName)) {
		MessageBox(nullptr, TEXT("InputLayoutの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createPixelShader(aFileName)) {
		MessageBox(nullptr, TEXT("PixelShaderシェーダーの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// シェーダーデータを取得する
/// @param aFileName 取得したいシェーダーのファイルパス
/// @return シェーダーデータ
ShaderLoader::ShaderData* ShaderLoader::getShaderData(const LPCSTR aFileName)
{
	if (!mShaderData.count(aFileName)) {
		MessageBox(nullptr, TEXT("存在しないシェーダーデータを取得しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return nullptr;
	}
	return &mShaderData[aFileName];
}

//-------------------------------------------------------------------------------------------------
/// 頂点シェーダーを作成する
/// @param aFileName 読み込みたいシェーダーのファイルパス
/// @return 作成結果 成功(true)
bool ShaderLoader::createVertexShader(const LPCSTR aFileName)
{
	ID3DBlob* blob = nullptr;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring fileName = cv.from_bytes(aFileName);

	HRESULT hr;
	hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, &blob, nullptr);
	if (FAILED(hr)) {
		return false;
	}
	const auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &mShaderData[aFileName].vs);
	if (FAILED(hr)) {
		return false;
	}

	blob->Release();
	blob = nullptr;

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 入力レイアウトを作成する
/// @param aFileName 読み込みたいシェーダーのファイルパス
/// @return 作成結果 成功(true)
bool ShaderLoader::createInputLayout(const LPCSTR aFileName)
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

	// リフレクションから頂点レイアウト作成
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

	// 頂点レイアウト作成
	const auto device = Direct3D11::getInst()->getDevice();
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
/// リフレクション内のDXGIFormatを検索する
/// @param aParamDesc 読み込むDesc
/// @return DXGI_FORMAT
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

	MessageBox(nullptr, TEXT("入力レイアウトの作成処理関数の追記が必要です。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return DXGI_FORMAT_UNKNOWN;
}

//-------------------------------------------------------------------------------------------------
/// ピクセルシェーダーを作成する
/// @param aFileName 読み込みたいシェーダーのファイルパス
/// @return 作成結果 成功(true)
bool ShaderLoader::createPixelShader(const LPCSTR aFileName)
{
	ID3DBlob* blob = nullptr;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring fileName = cv.from_bytes(aFileName);

	HRESULT hr;
	hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, "PS", "ps_5_0", 0, 0, &blob, nullptr);
	if (FAILED(hr)) {
		return false;
	}
	const auto device = Direct3D11::getInst()->getDevice();
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
