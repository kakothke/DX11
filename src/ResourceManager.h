#pragma once

//-------------------------------------------------------------------------------------------------
#include "Singleton.h"
#include "OBJLoader.h"
#include "SpriteLoader.h"
#include "TextureLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// リソース管理クラス
class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	void initialize();

	OBJLoader* getOBJLoader();
	SpriteLoader* getSpriteLoader();
	TextureLoader* getTextureLoader();
	ShaderLoader* getShaderLoader();

private:
	OBJLoader mOBJLoader;
	SpriteLoader mSpriteLoader;
	TextureLoader mTextureLoader;
	ShaderLoader mShaderLoader;

};

} // namespace
// EOF
