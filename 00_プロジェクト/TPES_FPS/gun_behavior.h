//=============================================
//
//銃のストラテジーパターン[gun_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GUN_BEHAVIOR_
#define _GUN_BEHAVIOR_
#include "gun.h"
#include "muzzle_flash.h"

//=============================================
//前方宣言
//=============================================
class CGun;

//=============================================
//弾発射ストラテジー
//=============================================
class CShot
{
public:
	CShot();
	virtual ~CShot();
	virtual void Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type,CGun*gun);
};

//=============================================
//リロードストラテジー
//=============================================
class CReload
{
public:
	CReload();
	virtual ~CReload();
	virtual bool Reload(CGun* gun) = 0;

	int& GetReloadCnt();

	void SetReloadCnt(int nCnt)
	{
		m_nReloadCnt = nCnt;
	}
private:
	int m_nReloadCnt;
};

#endif
