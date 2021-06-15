#pragma once

//-------------------------------------------------------------------------------------------------
#include "Singleton.h"


//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// リソース管理クラス
class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	bool initialize();

};

} // namespace
// EOF
