#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
#include <string>
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
/// シェーダーを作成する
/// @param aList 作成するシェーダーを指定する
/// @return 作成結果 成功(true)
bool ShaderLoader::load(ShaderList aList)
{
	std::string fileName;

	// 頂点シェーダーを作成する
	fileName = ShaderFileName::fileName(aList);
	fileName += "_vs.cso";
	if (!mShaderData[aList].vs.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("頂点シェーダーの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	// ピクセルシェーダーを作成する
	fileName = ShaderFileName::fileName(aList);
	fileName += "_ps.cso";
	if (!mShaderData[aList].ps.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("ピクセルシェーダーの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// シェーダー構造体を返す
const ShaderData& ShaderLoader::shaderData(ShaderList aList)
{
	return mShaderData[aList];
}

} // namespace
// EOF
