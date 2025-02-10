//=============================================
//
//ミニガンのストラテジーパターン[minigun_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "minigun_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CMiniGunShot::CMiniGunShot()
{
}

//=============================================
//デストラクタ
//=============================================
CMiniGunShot::~CMiniGunShot()
{
}

//=============================================
//コンストラクタ
//=============================================
CMiniGunReload::CMiniGunReload()
{
}

//=============================================
//デストラクタ
//=============================================
CMiniGunReload::~CMiniGunReload()
{
}

//=============================================
//リロード
//=============================================
bool CMiniGunReload::Reload(CGun* gun)
{
	bool bReload = true; //リロード中かどうか
	int nCnt = GetReloadCnt();

	++nCnt;

	if (nCnt >= CMiniGun::DEFAULT_MINIGUN_RELOAD_FRAME)
	{
		nCnt = 0;
		//現在の弾数取得
		int nAmmo = gun->GetAmmo();
		//デフォルトのマガジン弾数代入
		nAmmo = CMiniGun::DEFAULT_MINIGUN_MAG_SIZE;
		gun->SetAmmo(nAmmo);
		bReload = false;
	}

	SetReloadCnt(nCnt);
	return bReload;
}
