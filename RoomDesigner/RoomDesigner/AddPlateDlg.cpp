// AddPlateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDesigner.h"
#include "AddPlateDlg.h"
#include "afxdialogex.h"


// CAddPlateDlg dialog

IMPLEMENT_DYNAMIC(CAddPlateDlg, CDialogEx)

CAddPlateDlg::CAddPlateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddPlateDlg::IDD, pParent)
	, row(0)
	, col(0)
	, nf(0)
{

}

CAddPlateDlg::~CAddPlateDlg()
{
}

void CAddPlateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, row);
	DDX_Text(pDX, IDC_EDIT2, col);
	DDX_Text(pDX, IDC_EDIT3, nf);
}


BEGIN_MESSAGE_MAP(CAddPlateDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddPlateDlg message handlers
