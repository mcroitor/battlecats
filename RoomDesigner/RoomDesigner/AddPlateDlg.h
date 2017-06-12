#pragma once


// CAddPlateDlg dialog

class CAddPlateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPlateDlg)

public:
	CAddPlateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddPlateDlg();

// Dialog Data
	enum { IDD = IDD_ADD_PLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT row;
	UINT col;
	UINT nf;
};
