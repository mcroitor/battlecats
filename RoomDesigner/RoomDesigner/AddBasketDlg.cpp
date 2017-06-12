// AddBasketDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDesigner.h"
#include "AddBasketDlg.h"
#include "afxdialogex.h"


// CAddBasketDlg dialog

IMPLEMENT_DYNAMIC(CAddBasketDlg, CDialogEx)

CAddBasketDlg::CAddBasketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddBasketDlg::IDD, pParent)
	, row(0)
	, col(0)
{

}

CAddBasketDlg::~CAddBasketDlg()
{
}

void CAddBasketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, row);
	DDX_Text(pDX, IDC_EDIT2, col);
}


BEGIN_MESSAGE_MAP(CAddBasketDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddBasketDlg message handlers
