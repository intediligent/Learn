#pragma once

typedef struct danci 
{
	wchar_t word[32];
	wchar_t mean[256];
	int times;
	danci* next;
}danci;

typedef struct danciEx
{
	wchar_t word[32];
	wchar_t mean[256];
	int times;
	int rank;
	void * reserved;
	danciEx* next;
}danciEx;


class WordList
{
public:
	WordList(void);
public:
	~WordList(void);
protected:
	danci* danciList;
public:
	int add(const wchar_t* word, const wchar_t* meaning);
public:
	danciEx* find(const wchar_t* word);
public:
	int remove(const wchar_t* word);
protected:
	int listSize;
	int flag;
	danciEx* searchPtr;
public:
	int getSize(void);
public:
	int saveFile(void);
public:
	danciEx* search(wchar_t* meaning, int lenth);
public:
	int getLevel(void);
public:
	danciEx* search(int level, int index);
public:
	int getLevelNumber(int level);
	int setFlag(void);
protected:
	danciEx* danciListEx;
};
