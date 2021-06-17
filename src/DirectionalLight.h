#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
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
	DirectionalLight(Vector3 aRot);
	DirectionalLight(Color aColor);
	DirectionalLight(Vector3 aRot, Color aColor);
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
	/// カラー
	Color mColor;
	//@}

};

} // namespace
// EOF
