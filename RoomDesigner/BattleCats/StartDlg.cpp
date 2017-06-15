// StartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BattleCats.h"
#include "StartDlg.h"
#include "afxdialogex.h"


// CStartDlg dialog

IMPLEMENT_DYNAMIC(CStartDlg, CDialogEx)

CStartDlg::CStartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, nr_it(10)
{

}

CStartDlg::~CStartDlg()
{
}

void CStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, nr_it);
}


BEGIN_MESSAGE_MAP(CStartDlg, CDialogEx)
END_MESSAGE_MAP()


// CStartDlg message handlers
