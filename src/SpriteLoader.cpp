#include "SpriteLoader.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();
const static auto TEXTURE_LOADER = TextureLoader::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SpriteLoader::SpriteLoader()
	: mSpriteData()
{
	mSpriteData.clear();
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
SpriteLoader::~SpriteLoader()
{
	if (!mSpriteData.empty()) {
		mSpriteData.clear();
	}
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
SpriteLoader::SpriteData::~SpriteData()
{
	if (vertexBuffer) {
		vertexBuffer->Release();
		vertexBuffer = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// �X�v���C�g��ǂݍ���
/// @param aFileName �t�@�C���p�X
/// @return ���� �����itrue�j
bool SpriteLoader::load(const LPCSTR aFileName)
{
	if (mSpriteData.count(aFileName)) {
		MessageBox(nullptr, TEXT("�X�v���C�g�̓�d�ǂݍ��݁B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!std::ifstream(aFileName)) {
		MessageBox(nullptr, TEXT("�ǂݍ������Ƃ��Ă���X�v���C�g�����݂��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}	
	if (!TEXTURE_LOADER->load(aFileName)) {
		return false;
	}
	if (!createVertexBuffer(aFileName)) {
		MessageBox(nullptr, TEXT("���_�o�b�t�@�̍쐬�Ɏ��s���܂����B(Sprite)"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		mSpriteData.erase(aFileName);
		return false;
	}
	mSpriteData[aFileName].fileName = aFileName;

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �j��
/// @param aFileName �t�@�C���p�X
void SpriteLoader::release(const LPCSTR aFileName)
{
	if (!mSpriteData.count(aFileName)) {
		MessageBox(nullptr, TEXT("���݂��Ȃ��X�v���C�g��j�����悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
	mSpriteData.erase(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// �X�v���C�g�f�[�^���擾����
/// @param aFileName �t�@�C���p�X
/// @return �X�v���C�g�f�[�^
SpriteLoader::SpriteData* SpriteLoader::getSpriteData(const LPCSTR aFileName)
{
	if (!mSpriteData.count(aFileName)) {
		MessageBox(nullptr, TEXT("���݂��Ȃ��X�v���C�g���擾���悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return nullptr;
	}
	return &mSpriteData[aFileName];
}

//-------------------------------------------------------------------------------------------------
/// ���_�o�b�t�@���쐬����
/// @param aFileName �t�@�C���p�X
/// @return �쐬���� ����(true)
bool SpriteLoader::createVertexBuffer(const LPCSTR aFileName)
{
	SpriteVertex vertexes[4];
	createMesh(aFileName, vertexes);
	// �o�b�t�@���
	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(SpriteVertex) * 4;
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
		subResource.pSysMem = &vertexes[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
	HRESULT hr;
	hr = D3D11->getDevice()->CreateBuffer(&bufferDesc, &subResource, &mSpriteData[aFileName].vertexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�V�����쐬����
/// @param aFileName �t�@�C���p�X
/// @param aVertexes ���_�f�[�^
void SpriteLoader::createMesh(const LPCSTR aFileName, SpriteVertex* aVertexes)
{
	// �e�N�X�`���[�̃T�C�Y���Q��
	DirectX::XMFLOAT2 size = TEXTURE_LOADER->getTextureSize(aFileName);

	float width = (float)size.x / 2;
	float height = (float)size.y / 2;

	// �\��
	{
		// ���_0
		aVertexes[0].pos[0] = -width;
		aVertexes[0].pos[1] = -height;
		aVertexes[0].uv[0] = 0;
		aVertexes[0].uv[1] = 1;
		// ���_1
		aVertexes[1].pos[0] = width;
		aVertexes[1].pos[1] = -height;
		aVertexes[1].uv[0] = 1;
		aVertexes[1].uv[1] = 1;
		// ���_2
		aVertexes[2].pos[0] = -width;
		aVertexes[2].pos[1] = height;
		aVertexes[2].uv[0] = 0;
		aVertexes[2].uv[1] = 0;
		//// ���_3
		aVertexes[3].pos[0] = width;
		aVertexes[3].pos[1] = height;
		aVertexes[3].uv[0] = 1;
		aVertexes[3].uv[1] = 0;
	}
}

} // namespace
// EOF
