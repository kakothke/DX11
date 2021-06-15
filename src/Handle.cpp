#include "Handle.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static int INIT_NUM = -1;

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Handle::Handle()
	: mHandle(INIT_NUM)
	, mReleasedHandle(INIT_NUM)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Handle::~Handle()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
/// @return 現在の管理番号
int Handle::update()
{
	// 直前に破棄されたハンドル番号を返す
	if (mReleasedHandle != INIT_NUM) {
		int handleNum = mReleasedHandle;
		mReleasedHandle = INIT_NUM;
		return handleNum;
	}
	// ハンドル番号を進める
	mHandle++;
	return mHandle;
}

//-------------------------------------------------------------------------------------------------
/// 破棄
/// @param aHandle 破棄する管理番号
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
