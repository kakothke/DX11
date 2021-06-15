#include "Handle.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static int INIT_NUM = -1;

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Handle::Handle()
	: mHandle(INIT_NUM)
	, mReleasedHandle(INIT_NUM)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Handle::~Handle()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
/// @return ���݂̊Ǘ��ԍ�
int Handle::update()
{
	// ���O�ɔj�����ꂽ�n���h���ԍ���Ԃ�
	if (mReleasedHandle != INIT_NUM) {
		int handleNum = mReleasedHandle;
		mReleasedHandle = INIT_NUM;
		return handleNum;
	}
	// �n���h���ԍ���i�߂�
	mHandle++;
	return mHandle;
}

//-------------------------------------------------------------------------------------------------
/// �j��
/// @param aHandle �j������Ǘ��ԍ�
void Handle::release(const int& aHandle)
{
	if (aHandle > mHandle || 0 > aHandle) {
		return;
	}
	if (aHandle == mHandle) {
		mHandle--;
	}
	mReleasedHandle = aHandle;
}

} // namespace
// EOF
