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

	OBJLoader* OBJ();
	SpriteLoader* Sprite();
	TextureLoader* Texture();
	ShaderLoader* Shader();

private:
	OBJLoader mOBJ;
	SpriteLoader mSprite;
	TextureLoader mTexture;
	ShaderLoader mShader;

};

} // namespace
// EOF
