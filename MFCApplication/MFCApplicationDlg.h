class CMFCApplicationDlg : public CDialogEx
{
    // Construction
public:
    CMFCApplicationDlg(CWnd* pParent = nullptr);  // standard constructor

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support

    // Implementation
protected:
    HICON m_hIcon;
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

private:
    CString m_exePath;
    CString m_output;
    CEdit m_editPath;
    CEdit m_editOutput;

public:
    afx_msg void OnBnClickedButtonBrowse();
    afx_msg void OnBnClickedButtonRun();
    afx_msg void OnEnChangeEditOutput();
};
