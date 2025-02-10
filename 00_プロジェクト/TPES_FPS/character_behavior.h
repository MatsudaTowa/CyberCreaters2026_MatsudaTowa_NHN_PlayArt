//=============================================
//
//キャラクターのストラテジーパターン[character_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_BEHAVIOR_H_ //これが定義されてないとき

#define _CHARACTER_BEHAVIOR_H_
#include "main.h"
#include "manager.h"
#include "character.h"

//=============================================
//前方宣言
//=============================================
class CCharacter;

//=============================================
//移動ストラテジー
//=============================================
class CMove
{
public:
	CMove();
	virtual ~CMove();
	virtual void Move(CCharacter*character) = 0;
protected:
};

//=============================================
//混乱のストラテジー
//=============================================
class CStan
{
public:
	CStan();
	virtual ~CStan();
	virtual void Stan(CCharacter* character);
private:
};

//=============================================
//混乱のストラテジー
//=============================================
class CConfusion
{
public:
	CConfusion();
	virtual ~CConfusion();
	virtual void Confusion(CCharacter* character, float StartRot_y);
private:
};

//=============================================
//攻撃ストラテジー
//=============================================
class CGunAttack
{
public:
	CGunAttack();
	virtual ~CGunAttack();
	virtual void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CCharacter* character) = 0;
};
#endif
