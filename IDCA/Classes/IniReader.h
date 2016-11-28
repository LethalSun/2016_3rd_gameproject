//#pragma once
//
///*
//	Class IniReader
//	�ۼ����� : 16.11.27 21:59
//	�ۼ��� : �̱ٿ�
//	Ŭ���� ���� : .ini���Ϸκ��� ������ �о���̴� Ŭ���� IniReader.
//
//		�����ڿ��� Filename�� ȣ�����־�� �Ѵ�. (ex) "./Resources/Data/Config.ini"
//		���� Filename�� Private����� ������ �ִٰ� �� �Լ��� ȣ��Ǹ� ���.
//		�� ���� �Լ��� ���� int, float, bool, String���� �дµ��� ����Ѵ�.
//*/
//
//
//class IniReader
//{
//public :
//
//	IniReader(char* m_Filename);
//
//	int ReadInteger(const char* section, const char* Key, const int IntDefaultValue);
//	float ReadFloat(const char* section, const char* Key, const float FloatDefaultValue);
//	bool ReadBoolean(const char* section, const char* Key, const bool BoolDefaultValue);
//	char* ReadString(const char* section, const char* Key, const char* StringDefaultValue);
//
//
//private :
//
//	char m_Filename[255];
//
//};
//