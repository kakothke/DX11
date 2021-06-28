#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "OBJLoader.h"
#include "TextureLoader.h"
#include "ShaderLoader.h"
#include "Sound.h"
#include "FontLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ���\�[�X�Ǘ��N���X
class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	void initialize();

};

} // namespace
// EOF
