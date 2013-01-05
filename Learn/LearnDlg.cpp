// LearnDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Learn.h"
#include "LearnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLearnDlg �Ի���




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


// CLearnDlg ��Ϣ�������

BOOL CLearnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	meaning.Create(IDD_MEANING,this);
	m_test.Create(IDD_TEST,this);
	m_test.setWordList(meaning.getWordList());


//	SetTimer(1,1000,NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLearnDlg::OnPaint()
{
	CString str;
	str.Format(_T("Ŀǰ����¼ %d ������"),meaning.getSize() );
	SetDlgItemText(IDC_INFO,str);
	word_edit.SetWindowText(_T(""));
	//word_edit.SetSel(0,0);
	word_edit.SetFocus();

	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CLearnDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLearnDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	word_edit.GetWindowText(str);
	
	if(str.GetLength()==0)
		MessageBox(_T("������һ������"));
	else if( ((*(str.GetBuffer())) & 0xF000) == 0 )
	{
		meaning.setDanci(str);
		meaning.ShowWindow(SW_SHOW);
	}
	else
	{
		CString content;
		content.Format(_T("�����а�����%s���ĵ������£�\n\n"),str.GetBuffer());
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	meaning.DestroyWindow();
	m_test.DestroyWindow();
	OnCancel();
}

void CLearnDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	meaning.saveFile();

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi,sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory (&si, sizeof (STARTUPINFO));     //��ʼ��
	si.cb = sizeof (STARTUPINFO);
	si.wShowWindow=SW_SHOW;   
	si.dwFlags=STARTF_USESHOWWINDOW; 

	//ע��
	wchar_t szCmdline[] = _T("write.exe danciEx.xls");

	if (::CreateProcess (NULL, szCmdline, NULL,
		NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
	}
}

void CLearnDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	CDialog::OnTimer(nIDEvent);
}

void CLearnDlg::OnBnClickedTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_test.ShowWindow(SW_SHOW);
}
