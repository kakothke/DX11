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
/// シェーダーを読み込む
/// @param aFileName 読み込みたいシェーダーのファイルパス
/// @return 作成結果 成功(true)
bool ShaderLoader::load(const char* aFileName)
{
	if (mShaderData.count(aFileName)) {
		MessageBox(nullptr, TEXT("シェーダーファイルの二重読み込み。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	std::string fileName;
	// 頂点シェーダーを作成する
	fileName = aFileName;
	fileName += "_vs.cso";
	if (!mShaderData[aFileName].vs.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("頂点シェーダーの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// ピクセルシェーダーを作成する
	fileName = aFileName;
	fileName += "_ps.cso";
	if (!mShaderData[aFileName].ps.create(fileName.c_str())) {
		MessageBox(nullptr, TEXT("ピクセルシェーダーの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// シェーダーデータを取得する
ShaderData* ShaderLoader::getShaderData(const char* aFileName)
{
	if (mShaderData.count(aFileName)) {
		return &mShaderData[aFileName];
	}
	MessageBox(nullptr, TEXT("存在しないシェーダーデータを取得しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

} // namespace
// EOF
