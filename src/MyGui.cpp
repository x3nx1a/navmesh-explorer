//#ifndef IM_ARRAYSIZE
//#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
//#endif

#include "MyGui.h"

#include <vector>

#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "DrawingHelpers.h"

#include "sdk/gfx/imgui/imgui_impl_dx9.h"
#include "sdk/gfx/GFX3DFunction/GFXVideo3d.h"

#include "navmesh/RTNavMeshTerrain.h"

#define g_DebugMode (*reinterpret_cast<int*>(0x00EED6A7))

bool b_wnd_nav_info = false;

CRTNavMeshTerrain *pNavmesh = 0;

void MyGui::MainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Debug Mode", NULL, reinterpret_cast<bool*>(0x00EED6A7));
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("NavMesh"))
		{
			ImGui::MenuItem("NavMesh Info", NULL, &b_wnd_nav_info);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void MyGui::NavMeshInfo(bool *p_open)
{
	CGFXVideo3d *gfx = CGFXVideo3d::get();

	static bool bFreeze = false;
	if (!bFreeze || pNavmesh == 0)
	{
		pNavmesh = g_CurrentNavMesh;
	}

	ImGui::Begin("NavMesh Info", p_open);

	ImGui::Text("0x%p", pNavmesh);
	ImGui::Text("Region: 0x%04x", pNavmesh->region);

	ImGui::Text("Cells: %d", pNavmesh->m_navcells.size());

	ImGui::Checkbox("Freeze Current Mesh", &bFreeze);

	static bool bCells = false;
	ImGui::Checkbox("Render Cells", &bCells);

	static bool bEdgeInternal = false;
	ImGui::Checkbox("Render Edge (internal)", &bEdgeInternal);

	static bool bEdgeGlobal = false;
	ImGui::Checkbox("Render Edge (global)", &bEdgeGlobal);

	static bool bObjectOrigin = false;
	ImGui::Checkbox("Render Object Origin", &bObjectOrigin);

	static bool bObjectCells = false;
	ImGui::Checkbox("Render Object Cells", &bObjectCells);

	static int step = 20;
	ImGui::InputInt("Step", &step);

	// Render NavMeshTerrain Cells
	if (bCells)
	{
		for (std::vector<CRTNavCellQuad>::iterator it = pNavmesh->m_navcells.begin(); it != pNavmesh->m_navcells.end(); ++it)
		{
			D3DVECTOR v2 = {0.0, 30, 0.0};
			v2.x = it->vMin_X;
			v2.z = it->vMin_Z;

			D3DVECTOR v3 = {0.0, 30, 0.0};
			v3.x = it->vMax_X;
			v3.z = it->vMax_Z;

			D3DVECTOR pmiss1;
			pmiss1.x = v3.x;
			pmiss1.z = v2.z;

			D3DVECTOR pmiss2;
			pmiss2.x = v2.x;
			pmiss2.z = v3.z;

			PrettyLine3D(v2, pmiss1, step);
			PrettyLine3D(pmiss1, v3, step);
			PrettyLine3D(v3 ,pmiss2, step);
			PrettyLine3D(pmiss2, v2, step);
		}
	}

	// Render NavMeshTerrain Edges (internal)
	if (bEdgeInternal)
	{
		for (std::vector<CRTNavEdgeInternal>::iterator it = pNavmesh->m_edge_internal.begin(); it != pNavmesh->m_edge_internal.end(); ++it )
		{
			D3DVECTOR min, max;
			min.x = it->m_edge.EdgeMin.x;
			min.z = it->m_edge.EdgeMin.y;

			max.x = it->m_edge.EdgeMax.x;
			max.z = it->m_edge.EdgeMax.y;

			if (it->m_edge.N4_1 == 4)
			{
				PrettyLine3D(min, max, step, D3DCOLOR_ARGB(0, 0, 255, 0));
			} 
			else if (it->m_edge.N4_1 == 2)
			{
				PrettyLine3D(min, max, step, D3DCOLOR_ARGB(0, 255, 0, 0));
			}
			else
			{
				// Unsure what this means, but ill draw it anyways
				PrettyLine3D(min, max, step, D3DCOLOR_ARGB(0, 0, 255, 255));
			}
		}
	}

	if (bObjectOrigin || bObjectCells)
	{
		for (std::vector<CollisionObject*>::iterator it = pNavmesh->m_objectlist.begin(); it != pNavmesh->m_objectlist.end(); ++it)
		{
			CollisionObject *collision_object = *it;

			float yaw = -collision_object->yaw;

			if (bObjectOrigin) 
			{
				D3DVECTOR &vec = collision_object->origin;
				D3DVECTOR vec2d;
				if (gfx->Project(vec, vec2d) > 0)
				{
					{
						// Red X
						D3DXVECTOR3 pTarget(20,0,0);
						rotatey(pTarget, yaw);

						pTarget += vec;

						D3DVECTOR pTarget2D;
						if (gfx->Project(pTarget, pTarget2D) > 0) DXDrawLine(vec2d.x, vec2d.y, pTarget2D.x, pTarget2D.y, D3DCOLOR_ARGB(0, 255, 0, 0), 1.0);
					}

					{
						// Blue Y
						D3DXVECTOR3 pTarget(0,20,0);
						rotatey(pTarget, yaw);

						pTarget += vec;
						
						D3DVECTOR pTarget2D;
						if (gfx->Project(pTarget, pTarget2D) > 0) DXDrawLine(vec2d.x, vec2d.y, pTarget2D.x, pTarget2D.y, D3DCOLOR_ARGB(0, 0, 0, 255), 1.0);
					}

					{
						// Green Z
						D3DXVECTOR3 pTarget(0,0,20);
						rotatey(pTarget, yaw);
						
						pTarget += vec;

						D3DVECTOR pTarget2D;
						if (gfx->Project(pTarget, pTarget2D) > 0) DXDrawLine(vec2d.x, vec2d.y, pTarget2D.x, pTarget2D.y, D3DCOLOR_ARGB(0, 0, 255, 0), 1.0);
					}

					if (it == pNavmesh->m_objectlist.begin())
					{
						DrawRect(vec2d.x-5, vec2d.y-5, 10, 10, D3DCOLOR_ARGB(0, 255, 0, 0));
					} 
					else
					{
						DrawRect(vec2d.x-5, vec2d.y-5, 10, 10, D3DCOLOR_ARGB(0, 255, 255, 0));
					}
				}
			}

			if (bObjectCells)
			{
				CRTNavMeshObj *nvm = collision_object->m_nvm_obj;

				for (std::vector<CRTNavCellTri>::iterator it = nvm->m_cells.begin(); it != nvm->m_cells.end(); ++it)
				{
					CRTNavCellTri &cell = *it;

					D3DXVECTOR3 p1, p2, p3, p12d, p22d, p32d;

					p1 = cell.vP1;
					rotatey(p1, yaw);
					p1 += collision_object->origin;

					p2 = cell.vP2;
					rotatey(p2, yaw);
					p2 += collision_object->origin;

					p3 = cell.vP3;
					rotatey(p3, yaw);
					p3 += collision_object->origin;

					
					bool vis1 = gfx->Project(p1, p12d) > 0;
					bool vis2 = gfx->Project(p2, p22d) > 0;
					bool vis3 = gfx->Project(p3, p32d) > 0;

					if (vis1 && vis2) DXDrawLine(p12d.x, p12d.y, p22d.x, p22d.y, D3DCOLOR_ARGB(0, 255, 128, 0), 1.0);
					if (vis2 && vis3) DXDrawLine(p22d.x, p22d.y, p32d.x, p32d.y, D3DCOLOR_ARGB(0, 255, 128, 0), 1.0);
					if (vis1 && vis3) DXDrawLine(p12d.x, p12d.y, p32d.x, p32d.y, D3DCOLOR_ARGB(0, 255, 128, 0), 1.0);
				}
			}
		}
	}

	ImGui::End();
}

void MyGui::DoWork() {
	MainMenuBar();

	if (b_wnd_nav_info) NavMeshInfo(&b_wnd_nav_info);
}

