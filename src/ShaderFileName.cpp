#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// objファイル名を返す
/// @param aObjList 読み込みたいobjを指定する
/// @return ファイルパス
const char* ShaderFileName::fileName(ShaderList aObjList)
{
	return mFileName[aObjList];
}

//-------------------------------------------------------------------------------------------------
// objファイル名の初期化
std::unordered_map<ShaderList, const char*> ShaderFileName::mFileName = {
	{ShaderList::TestShader  , "res/shader/UnlitShader"},
};

} // namespace
// EOF
