//=============================================
//
//銃[gun.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun.h"
#include "assault_behavior.h"
#include "minigun_behavior.h"
//=============================================
//コンストラクタ
//=============================================
CGun::CGun():m_Ammo(),m_Lv(),m_ReloadFrame(),m_FireRate(), m_nRateCnt(0),m_nDamage(0),m_Size(),m_BulletSpeed(0.0f)
{
	m_pShot = nullptr;
	m_pReload = nullptr;
}

//=============================================
//デストラクタ
//=============================================
CGun::~CGun()
{
	if (m_pShot != nullptr)
	{
		delete m_pShot;
		m_pShot = nullptr;
	}
	if (m_pReload != nullptr)
	{
		delete m_pReload;
		m_pReload = nullptr;
	}
}

//=============================================
//リロード
//=============================================
bool CGun::Reload()
{
	bool bReload = true; //リロード中かどうか
	if (m_pReload != nullptr)
	{
		bReload = m_pReload->Reload(this);
	}
	return bReload;
}

//=============================================
//弾数取得
//=============================================
int& CGun::GetAmmo()
{
	return m_Ammo;
}

//=============================================
//レベル取得
//=============================================
int& CGun::GetLv()
{
	return m_Lv;
}

//=============================================
//ダメージ取得
//=============================================
int& CGun::GetDamage()
{
	return m_nDamage;
}

//=============================================
//リロードフレーム取得
//=============================================
int& CGun::GetReloadFrame()
{
	return m_ReloadFrame;
}

//=============================================
//発射レート取得
//=============================================
int& CGun::GetFireRate()
{
	return m_FireRate;
}

//=============================================
//弾速取得
//=============================================
float& CGun::GetBulletSpeed()
{
	return m_BulletSpeed;
}

//弾のスピード
const float CAssultRifle::DEFAULT_AR_BULLET_SPEED = 100.0f;
//弾のサイズ
const D3DXVECTOR3 CAssultRifle::DEFAULT_AR_SIZE = {2.0f,2.0f,2.0f};

//=============================================
//コンストラクタ
//=============================================
CAssultRifle::CAssultRifle()
{
	if (m_pShot == nullptr)
	{
		m_pShot = new CAssaultShot;
	}
	if (m_pReload == nullptr)
	{
		m_pReload = new CAssaultReload;
	}
}

//=============================================
//デストラクタ
//=============================================
CAssultRifle::~CAssultRifle()
{

}

//=============================================
//初期化
//=============================================
HRESULT CAssultRifle::Init()
{
	//現在の弾数取得
	int nAmmo = GetAmmo();
	//現在のレベル取得
	int nLv = GetLv();
	//現在のリロードフレーム取得
	int nReloadFrame = GetReloadFrame();
	//現在の発射レート取得
	int nFireRate = GetFireRate();
	//現在の弾速取得
	float fBulletSpeed = GetBulletSpeed();

	//デフォルトのマガジン弾数代入
	nAmmo = DEFAULT_AR_MAG_SIZE;
	//初期レベル代入
	nLv = 1;

	//デフォルトの発射レート代入
	nFireRate = DEFAULT_AR_FIRE_RATE;
	//デフォルトの弾速代入
	fBulletSpeed = DEFAULT_AR_BULLET_SPEED;

	//押したらすぐ発射するため
	m_nRateCnt = GetFireRate();

	//サイズの代入
	m_Size = DEFAULT_AR_SIZE;

	//各メンバー変数に代入
	SetAmmo(nAmmo);
	SetLv(nLv);
	SetReloadFrame(nReloadFrame);
	SetFireRate(nFireRate);
	SetBulletSpeed(fBulletSpeed);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CAssultRifle::Uninit()
{
}

//弾のスピード
const float CMiniGun::DEFAULT_MINIGUN_BULLET_SPEED = 100.0f;
//弾のサイズ
const D3DXVECTOR3 CMiniGun::DEFAULT_MINIGUN_SIZE = { 1.0f,1.0f,1.0f };
//=============================================
//コンストラクタ
//=============================================
CMiniGun::CMiniGun()
{
	if (m_pShot == nullptr)
	{
		m_pShot = new CMiniGunShot;
	}
	if (m_pReload == nullptr)
	{
		m_pReload = new CMiniGunReload;
	}
}

//=============================================
//デストラクタ
//=============================================
CMiniGun::~CMiniGun()
{
}

//=============================================
//初期化
//=============================================
HRESULT CMiniGun::Init()
{
	//現在の弾数取得
	int nAmmo = GetAmmo();
	//現在のレベル取得
	int nLv = GetLv();
	//現在のリロードフレーム取得
	int nReloadFrame = GetReloadFrame();
	//現在の発射レート取得
	int nFireRate = GetFireRate();
	//現在の弾速取得
	float fBulletSpeed = GetBulletSpeed();

	//デフォルトのマガジン弾数代入
	nAmmo = DEFAULT_MINIGUN_MAG_SIZE;
	//初期レベル代入
	nLv = 1;
	//デフォルトのリロードフレーム代入
	nReloadFrame = DEFAULT_MINIGUN_RELOAD_FRAME;
	//デフォルトの発射レート代入
	nFireRate = DEFAULT_MINIGUN_FIRE_RATE;
	//デフォルトの弾速代入
	fBulletSpeed = DEFAULT_MINIGUN_BULLET_SPEED;

	//押したらすぐ発射するため
	m_nRateCnt = DEFAULT_MINIGUN_FIRE_RATE;

	//ダメージの代入
	SetDamage(DEFAULT_MINIGUN_DAMAGE);

	//サイズの代入
	m_Size = DEFAULT_MINIGUN_SIZE;

	//各メンバー変数に代入
	SetAmmo(nAmmo);
	SetLv(nLv);
	SetReloadFrame(nReloadFrame);
	SetFireRate(nFireRate);
	SetBulletSpeed(fBulletSpeed);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CMiniGun::Uninit()
{
}
