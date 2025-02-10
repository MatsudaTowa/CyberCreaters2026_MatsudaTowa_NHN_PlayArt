//=============================================
//
//スモークグレネード処理[somoke_grenade.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "smoke.h"

#ifndef _SMOKE_GRENADE_H_ //これが定義されてないとき

#define _SMOKE_GRENADE_H_

class CSmokeGrenade : public CObjectX
{
public:
	static const int SMOKE_PRIORITY = 24; //描画順

	CSmokeGrenade(int nPriority = SMOKE_PRIORITY);
	~CSmokeGrenade()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//スモークグレネード作成
	static CSmokeGrenade* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);

private:
	static const char* MODEL_NAME;	//モデルの名前
	static const int CREATE_SMOKE_NUM = 100; //生成するスモークの数
	void HitField();
	D3DXVECTOR3 m_oldpos;
	D3DXVECTOR3 m_move;
	bool m_bBoot; //グレネードが起動したか
	int m_NumCreate; //何個生成したかカウントする変数
};

#endif