#include "pch.h"
#include "IniReader.h"
#include "string"
#include <iostream>
#include <windows.h>
#include <stdlib.h>

const int BUFFER_MAX = 255;

// �����ڿ��� m_Filename�� 0���� �ʱ�ȭ���ְ�, �Է¹��� Filename�� ��������� copy.
IniReader::IniReader(const char* inputFileName)
{
	char FileName[BUFFER_MAX];
	strcpy(FileName, inputFileName);

	memset(m_wFilename, 0, BUFFER_MAX);
	memset(m_wSectionText, 0, BUFFER_MAX);
	memset(m_wKeyText, 0, BUFFER_MAX);
	memset(m_wConvertHelper, 0, BUFFER_MAX);
	memset(m_ConvertHelper, 0, BUFFER_MAX);
	wcscpy(m_wFilename, TempConvertCharToWChar(FileName));
}


void IniReader::TransSectionNKey(const char* section, const char* key)
{
	mbstowcs(m_wSectionText, section, strlen(section) + 1);
	mbstowcs(m_wKeyText, key, strlen(key) + 1);
}


int IniReader::ReadInteger(const char* section, const char* key, const int intDefaultValue)
{
	TransSectionNKey(section, key);

	int iResult = GetPrivateProfileInt(m_wSectionText, m_wKeyText, intDefaultValue, m_wFilename);
	return iResult;
}


float IniReader::ReadFloat(const char* section, const char* key, const float floatDefaultValue)
{
	wchar_t result[BUFFER_MAX] = { 0 };
	wchar_t default[BUFFER_MAX] = { 0 };
	char resultInChar[BUFFER_MAX] = { 0 };
	char defaultInChar[BUFFER_MAX] = { 0 };
	float floatResult = 0.f;

	TransSectionNKey(section, key);

	sprintf(defaultInChar, "%f", floatDefaultValue);
	mbstowcs(default, defaultInChar, strlen(defaultInChar) + 1);

	GetPrivateProfileString(m_wSectionText, m_wKeyText, default, result, BUFFER_MAX, m_wFilename);
	floatResult = atof(TempConvertWCharToChar(result));
	return floatResult;
}


void IniReader::ReadString(const char* section, const char* key, const char* stringDefaultValue, char* destChar)
{
	// TODO :: ���ڷ� �޾Ƽ� CHAR�� �Ѱ��ְų�, ��ȯ���� stl::String�� ����ϴ���.
	// Memory Leak ����.
	wchar_t defaultValue[BUFFER_MAX];
	wchar_t resultValue[BUFFER_MAX];

	TransSectionNKey(section, key);
	//memset(destChar, 0x00, BUFFER_MAX);
	mbstowcs(defaultValue, stringDefaultValue, strlen(stringDefaultValue) + 1);

	GetPrivateProfileString(m_wSectionText, m_wKeyText, defaultValue, resultValue, BUFFER_MAX, m_wFilename);
	strcpy(destChar, TempConvertWCharToChar(resultValue));
	return;
}


wchar_t* IniReader::TempConvertCharToWChar(char* string)
{
	mbstowcs(m_wConvertHelper, string, strlen(string) + 1);
	return m_wConvertHelper;
}


char* IniReader::TempConvertWCharToChar(wchar_t* string)
{
	wcstombs(m_ConvertHelper, string, wcslen(string) + 1);
	return m_ConvertHelper;
}