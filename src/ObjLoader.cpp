#include "OBJLoader.h"

//-------------------------------------------------------------------------------------------------
#include "SplitString.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
OBJLoader::OBJLoader()
	: mOBJData()
{
	mOBJData.clear();
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
OBJLoader::~OBJLoader()
{
	if (!mOBJData.empty()) {
		mOBJData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJファイルを読み込む
/// @param aFileName 読み込みたいOBJのファイルパス
bool OBJLoader::load(const char* const aFileName)
{
	if (mOBJData.count(aFileName)) {
		MessageBox(nullptr, TEXT("OBJファイルの二重読み込み。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	std::vector<OBJVertex> vertexes;
	std::vector<std::string> mtlNames;
	if (!loadOBJFile(aFileName, vertexes, mtlNames)) {
		MessageBox(nullptr, TEXT(".objファイルの読み込みに失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!loadMtlFile(aFileName, mtlNames)) {
		MessageBox(nullptr, TEXT(".mtlファイルの読み込みに失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createVertexBuffer(aFileName, vertexes)) {
		MessageBox(nullptr, TEXT("頂点バッファの作成に失敗しました。(OBJ)"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createIndexBuffer(aFileName)) {
		MessageBox(nullptr, TEXT("インデックスバッファの作成に失敗しました。(OBJ)"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// OBJファイルを破棄する
/// @param aFileName 破棄したいOBJのファイルパス
void OBJLoader::release(const char* const aFileName)
{
	if (mOBJData.count(aFileName)) {
		mOBJData.erase(aFileName);
	} else {
		MessageBox(nullptr, TEXT("存在しないOBJデータを破棄しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJファイルのデータを取得する
/// @param aFileName 取得したいOBJのファイルパス
OBJData* OBJLoader::getObjData(const char* const aFileName)
{
	if (mOBJData.count(aFileName)) {
		return &mOBJData[aFileName];
	}
	MessageBox(nullptr, TEXT("存在しないOBJデータを取得しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// OBJファイルを読み込む
/// @param aFileName 読み込みたいOBJのファイルパス
/// @param aVertexData 要素を追加させる頂点データ構造体
/// @return 作成結果 成功(true)
bool OBJLoader::loadOBJFile(const char* const aFileName, std::vector<OBJVertex>& aVertexes, std::vector<std::string>& aMtlNames)
{
	// ファイルを読み込む
	std::ifstream ifs(aFileName);
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<float>> v, vt, vn;
	std::string line, usemtlName;
	while (getline(ifs, line)) {
		// コメントは無視する
		if (line[0] == '#') {
			continue;
		}
		// 頂点座標
		else if (line.substr(0, 2) == "v ") {
			pushStoV(v, SplitString::split(line.substr(2), ' '));
		}
		// UV座標
		else if (line.substr(0, 2) == "vt") {
			pushStoV(vt, SplitString::split(line.substr(3), ' '));
		}
		// 法線座標
		else if (line.substr(0, 2) == "vn") {
			pushStoV(vn, SplitString::split(line.substr(3), ' '));
		}
		// 面情報
		else if (line.substr(0, 2) == "f ") {
			std::vector<std::string> spaceSplit = SplitString::split(line.substr(2), ' ');
			for (UINT i = 0; i < spaceSplit.size(); i++) {
				OBJVertex tmp;
				std::vector<std::string> slashSplit = SplitString::split(spaceSplit[i], '/');
				// 頂点座標
				for (UINT j = 0; !v.empty() && j < v[0].size(); j++) {
					tmp.pos[j] = v[std::stoi(slashSplit[0]) - 1][j];
				}
				// UV座標
				for (UINT j = 0; !vt.empty() && j < vt[0].size(); j++) {
					tmp.uv[j] = vt[std::stoi(slashSplit[1]) - 1][j];
				}
				// 法線座標
				for (UINT j = 0; !vn.empty() && j < vn[0].size(); j++) {
					tmp.nor[j] = vn[std::stoi(slashSplit[2]) - 1][j];
				}
				// 各バッファコンテナに追加
				aVertexes.push_back(tmp);
				mOBJData[aFileName].indexes[usemtlName].push_back(aVertexes.size() - 1);
			}
		}
		// 所属マテリアル名の切り替え
		else if (line.substr(0, 6) == "usemtl") {
			usemtlName = line.substr(7);
		}
		// マテリアルファイル名を保存
		else if (line.substr(0, 6) == "mtllib") {
			aMtlNames.push_back(line.substr(7));
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
bool OBJLoader::loadMtlFile(const char* const aFileName, const std::vector<std::string>& aMtlNames)
{
	for (auto mtlName : aMtlNames) {
		std::string filePath = aFileName;
		filePath.erase(filePath.rfind("/") + 1);
		// ファイルを読み込む
		std::ifstream ifs(filePath + mtlName);
		if (!ifs) {
			return false;
		}

		std::string line, newmtlName;
		while (getline(ifs, line)) {
			// コメントは無視する
			if (line[0] == '#') {
				continue;
			}
			// アンビエント
			else if (line.substr(0, 2) == "Ka") {
				std::vector<std::string> splitSpace = SplitString::split(line.substr(3), ' ');
				for (UINT i = 0; i < splitSpace.size(); i++) {
					mOBJData[aFileName].materials[newmtlName].ambient[i] = std::stof(splitSpace[i]);
				}
			}
			// デフューズ
			else if (line.substr(0, 2) == "Kd") {
				std::vector<std::string> splitSpace = SplitString::split(line.substr(3), ' ');
				for (UINT i = 0; i < splitSpace.size(); i++) {
					mOBJData[aFileName].materials[newmtlName].diffuse[i] = std::stof(splitSpace[i]);
				}
			}
			// スペキュラー
			else if (line.substr(0, 2) == "Ks") {
				std::vector<std::string> splitSpace = SplitString::split(line.substr(3), ' ');
				for (UINT i = 0; i < splitSpace.size(); i++) {
					mOBJData[aFileName].materials[newmtlName].specular[i] = std::stof(splitSpace[i]);
				}
			}
			// マテリアルグループ名を変更
			else if (line.substr(0, 6) == "newmtl") {
				newmtlName = line.substr(7);
			}
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 頂点バッファを作成する
/// @param aFileName 読み込みたいOBJのファイルパス
/// @param aVertexData 参照する頂点データ構造体
/// @return 作成結果 成功(true)
bool OBJLoader::createVertexBuffer(const char* const aFileName, const std::vector<OBJVertex>& aVertexes)
{
	// バッファ情報
	D3D11_BUFFER_DESC bufferDesc;
	{
		// バッファのサイズ
		bufferDesc.ByteWidth = sizeof(OBJVertex) * (UINT)aVertexes.size();
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
		subResource.pSysMem = &aVertexes[0];
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemPitch = 0;
		// textureデータを使用する際に使用するメンバ
		subResource.SysMemSlicePitch = 0;
	}

	// バッファ作成
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
		&bufferDesc,
		&subResource,
		&mOBJData[aFileName].vertexBuffer
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// インデックスバッファを作成する
/// @param aFileName 読み込みたいOBJのファイルパス
/// @return 作成結果 成功(true)
bool OBJLoader::createIndexBuffer(const char* const aFileName)
{
	int cnt = 0;
	for (auto index : mOBJData[aFileName].indexes) {
		mOBJData[aFileName].indexBuffers.emplace_back();
		// バッファ情報
		D3D11_BUFFER_DESC bufferDesc;
		{
			// バッファのサイズ
			bufferDesc.ByteWidth = sizeof(UINT) * (UINT)index.second.size();
			// 使用方法
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			// BIND設定
			bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
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
			subResource.pSysMem = &index.second[0];
			// textureデータを使用する際に使用するメンバ
			subResource.SysMemPitch = 0;
			// textureデータを使用する際に使用するメンバ
			subResource.SysMemSlicePitch = 0;
		}

		// バッファ作成
		if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
			&bufferDesc,
			&subResource,
			&mOBJData[aFileName].indexBuffers[cnt]
		))) {
			return false;
		}

		cnt++;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 複数の文字列を数値に変換して座標情報をpushする
/// @tparam T テンプレート引数
/// @param aVector pushするvector
/// @param aStoV 数値に変換する文字列
void OBJLoader::pushStoV(std::vector<std::vector<float>>& aVector, const std::vector<std::string>& aStoV)
{
	std::vector<float> values;
	for (UINT i = 0; i < aStoV.size(); i++) {
		values.push_back(std::stof(aStoV[i]));
	}
	aVector.push_back(values);
}

} // namespace
// EOF
