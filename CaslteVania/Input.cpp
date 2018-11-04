#include "Input.h"

LPDIRECTINPUT8 dinput;
LPDIRECTINPUTDEVICE8 dkeyboard;

char keys[256];
char keysBuffer[256];

int InitDirectInput()
{
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dinput,
		NULL);

	if (result != DI_OK)
		return 0;

	// Kh?i t?o keyboard
	result = dinput->CreateDevice(GUID_SysKeyboard, &dkeyboard, NULL);

	if (result != DI_OK)
		return 0;

	return 1;
}

int InitKeyboard(HWND hwnd)
{
	// Thi?t l?p ??nh d?ng d? li?u
	HRESULT result = dkeyboard->SetDataFormat(&c_dfDIKeyboard);

	if (result != DI_OK)
		return 0;

	// Thi?t l?p m?c ?? h?p t�c
	// Ch? ra m?c ?? b�n ph�m direct input s? ch? ra theo m?c ?? ?u ti�n
	result = dkeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	if (result != DI_OK)
		return 0;

	// Gi�nh ki?m so�t thi?t b? ?? gi�nh l?y b�n ph�m ?? c� th? b?t ??u ki?m tra n�t ???c nh?n
	result = dkeyboard->Acquire();

	if (result != DI_OK)
		return 0;

	return 1;
}

void PollKeyboard()
{
	for (int i = 0; i < 256; i++)
		keysBuffer[i] = keys[i];

	dkeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
}

int IsKeyDown(int key)
{
	return (keys[key] & 0x80);
}

int IsKeyPress(int key)
{
	return (IsKeyDown(key) && !(keysBuffer[key] & 0x80));
}

int IsKeyRelease(int key)
{
	return (!IsKeyDown(key) && (keysBuffer[key] & 0x80));
}

void KillKeyboard()
{
	if (dkeyboard != NULL)
	{
		dkeyboard->Unacquire();
		dkeyboard->Release();
		dkeyboard = NULL;
	}
}