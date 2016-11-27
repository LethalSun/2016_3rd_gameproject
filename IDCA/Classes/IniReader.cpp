#include "pch.h"
#include "IniReader.h"
#include <iostream>
#include <Windows.h>


// 생성자에서 m_Filename을 0으로 초기화해주고, 입력받은 Filename을 멤버변수에 copy.
IniReader::IniReader(char* FileName)
{
	memset(m_Filename, 0x00, 255);
	memcpy(m_Filename, FileName, strlen(FileName));
}


int IniReader::ReadInteger(char* Section, char* Key, int IntDefaultValue)
{
	int iResult = GetPrivateProfileInt(Section, Key, IntDefaultValue, m_Filename);
	return iResult;
}


float IniReader::ReadFloat(char* Section, char* Key, float FloatDefaultValue)
{
	char Result[255];
	char Default[255];
	float FloatResult;

	sprintf(Default, "%f", FloatDefaultValue);
	GetPrivateProfileString(Section, Key, Default, Result, 255, m_Filename);
	FloatResult = atof(Result);
	return FloatResult;
}


bool IniReader::ReadBoolean(char* Section, char* Key, bool BoolDefaultValue)
{
	char Result[255];
	char Default[255];
	bool BoolResult;
	
	sprintf(Default, "%s", BoolDefaultValue ? "True" : "False");
	GetPrivateProfileString(Section, Key, Default, Result, 255, m_Filename);
	BoolResult = (strcmp(Result, "True") == 0 ||
		strcmp(Result, "true") == 0) ? true : false;
	return BoolResult;
}


char* IniReader::ReadString(char* Section, char* Key, const char* StringDefaultValue)
{
	char* Result = new char[255];
	memset(Result, 0x00, 255);
	GetPrivateProfileString(Section, Key,
		StringDefaultValue, Result, 255, m_Filename);
	return Result;
}