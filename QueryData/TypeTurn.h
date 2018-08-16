#pragma once  
#include"stdafx.h"
using namespace std;
class TypeTurn
{
public:
	static wstring UTF8ToUnicode(string str);
	static string UnicodeToUTF8(wstring str);

	static wstring TypeTurn::ANSIToUnicode(string str);
	static string TypeTurn::UnicodeToANSI(wstring str);
	static string TypeTurn::WideToMutilByte(const wstring& _src);
	static wstring TypeTurn::MutilByteToWide(const string& _src);
	static LPCWSTR TypeTurn::stringToLPCWSTR(string orig);
	static string TypeTurn::WChar2Ansi(LPCWSTR pwszSrc);
	static wchar_t* TypeTurn::multiByteToWideChar(const string pKey);
	static void TypeTurn::Wchar_tToString(std::string& szDst, const wchar_t *wchar);
	static wstring TypeTurn::s2ws(const std::string& s); 
	static vector<string> TypeTurn::splitStr(string str, char delimiter);
};
wstring TypeTurn::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
wstring TypeTurn::UTF8ToUnicode(const string str)
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t *  pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	wstring  rt;
	rt = (wchar_t*)pUnicode;
	delete  pUnicode;

	return  rt;
}

string TypeTurn::UnicodeToUTF8(wstring str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_UTF8,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

wstring TypeTurn::ANSIToUnicode(string str)
{
	int len = 0;
	len = str.length();
	int unicodeLen = ::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t * pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	wstring rt;
	rt = (wchar_t*)pUnicode;
	delete pUnicode;
	return rt;
}


string TypeTurn::UnicodeToANSI(wstring str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}
string TypeTurn::WideToMutilByte(const wstring& _src)
{
	int nBufSize = WideCharToMultiByte(GetACP(), 0, _src.c_str(), -1, NULL, 0, 0, FALSE);
	char *szBuf = new char[nBufSize];
	WideCharToMultiByte(GetACP(), 0, _src.c_str(), -1, szBuf, nBufSize, 0, FALSE);
	string strRet(szBuf);
	delete[]szBuf;
	szBuf = NULL;
	return strRet;
}
wstring TypeTurn::MutilByteToWide(const string& _src)
{
	//计算字符串 string 转成 wchar_t 之后占用的内存字节数
	int nBufSize = MultiByteToWideChar(GetACP(), 0, _src.c_str(), -1, NULL, 0);
	//为 wsbuf 分配内存 BufSize 个字节
	wchar_t *wsBuf = new wchar_t[nBufSize];
	//转化为 unicode 的 WideString
	MultiByteToWideChar(GetACP(), 0, _src.c_str(), -1, wsBuf, nBufSize);
	wstring wstrRet(wsBuf);
	delete[]wsBuf;
	wsBuf = NULL;
	return wstrRet;
}
LPCWSTR TypeTurn::stringToLPCWSTR(string orig)
{

	size_t size = orig.length();
	wchar_t *buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, orig.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = 0;  //确保以 '\0' 结尾 
	return buffer;
}
string TypeTurn::WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);

	if (nLen <= 0) return std::string("");

	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;

	std::string strTemp(pszDst);
	delete[] pszDst;

	return strTemp;
}
wchar_t* TypeTurn::multiByteToWideChar(const string str)
{
	std::string temp = str;
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, NULL, 0);
	wchar_t * wszUtf8 = new wchar_t[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, (LPWSTR)wszUtf8, len);
	std::wstring r = wszUtf8;
	return wszUtf8;
}
void TypeTurn::Wchar_tToString(std::string& szDst, const wchar_t *wchar)
{
	const wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
	char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
}
vector<string> TypeTurn::splitStr(string str, char delimiter) {
	vector<string> r;
	string tmpstr;
	while (!str.empty()) {
		int ind = str.find_first_of(delimiter);
		if (ind == -1) {
			r.push_back(str);
			str.clear();
		}
		else {
			r.push_back(str.substr(0, ind));
			str = str.substr(ind + 1, str.size() - ind - 1);
		}
	}
	return r;
}