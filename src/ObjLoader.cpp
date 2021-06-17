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
/// �R���X�g���N�^
OBJLoader::OBJLoader()
	: mOBJData()
{
	mOBJData.clear();
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
OBJLoader::~OBJLoader()
{
	if (!mOBJData.empty()) {
		mOBJData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJ�t�@�C����ǂݍ���
/// @param aFileName �ǂݍ��݂���OBJ�̃t�@�C���p�X
/// @return ���� ����(true)
bool OBJLoader::load(const char* const aFileName)
{
	if (mOBJData.count(aFileName)) {
		MessageBox(nullptr, TEXT("OBJ�t�@�C���̓�d�ǂݍ��݁B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	std::vector<OBJVertex> vertexes;
	std::vector<std::string> mtlNames;
	if (!createMesh(aFileName, vertexes, mtlNames)) {
		MessageBox(nullptr, TEXT(".obj�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!loadMtlFile(aFileName, mtlNames)) {
		MessageBox(nullptr, TEXT(".mtl�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mOBJData.erase(aFileName);
		return false;
	}
	if (!createVertexBuffer(aFileName, vertexes)) {
		MessageBox(nullptr, TEXT("���_�o�b�t�@�̍쐬�Ɏ��s���܂����B(OBJ)"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mOBJData.erase(aFileName);
		return false;
	}
	if (!createIndexBuffer(aFileName)) {
		MessageBox(nullptr, TEXT("�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂����B(OBJ)"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mOBJData.erase(aFileName);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// OBJ�t�@�C����j������
/// @param aFileName �j��������OBJ�̃t�@�C���p�X
void OBJLoader::release(const char* const aFileName)
{
	if (!mOBJData.count(aFileName)) {
		MessageBox(nullptr, TEXT("���݂��Ȃ�OBJ�f�[�^��j�����悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
	mOBJData.erase(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// OBJ�t�@�C���̃f�[�^���擾����
/// @param aFileName �擾������OBJ�̃t�@�C���p�X
OBJData* OBJLoader::getOBJData(const char* const aFileName)
{
	if (!mOBJData.count(aFileName)) {
		MessageBox(nullptr, TEXT("���݂��Ȃ�OBJ�f�[�^���擾���悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return nullptr;
	}
	return &mOBJData[aFileName];
}

//-------------------------------------------------------------------------------------------------
/// ���b�V�����쐬����
/// @param aFileName �쐬������OBJ�̃t�@�C���p�X
/// @param aVertexData �v�f��ǉ������钸�_�f�[�^�\����
/// @return �쐬���� ����(true)
bool OBJLoader::createMesh(const char* const aFileName, std::vector<OBJVertex>& aVertexes, std::vector<std::string>& aMtlNames)
{
	// �t�@�C����ǂݍ���
	std::ifstream ifs(aFileName);
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<float>> v, vt, vn;
	std::unordered_map<std::string, UINT> vertexID;
	std::string line, usemtlName;
	while (getline(ifs, line)) {
		// �󔒂͏���
		if (line[0] == ' ' || line[0] == '	') {
			while (line[0] == ' ' || line[0] == '	') {
				line.erase(0, 1);
			}
		}
		// �R�����g�͖�������
		if (line[0] == '#') {
			continue;
		}
		// ���_���W
		else if (line.substr(0, 2) == "v ") {
			pushStoV(v, StringSupport::split(line.substr(2), ' '));
			// z���𔽓]������
			v[v.size() - 1][2] *= -1;
		}
		// UV���W
		else if (line.substr(0, 2) == "vt") {
			pushStoV(vt, StringSupport::split(line.substr(3), ' '));
			// v���𔽓]������
			vt[vt.size() - 1][1] = (1.0f - vt[vt.size() - 1][1]);
		}
		// �@�����W
		else if (line.substr(0, 2) == "vn") {
			pushStoV(vn, StringSupport::split(line.substr(3), ' '));
			// z���𔽓]������
			vn[vn.size() - 1][2] *= -1;
		}
		// �ʏ��
		else if (line.substr(0, 2) == "f ") {
			std::vector<std::string> spaceSplit = StringSupport::split(line.substr(2), ' ');
			for (UINT i = 0; i < spaceSplit.size(); i++) {
				OBJVertex tmp;
				std::vector<std::string> slashSplit = StringSupport::split(spaceSplit[i], '/');
				// ���_���W
				for (UINT j = 0; !v.empty() && j < v[0].size(); j++) {
					tmp.pos[j] = v[std::stoi(slashSplit[0]) - 1][j];
				}
				// UV���W
				for (UINT j = 0; !vt.empty() && j < vt[0].size(); j++) {
					tmp.uv[j] = vt[std::stoi(slashSplit[1]) - 1][j];
				}
				// �@�����W
				for (UINT j = 0; !vn.empty() && j < vn[0].size(); j++) {
					tmp.nor[j] = vn[std::stoi(slashSplit[2]) - 1][j];
				}
				// ���_��񒲍��p������쐬
				std::string key;
				for (int i = 0; i < 3; i++) {
					std::ostringstream sout;
					sout << std::setfill('0') << std::setw(5) << slashSplit[i];
					key += sout.str();
				}
				// �d���`�F�b�N
				if (vertexID.count(key) == 0) {
					// ���_���ǉ�
					aVertexes.push_back(tmp);
					mOBJData[aFileName].indexes[usemtlName].push_back((UINT)aVertexes.size() - 1);
					vertexID[key] = (UINT)aVertexes.size() - 1;
				} else {
					// �o�^����Ă��钸�_�o�b�t�@�̗v�f�ԍ����C���f�b�N�X�o�b�t�@�ɕۑ�����
					mOBJData[aFileName].indexes[usemtlName].push_back(vertexID[key]);
				}
			}
			// 4���_�Ή�
			if (spaceSplit.size() > 3) {
				UINT size = (UINT)mOBJData[aFileName].indexes[usemtlName].size();
				mOBJData[aFileName].indexes[usemtlName].push_back(mOBJData[aFileName].indexes[usemtlName][size - 4]);
				mOBJData[aFileName].indexes[usemtlName].push_back(mOBJData[aFileName].indexes[usemtlName][size - 2]);
			}
		}
		// �����}�e���A�����̐؂�ւ�
		else if (line.substr(0, 6) == "usemtl") {
			usemtlName = line.substr(7);
		}
		// �}�e���A���t�@�C������ۑ�
		else if (line.substr(0, 6) == "mtllib") {
			aMtlNames.push_back(line.substr(7));
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// .mtl�t�@�C����ǂݍ���
/// @param aFileName �t�@�C���p�X
/// @param aMtlNames �}�e���A����
/// @return ���� ����(true)
bool OBJLoader::loadMtlFile(const char* const aFileName, const std::vector<std::string>& aMtlNames)
{
	// �}�e���A�������݂��Ȃ��Ƃ�
	if (aMtlNames.empty()) {
		// �Ƃ肠�������
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
	// �}�e���A���t�@�C����ǂݍ���
	for (auto mtlName : aMtlNames) {
		std::string filePath = aFileName;
		filePath.erase(filePath.rfind("/") + 1);
		// �t�@�C����ǂݍ���
		std::ifstream ifs(filePath + mtlName);
		if (!ifs) {
			return false;
		}

		std::string line, newmtlName;
		while (getline(ifs, line)) {
			// �󔒂͏���
			if (line[0] == ' ' || line[0] == '	') {
				while (line[0] == ' ' || line[0] == '	') {
					line.erase(0, 1);
				}
			}
			// �R�����g�͖�������
			if (line[0] == '#') {
				continue;
			}
			// �}�e���A���O���[�v����ύX
			else if (line.substr(0, 6) == "newmtl") {
				newmtlName = line.substr(7);
			}
			// �A���r�G���g
			else if (line.substr(0, 2) == "Ka") {
				std::vector<std::string> splitSpace = StringSupport::split(line.substr(3), ' ');
				for (UINT i = 0; i < splitSpace.size(); i++) {
					mOBJData[aFileName].materials[newmtlName].ambient[i] = std::stof(splitSpace[i]);
				}
			}
			// �f�t���[�Y
			else if (line.substr(0, 2) == "Kd") {
				std::vector<std::string> splitSpace = StringSupport::split(line.substr(3), ' ');
				for (UINT i = 0; i < splitSpace.size(); i++) {
					mOBJData[aFileName].materials[newmtlName].diffuse[i] = std::stof(splitSpace[i]);
				}
			}
			// �X�y�L�����[
			else if (line.substr(0, 2) == "Ks") {
				std::vector<std::string> splitSpace = StringSupport::split(line.substr(3), ' ');
				for (UINT i = 0; i < splitSpace.size(); i++) {
					mOBJData[aFileName].materials[newmtlName].specular[i] = std::stof(splitSpace[i]);
				}
			}
			// �e�N�X�`��
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
/// ���_�o�b�t�@���쐬����
/// @param aFileName �ǂݍ��݂���OBJ�̃t�@�C���p�X
/// @param aVertexData �Q�Ƃ��钸�_�f�[�^�\����
/// @return �쐬���� ����(true)
bool OBJLoader::createVertexBuffer(const char* const aFileName, const std::vector<OBJVertex>& aVertexes)
{
	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(OBJVertex) * (UINT)aVertexes.size();
		// �g�p���@
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		// BIND�ݒ�
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
		bufferDesc.CPUAccessFlags = 0;
		// ���\�[�X�I�v�V�����̃t���O
		bufferDesc.MiscFlags = 0;
		// �\���̂̃T�C�Y
		bufferDesc.StructureByteStride = 0;
	}

	// ���\�[�X���
	D3D11_SUBRESOURCE_DATA subResource;
	{
		// �o�b�t�@�̒��g�̐ݒ�
		subResource.pSysMem = &aVertexes[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
	HRESULT hr;
	auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreateBuffer(&bufferDesc, &subResource, &mOBJData[aFileName].vertexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �C���f�b�N�X�o�b�t�@���쐬����
/// @param aFileName �ǂݍ��݂���OBJ�̃t�@�C���p�X
/// @return �쐬���� ����(true)
bool OBJLoader::createIndexBuffer(const char* const aFileName)
{
	int cnt = 0;
	for (auto index : mOBJData[aFileName].indexes) {
		mOBJData[aFileName].indexBuffers.emplace_back();
		// �o�b�t�@���
		D3D11_BUFFER_DESC bufferDesc;
		{
			// �o�b�t�@�̃T�C�Y
			bufferDesc.ByteWidth = sizeof(UINT) * (UINT)index.second.size();
			// �g�p���@
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			// BIND�ݒ�
			bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
			bufferDesc.CPUAccessFlags = 0;
			// ���\�[�X�I�v�V�����̃t���O
			bufferDesc.MiscFlags = 0;
			// �\���̂̃T�C�Y
			bufferDesc.StructureByteStride = 0;
		}

		// ���\�[�X���
		D3D11_SUBRESOURCE_DATA subResource;
		{
			// �o�b�t�@�̒��g�̐ݒ�
			subResource.pSysMem = &index.second[0];
			// texture�f�[�^���g�p����ۂɎg�p���郁���o
			subResource.SysMemPitch = 0;
			// texture�f�[�^���g�p����ۂɎg�p���郁���o
			subResource.SysMemSlicePitch = 0;
		}

		// �o�b�t�@�쐬
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
/// �����̕�����𐔒l�ɕϊ����č��W����push����
/// @tparam T �e���v���[�g����
/// @param aVector push����vector
/// @param aStoV ���l�ɕϊ����镶����
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
