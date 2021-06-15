#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN:
		// �L�[����������
		switch ((char)wParam) {
		case VK_ESCAPE:
			// ESC
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		// ����{�^�����N���b�N������
		PostQuitMessage(0);
		break;
	}
	// ��L�ȊO�̃��b�Z�[�W��Windows�֏�����C����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Window::Window()
	: mWindowHandle(nullptr)
	, mMutex(nullptr)
	, mWindowName(TEXT("NULL"))
	, mWindowWidth(0)
	, mWindowHeight(0)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Window::~Window()
{
	// �E�B���h�E�̔j��
	if (mWindowHandle) {
		DestroyWindow(mWindowHandle);
		UnregisterClass(mWindowName, GetModuleHandle(NULL));
	}
	// �~���[�e�b�N�X�̊J��
	if (mMutex) {
		ReleaseMutex(mMutex);
		CloseHandle(mMutex);
	}
}

//-------------------------------------------------------------------------------------------------
/// ����������
/// @param aWindowName �E�B���h�E��
/// @param aWidth �E�B���h�E���T�C�Y
/// @param aHeight �E�B���h�E�c�T�C�Y
/// @return ���������� ����(true)
bool Window::initialize(const LPCTSTR aWindowName, const USHORT& aWidth, const USHORT& aHeight)
{
	/// �E�B���h�E����ۑ�
	mWindowName = aWindowName;
	mWindowWidth = aWidth;
	mWindowHeight = aHeight;

	// ���d�N�����`�F�b�N����
	if (!checkMultiple()) {
		// ���ɋN������Ă���A�v���P�[�V������O�ʂɕ\�����ďI��
		return false;
	}
	// �E�B���h�E���쐬����
	if (!createWindow()) {
		MessageBox(nullptr, TEXT("�E�B���h�E�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E�̃T�C�Y��ݒ肷��
/// @param aWidth �c�T�C�Y
/// @param aHeight ���T�C�Y
/// @param aCenter �����ɕ\��
void Window::setSize(const USHORT& aWidth, const USHORT& aHeight, const bool& aCenter)
{
	// �E�B���h�E�T�C�Y��ۑ�����
	mWindowWidth = aWidth;
	mWindowHeight = aHeight;

	// ��N���C�A���g�̈�����Z�����E�B���h�E�T�C�Y���v�Z
	RECT wndRect, cltRect;
	GetWindowRect(mWindowHandle, &wndRect);
	GetClientRect(mWindowHandle, &cltRect);
	int resizeW = ((wndRect.right - wndRect.left) - (cltRect.right - cltRect.left)) + mWindowWidth;
	int resizeH = ((wndRect.bottom - wndRect.top) - (cltRect.bottom - cltRect.top)) + mWindowHeight;

	// �쐬�����E�B���h�E�̈ʒu�ƃT�C�Y��ύX
	SetWindowPos(
		mWindowHandle,
		nullptr,
		(GetSystemMetrics(SM_CXSCREEN) - resizeW) / 2, // ���j�^�[�̒����ɕ\��
		(GetSystemMetrics(SM_CYSCREEN) - resizeH) / 2, // ���j�^�[�̒����ɕ\��
		resizeW,
		resizeH,
		SWP_NOZORDER | SWP_NOOWNERZORDER
	);
}

//-------------------------------------------------------------------------------------------------
/// �쐬�����E�B���h�E�n���h����Ԃ�
const HWND Window::hWnd() const
{
	return mWindowHandle;
}

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E����Ԃ�
const LPCTSTR Window::windowName() const
{
	return mWindowName;
}

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E���T�C�Y��Ԃ�
const USHORT& Window::windowWidth() const
{
	return mWindowWidth;
}

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E�c�T�C�Y��Ԃ�
const USHORT& Window::windowHeight() const
{
	return mWindowHeight;
}

//-------------------------------------------------------------------------------------------------
/// ���d�N�����`�F�b�N����
/// @return �`�F�b�N���� ���ɋN������Ă���E�B���h�E�����݂��Ȃ�(true)
bool Window::checkMultiple()
{
	mMutex = CreateMutex(nullptr, FALSE, mWindowName);

	DWORD theErr = GetLastError();
	if (theErr == ERROR_ALREADY_EXISTS) {
		// ���ɋN������Ă���E�B���h�E���擾
		HWND hWnd = FindWindow(mWindowName, nullptr);
		if (IsIconic(hWnd)) {
			// �ŏ�������Ă���Ό��ɖ߂�
			ShowWindowAsync(hWnd, SW_RESTORE);
		}
		// �O�ʕ\������
		SetForegroundWindow(hWnd);

		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E���쐬����
/// @return �쐬���� ����(true)
bool Window::createWindow()
{
	// �E�B���h�E�N���X��o�^����
	if (!registerClass()) {
		return false;
	}

	// �E�B���h�E�쐬
	mWindowHandle =
		CreateWindow(
			mWindowName,
			mWindowName,
			// �ő剻�{�^���ƃT�C�Y�ύX�𖳌�
			WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			GetModuleHandle(NULL),
			nullptr
		);

	// �E�B���h�E�̍쐬�ɐ������Ă��邩���`�F�b�N
	if (!mWindowHandle) {
		return false;
	}

	// �E�B���h�E�̃T�C�Y�𒲐�����
	setSize(mWindowWidth, mWindowHeight);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E�N���X��o�^����
/// @return �o�^���� ����(true)
bool Window::registerClass()
{
	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = mWindowName;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	// �E�B���h�E�N���X��o�^
	if (RegisterClassEx(&wc) == 0) {
		return false;
	}

	return true;
}

} // namespace
// EOF
