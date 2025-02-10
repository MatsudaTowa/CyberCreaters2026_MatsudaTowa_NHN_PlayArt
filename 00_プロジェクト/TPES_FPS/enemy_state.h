////=============================================
////
////ボスのステートパターン[boss_state.h]
////Auther Matsuda Towa
////
////=============================================
//#ifndef _ENEMY_STATE_H_
//#define _ENEMY_STATE_H_
//
//#include "character_state.h"
//#include "enemy.h"
//
////=============================================
////前方宣言
////=============================================
//class CEnemy;
//
////=============================================
////ボスのステートクラス TODO:キャラクターのステートを継承して
////=============================================
//class CEnemyState
//{
//public:
//	virtual void Start(CEnemy* enemy);
//	virtual void Chase(CEnemy* enemy);
//	virtual void Stan(CEnemy* enemy);
//	virtual void Wandering(CEnemy* enemy);
//	virtual void Confusion(CEnemy* enemy);
//	virtual void Tackle(CEnemy* enemy);
//	virtual void DrawDebug();
//};
//
////=============================================
////エネミーの追跡状態
////=============================================
//class CChaseState : public CEnemyState
//{
//public:
//	CChaseState();
//	~CChaseState();
//	virtual void Chase(CEnemy* enemy)override;
//	virtual void DrawDebug()override;
//private:
//	static const int HP_LOW = 30;
//	static const int PLAY_TACKLE_FLAME = 300; //タックルを実行するまでのフレーム
//	int m_PlayTackleCnt; //タックルまでの計測用
//};
//
////=============================================
////エネミーのスタン状態
////=============================================
//class CBossStanState :public CEnemyState
//{
//public:
//	void Start(CEnemy* enemy) override;
//	virtual void Stan(CEnemy* enemy);
//	virtual void DrawDebug()override;
//private:
//	static constexpr int STAN_FRAME = 600; //スタン時間
//	int m_StanCnt; //スタン計測カウント
//};
//
////=============================================
////エネミーの徘徊状態
////=============================================
//class CWanderingState : public CEnemyState
//{
//public:
//	virtual void Wandering(CEnemy* enemy)override;
//	virtual void DrawDebug()override;
//};
//
////=============================================
////エネミーの混乱状態
////=============================================
//class CConfusionBossState : public CEnemyState
//{
//public:
//	void Start(CEnemy* enemy) override;
//	virtual void Confusion(CEnemy* enemy)override;
//	virtual void DrawDebug()override;
//private:
//	float m_StartRot;
//	bool m_isRight; //見渡す(true:右 false:左)
//};
//
////=============================================
////エネミーのタックル状態
////=============================================
//class CTackleState : public CEnemyState
//{
//public:
//	void Start(CEnemy* enemy) override;
//	virtual void Tackle(CEnemy* enemy)override;
//	virtual void DrawDebug()override;
//};
//#endif