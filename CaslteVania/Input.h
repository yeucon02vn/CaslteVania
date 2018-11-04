#pragma once
#include <dinput.h>

int InitDirectInput();
int InitKeyboard(HWND);
void PollKeyboard();

int IsKeyDown(int key);

int IsKeyRelease(int key);
int IsKeyPress(int key);

void KillKeyboard();
