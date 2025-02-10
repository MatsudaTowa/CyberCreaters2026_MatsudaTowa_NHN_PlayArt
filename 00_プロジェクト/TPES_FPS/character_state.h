//=============================================
//
//キャラクターのステートパターン[character_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_STATE_H_
#define _CHARACTER_STATE_H_

#include "character.h"

//=============================================
//前方宣言
//=============================================
class CCharacter;

//=============================================
//キャラクターのステートクラス
//=============================================
class CCharacterState
{
public:
	virtual void Start(CCharacter* character);
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character); 
	virtual void Stan(CCharacter* character);
	virtual void Confusion(CCharacter* character);
	virtual void Move(CCharacter* character);
};

//=============================================
//キャラクターの撃ってる状態
//=============================================
class CShotState : public CCharacterState
{
public:
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)override;
};

//=============================================
//キャラクターのスタン状態
//=============================================
class CStanState : public CCharacterState
{
public:
	void Start(CCharacter* character) override;
	virtual void Stan(CCharacter* character)override;
private:
	int m_StanCnt; //スタン計測カウント
};

//=============================================
//キャラクターの混乱状態
//=============================================
class CConfusionState : public CCharacterState
{
public:
	void Start(CCharacter* character) override;
	virtual void Confusion(CCharacter* character)override;
private:
	float m_StartRot;
	bool m_isRight; //見渡す(true:右 false:左)
};

//=============================================
//キャラクターの動いてる状態
//=============================================
class CMoveState : public CCharacterState
{
public:
	virtual void Move(CCharacter* character)override;
};

#endif // !_CHARACTER_STATE_H
