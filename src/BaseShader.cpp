#include "BaseShader.h"

//-------------------------------------------------------------------------------------------------
#include <stdio.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BaseShader::BaseShader()
	: mSize(0)
	, mData(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
BaseShader::~BaseShader()
{
	if (mData != nullptr) {
		delete[] mData;
	}
}

//-------------------------------------------------------------------------------------------------
/// シェーダを読み込む
/// @param file_name 読み込み対象のファイル名
/// @return 読み込み結果 成功(true)
bool BaseShader::load(const char* file_name)
{
	FILE* fp = nullptr;
	// 拡張子チェック
	if (strstr(file_name, ".cso") == nullptr)
	{
		return false;
	}

	fopen_s(&fp, file_name, "rb");
	if (fp == nullptr)
	{
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	mSize = ftell(fp);
	if (mSize == 0)
	{
		fclose(fp);
		return false;
	}
	fseek(fp, 0, SEEK_SET);
	mData = new char[mSize];
	fread_s(mData, mSize, mSize, 1, fp);
	fclose(fp);

	return true;
}

} // namespace
// EOF
