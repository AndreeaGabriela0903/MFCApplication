
// MFCApplication.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCApplicationApp:
// See MFCApplication.cpp for the implementation of this class
//


class CMFCApplicationApp : public CWinApp
{
private:
	CString m_exePath;
	CString m_output;
	CEdit m_editPath;
	CEdit m_editOutput;

public:
	CMFCApplicationApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicationApp theApp;
