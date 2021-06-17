#include "SpriteLoader.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "TextureLoader.h"

namespace KDXK {

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
/// �X�v���C�g��ǂݍ���
/// @param aFileName �t�@�C���p�X
/// @return ���� �����itrue�j
bool SpriteLoader::load(const char* const aFileName)
{
	if (mSpriteData.count(aFileName)) {
		MessageBox(nullptr, TEXT("�X�v���C�g�̓�d�ǂݍ��݁B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	if (!std::ifstream(aFileName)) {
		MessageBox(nullptr, TEXT("�ǂݍ������Ƃ��Ă���X�v���C�g�����݂��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	const auto texture = TextureLoader::getInst();
	if (!texture->load(aFileName)) {
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
void SpriteLoader::release(const char* const aFileName)
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
SpriteData* SpriteLoader::getSpriteData(const char* const aFileName)
{
	if (!mSpriteData.count(aFileName)) {
		MessageBox(nullptr, TEXT("���݂��Ȃ��X�v���C�g���擾���悤�Ƃ��Ă��܂��B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return nullptr;
	}
	return &mSpriteData[aFileName];
}

//-------------------------------------------------------------------------------------------------
/// ���_�o�b�t�@�쐬
/// @param aFileName �t�@�C���p�X
/// @return �쐬���� ����(true)
bool SpriteLoader::createVertexBuffer(const char* const aFileName)
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
	const auto device = Direct3D11::getInst()->getDevice();
	hr = device->CreateBuffer(&bufferDesc, &subResource, &mSpriteData[aFileName].vertexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�V���쐬
/// @param aFileName �t�@�C���p�X
/// @param aVertexes ���_�f�[�^
void SpriteLoader::createMesh(const char* const aFileName, SpriteVertex* aVertexes)
{
	// �e�N�X�`���[�̃T�C�Y���Q��
	ID3D11Resource* res = nullptr;
	const auto texture = TextureLoader::getInst();
	texture->getTexture(aFileName)->GetResource(&res);
	ID3D11Texture2D* tex2D = nullptr;
	res->QueryInterface(&tex2D);
	D3D11_TEXTURE2D_DESC desc;
	tex2D->GetDesc(&desc);

	float width = (float)desc.Width;
	float height = (float)desc.Height;

	res->Release();
	res = nullptr;
	tex2D->Release();
	tex2D = nullptr;

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
