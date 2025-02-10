//=============================================
//
//ボスのストラテジーパターン[boss_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BOSS_BEHAVIOR_
#define _BOSS_BEHAVIOR_
#include "enemy_behavior.h"
#include "boss_enemy.h"
#include "move_point.h"
#include "enemy_reaction_UI.h"

//=============================================
//前方宣言
//=============================================
class CBossEnemy;

//=============================================
//敵の徘徊のストラテジー
//=============================================
class CBossWandering
{
public:
	//止まってるフレーム数
	static const int STOP_FRAME = 30;
	CBossWandering();
	~CBossWandering();
	void Wandering(CBossEnemy* boss);
	void StopCnt();
	void PickNextMovePoint(CMovePoint* pMovePoint);
	void DrawDebug();
private:
	int m_MoveIdx; //移動先の番号
	int m_StopCnt; //止まってるカウント
	bool m_isMove; //動くかどうか
};

//=============================================
//敵の追従のストラテジー
//=============================================
class CBossChase
{
public:
	CBossChase();
	~CBossChase();
	void Chase(CBossEnemy* boss, CObject* obj);
	void MovetoPlayer(float distance, const float& threshold, D3DXVECTOR3& Vector, CBossEnemy* boss);
	void DrawDebug();
private:
	BOOL m_bTargetPlayer;
};

//=============================================
//敵のスタンのストラテジー
//=============================================
class CBossStan
{
public:
	CBossStan();
	~CBossStan();
	void Stan(CBossEnemy* boss);
};

//=============================================
//混乱のストラテジー
//=============================================
class CBossConfusion
{
public:
	CBossConfusion();
	~CBossConfusion();
	void Confusion(CBossEnemy* boss, float StartRot_y);
	void MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CBossEnemy* boss);
	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector,CBossEnemy* boss);
private:
	static constexpr float LOOK_RANGE = 1.6f; //見渡す範囲
	static constexpr int NUM_TURN = 2; //見渡す回数
	int m_TurnCnt; //何回見渡したか
	bool m_isRight; //見渡す(true:右 false:左)
};

//=============================================
//敵の銃の攻撃のストラテジー
//=============================================
class CBossGunAttack : public CEnemyGunAttack
{
public:
	CBossGunAttack();
	~CBossGunAttack() override;
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character) override;

private:
	static const int SHOT_STATE_FRAME = 90; //射撃フレーム

	int m_nStateChangeCnt;//ステート変更カウント
};

//=============================================
//突進攻撃のストラテジー
//=============================================
class CBossTackle
{
public:
	static const int TACKLE_DAMAGE = 30;

	CBossTackle();
	~CBossTackle();
	void Tackle(CBossEnemy* boss);

	void ColisionReset(CBossEnemy* boss);

	//ステイカウント取得
	int& GetStayCnt()
	{
		return m_TackleCnt;
	}

	//タックルカウント取得
	int& GetTackleCnt()
	{
		return m_TackleCnt;
	}


	//タックル状態取得
	bool& GetisTackle()
	{
		return m_isTackle;
	}

	//ステイカウント代入
	void SetStayCnt(int StayCnt)
	{
		m_StayCnt = StayCnt;
	}

	//タックルカウント代入
	void SetTackleCnt(int TackleCnt)
	{
		m_TackleCnt = TackleCnt;
	}

	//タックル状態代入
	void SetisTackle(bool isTackle)
	{
		m_isTackle = isTackle;
	}
private:
	static const int STAY_FLAME = 60; //突進までの待機時間
	static const int TACKLE_FLAME = 30; //タックル時間
	void LookAtPlayer(CCharacter* character); //プレイヤーのほうを向かせる処理
	int m_StayCnt;
	int m_TackleCnt;
	bool m_isTackle;
};

//=============================================
//探索のストラテジー
//=============================================
class CBossSearch
{
public:
	CBossSearch();
	~CBossSearch();
	void Search(CBossEnemy* boss,D3DXVECTOR3 TargetPos);
private:
};
#endif // !_ENEMY_BEHAVIOR_
