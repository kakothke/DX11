#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "TextureLoader.h"
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto D3D11 = Direct3D11::getInst();
const static auto TEXTURE_LOADER = TextureLoader::getInst();
const static auto SHADER_LOADER = ShaderLoader::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SpriteRenderer::SpriteRenderer()
	: mVertexBuffer(nullptr)
	, mTextureName(nullptr)
	, mTextureSize(1)
	, mShaderData()
	, mColor()
	, mPivot()
	, mAnchor()
	, mSplit(1.0f, 1.0f)
	, mUVPos()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
SpriteRenderer::~SpriteRenderer()
{
	if (mVertexBuffer) {
		mVertexBuffer->Release();
		mVertexBuffer = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
/// @param aTransform トランスフォーム
void SpriteRenderer::render(Transform aTransform, const bool& a3DModeFlag)
{
	// 読み込みチェック
	if (!mTextureName || !mShaderData || !mVertexBuffer) {
		return;
	}

	// サイズをテクスチャーのサイズに合わせる
	aTransform.scale.x *= mTextureSize.x;
	aTransform.scale.y *= mTextureSize.y;
	if (a3DModeFlag) {
		aTransform.scale /= 100.0f;
	}

	// プリミティブの形状を指定
	D3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// シェーダーの指定
	D3D11->setShader(mShaderData);

	UINT strides = sizeof(VertexData);
	UINT offsets = 0;

	// IAに設定する頂点バッファの指定
	D3D11->getContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &strides, &offsets);

	// コンスタントバッファを更新
	D3D11->getConstantBuffer()->updateColor(mColor, mColor);
	D3D11->getConstantBuffer()->setSpriteSplit(mSplit);
	D3D11->getConstantBuffer()->setSpriteUVpos(mUVPos);
	if (a3DModeFlag) {
		D3D11->getConstantBuffer()->setMatrixW(aTransform);
		D3D11->getConstantBuffer()->updateMatrix();
	} else {
		D3D11->getConstantBuffer()->setSpriteMatrixW(aTransform, mPivot);
		D3D11->getConstantBuffer()->setSpriteMatrixP(mAnchor);
		D3D11->getConstantBuffer()->updateSprite();
	}

	// テクスチャーセット	
	D3D11->setTexture(TEXTURE_LOADER->getTexture(mTextureName));

	// 描画
	D3D11->getContext()->Draw(8, 0);

}

//-------------------------------------------------------------------------------------------------
/// テクスチャーを設定する
/// @param aFileName ファイルパス
void SpriteRenderer::setTexture(const LPCSTR aFileName)
{
	mTextureName = aFileName;
	mTextureSize = TEXTURE_LOADER->getTextureSize(aFileName);

	// テクスチャー取得エラー
	if (mTextureSize == Vector2(0)) {
		mTextureName = nullptr;
		mTextureSize = Vector2(1);
		return;
	}

	// 頂点バッファがまだ作成されていない場合作成する
	if (!mVertexBuffer) {
		createVertexBuffer();
	}
}

//-------------------------------------------------------------------------------------------------
/// シェーダーを設定する
/// @param aFileName ファイルパス
void SpriteRenderer::setShader(const LPCSTR aFileName)
{
	mShaderData = SHADER_LOADER->getShaderData(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// カラーを設定する
/// @param aColor カラー
void SpriteRenderer::setColor(const Color& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
/// 描画原点を設定する
/// @param aX 原点x(-1~1)
/// @param aY 原点y(-1~1)
void SpriteRenderer::setPivot(float aX, float aY)
{
	aX = Math::Clamp(aX, -1.0f, 1.0f);
	aY = Math::Clamp(aY, -1.0f, 1.0f);

	mPivot.x = (mTextureSize.x / 2) * -aX;
	mPivot.y = (mTextureSize.y / 2) * aY;
}

//-------------------------------------------------------------------------------------------------
/// 描画開始位置を設定する
/// @param aX 描画開始位置x(-1~1)
/// @param aY 描画開始位置y(-1~1)
void SpriteRenderer::setAnchor(float aX, float aY)
{
	aX = Math::Clamp(aX, -1.0f, 1.0f);
	aY = Math::Clamp(aY, -1.0f, 1.0f);

	mAnchor.x = aX;
	mAnchor.y = aY;
}

//-------------------------------------------------------------------------------------------------
/// UV分割数を設定する
/// @param aX 分割数x
/// @param aY 分割数y
void SpriteRenderer::setSplit(const UINT& aX, const UINT& aY)
{
	mSplit.x = (float)aX;
	mSplit.y = (float)aY;

	mTextureSize.x /= aX;
	mTextureSize.y /= aY;
}

//-------------------------------------------------------------------------------------------------
/// UV位置を設定する
void SpriteRenderer::setUVPos(const UINT& aX, const UINT& aY)
{
	mUVPos.x = (float)aX;
	mUVPos.y = (float)aY;
}

//-------------------------------------------------------------------------------------------------
/// 頂点バッファを作成する
/// @return 結果 成功(true)
bool SpriteRenderer::createVertexBuffer()
{
	// 頂点作成
	VertexData vertexes[8] = {};
	Vector2 size = 0.5f;
	// 頂点0
	vertexes[0].pos[0] = -size.x;
	vertexes[0].pos[1] = -size.y;
	vertexes[0].uv[0] = 0.0f;
	vertexes[0].uv[1] = 1.0f;
	vertexes[0].nor[2] = -1.0f;
	// 頂点1
	vertexes[1].pos[0] = size.x;
	vertexes[1].pos[1] = -size.y;
	vertexes[1].uv[0] = 1.0f;
	vertexes[1].uv[1] = 1.0f;
	vertexes[1].nor[2] = -1.0f;
	// 頂点2
	vertexes[2].pos[0] = -size.x;
	vertexes[2].pos[1] = size.y;
	vertexes[2].uv[0] = 0.0f;
	vertexes[2].uv[1] = 0.0f;
	vertexes[2].nor[2] = -1.0f;
	// 頂点3
	vertexes[3].pos[0] = size.x;
	vertexes[3].pos[1] = size.y;
	vertexes[3].uv[0] = 1.0f;
	vertexes[3].uv[1] = 0.0f;
	vertexes[3].nor[2] = -1.0f;
	// 頂点4
	vertexes[4].pos[0] = -size.x;
	vertexes[4].pos[1] = -size.y;
	vertexes[4].uv[0] = 0.0f;
	vertexes[4].uv[1] = 1.0f;
	vertexes[4].nor[2] = 1.0f;
	// 頂点5
	vertexes[5].pos[0] = size.x;
	vertexes[5].pos[1] = -size.y;
	vertexes[5].uv[0] = 1.0f;
	vertexes[5].uv[1] = 1.0f;
	vertexes[5].nor[2] = 1.0f;
	// 頂点6
	vertexes[6].pos[0] = -size.x;
	vertexes[6].pos[1] = size.y;
	vertexes[6].uv[0] = 0.0f;
	vertexes[6].uv[1] = 0.0f;
	vertexes[6].nor[2] = 1.0f;
	// 頂点7
	vertexes[7].pos[0] = size.x;
	vertexes[7].pos[1] = size.y;
	vertexes[7].uv[0] = 1.0f;
	vertexes[7].uv[1] = 0.0f;
	vertexes[7].nor[2] = 1.0f;

	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(VertexData) * 8;
		// 使用方法
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		// BIND設定
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// リソースへのCPUのアクセス権限についての設定
		bufferDesc.CPUAccessFlags = 0;
		// リソースオプションのフラグ
		bufferDesc.MiscFlags = 0;
		// 構造体のサイズ
		bufferDesc.StructureByteStride = 0;
	}

	// リソース情報
	D3D11_SUBRESOURCE_DATA subResource;
	{
		// バッファの中身の設定
		subResource.pSysMem = &vertexes[0];
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemPitch = 0;
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemSlicePitch = 0;
	}

	// バッファ作成
	HRESULT hr;
	hr = D3D11->getDevice()->CreateBuffer(&bufferDesc, &subResource, &mVertexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

} // namespace
// EOF
