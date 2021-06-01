#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
#include "OBJFileName.h"
#include "SpriteFileName.h"
#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
ResourceManager::ResourceManager()
	: mOBJ()
	, mSprite()
	, mTexture()
	, mShader()
{
}

//-------------------------------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
}

//-------------------------------------------------------------------------------------------------
void ResourceManager::initialize()
{
	// OBJs
	mOBJ.load(OBJFileName::fileName(OBJList::Cube));
	mOBJ.load(OBJFileName::fileName(OBJList::Sphere));
	mOBJ.load(OBJFileName::fileName(OBJList::TestObj));

	// Sprites
	mSprite.load(SpriteFileName::fileName(SpriteList::TestTexture));

	// Shaders
	mShader.load(ShaderFileName::fileName(ShaderList::Unlit));
	mShader.load(ShaderFileName::fileName(ShaderList::Standard));
	mShader.load(ShaderFileName::fileName(ShaderList::Sprite));
}

//-------------------------------------------------------------------------------------------------
OBJLoader* ResourceManager::OBJ()
{
	return &mOBJ;
}

//-------------------------------------------------------------------------------------------------
SpriteLoader* ResourceManager::Sprite()
{
	return &mSprite;
}

//-------------------------------------------------------------------------------------------------
TextureLoader* ResourceManager::Texture()
{
	return &mTexture;
}

//-------------------------------------------------------------------------------------------------
ShaderLoader* ResourceManager::Shader()
{
	return &mShader;
}

} // namespace
// EOF
