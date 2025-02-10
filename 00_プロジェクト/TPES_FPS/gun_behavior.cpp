//=============================================
//
//銃のストラテジーパターン[gun_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CShot::CShot()
{
}

//=============================================
//デストラクタ
//=============================================
CShot::~CShot()
{
}

//=============================================
//弾発射処理
//=============================================
void CShot::Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CGun* gun)
{
	//現在の弾数取得
	int nAmmo = gun->GetAmmo();
	if (nAmmo > 0)
	{
		CBullet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), move,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 600, nDamage, Allegiance, type);

		CMuzzleFlash::Create(pos);
		--nAmmo;
	}
	gun->SetAmmo(nAmmo);
}

//=============================================
//コンストラクタ
//=============================================
CReload::CReload():m_nReloadCnt(0)
{
}

//=============================================
//デストラクタ
//=============================================
CReload::~CReload()
{
}

//=============================================
//カウント取得
//=============================================
int& CReload::GetReloadCnt()
{
	return m_nReloadCnt;
}
