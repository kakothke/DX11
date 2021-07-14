#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "GameObjectTag.h"
#include "Color.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ディレクショナルライト基底クラス
/// @brief 静的なディレクショナルライトとしても使用可能
class DirectionalLight : public BaseGameObject
{
public:
	/// @name コンストラクタ
	//@{
	DirectionalLight();
	DirectionalLight(Vector3 aAngle);
	DirectionalLight(Color aColor);
	DirectionalLight(Vector3 aAngle, Color aColor);
	virtual ~DirectionalLight();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}


protected:
	/// @name プロテクテッドメンバ関数
	//@{
	/// コンスタントバッファを更新する
	void updateConstantBuffer();
	//@}

	/// @name プロテクテッドメンバ変数
	//@{
	/// オイラー角の回転方向
	Vector3 mAngle;
	/// カラー
	Color mColor;
	//@}

};

} // namespace
// EOF
