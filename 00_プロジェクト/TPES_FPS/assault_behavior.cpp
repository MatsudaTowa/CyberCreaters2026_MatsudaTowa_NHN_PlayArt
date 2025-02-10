//=============================================
//
//アサルト銃のストラテジーパターン[assault_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "assault_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CAssaultShot::CAssaultShot()
{
}

//=============================================
//デストラクタ
//=============================================
CAssaultShot::~CAssaultShot()
{
}

//=============================================
//コンストラクタ
//=============================================
CAssaultReload::CAssaultReload()
{
}

//=============================================
//デストラクタ
//=============================================
CAssaultReload::~CAssaultReload()
{
}

//=============================================
//アサルトリロード処理
//=============================================
bool CAssaultReload::Reload(CGun* gun)
{
	bool bReload = true; //リロード中かどうか
	int nCnt = GetReloadCnt();
	
	nCnt++;

	if (nCnt >= gun->GetReloadFrame())
	{
		nCnt = 0;
		//現在の弾数取得
		int nAmmo = gun->GetAmmo();
		//デフォルトのマガジン弾数代入
		nAmmo = CAssultRifle::DEFAULT_AR_MAG_SIZE;
		gun->SetAmmo(nAmmo);
		bReload = false;
	}

	SetReloadCnt(nCnt);
	return bReload;
}
