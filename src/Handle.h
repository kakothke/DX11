#pragma once

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ���\�[�X�Ǘ��ԍ�
class Handle
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Handle();
	~Handle();
	//@}

	/// @name �X�V/�j��
	//@{
	int update();
	void release(const int& aHandle);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ���݂̊Ǘ��ԍ�
	int mHandle;
	/// �j�����ꂽ�Ǘ��ԍ�
	int mReleasedHandle;
	//@}

};

} // namespace
// EOF
