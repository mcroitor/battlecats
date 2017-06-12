#pragma once


// CInitRoomDlg dialog

class CInitRoomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInitRoomDlg)

public:
	CInitRoomDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInitRoomDlg();

// Dialog Data
	enum { IDD = IDD_INIT_ROOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT width;
	UINT height;
};
