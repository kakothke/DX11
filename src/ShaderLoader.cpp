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
/// @param aShaderList 作成するシェーダーを指定する
/// @return 作成結果 成功(true)
bool ShaderLoader::load(ShaderList aShaderList)
{
	if (mShaderData.count(aShaderList)) {
		MessageBox(nullptr, TEXT("シェーダーファイルの二重読み込み。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	std::string fileName;
	// 頂点シェーダーを作成する
	fileName = ShaderFileName::fileName(aShaderList);
	fileName += "_vs.cso";
	if (!mShaderData[aShaderList].vs.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("頂点シェーダーの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// ピクセルシェーダーを作成する
	fileName = ShaderFileName::fileName(aShaderList);
	fileName += "_ps.cso";
	if (!mShaderData[aShaderList].ps.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("ピクセルシェーダーの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// シェーダーデータを返す
ShaderData* ShaderLoader::getShaderData(ShaderList aShaderList)
{
	if (mShaderData.count(aShaderList)) {
		return &mShaderData[aShaderList];
	}
	MessageBox(nullptr, TEXT("読み込まれていないシェーダーデータを取得しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

} // namespace
// EOF
