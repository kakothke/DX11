#pragma once

//-------------------------------------------------------------------------------------------------
#include "Singleton.h"


//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ���\�[�X�Ǘ��N���X
class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	bool initialize();

};

} // namespace
// EOF
