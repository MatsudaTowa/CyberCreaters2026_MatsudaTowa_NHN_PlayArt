//=============================================
//
//通常の敵の処理[normal_enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "normal_enemy.h"
#include "normal_enemy_behavior.h"

//影のサイズ
const D3DXVECTOR3 CNormalEnemy::SHADOW_SIZE = { 20.0f, 0.0, 20.0f };

//=============================================
//コンストラクタ
//=============================================
CNormalEnemy::CNormalEnemy(int nPriority):CEnemy(nPriority)
{
	if (m_pMove == nullptr)
	{
		m_pMove = new CNormalMove;
	}
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CNormalAttack;
	}
	if (m_pStan == nullptr)
	{
		m_pStan = new CEnemyStan;
	}
	if (m_pConfusion == nullptr)
	{
		m_pConfusion = new CEnemyConfusion;
	}
}

//=============================================
//デストラクタ
//=============================================
CNormalEnemy::~CNormalEnemy()
{
}

//=============================================
//初期化
//=============================================
HRESULT CNormalEnemy::Init()
{
	//銃初期化
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->SetReloadFrame(DEFAULT_AR_RELOAD_FRAME);
		m_pGun->SetDamage(DEFAULT_AR_DAMAGE);

		m_pGun->Init();
	}

	SetLife(DEFAULT_LIFE);

	//影のサイズ設定
	SetShadowSize(SHADOW_SIZE);

	//親クラスの初期化を呼ぶ
	CEnemy::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CNormalEnemy::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CEnemy::Uninit();
}

//=============================================
//更新
//=============================================
void CNormalEnemy::Update()
{
	CEnemy::Update();
	Motion(NUM_PARTS); //モーション処理
}

//=============================================
//描画
//=============================================
void CNormalEnemy::Draw()
{
	CEnemy::Draw();
}

//=============================================
//ウルトヒット処理
//=============================================
void CNormalEnemy::MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)
{
	ChangeState(new CStanState);

	//親クラスのヒット処理
	CEnemy::MediumUltHit(UltPos,nDamage);
}
