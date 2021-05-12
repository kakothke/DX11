#include "VertexShader.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
VertexShader::VertexShader()
	: mInterface(nullptr)
	, mInputLayout(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
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
/// シェーダを作成する
/// @param aFileName 指定されたファイルのシェーダを作成する
/// @return 作成結果 成功(true)
bool VertexShader::create(const char* aFileName)
{
	// シェーダの読み込み
	if (!load(aFileName)) {
		return false;
	}

	// シェーダの作成
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateVertexShader(
		mData,
		mSize,
		nullptr,
		&mInterface
	))) {
		return false;
	}

	// 入力レイアウトの作成
	if (!createInputLayout()) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 入力レイアウトを作成する
/// @detail （とりあえず手動で作成するが、後々自動作成出来る様にさせたい）
/// @return 作成結果 成功(true)
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
