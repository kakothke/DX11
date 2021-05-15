#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Window::~Window()
{
	// �E�B���h�E�̔j��
	if (mWindowHandle) {
		DestroyWindow(mWindowHandle);
		UnregisterClass(Define::WindowName, GetModuleHandle(NULL));
	}
	// �~���[�e�b�N�X�̊J��
	if (mMutex) {
		ReleaseMutex(mMutex);
		CloseHandle(mMutex);
	}
}

//-------------------------------------------------------------------------------------------------
/// ����������
/// @return ���������� ����(true)
bool Window::initialize()
{
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
/// �쐬�����E�B���h�E�n���h����Ԃ�
const HWND Window::hWnd() const
{
	return mWindowHandle;
}

//-------------------------------------------------------------------------------------------------
/// ���d�N�����`�F�b�N����
/// @return �`�F�b�N���� ���ɋN������Ă���E�B���h�E�����݂��Ȃ�(true)
bool Window::checkMultiple()
{
	mMutex = CreateMutex(nullptr, FALSE, Define::WindowName);

	DWORD theErr = GetLastError();
	if (theErr == ERROR_ALREADY_EXISTS) {
		// ���ɋN������Ă���E�B���h�E���擾
		HWND hWnd = FindWindow(Define::WindowName, nullptr);
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
			Define::WindowName,
			Define::WindowName,
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
	resizeWindow();

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
	wc.lpszClassName = Define::WindowName;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	// �E�B���h�E�N���X��o�^
	if (RegisterClassEx(&wc) == 0) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E�̃T�C�Y�𒲐�����
void Window::resizeWindow()
{
	// ��N���C�A���g�̈�����Z�����E�B���h�E�T�C�Y���v�Z
	RECT wndRect, cltRect;
	GetWindowRect(mWindowHandle, &wndRect);
	GetClientRect(mWindowHandle, &cltRect);
	int resizeW = ((wndRect.right - wndRect.left) - (cltRect.right - cltRect.left)) + Define::ResolutionWidth;
	int resizeH = ((wndRect.bottom - wndRect.top) - (cltRect.bottom - cltRect.top)) + Define::ResolutionHeight;

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

} // namespace
// EOF
