#include "SpriteLoader.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto D3D11 = Direct3D11::getInst();
const static auto TEXTURE_LOADER = TextureLoader::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SpriteLoader::SpriteLoader()
	: mSpriteData()
{
	mSpriteData.clear();
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
SpriteLoader::~SpriteLoader()
{
	if (!mSpriteData.empty()) {
		mSpriteData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
SpriteLoader::SpriteData::~SpriteData()
{
	if (vertexBuffer) {
		vertexBuffer->Release();
		vertexBuffer = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// スプライトを読み込む
/// @param aFileName ファイルパス
/// @return 結果 成功（true）
bool SpriteLoader::load(const LPCSTR aFileName)
{
	if (mSpriteData.count(aFileName)) {
		MessageBox(nullptr, TEXT("スプライトの二重読み込み。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!std::ifstream(aFileName)) {
		MessageBox(nullptr, TEXT("読み込もうとしているスプライトが存在しません。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}	
	if (!TEXTURE_LOADER->load(aFileName)) {
		return false;
	}
	if (!createVertexBuffer(aFileName)) {
		MessageBox(nullptr, TEXT("頂点バッファの作成に失敗しました。(Sprite)"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mSpriteData.erase(aFileName);
		return false;
	}
	mSpriteData[aFileName].fileName = aFileName;

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 破棄
/// @param aFileName ファイルパス
void SpriteLoader::release(const LPCSTR aFileName)
{
	if (!mSpriteData.count(aFileName)) {
		MessageBox(nullptr, TEXT("存在しないスプライトを破棄しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
	mSpriteData.erase(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// スプライトデータを取得する
/// @param aFileName ファイルパス
/// @return スプライトデータ
SpriteLoader::SpriteData* SpriteLoader::getSpriteData(const LPCSTR aFileName)
{
	if (!mSpriteData.count(aFileName)) {
		MessageBox(nullptr, TEXT("存在しないスプライトを取得しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return nullptr;
	}
	return &mSpriteData[aFileName];
}

//-------------------------------------------------------------------------------------------------
/// 頂点バッファを作成する
/// @param aFileName ファイルパス
/// @return 作成結果 成功(true)
bool SpriteLoader::createVertexBuffer(const LPCSTR aFileName)
{
	SpriteVertex vertexes[4];
	createMesh(aFileName, vertexes);
	// バッファ情報
	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(SpriteVertex) * 4;
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
	hr = D3D11->getDevice()->CreateBuffer(&bufferDesc, &subResource, &mSpriteData[aFileName].vertexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// メッシュを作成する
/// @param aFileName ファイルパス
/// @param aVertexes 頂点データ
void SpriteLoader::createMesh(const LPCSTR aFileName, SpriteVertex* aVertexes)
{
	// テクスチャーのサイズを参照
	DirectX::XMFLOAT2 size = TEXTURE_LOADER->getTextureSize(aFileName);

	float width = (float)size.x / 2;
	float height = (float)size.y / 2;

	// 表面
	{
		// 頂点0
		aVertexes[0].pos[0] = -width;
		aVertexes[0].pos[1] = -height;
		aVertexes[0].uv[0] = 0;
		aVertexes[0].uv[1] = 1;
		// 頂点1
		aVertexes[1].pos[0] = width;
		aVertexes[1].pos[1] = -height;
		aVertexes[1].uv[0] = 1;
		aVertexes[1].uv[1] = 1;
		// 頂点2
		aVertexes[2].pos[0] = -width;
		aVertexes[2].pos[1] = height;
		aVertexes[2].uv[0] = 0;
		aVertexes[2].uv[1] = 0;
		//// 頂点3
		aVertexes[3].pos[0] = width;
		aVertexes[3].pos[1] = height;
		aVertexes[3].uv[0] = 1;
		aVertexes[3].uv[1] = 0;
	}
}

} // namespace
// EOF
