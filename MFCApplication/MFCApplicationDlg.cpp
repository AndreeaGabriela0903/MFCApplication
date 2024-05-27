#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CMFCApplicationDlg::OnBnClickedButtonBrowse)
    ON_BN_CLICKED(IDC_BUTTON_RUN, &CMFCApplicationDlg::OnBnClickedButtonRun)
    ON_EN_CHANGE(IDC_EDIT_OUTPUT, &CMFCApplicationDlg::OnEnChangeEditOutput)
END_MESSAGE_MAP()

CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
    DDX_Control(pDX, IDC_EDIT_OUTPUT, m_editOutput);
}

BOOL CMFCApplicationDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    SetWindowText(_T("MFC Application Dialog"));

    return TRUE;
}

void CMFCApplicationDlg::OnBnClickedButtonBrowse()
{
    CFileDialog dlg(TRUE, _T("exe"), nullptr, 0, _T("Executable Files (*.exe)|*.exe|All Files (*.*)|*.*||"));
    if (dlg.DoModal() == IDOK)
    {
        m_exePath = dlg.GetPathName();
        m_editPath.SetWindowText(m_exePath);
    }
}

void CMFCApplicationDlg::OnBnClickedButtonRun()
{
    if (m_exePath.IsEmpty())
    {
        AfxMessageBox(_T("Please select an executable first."));
        return;
    }

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    HANDLE hRead, hWrite;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0))
    {
        AfxMessageBox(_T("Failed to create pipe."));
        return;
    }

    STARTUPINFO si = { 0 };
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.hStdOutput = hWrite;
    si.hStdError = hWrite;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi = { 0 };

    if (!CreateProcess(NULL, m_exePath.GetBuffer(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        AfxMessageBox(_T("Failed to launch executable."));
        CloseHandle(hWrite);
        CloseHandle(hRead);
        return;
    }

    CloseHandle(hWrite);

    DWORD dwRead;
    CHAR chBuf[4096];
    CString output;

    while (ReadFile(hRead, chBuf, sizeof(chBuf) - 1, &dwRead, NULL) && dwRead > 0)
    {
        chBuf[dwRead] = '\0';
        output += chBuf;
    }

    m_editOutput.SetWindowText(output);

    CloseHandle(hRead);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


void CMFCApplicationDlg::OnEnChangeEditOutput()
{

   
}
