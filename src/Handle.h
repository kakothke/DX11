#pragma once

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// リソース管理番号
class Handle
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Handle();
	~Handle();
	//@}

	/// @name 更新/破棄
	//@{
	int update();
	void release(const int& aHandle);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// 現在の管理番号
	int mHandle;
	/// 破棄された管理番号
	int mReleasedHandle;
	//@}

};

} // namespace
// EOF
