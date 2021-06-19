#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// スプライト読み込みクラス
class SpriteLoader : public Singleton<SpriteLoader>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	SpriteLoader();
	~SpriteLoader();
	//@}

	/// @name 読み込み、破棄
	//@{
	bool load(const LPCSTR aFileName);
	void release(const LPCSTR aFileName);
	//@}

	/// @name 公開構造体
	//@{
	/// 頂点データ構造体
	struct SpriteVertex
	{
		float pos[3] = {};
		float uv[2] = {};
	};
	/// スプライトデータ構造体
	struct SpriteData
	{
		/// 頂点バッファ(Shader送信用)
		ID3D11Buffer* vertexBuffer;
		/// ファイル名
		LPCSTR fileName;
		/// デストラクタ
		~SpriteData();
	};
	//@}

	/// @name アクセサ
	//@{
	/// スプライトデータを取得する
	SpriteData* getSpriteData(const LPCSTR aFileName);
	//@}

private:
	/// @name 内部実装
	//@{
	/// 頂点バッファを作成する
	bool createVertexBuffer(const LPCSTR aFileName);
	/// メッシュを作成する
	void createMesh(const LPCSTR aFileName, SpriteVertex* aVertexes);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// スプライトデータ
	std::unordered_map<LPCSTR, SpriteData> mSpriteData;
	//@}

};

} // namespace
// EOF
