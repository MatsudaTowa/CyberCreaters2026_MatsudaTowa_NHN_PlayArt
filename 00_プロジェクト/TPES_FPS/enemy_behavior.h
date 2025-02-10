//=============================================
//
//エネミーのストラテジーパターン[enemy_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_BEHAVIOR_
#define _ENEMY_BEHAVIOR_
#include "character_behavior.h"
#include "enemy.h"
#include "enemy_reaction_UI.h"

//=============================================
//敵の移動のストラテジー
//=============================================
class CEnemyMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数

	CEnemyMove();
	~CEnemyMove() override;
	void Move(CCharacter* character)override;
	void SetMoveVec(D3DXVECTOR3 move_vec)
	{
		m_move_vec = move_vec;
	}
private:
	D3DXVECTOR3 m_move_vec;
};

//=============================================
//敵のスタンのストラテジー
//=============================================
class CEnemyStan : public CStan
{
public:
	CEnemyStan();
	~CEnemyStan() override;
	void Stan(CCharacter* character)override;
private:
};

//=============================================
//敵の混乱のストラテジー
//=============================================
class CEnemyConfusion : public CConfusion
{
public:
	CEnemyConfusion();
	~CEnemyConfusion() override;
	void Confusion(CCharacter* character, float StartRot_y)override;
	void MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CCharacter* character);
	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character);
private:
	static constexpr float LOOK_RANGE = 1.57f; //見渡す範囲
	static constexpr int NUM_TURN = 2; //見渡す回数

	CEnemy_Reaction_UI* m_pReaction;
	int m_TurnCnt; //何回見渡したか
	bool m_isRight; //見渡す(true:右 false:左)
};

//=============================================
//敵の攻撃のストラテジー
//=============================================
class CEnemyGunAttack : public CGunAttack
{
public:
	CEnemyGunAttack();
	~CEnemyGunAttack() override;
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;
	void LookAtPlayer(CCharacter* character); //プレイヤーのほうを向かせる処理

private:
};
#endif // !_ENEMY_BEHAVIOR_
