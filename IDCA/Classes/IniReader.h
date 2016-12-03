#pragma once

/*
	Class IniReader
	�ۼ����� : 16.11.27 21:59
	�ۼ��� : �̱ٿ�
	Ŭ���� ���� : .ini���Ϸκ��� ������ �о���̴� Ŭ���� IniReader.

		�����ڿ��� Filename�� ȣ�����־�� �Ѵ�. (ex) "./Resources/Data/Config.ini"
		���� Filename�� Private����� ������ �ִٰ� �� �Լ��� ȣ��Ǹ� ���.
		�� ���� �Լ��� ���� int, float, String���� �дµ��� ����Ѵ�.
*/


class IniReader
{
public :

	IniReader(const char* m_Filename);


	int ReadInteger(const char* section, const char* Key, const int IntDefaultValue);
	float ReadFloat(const char* section, const char* Key, const float FloatDefaultValue);
	void ReadString(const char* section, const char* Key, const char* StringDefaultValue, char* destChar);


private :

	wchar_t m_wFilename[255];
	wchar_t m_wSectionText[255];
	wchar_t m_wKeyText[255];

	wchar_t m_wConvertHelper[255];
	char m_ConvertHelper[255];

	void TransSectionNKey(const char* section, const char* key);
	char* TempConvertWCharToChar(wchar_t* string);
	wchar_t* TempConvertCharToWChar(char* string);

};
