#pragma once
#include <D3DX9.h>
#include "Common\DXUtil.h"
#include "Common\D3DEnumeration.h"
#include "Common\D3DSettings.h"
#include "Common\D3DApp.h"
#include "Common\D3DFile.h"
#include "Common\D3DFont.h"
#include "Common\D3DUtil.h"

#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dx9dt.lib")
#pragma comment(lib, "comctl32.lib")


class CGFXVideo3d : public CD3DApplication
{
public:
	CGFXVideo3d(void);
	virtual ~CGFXVideo3d(void);

	virtual void pad0() = 0;
	virtual void pad1() = 0;
	virtual void pad2() = 0;
	virtual void pad3() = 0;
	virtual void pad4() = 0;
	virtual void pad5() = 0;
	virtual void GetViewportDimensions(int *dim) = 0;
	virtual void pad7() = 0;
	virtual void pad8() = 0;

	virtual char BeginScene(void) = 0;
	virtual char EndScene(void) = 0;
	virtual char Present(int, int, int, int) = 0;

	static inline CGFXVideo3d* get() {
		return *((CGFXVideo3d**)0x0110F7EC);
	}

	char EndSceneIMPL();

	float Project(D3DVECTOR &origin, D3DVECTOR &pos2d);



	// 0x340 is here

	char gapbasfasdaf[0x550-0x340];


	D3DMATRIX m_viewmatrix; //0x0550 


};


void DrawRect(int x, int y, int height, int width, int color);
void DrawRect(int x, int y, int height, int width);
