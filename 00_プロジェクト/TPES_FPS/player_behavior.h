//=============================================
//
//プレイヤーのストラテジーパターン[player_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_BEHAVIOR_
#define _PLAYER_BEHAVIOR_
#include "character_behavior.h"
#include "player.h"

class CPlayer;
//=============================================
//プレイヤーの移動のストラテジー
//=============================================
class CPlayerMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数

	CPlayerMove();
	~CPlayerMove() override;
	void Move(CCharacter* character)override;
};

//=============================================
//プレイヤーの移動のストラテジー
//=============================================
class CPlayerSliding
{
public:
	CPlayerSliding();
	~CPlayerSliding();
	void Sliding(CPlayer* player);
};


//=============================================
//プレイヤーの攻撃のストラテジー
//=============================================
class CPlayerAttack : public CGunAttack
{
public:
	CPlayerAttack();
	~CPlayerAttack() override;
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
private:
	void ShotBullet(CCharacter* character, CCamera* pCamera, const CBullet::BULLET_ALLEGIANCE& Allegiance, const CBullet::BULLET_TYPE& type);
};

class CPlayerAvoidance
{
public:
	CPlayerAvoidance();
	~CPlayerAvoidance();
	void Avoidance(CCharacter* character);
};
#endif // !_ENEMY_BEHAVIOR_
