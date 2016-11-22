#include "json/json.h"

class Config : public Component
{
public :
	CREATE_FUNC(Config);
	virtual bool init();


	/* Get, Set Functions */
	void setPlayerPlist(char*);
	void setPlayerInitialSprite(char*);
	char* getPlayerPlist();
	char* getPlayerInitialSprite();
	

	/* Member Functions */
	bool ReadFromFile(const char, char, int);


	/* Membar Variable */
	const int m_BufferSize = 1024;


private :
	enum Button
	{
		LeftStickX,
		LeftStickY
	};

	char* m_pPlayerPlist;
	char* m_pPlayerInitialSprite;

	CC_SYNTHESIZE(float, m_PlayerMoveSpeed, PlayerMoveSpeed);

};