#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
#include "OBJFileName.h"
#include "SpriteFileName.h"
#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
ResourceManager::ResourceManager()
	: mOBJLoader()
	, mSpriteLoader()
	, mTextureLoader()
	, mShaderLoader()
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
	mOBJLoader.load(OBJFileName::fileName(OBJList::Cube));
	mOBJLoader.load(OBJFileName::fileName(OBJList::Sphere));
	mOBJLoader.load(OBJFileName::fileName(OBJList::TestObj));

	// Sprites
	mSpriteLoader.load(SpriteFileName::fileName(SpriteList::TestTexture));

	// Shaders
	mShaderLoader.load(ShaderFileName::fileName(ShaderList::Unlit));
	mShaderLoader.load(ShaderFileName::fileName(ShaderList::Standard));
	mShaderLoader.load(ShaderFileName::fileName(ShaderList::Sprite));
}

//-------------------------------------------------------------------------------------------------
OBJLoader* ResourceManager::getOBJLoader()
{
	return &mOBJLoader;
}

//-------------------------------------------------------------------------------------------------
SpriteLoader* ResourceManager::getSpriteLoader()
{
	return &mSpriteLoader;
}

//-------------------------------------------------------------------------------------------------
TextureLoader* ResourceManager::getTextureLoader()
{
	return &mTextureLoader;
}

//-------------------------------------------------------------------------------------------------
ShaderLoader* ResourceManager::getShaderLoader()
{
	return &mShaderLoader;
}

} // namespace
// EOF
