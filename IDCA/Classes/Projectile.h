#pragma once	

/*
	class Projectile
	����ü�� ����ϴ� �⺻ Ŭ����.
	�ۼ����� : 16.12.01
	�ۼ��� �̱ٿ�
	����ü Ŭ�������� ���� �ʿ��ұ�??
*/


class Projectile : public Node
{
public :
	Projectile();
	virtual ~Projectile() = 0;

private :
	Sprite* m_pSprite;
	int m_UnitVec[2];
};