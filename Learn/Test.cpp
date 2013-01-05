// Test.cpp : 实现文件
//

#include "stdafx.h"
#include "Learn.h"
#include "Test.h"


// CTest 对话框

IMPLEMENT_DYNAMIC(CTest, CDialog)

CTest::CTest(CWnd* pParent /*=NULL*/)
	: CDialog(CTest::IDD, pParent)
	, m_currWord(NULL)
	, m_wl(NULL)
	, m_wordMap(NULL)
	, m_levelSize(NULL)
	, m_level(-1)
{
	srand( (UINT)time(NULL) );
}

CTest::~CTest()
{
}

void CTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTest, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CTest::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CTest::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Right, &CTest::OnBnClickedRight)
	ON_BN_CLICKED(IDC_WRONG, &CTest::OnBnClickedWrong)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CTest 消息处理程序

void CTest::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if( m_wordMap )
	{
		for( int i=0;i<=m_level;i++)
		{
			if( m_wordMap[i] )
				delete m_wordMap[i];
		}
		delete m_wordMap;
	}

	if( m_levelSize )
		delete m_levelSize;

	OnCancel();
}

void CTest::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if( m_currWord )
	{
		GetDlgItem(IDC_WORD3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MEAN)->SetWindowText(m_currWord->mean);
	}
	//OnOK();
}

void CTest::OnBnClickedRight()
{
	// TODO: 在此添加控件通知处理程序代码
	if( m_currWord->rank>0 )
	{
		m_currWord->rank--;
		m_wl->setFlag();
	}

	m_currWord = generateWord();

	GetDlgItem(IDC_WORD3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_MEAN)->SetWindowText(_T(""));
	GetDlgItem(IDC_WORD)->SetWindowText(m_currWord?m_currWord->word:_T("All Word Tested!"));
}

void CTest::OnBnClickedWrong()
{
	// TODO: 在此添加控件通知处理程序代码
	m_currWord->rank++;
	m_wl->setFlag();

	m_currWord = generateWord();

	GetDlgItem(IDC_WORD3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_MEAN)->SetWindowText(_T(""));
	GetDlgItem(IDC_WORD)->SetWindowText(m_currWord?m_currWord->word:_T("All Word Tested!"));
}

void CTest::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if ( m_wl )
	{
		m_level = m_wl->getLevel();
		m_levelSize = new int[m_level+1];
		m_wordMap = new bool*[m_level+1];
		for( int i=0;i<=m_level;i++)
		{
			int num = m_wl->getLevelNumber(i);
			m_levelSize[i] = num;
			if( num>0 )
			{
				m_wordMap[i] = new bool[num];
				memset(m_wordMap[i],0,num);
			}
			else
				m_wordMap[i] = NULL;
		}
	}

	m_currWord = generateWord();

	GetDlgItem(IDC_WORD3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_MEAN)->SetWindowText(_T(""));
	GetDlgItem(IDC_WORD)->SetWindowText(m_currWord?m_currWord->word:_T("No Test Word!"));

}

int CTest::setWordList(WordList * wordList)
{
	m_wl = wordList;
	return 0;
}

danciEx* CTest::generateWord(void)
{
	int level = getLevel();

	if ( level==-1 )
	{
		return NULL;
	}

	int idx = rand()%m_levelSize[level];

	while ( m_wordMap[level][idx] )
	{
		idx = rand()%m_levelSize[level];
	}

	danciEx* ptr;
	ptr = m_wl->search(level,idx);
	m_wordMap[level][idx] = TRUE;

	return ptr;
}

int CTest::getLevel(void)
{
	for( int level=m_level;level>=0;level-- )
	for( int num=0;num<m_levelSize[level];num++ )
	{
		if( m_wordMap[level][num]==FALSE )
			return level;
	}
	return -1;
}
