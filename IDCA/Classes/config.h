
class Config
{
public :

	void init();

	/* Get, Set Functions */
	void setPlayerPlist(char*);
	void setPlayerInitialSprite(char*);
	char* getPlayerPlist();
	char* getPlayerInitialSprite();


private :
	enum Button
	{
		LeftStickX,
		LeftStickY
	};

	char* m_pPlayerPlist;
	char* m_pPlayerInitialSprite;

	CC_SYNTHESIZE(float, m_PlayerMoveSpeed, PlayerMoveSpeed);
	CC_SYNTHESIZE(Vec2, m_);

};