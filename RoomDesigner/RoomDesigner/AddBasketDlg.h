#pragma once


// CAddBasketDlg dialog

class CAddBasketDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddBasketDlg)

public:
	CAddBasketDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddBasketDlg();

// Dialog Data
	enum { IDD = IDD_ADD_BASKET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT row;
	UINT col;
};
