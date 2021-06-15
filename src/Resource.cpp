#include "Resource.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
bool Resource::initialize()
{
	bool result;

	// OBJs
	result = mOBJ.load(ResourceFileName::OBJ.at(OBJList::Cube));
	result = mOBJ.load(ResourceFileName::OBJ.at(OBJList::Sphere));
	result = mOBJ.load(ResourceFileName::OBJ.at(OBJList::SkyBox));
	result = mOBJ.load(ResourceFileName::OBJ.at(OBJList::Test));

	// Sprites
	result = mSprite.load(ResourceFileName::Sprite.at(SpriteList::Test));

	// Shaders
	result = mShader.load(ResourceFileName::Shader.at(ShaderList::Unlit));
	result = mShader.load(ResourceFileName::Shader.at(ShaderList::Standard));
	result = mShader.load(ResourceFileName::Shader.at(ShaderList::Sprite));
	result = mShader.load(ResourceFileName::Shader.at(ShaderList::SkyBox));

	return result;
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
