// Meaning.cpp : 实现文件
//

#include "stdafx.h"
#include "Learn.h"
#include "Meaning.h"


// CMeaning 对话框

IMPLEMENT_DYNAMIC(CMeaning, CDialog)

CMeaning::CMeaning(CWnd* pParent /*=NULL*/)
	: CDialog(CMeaning::IDD, pParent)
	, m_danci(_T(""))
	, m_word(NULL)
{

}

CMeaning::~CMeaning()
{
}

void CMeaning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, meaning_edit);
}


BEGIN_MESSAGE_MAP(CMeaning, CDialog)
	ON_BN_CLICKED(IDOK3, &CMeaning::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK, &CMeaning::OnBnClickedOk)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK4, &CMeaning::OnBnClickedOk4)
END_MESSAGE_MAP()


// CMeaning 消息处理程序

void CMeaning::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString meaning;
	meaning_edit.GetWindowText(meaning);
	if ( meaning.GetLength()==0 )
	{
		MessageBox(_T("请输入含义"));
	}
	else if( m_wordList.add(m_danci,meaning)==0 )
	{
		MessageBox(_T("词条添加成功"));
		GetParent()->Invalidate(TRUE);
		OnOK();
	}
}

int CMeaning::setDanci(CString danci)
{
	m_danci = danci;
	return 0;
}

void CMeaning::OnBnClickedOk3()
{
	// TODO: 在此添加控件通知处理程序代码
	// 删除
	if( m_word )
	{
		if ( m_wordList.remove(m_danci.GetBuffer()) )
		{
			MessageBox(_T("词条删除成功"));
			GetParent()->Invalidate(TRUE);
			OnOK();
		}
	}
	else
		MessageBox(_T("没有这个词条"));
}

void CMeaning::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	m_word = m_wordList.find(m_danci.GetBuffer());
	CString str;
	int lenght=0;

	if( m_word )
	{
		str.Format(_T("你真逊，%s 已经被查询过 %d 次了"), m_danci, m_word->times);
		SetDlgItemText(IDC_STATIC,str);
		meaning_edit.SetWindowText(m_word->mean);
		lenght = (int)wcslen(m_word->mean);
	}
	else
	{
		str.Format(_T("恭喜你，%s 是个新单词，请输入单词含义："), m_danci);
		SetDlgItemText(IDC_STATIC,str);
		meaning_edit.SetWindowText(_T(""));
	}
	//GetDlgItem(IDOK)->SetFocus();
	meaning_edit.SetSel(lenght,lenght);
	meaning_edit.SetFocus();
}

int CMeaning::getSize(void)
{
	return m_wordList.getSize();
}

int CMeaning::saveFile(void)
{
	return m_wordList.saveFile();
}

danciEx* CMeaning::search(wchar_t* mean, int lenth)
{
	return m_wordList.search(mean,lenth);
}

void CMeaning::OnBnClickedOk4()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->Invalidate(TRUE);
	OnOK();
}

WordList* CMeaning::getWordList(void)
{
	return &m_wordList;
}
