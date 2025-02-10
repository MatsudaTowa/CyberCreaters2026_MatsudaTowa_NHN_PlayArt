//=============================================
//
//プレイヤーのステートパターン[player_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include "character.h"
#include "player.h"
#include "ult.h"

//=============================================
//前方宣言
//=============================================
class CPlayer;

//=============================================
//キャラクターのステートクラス
//=============================================
class CPlayerState
{
public:
	virtual void Default(CPlayer* player);
	virtual void Ult(CPlayer* player);
	virtual void Avoidance(CPlayer* player);
	virtual void Blown(CPlayer* player);
};

//=============================================
//キャラクターの通常状態
//=============================================
class CDefaultState : public CPlayerState
{
public:
	virtual void Default(CPlayer* player)override;
};

//=============================================
//キャラクターのウルト状態
//=============================================
class CUltState : public CPlayerState
{
public:
	virtual void Ult(CPlayer* player) override;
};

//=============================================
//キャラクターの回避状態
//=============================================
class CAvoidanceState : public CPlayerState
{
public:
	virtual void Avoidance(CPlayer* player) override;
};

//=============================================
//キャラクターの吹っ飛ばされ状態
//=============================================
class CBlownState : public CPlayerState
{
public:
	CBlownState();
	virtual void Blown(CPlayer* player) override;
private:
	int m_nStanCnt;
};

#endif // !_PLAYER_STATE_H
