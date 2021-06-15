#pragma once

//-------------------------------------------------------------------------------------------------
#include "Singleton.h"
#include "OBJLoader.h"
#include "SpriteLoader.h"
#include "TextureLoader.h"
#include "ShaderLoader.h"
#include "Sound.h"

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
