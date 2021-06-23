#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// プレイヤー
class Player : public BaseGameObject
{
public:
	/// name コンストラクタ
	//@{
	Player();
	//@}

	/// @name 初期化/更新/描画
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

	/// @name アクセサ
	//@{
	/// ボスの位置を設定する
	void setBossPos(const Vector3& aPos);
	//@}

private:
	/// @name 内部実装
	//@{
	void move();
	void shot();
	//@}

	/// @name プライベートメンバ変数
	//@{
	OBJRenderer mRenderer;
	Vector2 mVelocity;
	float mDistanceFromBoss;
	DirectX::XMMATRIX mPoseMat;
	//@}

	/// @name 他のオブジェクトとの繋がり
	//@{
	Vector3 mBossPos;
	//@}

};

} // namespace
// EOF
