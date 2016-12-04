
/*
	Config
	IniReader�� �о�� File�� ��Ʈ�� ���ο� ������, �׸� �̿��Ͽ� .ini���Ϸκ��� �����͸� �о���̴� Ŭ����.
	�о���� �����ʹ� Section���� �������� �ְ�, get~�Լ��� �̿��Ͽ� ������ �� �ִ�.
*/

class IniReader;

class Config
{
public :
	static Config* getInstance();
	void deleteInstance();

	Config();

	/* Member Functions */
	void SetData();
	char* readStringHelper(const char*, const char*, const char*);

private :

	static Config* _instance;
	IniReader* iniReader;
	const char* iniFileRoute = "..\\Resources\\Data\\Spec.ini";
	char* m_pReadHelper;
	

	/* Section Static */
	CC_SYNTHESIZE(float, m_WinSizeWidth, WinSizeWidth);
	CC_SYNTHESIZE(float, m_WinSizeHeight, WinSizeHeight);


	/* Section Player */
	CC_SYNTHESIZE(char*, m_pPlayerPlistFileName, PlayerPlistFileName);
	CC_SYNTHESIZE(char*, m_pPlayerWarriorFileName, PlayerWarriorFileName);
	CC_SYNTHESIZE(char*, m_pPlayerSpriteFrameFileExtention, PlayerSpriteFrameFileExtention);


	/* Section Map */
	CC_SYNTHESIZE(char*, m_pMapName1, MapName1);

	
	/* Section ENEMY_CHOCO */
	CC_SYNTHESIZE(char*, m_pChocoPlistFileName, ChocoPlistFileName);
	CC_SYNTHESIZE(char*, m_pChocoSpriteFileName, ChocoSpriteFileName);
	CC_SYNTHESIZE(char*, m_pChocoFrameFileExtention, ChocoFrameFileExtention);

	CC_SYNTHESIZE(float, m_ChocoSearchingRange, ChocoSearchingRange);
	CC_SYNTHESIZE(float, m_ChocoChasingRange, ChocoChasingRange);
	CC_SYNTHESIZE(float, m_ChocoAttackRange, ChocoAttackRange);
	CC_SYNTHESIZE(float, m_ChocoMoveSpeed, ChocoMoveSpeed);

};