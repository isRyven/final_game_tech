/*
-------------------------------------------------------------------------------
Name:
	FPL-Demo | No Runtime Linking

Description:
	Demo for showing how FPL works without runtime-linking

Requirements:
	- C99 Compiler
	- Final Platform Layer

Author:
	Torsten Spaete

Changelog:
	## 2018-10-01
	- Initial version
-------------------------------------------------------------------------------
*/

#define FPL_IMPLEMENTATION
#define FPL_NO_RUNTIME_LINKING
#include <final_platform_layer.h>

int main(int argc, char **args) {
	fplSettings settings = fplMakeDefaultSettings();
	fplCopyString("No Runtime Linking", settings.window.windowTitle, fplArrayCount(settings.window.windowTitle) - 1);
	settings.video.driver = fplVideoDriverType_Software;
	settings.video.isAutoSize = true;
	if (fplPlatformInit(fplInitFlags_Video, &settings)) {
		while (fplWindowUpdate()) {
			fplEvent ev;
			while (fplPollEvent(&ev)) {}
			fplVideoBackBuffer *backBuffer = fplGetVideoBackBuffer();
			for (uint32_t y = 0; y < backBuffer->height; ++y) {
				uint32_t *p = (uint32_t *)((uint8_t *)backBuffer->pixels + y * backBuffer->lineWidth);
				for (uint32_t x = 0; x < backBuffer->width; ++x) {
					uint32_t color = 0xFFFFFF00;
					*p++ = color;
				}
			}
			fplVideoFlip();
		}
		fplPlatformRelease();
	}
	return 0;
}