#pragma once

class CObj;
struct CRuntimeClass;

#include "Obj.h"
#include <Windows.h>

// Funfact: Joymax stole this class from afx.h and renamed various macros. LOL.
struct CRuntimeClass
{
	const char * m_lpszClassName;
	int m_nObjectSize;
	unsigned int m_wSchema; // schema number of the loaded class

	CRuntimeClass *m_pBaseClass;

	int field_10;
	int field_14;

	CObj*(__stdcall *m_pfnCreateObject)();
	CObj*(__stdcall *m_pfnDeleteObject)();



	CObj *CreateObject();
	BOOL IsDerivedFrom(const CRuntimeClass* pBaseClass) const;


	// dynamic name lookup and creation
	static CRuntimeClass* __stdcall FromName(const char * lpszClassName);
	static CRuntimeClass* __stdcall FromName(const wchar_t * lpszClassName);
	static CObj* __stdcall CreateObject(const char * lpszClassName);
	static CObj* __stdcall CreateObject(const wchar_t * lpszClassName);
};

