#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>
#include "OBJList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// OBJファイル名取得用クラス
class OBJFileName
{
public:
	static const char* fileName(OBJList aOBJList);

private:
	OBJFileName();
	static std::unordered_map<OBJList, const char*> mFileName;

};

} // namespace
// EOF
