#include "OBJLoader.h"

//-------------------------------------------------------------------------------------------------
#include "SplitString.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
bool OBJLoader::load(const char* aFileName)
{
	if (mOBJData.count(aFileName)) {
		MessageBox(nullptr, TEXT("OBJ�t�@�C���̓�d�ǂݍ��݁B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	std::vector<OBJVertexData> vertexData;
	if (!createMesh(aFileName, vertexData)) {
		MessageBox(nullptr, TEXT("OBJ�t�@�C���̃��b�V���̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createVertexBuffer(aFileName, vertexData)) {
		MessageBox(nullptr, TEXT("OBJ�t�@�C���̒��_�o�b�t�@�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!createIndexBuffer(aFileName)) {
		MessageBox(nullptr, TEXT("OBJ�t�@�C���̃C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	vertexData.clear();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// OBJ�t�@�C����j������
/// @param aFileName �j��������OBJ�̃t�@�C���p�X
void OBJLoader::release(const char* aFileName)
{
	if (mOBJData.count(aFileName)) {
		mOBJData.erase(aFileName);
	} else {
		MessageBox(nullptr, TEXT("���݂��Ȃ�OBJ�f�[�^��j�����悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJ�t�@�C���̃f�[�^���擾����
/// @param aFileName �擾������OBJ�̃t�@�C���p�X
OBJData* OBJLoader::getObjData(const char* aFileName)
{
	if (mOBJData.count(aFileName)) {
		return &mOBJData[aFileName];
	}
	MessageBox(nullptr, TEXT("���݂��Ȃ�OBJ�f�[�^���擾���悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// ���b�V�����쐬����
/// @param aFileName �ǂݍ��݂���OBJ�̃t�@�C���p�X
/// @param aVertexData �v�f��ǉ������钸�_�f�[�^�\����
/// @return �쐬���� ����(true)
bool OBJLoader::createMesh(const char* aFileName, std::vector<OBJVertexData>& aVertexData)
{
	// �t�@�C����ǂݍ���
	std::ifstream ifs(aFileName);
	if (!ifs) {
		return false;
	}

	std::vector<std::vector<float>> positions, textures, normals;

	std::string str;
	while (getline(ifs, str)) {
		// �R�����g�͖�������
		if (str[0] == '#') {
			continue;
		}
		// ���_���W
		if (str.substr(0, 2) == "v ") {
			pushAtofVector(positions, SplitString::split(str.substr(2), ' '));
		}
		// UV���W
		else if (str.substr(0, 2) == "vt") {
			pushAtofVector(textures, SplitString::split(str.substr(3), ' '));
		}
		// �@�����W
		else if (str.substr(0, 2) == "vn") {
			pushAtofVector(normals, SplitString::split(str.substr(3), ' '));
		}
		// �ʏ��
		else if (str.substr(0, 2) == "f ") {
			std::vector<std::string> spaceSplit = SplitString::split(str.substr(2), ' ');
			for (UINT i = 0; i < spaceSplit.size(); i++) {
				OBJVertexData tmp;
				std::vector<std::string> slashSplit = SplitString::split(spaceSplit[i], '/');
				// ���_���W
				for (UINT j = 0; !positions.empty() && j < positions[0].size(); j++) {
					tmp.pos[j] = positions[std::stoi(slashSplit[0]) - 1][j];
				}
				// UV���W
				for (UINT j = 0; !textures.empty() && j < textures[0].size(); j++) {
					tmp.uv[j] = textures[std::stoi(slashSplit[1]) - 1][j];
				}
				// �@�����W
				for (UINT j = 0; !normals.empty() && j < normals[0].size(); j++) {
					tmp.nor[j] = normals[std::stoi(slashSplit[2]) - 1][j];
				}
				// �e�o�b�t�@�R���e�i�ɒǉ�
				aVertexData.push_back(tmp);
				mOBJData[aFileName].indexes.push_back(aVertexData.size() - 1);
			}
		}
		// �g�p���Ă���mtl�t�@�C���̒ǉ�
		else if (str.substr(0, 6) == "usemtl") {

		}
		// �������Ă���}�e���A���̖��O���o���Ă���
		else if (str.substr(0, 6) == "mtllib") {

		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���_�o�b�t�@���쐬����
/// @param aFileName �ǂݍ��݂���OBJ�̃t�@�C���p�X
/// @param aVertexData �Q�Ƃ��钸�_�f�[�^�\����
/// @return �쐬���� ����(true)
bool OBJLoader::createVertexBuffer(const char* aFileName, const std::vector<OBJVertexData>& aVertexData)
{
	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(OBJVertexData) * aVertexData.size();
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
		subResource.pSysMem = &aVertexData[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
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
/// �C���f�b�N�X�o�b�t�@���쐬����
/// @param aFileName �ǂݍ��݂���OBJ�̃t�@�C���p�X
/// @return �쐬���� ����(true)
bool OBJLoader::createIndexBuffer(const char* aFileName)
{
	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(UWORD) * mOBJData[aFileName].indexes.size();
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
		subResource.pSysMem = &mOBJData[aFileName].indexes[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(
		&bufferDesc,
		&subResource,
		&mOBJData[aFileName].indexBuffer
	))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �������float�^�ɕϊ����č��W����push����
/// @tparam T �e���v���[�g����
/// @param aData push����f�[�^��
/// @param aStr float�^�ɒ���������
template <typename T>
void OBJLoader::pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr)
{
	std::vector<T> values;
	for (UINT i = 0; i < aStr.size(); i++) {
		values.push_back(std::stof(aStr[i]));
	}
	aData.push_back(values);
}

} // namespace
// EOF
