#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
#include <string>
#include <codecvt>
#include "ShaderFileName.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
/// シェーダーを読み込む
/// @param aFileName 読み込みたいシェーダーのファイルパス
/// @return 作成結果 成功(true)
bool ShaderLoader::load(const char* const aFileName)
{
	if (mShaderData.count(aFileName)) {
		MessageBox(nullptr, TEXT("シェーダーファイルの二重読み込み。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
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
ShaderData* ShaderLoader::getShaderData(const char* const aFileName)
{
	if (mShaderData.count(aFileName)) {
		return &mShaderData[aFileName];
	}
	MessageBox(nullptr, TEXT("存在しないシェーダーデータを取得しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// 頂点シェーダー作成
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
/// 入力レイアウト作成
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
/// ピクセルシェーダー作成
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
