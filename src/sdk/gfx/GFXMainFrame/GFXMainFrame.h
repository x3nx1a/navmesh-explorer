#pragma once

#include <Windows.h>
#include "sdk/BSLib/RuntimeClass.h"
#include "sdk/gfx/GFXMainFrame/CMsgHandler.h"
#include "sdk/gfx/GFXMainFrame/ObjChild.h"


class CGFXMainFrame : public CObjChild, public CMsgHandler {
public:
	virtual char F8(int a1); // maybe init (cgame implementation loads settings)
	virtual char F9(); // returns 1 in this impl
	virtual void Cycle();
	virtual void SetNextProcess(CRuntimeClass*); // this func is also referenced by address. WTF.
	virtual void Renderer(); // wat?
	virtual char RenderFrame();
	virtual void F14();
	virtual void F15(); // asserts if m_blDrawing == 0
	virtual char VirtualApplyDepthBufferPriority(int a1); // returns 0
	virtual int F17(int a1); // returns 1
	virtual char F18(int a1); // returns 0


	HWND hwnd() const;
	
public:
	char gap_0[4*4];
	
	HWND mainHWND;
};
