#include "OBJLoader.h"

//-------------------------------------------------------------------------------------------------
#include <codecvt>
#include <sstream>
#include <iomanip>
#include "StringSupport.h"
#include "Direct3D11.h"
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
/// @return 結果 成功(true)
bool OBJLoader::load(const char* const aFileName)
{
	if (mOBJData.count(aFileName)) {
		MessageBox(nullptr, TEXT("OBJファイルの二重読み込み。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	std::vector<OBJVertex> vertexes;
	std::vector<std::string> mtlNames;
	if (!createMesh(aFileName, vertexes, mtlNames)) {
		MessageBox(nullptr, TEXT(".objファイルの読み込みに失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!loadMtlFile(aFileName, mtlNames)) {
		MessageBox(nullptr, TEXT(".mtlファイルの読み込みに失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mOBJData.erase(aFileName);
		return false;
	}
	if (!createVertexBuffer(aFileName, vertexes)) {
		MessageBox(nullptr, TEXT("頂点バッファの作成に失敗しました。(OBJ)"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mOBJData.erase(aFileName);
		return false;
	}
	if (!createIndexBuffer(aFileName)) {
		MessageBox(nullptr, TEXT("インデックスバッファの作成に失敗しました。(OBJ)"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mOBJData.erase(aFileName);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// OBJファイルを破棄する
/// @param aFileName 破棄したいOBJのファイルパス
void OBJLoader::release(const char* const aFileName)
{
	if (!mOBJData.count(aFileName)) {
		MessageBox(nullptr, TEXT("存在しないOBJデータを破棄しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
	mOBJData.erase(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// OBJファイルのデータを取得する
/// @param aFileName 取得したいOBJのファイルパス
OBJData* OBJLoader::getOBJData(const char* const aFileName)
{
	if (!mOBJData.count(aFileName)) {
		MessageBox(nullptr, TEXT("存在しないOBJデータを取得しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return nullptr;
	}
	return &mOBJData[aFileName];
}

//-------------------------------------------------------------------------------------------------
/// メッシュを作成する
/// @param aFileName 作成したいOBJのファイルパス
/// @param aVertexData 要素を追加させる頂点データ構造体
/// @return 作成結果 成功(true)
bool OBJLoader::createMesh(const char* const aFileName, std::vector<OBJVertex>& aVertexes, std::vector<std::string>& aMtlNames)
{
	// ファイルを読み込む
	std::ifstream ifs(aFileName);
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<float>> v, vt, vn;
	std::unordered_map<std::string, UINT> vertexID;
	std::string line, usemtlName;
	while (getline(ifs, line)) {
		// 空白は消す
		if (line[0] == ' ' || line[0] == '	') {
			while (line[0] == ' ' || line[0] == '	') {
				line.erase(0, 1);
			}
		}
		// コメントは無視する
		if (line[0] == '#') {
			continue;
		}
		// 頂点座標
		else if (line.substr(0, 2) == "v ") {
			pushStoV(v, StringSupport::split(line.substr(2), ' '));
			// z軸を反転させる
			v[v.size() - 1][2] *= -1;
		}
		// UV座標
		else if (line.substr(0, 2) == "vt") {
			pushStoV(vt, StringSupport::split(line.substr(3), ' '));
			// v軸を反転させる
			vt[vt.size() - 1][1] = (1.0f - vt[vt.size() - 1][1]);
		}
		// 法線座標
		else if (line.substr(0, 2) == "vn") {
			pushStoV(vn, StringSupport::split(line.substr(3), ' '));
			// z軸を反転させる
			vn[vn.size() - 1][2] *= -1;
		}
		// 面情報
		else if (line.substr(0, 2) == "f ") {
			std::vector<std::string> spaceSplit = StringSupport::split(line.substr(2), ' ');
			for (UINT i = 0; i < spaceSplit.size(); i++) {
				OBJVertex tmp;
				std::vector<std::string> slashSplit = StringSupport::split(spaceSplit[i], '/');
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
				// 頂点情報調査用文字列作成
				std::string key;
				for (int i = 0; i < 3; i++) {
					std::ostringstream sout;
					sout << std::setfill('0') << std::setw(5) << slashSplit[i];
					key += sout.str();
				}
				// 重複チェック
				if (vertexID.count(key) == 0) {
					// 頂点情報追加
					aVertexes.push_back(tmp);
					mOBJData[aFileName].indexes[usemtlName].push_back((UINT)aVertexes.size() - 1);
					vertexID[key] = (UINT)aVertexes.size() - 1;
				} else {
					// 登録されている頂点バッファの要素番号をインデックスバッファに保存する
					mOBJData[aFileName].indexes[usemtlName].push_back(vertexID[key]);
				}
			}
			// 4頂点対応
			if (spaceSplit.size() > 3) {
				UINT size = (UINT)mOBJData[aFileName].indexes[usemtlName].size();
				mOBJData[aFileName].indexes[usemtlName].push_back(mOBJData[aFileName].indexes[usemtlName][size - 4]);
				mOBJData[aFileName].indexes[usemtlName].push_back(mOBJData[aFileName].indexes[usemtlName][size - 2]);
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
/// .mtlファイルを読み込む
/// @param aFileName ファイルパス
/// @param aMtlNames マテリアル名
/// @return 結果 成功(true)
bool OBJLoader::loadMtlFile(const char* const aFileName, const std::vector<std::string>& aMtlNames)
{
	// マテリアルが存在しないとき
	if (aMtlNames.empty()) {
		// とりあえず代入
		mOBJData[aFileName].materials[""].ambient[0] = 1;
		mOBJData[aFileName].materials[""].ambient[1] = 1;
		mOBJData[aFileName].materials[""].ambient[2] = 1;
		mOBJData[aFileName].materials[""].diffuse[0] = 1;
		mOBJData[aFileName].materials[""].diffuse[1] = 1;
		mOBJData[aFileName].materials[""].diffuse[2] = 1;
		mOBJData[aFileName].materials[""].specular[0] = .5f;
		mOBJData[aFileName].materials[""].specular[1] = .5f;
		mOBJData[aFileName].materials[""].specular[2] = .5f;
		return true;
	}
	// マテリアルファイルを読み込む
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
			// 空白は消す
			if (line[0] == ' ' || line[0] == '	') {
				while (line[0] == ' ' || line[0] == '	') {
					line.erase(0, 1);
				}
			}
			// コメントは無視する
			if (line[0] == '#') {
				continue;
			}
			// マテリアルグループ名を変更
			else if (line.substr(0, 6) == "newmtl") {
				newmtlName = line.substr(7);
			}
			// アンビエント
			else if (line.substr(0, 2) == "Ka") {
				std::vector<std::string> splitSpace = StringSupport::split(line.substr(3), ' ');
				for (UINT i = 0; i < splitSpace.size(); i++) {
					mOBJData[aFileName].materials[newmtlName].ambient[i] = std::stof(splitSpace[i]);
				}
			}
			// デフューズ
			else if (line.substr(0, 2) == "Kd") {
				std::vector<std::string> splitSpace = StringSupport::split(line.substr(3), ' ');
				for (UINT i = 0; i < splitSpace.size(); i++) {
					mOBJData[aFileName].materials[newmtlName].diffuse[i] = std::stof(splitSpace[i]);
				}
			}
			// スペキュラー
			else if (line.substr(0, 2) == "Ks") {
				std::vector<std::string> splitSpace = StringSupport::split(line.substr(3), ' ');
				for (UINT i = 0; i < splitSpace.size(); i++) {
					mOBJData[aFileName].materials[newmtlName].specular[i] = std::stof(splitSpace[i]);
				}
			}
			// テクスチャ
			else if (line.substr(0, 6) == "map_Kd") {
				std::string texName = filePath + line.substr(7);
				mOBJData[aFileName].materials[newmtlName].textureFileName = texName;
				auto texture = TextureLoader::getInst();
				texture->load(texName.c_str());
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
	HRESULT hr;
	auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreateBuffer(&bufferDesc, &subResource, &mOBJData[aFileName].vertexBuffer);
	if (FAILED(hr)) {
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
		HRESULT hr;
		auto device = Direct3D11::getInst()->getDevice();
		hr = device->CreateBuffer(&bufferDesc, &subResource, &mOBJData[aFileName].indexBuffers[cnt]);
		if (FAILED(hr)) {
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
