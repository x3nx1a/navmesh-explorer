#include "DrawingHelpers.h"

#include "sdk/gfx/GFX3DFunction/GFXVideo3d.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "navmesh/RTNavMeshTerrain.h"

// Our own copy of the NavMesh to avoid flickering
extern CRTNavMeshTerrain *pNavmesh;

void PrettyLine3D(D3DVECTOR &p1, D3DVECTOR& p2, int step, int color)
{
	CGFXVideo3d *gfx = CGFXVideo3d::get();

	float distance_x = p2.x - p1.x;
	float distance_z = p2.z - p1.z;

	float distance = sqrt(distance_x * distance_x + distance_z * distance_z);

	D3DVECTOR prev2d = {0,0,0};
	bool prevVis = false;

	for (int a = 0; a <= distance; a+=step)
	{
		D3DVECTOR p;
		p.x = p1.x + distance_x / distance * a;
		p.z = p1.z + distance_z / distance * a;

		pNavmesh->FindHeight(p);
		D3DVECTOR p2d;
		bool vis = gfx->Project(p, p2d) > 0;
		if (vis)
		{
			if (a>0 && prevVis) {
				DXDrawLine(prev2d.x, prev2d.y, p2d.x, p2d.y, color, 1.0);
			}
		}

		prev2d = p2d;
		prevVis = vis;

	}
}


void PrettyLine3D(D3DVECTOR &p1, D3DVECTOR& p2, int step)
{
	PrettyLine3D(p1, p2, step, 0x00FF88FF);
}

// I feel guilty for this function, sorry. I couldn't figure out how to do this with DirectX :(
void rotatey(D3DXVECTOR3& vec, float radiant)
{
	float x = cos(radiant) * vec.x + sin(radiant) * vec.z;
	float y = vec.y;
	float z = -sin(radiant) * vec.x + cos(radiant) * vec.z;

	vec.x = x;
	vec.y = y;
	vec.z = z;
}