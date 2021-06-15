#pragma once

//-------------------------------------------------------------------------------------------------
#include "Singleton.h"
#include "OBJLoader.h"
#include "SpriteLoader.h"
#include "TextureLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// リソース管理クラス
class Resource : public Singleton<Resource>
{
public:
	Resource();
	~Resource();

	bool initialize();

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
