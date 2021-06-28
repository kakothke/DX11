#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto OBJ_LOADER = OBJLoader::getInst();
const static auto SHADER_LOADER = ShaderLoader::getInst();
const static auto TEXTURE_LOADER = TextureLoader::getInst();
const static auto SOUND = Sound::getInst();
const static auto FONT_LOADER = FontLoader::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
ResourceManager::ResourceManager()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
ResourceManager::~ResourceManager()
{
}

//-------------------------------------------------------------------------------------------------
/// 初期読み込み
void ResourceManager::initialize()
{
	// OBJs
	OBJ_LOADER->load(ResourceFileName::OBJ.at(OBJList::Boss));
	OBJ_LOADER->load(ResourceFileName::OBJ.at(OBJList::Player));
	OBJ_LOADER->load(ResourceFileName::OBJ.at(OBJList::SkyBox));
	OBJ_LOADER->load(ResourceFileName::OBJ.at(OBJList::Kabocha));

	// Sprites
	TEXTURE_LOADER->load(ResourceFileName::Sprite.at(SpriteList::Test));

	// Shaders
	SHADER_LOADER->load(ResourceFileName::Shader.at(ShaderList::Unlit));
	SHADER_LOADER->load(ResourceFileName::Shader.at(ShaderList::Standard));
	SHADER_LOADER->load(ResourceFileName::Shader.at(ShaderList::Sprite));
	SHADER_LOADER->load(ResourceFileName::Shader.at(ShaderList::SkyBox));

	// BGM
	SOUND->load((int)SoundList::BGM_00, ResourceFileName::Sound.at(SoundList::BGM_00));
	SOUND->setBeginPos((int)SoundList::BGM_00, 65333);
	SOUND->setLoop((int)SoundList::BGM_00, true);
	SOUND->setLoopPos((int)SoundList::BGM_00, 588000, 4377333);

	// SE
	SOUND->load((int)SoundList::SE_Shot, ResourceFileName::Sound.at(SoundList::SE_Shot));

	// Font
	FONT_LOADER->load(TEXT("あんずもじ湛"), TEXT("res/font/APJapanesefontF.ttf"));

}

} // namespace
// EOF
