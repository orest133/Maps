#include "getResolution.h"

void getResolution::GetDesktopResolution(int& vertical, int& horizontal) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
