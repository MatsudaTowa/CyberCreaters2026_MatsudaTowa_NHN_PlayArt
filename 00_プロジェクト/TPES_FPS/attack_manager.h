//=============================================
//
//攻撃管理クラス[attack_manager.h]
//Auther Matsuda Towa
//
//=============================================
#include"main.h"
#include "Billboard.h"

#ifndef _ATTACK_MANAGER_H_ //これが定義されてないとき

#define _ATTACK_MANAGER_H_

//=============================================
//攻撃管理クラス
//=============================================
class CAttack_Manager : public CBillboard
{
public:
	CAttack_Manager(int nPriority);
	~CAttack_Manager()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	bool HitEnemy();
	bool HitPlayer();
	bool HitBlock();
	bool HitGround();

	//寿命の設定
	void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	//ダメージの設定
	void SetDamage(int nDamage)
	{
		m_nDamage = nDamage;
	}

	//寿命の取得
	int GetLife();

	//ダメージの取得
	int GetDamage();
private:

	int m_nLife; //寿命
	int m_nDamage; //ダメージ
	int m_nNumkill; //何体倒したか

};
#endif