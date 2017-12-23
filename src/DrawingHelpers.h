#pragma once

#include <d3dx9.h>

void PrettyLine3D(D3DVECTOR &p1, D3DVECTOR& p2, int step, int color);
void PrettyLine3D(D3DVECTOR &p1, D3DVECTOR& p2, int step);

void rotatey(D3DXVECTOR3& vec, float radiant);
