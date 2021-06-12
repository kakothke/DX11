#include "Resource.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
Resource::Resource()
	: mOBJ()
	, mSprite()
	, mTexture()
	, mShader()
{
}

//-------------------------------------------------------------------------------------------------
Resource::~Resource()
{
}

//-------------------------------------------------------------------------------------------------
void Resource::initialize()
{
	// OBJs
	mOBJ.load(ResourceFileName::OBJ.at(OBJList::Cube));
	mOBJ.load(ResourceFileName::OBJ.at(OBJList::Sphere));
	mOBJ.load(ResourceFileName::OBJ.at(OBJList::SkyBox));
	mOBJ.load(ResourceFileName::OBJ.at(OBJList::Test));

	// Sprites
	mSprite.load(ResourceFileName::Sprite.at(SpriteList::Test));

	// Shaders
	mShader.load(ResourceFileName::Shader.at(ShaderList::Unlit));
	mShader.load(ResourceFileName::Shader.at(ShaderList::Standard));
	mShader.load(ResourceFileName::Shader.at(ShaderList::Sprite));
	mShader.load(ResourceFileName::Shader.at(ShaderList::SkyBox));
}

//-------------------------------------------------------------------------------------------------
OBJLoader* Resource::OBJ()
{
	return &mOBJ;
}

//-------------------------------------------------------------------------------------------------
SpriteLoader* Resource::Sprite()
{
	return &mSprite;
}

//-------------------------------------------------------------------------------------------------
TextureLoader* Resource::Texture()
{
	return &mTexture;
}

//-------------------------------------------------------------------------------------------------
ShaderLoader* Resource::Shader()
{
	return &mShader;
}

} // namespace
// EOF
