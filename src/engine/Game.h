#pragma once
#include "sdk/gfx/GFXMainFrame/GFXMainFrame.h"

class CGame : public CGFXMainFrame {
public:
	void InitGameAssets();
};

#define g_CGame ((CGame*)0x00EECE80)
