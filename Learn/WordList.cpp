#include "StdAfx.h"
#include "WordList.h"
#include <locale.h>

WordList::WordList(void)
: danciList(NULL)
, listSize(0)
, flag(0)
, searchPtr(NULL)
, danciListEx(NULL)
{
	FILE* listFile=NULL;
	if ( _wfopen_s(&listFile,_T("danciEx.dat"),_T("rb")) )
	{
		//MessageBox(_T("无法读取字典文件"));
		return;
	}

	danciEx* pre = NULL;
	danciEx* ptr = NULL;
	while( 1 )
	{
		pre = ptr;
		ptr = new danciEx;
		if( fread(ptr,1,sizeof(danciEx),listFile)!=sizeof(danciEx) )
		{
			delete ptr;
			break;
		}
		ptr->next = NULL;
		ptr->reserved = NULL;
		if( pre==NULL )
			danciListEx = ptr;
		else
			pre->next = ptr;
		listSize++;
	}
	
	fclose(listFile);

	_tsetlocale(LC_ALL,_T("chs"));
}

WordList::~WordList(void)
{
	saveFile();

	danci* ptr = danciList;
	while (ptr!=NULL)
	{
		danciList = ptr->next;
		delete ptr;
		ptr = danciList;
	}

	danciEx* ptrEx = danciListEx;
	while (ptrEx!=NULL)
	{
		danciListEx = ptrEx->next;
		delete ptrEx;
		ptrEx = danciListEx;
	}
}

int WordList::add(const wchar_t* word, const wchar_t* meaning)
{
	if ( danciListEx==NULL )
	{
		danciListEx=new danciEx;
		wcscpy_s(danciListEx->word,word);
		wcscpy_s(danciListEx->mean,meaning);
		danciListEx->times = 1;
		danciListEx->next = NULL;
		danciListEx->rank = 0;
		danciListEx->reserved = NULL;
		listSize++;
		flag = 1;
		return 0;
	}

	danciEx* ptr=danciListEx;
	danciEx* pre=danciListEx;

	while( ptr!=NULL )
	{
		if( wcscmp(ptr->word,word)<0 )
		{
			pre = ptr;
			ptr = ptr->next;
			continue;
		}

		if( wcscmp(ptr->word,word)==0 )
		{
			wcscpy_s(ptr->mean,meaning);
		}
		else
		{
			if ( ptr==danciListEx )
			{
				danciListEx=new danciEx;
				wcscpy_s(danciListEx->word,word);
				wcscpy_s(danciListEx->mean,meaning);
				danciListEx->times = 1;
				danciListEx->next = ptr;
				danciListEx->rank = 0;
				danciListEx->reserved = NULL;

			}
			else
			{
				pre->next=new danciEx;
				pre = pre->next;
				wcscpy_s(pre->word,word);
				wcscpy_s(pre->mean,meaning);
				pre->times = 1;
				pre->next = ptr;
				pre->rank = 0;
				pre->reserved = NULL;
			}
			listSize++;
		}
		flag = 1;
		return 0;
	}

	pre->next=new danciEx;
	pre = pre->next;
	wcscpy_s(pre->word,word);
	wcscpy_s(pre->mean,meaning);
	pre->times = 1;
	pre->next = NULL;
	pre->rank = 0;
	pre->reserved = NULL;

	listSize++;
	flag = 1;
	return 0;
}

danciEx* WordList::find(const wchar_t* word)
{
	danciEx* ptr=danciListEx;
	while( ptr!=NULL )
	{
		if( wcscmp(ptr->word,word)==0 )
		{
			ptr->times++;
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

int WordList::remove(const wchar_t* word)
{
	danciEx* ptr=danciListEx;
	danciEx* pre=danciListEx;

	while( ptr!=NULL )
	{
		if( wcscmp(ptr->word,word)==0 )
		{
			if( pre==danciListEx )
				danciListEx = ptr->next;
			else
				pre->next = ptr->next;
			delete ptr;
			listSize--;
			flag = 1;
			return 1;
		}
		pre = ptr;
		ptr = ptr->next;
	}

	return 0;
}

int WordList::getSize(void)
{
	return listSize;
}

int WordList::saveFile(void)
{
	if ( flag )
	{
		FILE* listFile=NULL;
		if ( _wfopen_s(&listFile,_T("danciEx.xls"),_T("w")) )
		{
			//MessageBox(_T("无法读取字典文件"));
			return 0;
		}

		danciEx* ptrEx = danciListEx;
		int i=0;

		if ( listFile )
		{
			fwprintf(listFile,_T("索引\t\t单词\t\t含义\t\t查询频率\t\t记忆难度\n"));
			while( ptrEx )
			{
				fwprintf(listFile,_T("%d\t\t%s\t\t%s\t\t%d\t\t%d\n"),++i,ptrEx->word,ptrEx->mean,ptrEx->times,ptrEx->rank);
				ptrEx = ptrEx->next;
			}
			fclose(listFile);
		}

		if ( _wfopen_s(&listFile,_T("danciEx.dat"),_T("wb")) )
		{
			//MessageBox(_T("无法读取字典文件"));
			return 0;
		}

		if( listFile )
		{
			ptrEx = danciListEx;
			while( ptrEx )
			{
				fwrite(ptrEx,sizeof(danciEx),1,listFile);
				ptrEx = ptrEx->next;
			}
			fclose(listFile);
		}

		flag = 0;
	}

	return 1;
}

danciEx* WordList::search(wchar_t* meaning, int lenth)
{
	danciEx* ptr;

	if( searchPtr==NULL )
		ptr = danciListEx;
	else
		ptr = searchPtr->next;

	while( ptr!=NULL )
	{
		int i=0,j=0;
		while( ptr->mean[i]!='\0' )
		{
			for( j=0;j<lenth;j++ )
			{
				if( ptr->mean[i+j]=='\0'||ptr->mean[i+j]!=meaning[j] )
				{
					break;
				}
			}
			if( j==lenth )
			{
				searchPtr = ptr;
				return ptr;
			}
			i++;
		}
		ptr = ptr->next;
	}

	searchPtr = NULL;
	return NULL;
}

int WordList::getLevel(void)
{
	int level=0;

	danciEx* ptr = danciListEx;
	while (ptr!=NULL)
	{
		if( level<ptr->rank )
			level = ptr->rank;
		ptr = ptr->next;
	}

	return level;
}

danciEx* WordList::search(int level, int index)
{
	danciEx* ptr = danciListEx;
	while (ptr)
	{
		if( ptr->rank==level )
			index--;
		if( index<0 )
			return ptr;
		ptr = ptr->next;
	}

	return ptr;
}

int WordList::getLevelNumber(int level)
{
	int number=0;

	danciEx* ptr = danciListEx;
	while (ptr!=NULL)
	{
		if( level==ptr->rank )
			number++;
		ptr = ptr->next;
	}

	return number;
}

int WordList::setFlag(void)
{
	flag = 1;
	return 0;
}