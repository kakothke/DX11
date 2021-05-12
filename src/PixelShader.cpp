#include "PixelShader.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
PixelShader::PixelShader()
	: mInterface(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
PixelShader::~PixelShader()
{
	if (mInterface) {
		mInterface->Release();
		mInterface = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// シェーダを作成する
/// @param aFileName 指定されたファイルのシェーダを作成する
/// @return 作成結果 成功(true)
bool PixelShader::create(const char* aFileName)
{
	// シェーダの読み込み
	if (!load(aFileName)) {
		return false;
	}

	// シェーダの作成
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
