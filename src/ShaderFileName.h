#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �V�F�[�_�[���X�g
enum class ShaderList
{
	Unlit,
	Standard
};

/// �V�F�[�_�[�t�@�C�����擾�p�N���X
class ShaderFileName
{
public:
	/// �w�肵���V�F�[�_�[�̃t�@�C���p�X���擾����
	/// @param aList �擾�������V�F�[�_�[�t�@�C�����w�肷��񋓌^
	/// @return �t�@�C���p�X
	inline static const char* fileName(ShaderList aList)
	{
		return mFileName[aList];
	}

private:
	ShaderFileName();
	static std::unordered_map<ShaderList, const char*> mFileName;

};

} // namespace
// EOF
