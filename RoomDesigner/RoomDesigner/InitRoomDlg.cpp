// InitRoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDesigner.h"
#include "InitRoomDlg.h"
#include "afxdialogex.h"


// CInitRoomDlg dialog

IMPLEMENT_DYNAMIC(CInitRoomDlg, CDialogEx)

CInitRoomDlg::CInitRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitRoomDlg::IDD, pParent)
	, width(10)
	, height(10)
{

}

CInitRoomDlg::~CInitRoomDlg()
{
}

void CInitRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, width);
	DDX_Text(pDX, IDC_HEIGHT, height);
}


BEGIN_MESSAGE_MAP(CInitRoomDlg, CDialogEx)
END_MESSAGE_MAP()


// CInitRoomDlg message handlers
