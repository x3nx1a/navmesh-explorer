#include "GFXVideo3d.h"
#include <cstdio>

#include <cmath>

#include "sdk/gfx/imgui/imgui_impl_dx9.h"
#include "MyGui.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"

CGFXVideo3d::CGFXVideo3d(void)
{
}


CGFXVideo3d::~CGFXVideo3d(void)
{
}

long long framecount = 0;

void DrawRect(int x, int y, int height, int width, int color) {

	/* 
	* x1|y1        x2|y1
	* --------------
	* |            |
	* |            |
	* --------------
	* x1|y2        x2|y2
	*/

	int x1 = x;
	int x2 = x + width;
	int y1 = y;
	int y2 = y + height;

	// Draw vertical Left
	DXDrawLine(x1, y1, x2, y1, color, 1.0);
	DXDrawLine(x2, y1, x2, y2, color, 1.0);
	DXDrawLine(x2, y2, x1, y2, color, 1.0);
	DXDrawLine(x1, y2, x1, y1, color, 1.0);

}

void DrawRect(int x, int y, int height, int width) {
	DrawRect(x, y, height, width, 0x00FF0000);
}


float CGFXVideo3d::Project(D3DVECTOR &origin, D3DVECTOR &pos2d) {
	D3DMATRIX *view = &(this->m_viewmatrix);
	D3DVIEWPORT9 viewport;

	this->m_pd3dDevice->GetViewport(&viewport);

	float w = view->_14 * origin.x + view->_24 * origin.y + view->_34 * origin.z + view->_44;

	pos2d.x = 0;
	pos2d.y = 0;

	if (w > 0) {
		// can see object

		float x = view->_11 * origin.x + view->_21 * origin.y + view->_31 * origin.z + view->_41;
		float y = view->_12 * origin.x + view->_22 * origin.y + view->_32 * origin.z + view->_42;

		int screendim[2] = {0};

		this->GetViewportDimensions(screendim);

		int pos_x = ((x / w) * (viewport.Width / 2.0)) + viewport.X + (viewport.Width / 2.0);
		int pos_y = viewport.Y + (viewport.Height / 2.0) - ((y / w) * (viewport.Height / 2.0));


		pos2d.x = pos_x;
		pos2d.y = pos_y;
	}

	return w;
}


struct CUSTOMVERTEX {
	float x, y, z; // Position in 3d space 
	DWORD color; // Color 
}; 

CUSTOMVERTEX g_triangle[] = {
	{-2.0f, -2.0f, 5.0f, D3DCOLOR_XRGB( 255, 0, 0 )}, // Bottom left vertex 
	{ 0.0f, 2.0f, 5.0f, D3DCOLOR_XRGB( 0, 0, 255 )}, // Top vertex 
	{ 2.0f, -2.0f, 5.0f, D3DCOLOR_XRGB( 0, 255, 0 )} // Bottom right vertex 
};

char CGFXVideo3d::EndSceneIMPL(void) {

	// Skip first 100 frames because of bugs
	if (framecount++ > 100) {

		ImGui_ImplDX9_NewFrame();

		MyGui::DoWork();

		ImGui::Render();
	}

	this->m_pd3dDevice->EndScene();

	return 1;
}
