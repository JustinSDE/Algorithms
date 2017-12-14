
// Dijkstra_Prim_Mixture.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDijkstra_Prim_MixtureApp:
// See Dijkstra_Prim_Mixture.cpp for the implementation of this class
//

class CDijkstra_Prim_MixtureApp : public CWinApp
{
public:
	CDijkstra_Prim_MixtureApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDijkstra_Prim_MixtureApp theApp;