// LearnDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Learn.h"
#include "LearnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLearnDlg 对话框




CLearnDlg::CLearnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLearnDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLearnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, word_edit);
}

BEGIN_MESSAGE_MAP(CLearnDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CLearnDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLearnDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CLearnDlg::OnBnClickedButton2)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TEST, &CLearnDlg::OnBnClickedTest)
END_MESSAGE_MAP()


// CLearnDlg 消息处理程序

BOOL CLearnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	meaning.Create(IDD_MEANING,this);
	m_test.Create(IDD_TEST,this);
	m_test.setWordList(meaning.getWordList());


//	SetTimer(1,1000,NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLearnDlg::OnPaint()
{
	CString str;
	str.Format(_T("目前共收录 %d 个词条"),meaning.getSize() );
	SetDlgItemText(IDC_INFO,str);
	word_edit.SetWindowText(_T(""));
	//word_edit.SetSel(0,0);
	word_edit.SetFocus();

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CLearnDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLearnDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str = _T("");
	word_edit.GetWindowText(str);
	
	if(str.GetLength()==0)
		MessageBox(_T("请输入一个单词"));
	else if( ((*(str.GetBuffer())) & 0xF000) == 0 )
	{
		meaning.setDanci(str);
		meaning.ShowWindow(SW_SHOW);
	}
	else
	{
		CString content;
		content.Format(_T("含义中包含“%s”的单词如下：\n\n"),str.GetBuffer());
		danciEx* ptr=NULL;
		int i=0;
		while( (ptr=meaning.search(str.GetBuffer(),str.GetLength())) )
		{
			CString append;			
			append.Format(_T("%d. %s: %s\n"),++i,ptr->word,ptr->mean);
			content += append;
		}
		MessageBox(content);
	}
}

void CLearnDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	meaning.DestroyWindow();
	m_test.DestroyWindow();
	OnCancel();
}

void CLearnDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	meaning.saveFile();

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi,sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory (&si, sizeof (STARTUPINFO));     //初始化
	si.cb = sizeof (STARTUPINFO);
	si.wShowWindow=SW_SHOW;   
	si.dwFlags=STARTF_USESHOWWINDOW; 

	//注意
	wchar_t szCmdline[] = _T("write.exe danciEx.xls");

	if (::CreateProcess (NULL, szCmdline, NULL,
		NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
	}
}

void CLearnDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	CRect rt;
	meaning.GetWindowRect(&rt);
	ClientToScreen(&rt);
	meaning.MoveWindow(rt);

	m_test.GetWindowRect(&rt);
	ClientToScreen(&rt);
	m_test.MoveWindow(rt);

}

void CLearnDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	CDialog::OnTimer(nIDEvent);
}

void CLearnDlg::OnBnClickedTest()
{
	// TODO: 在此添加控件通知处理程序代码
	m_test.ShowWindow(SW_SHOW);
}
