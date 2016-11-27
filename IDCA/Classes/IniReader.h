#pragma once

/*
	Class IniReader
	작성일자 : 16.11.27 21:59
	작성자 : 이근원
	클래스 설명 : .ini파일로부터 정보를 읽어들이는 클래스 IniReader.

		생성자에서 Filename을 호출해주어야 한다. (ex) "./Resources/Data/Config.ini"
		받은 Filename을 Private멤버로 가지고 있다가 각 함수가 호출되면 사용.
		그 외의 함수는 각각 int, float, bool, String값을 읽는데에 사용한다.
*/



// .ini 파일로부터 정보를 읽어들이는 클래스 IniReader.

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
