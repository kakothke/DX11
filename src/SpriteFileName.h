#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �V�F�[�_�[���X�g
enum class SpriteList
{
	TestImage,
};

/// �V�F�[�_�[�t�@�C�����擾�p�N���X
class SpriteFileName
{
public:
	/// �w�肵���V�F�[�_�[�̃t�@�C���p�X���擾����
	/// @param aList �擾�������V�F�[�_�[�t�@�C�����w�肷��񋓌^
	/// @return �t�@�C���p�X
	inline static const char* fileName(SpriteList aList)
	{
		return mFileName[aList];
	}

private:
	SpriteFileName();
	static std::unordered_map<SpriteList, const char*> mFileName;

};

} // namespace
// EOF
