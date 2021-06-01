#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

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
	mOBJ.load(ResourceFileName::OBJ.at(OBJList::Cube));
	mOBJ.load(ResourceFileName::OBJ.at(OBJList::Sphere));
	mOBJ.load(ResourceFileName::OBJ.at(OBJList::Test));

	// Sprites
	mSprite.load(ResourceFileName::Sprite.at(SpriteList::Test));

	// Shaders
	mShader.load(ResourceFileName::Shader.at(ShaderList::Unlit));
	mShader.load(ResourceFileName::Shader.at(ShaderList::Standard));
	mShader.load(ResourceFileName::Shader.at(ShaderList::Sprite));
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
