#pragma once

/*
	Class IniReader
	�ۼ����� : 16.11.27 21:59
	�ۼ��� : �̱ٿ�
	Ŭ���� ���� : .ini���Ϸκ��� ������ �о���̴� Ŭ���� IniReader.

		�����ڿ��� Filename�� ȣ�����־�� �Ѵ�. (ex) "./Resources/Data/Config.ini"
		���� Filename�� Private����� ������ �ִٰ� �� �Լ��� ȣ��Ǹ� ���.
		�� ���� �Լ��� ���� int, float, bool, String���� �дµ��� ����Ѵ�.
*/



// .ini ���Ϸκ��� ������ �о���̴� Ŭ���� IniReader.

class IniReader
{
public :

	IniReader(char* m_Filename);

	int ReadInteger(char* Section, char* Key, int IntDefaultValue);
	float ReadFloat(char* Section, char* Key, float FloatDefaultValue);
	bool ReadBoolean(char* Section, char* Key, bool BoolDefaultValue);
	char* ReadString(char* Section, char* Key, const char* StringDefaultValue);


private :

	char m_Filename[255];

};
