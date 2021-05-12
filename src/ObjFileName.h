#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>
#include "ObjList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// obj�t�@�C�����擾�p�N���X
class ObjFileName
{
public:
	static const char* fileName(ObjList aObjList);

private:
	ObjFileName();
	static std::unordered_map<ObjList, const char*> mFileName;

};

} // namespace
// EOF
