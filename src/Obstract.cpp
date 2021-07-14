#include "Obstract.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"
#include "Sound.h"
#include "GrazeEffect.h"
#include "Player.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
Player* Obstract::mPlayer = nullptr;

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Obstract::Obstract()
	: mRenderer()
	, mColor()
	, mMoveSpeed(0.0f)
{
	// トランスフォーム設定
	mTransform.pos = Vector3(0.0f, -3.0f, 500.0f);
	mTransform.scale = Vector3(2.0f, 5.0f, 1.0f);
	mTransform.pos.x += Random::RandomFloat(500, 0.1f) * Random::RandomSign();
	mTransform.scale.x += Random::RandomInt(5);

	// タグ設定
	setTag(GameObjectTag::Obstract);

	/// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Obstract));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mColor.a = 0.0f;
	mRenderer.setColor(mColor);
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Obstract::~Obstract()
{
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
void Obstract::initialize()
{
	mPlayer = (Player*)mGameObjectList->findWorldGameObject(GameObjectTag::Player);;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Obstract::update()
{
	// 定数
	const static float DELETE_POS = -20.0f;
	const static float COLOR_SPEED = 0.01f;

	// 移動
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();

	// 色
	if (mColor.a < 1) {
		mColor.a += COLOR_SPEED * mMoveSpeed * FPS->deltaTime();
	}

	// 当たり判定
	collisionPlayer();

	// 消去
	if (mTransform.pos.z < DELETE_POS) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Obstract::draw()
{
	mRenderer.setColor(mColor);
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// 移動速度を設定する
void Obstract::setMoveSpeed(const float& aSpeed)
{
	mMoveSpeed = aSpeed;
}

//-------------------------------------------------------------------------------------------------
/// プレイヤーとの当たり判定
void Obstract::collisionPlayer()
{
	const static float PLAYER_SIZE = 0.5f;

	if (mPlayer->activeSelf()) {
		Vector3 playerPos = mPlayer->transform().pos;
		Transform collisionTransform = mTransform;
		collisionTransform.pos.y = 0;
		collisionTransform.scale.y = 2.0f;

		// プレイヤーにヒット
		if (collisionTransform.pos.x - collisionTransform.scale.x / 2.0f < playerPos.x + PLAYER_SIZE &&
			collisionTransform.pos.x + collisionTransform.scale.x / 2.0f > playerPos.x - PLAYER_SIZE &&
			collisionTransform.pos.y - collisionTransform.scale.y / 2.0f < playerPos.y + PLAYER_SIZE &&
			collisionTransform.pos.y + collisionTransform.scale.y / 2.0f > playerPos.y - PLAYER_SIZE &&
			collisionTransform.pos.z - collisionTransform.scale.z / 2.0f < playerPos.z + PLAYER_SIZE &&
			collisionTransform.pos.z + collisionTransform.scale.z / 2.0f > playerPos.z - PLAYER_SIZE) {
			mPlayer->missEvent();
			destroyThisGameObject();
			return;
		}

		// プレイヤーにかすり
		collisionTransform.scale.x *= 4.0f;
		if (collisionTransform.pos.x - collisionTransform.scale.x / 2.0f < playerPos.x + PLAYER_SIZE &&
			collisionTransform.pos.x + collisionTransform.scale.x / 2.0f > playerPos.x - PLAYER_SIZE &&
			collisionTransform.pos.y - collisionTransform.scale.y / 2.0f < playerPos.y + PLAYER_SIZE &&
			collisionTransform.pos.y + collisionTransform.scale.y / 2.0f > playerPos.y - PLAYER_SIZE &&
			collisionTransform.pos.z - collisionTransform.scale.z / 2.0f < playerPos.z + PLAYER_SIZE &&
			collisionTransform.pos.z + collisionTransform.scale.z / 2.0f > playerPos.z - PLAYER_SIZE) {
			SOUND->playOneShot((int)SoundList::SE_Graze);

			mGameObjectList->instanceToWorldAlpha(new GrazeEffect(collisionTransform.pos, playerPos));
		}
	}
}

} // namespace
// EOF
