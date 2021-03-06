
// QueryDataDlg.h: 头文件
//

#pragma once

#include <sstream>
#include <string>

char * Cstring2char(CString str);

// CQueryDataDlg 对话框
class CQueryDataDlg : public CDialogEx
{
// 构造
public:
	CQueryDataDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QUERYDATA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CMenu   m_Menu;
	CString m_Name;
	CString m_Password;
	std::string token;
	int area;
	int type;

	int totalData;
	std::string DataFromUrl;  //需要解析的数据

	std::vector<std::string> vectoehead;
	std::vector<std::wstring> wvectoehead;
	std::vector<std::vector<std::wstring>> vectordata;
	unsigned int querynum;
	char* urlForUser;
	char* urlForData;


	CString m_Sn;
	COleDateTime m_starttime;
	COleDateTime m_endTime;
	CString m_strstarttime;
	CString m_strendtime;
	HANDLE  m_hThread = nullptr;

	wchar_t strExeFileDir[MAX_PATH_LEN];
	wchar_t strLanguageSettingPath[MAX_PATH_LEN];
	wchar_t strLanguagePath[MAX_PATH_LEN];

private:
	CComboBox m_cobNum;
	CListCtrl m_listdata;
	//wstring m_szLang
	WCHAR m_szLang[100] = { 0 };
	//LPTSTR   m_szLang;

	std::wstring messageW;
	std::wstring messageD;



public:
	int CQueryDataDlg::postUserInfo();
	int CQueryDataDlg::postFordata();

	void ChangeMainPageLanguage();



// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuery();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnConfigUseraccount();
	afx_msg void OnDtnDatetimechangeDatetimepickerStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerStart2(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnLvnGetdispinfoListRespot(NMHDR *pNMHDR, LRESULT *pResult);

	/// <summary>
	///		执行线程函数
	/// </summary>
	/// <param name = "lpParam">
	///		执行线程参数
	/// </param>
	static DWORD WINAPI ThreadProc(LPVOID lpParam)
	{
		CQueryDataDlg * pDlg = (CQueryDataDlg *)lpParam;
		return pDlg->StartQuery();
	}

	/// <summary>
	///		查询
	/// </summary>
	DWORD   StartQuery();

public:
	UINT32 GetModuleFileDirectory(wchar_t* wBuf, UINT32 sizeInWord)
	{
		UINT32 nLen = ::GetModuleFileName(NULL, wBuf, sizeInWord);

		if (0 == nLen)
		{
			return 0;
		}

		for (; wBuf[--nLen] != L'\\'; )
		{
			wBuf[nLen] = 0;
		}

		wBuf[nLen] = 0;

		return nLen;
	}

	BOOL isFileExist(const std::wstring& wstrFilePath)
	{
		HANDLE hFile = INVALID_HANDLE_VALUE;

		if (INVALID_HANDLE_VALUE == (hFile = CreateFile(wstrFilePath.c_str(), 0, 0, NULL, OPEN_EXISTING, 0, NULL)))
		{
			return FALSE;
		}

		CloseHandle(hFile);
		return TRUE;
	}

	void catFilePath(wchar_t* pFilePath, const wchar_t* pFileDirectory, const wchar_t* pFileName)
	{
		//获取模板文件名称
		wcscpy_s(pFilePath, MAX_PATH_LEN, pFileDirectory);
		wcscat_s(pFilePath, MAX_PATH_LEN, L"\\");
		wcscat_s(pFilePath, MAX_PATH_LEN, pFileName);
	}

	//DWORD GetPrivateProfileString(
	//	LPCTSTR lpAppName,
	//	LPCTSTR lpKeyName,
	//	LPCTSTR lpDefault,
	//	LPTSTR  lpReturnedString,
	//	DWORD   nSize,
	//	LPCTSTR lpFileName
	//	);

	CString My_LoadString(CString szID)
	{
		CString szValue;
		DWORD dwSize = 1000;
		GetPrivateProfileString(L"String", szID, L"Not found", szValue.GetBuffer(dwSize), dwSize, strLanguagePath);
		szValue.ReleaseBuffer();
		szValue.Replace(L"\\n", L"\n");	//替换回换行符号

		return szValue;
	}

	void LoadLanguage(LPCTSTR szLangSel = L"");//加载语言项
	afx_msg void OnBnClickedButtoEnglish();
	afx_msg void OnBnClickedButtonChinese();
};
