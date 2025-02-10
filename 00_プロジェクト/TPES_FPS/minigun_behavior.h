//=============================================
//
//ミニガンのストラテジーパターン[minigun_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MINIGUN_BEHAVIOR_
#define _MINIGUN_BEHAVIOR_
#include "gun_behavior.h"
#include "gun.h"

//=============================================
//ミニガンの弾発射ストラテジー
//=============================================
class CMiniGunShot : public CShot
{
public:
	CMiniGunShot();
	~CMiniGunShot() override;
};

//=============================================
//リロードストラテジー
//=============================================
class CMiniGunReload : public CReload
{
public:
	CMiniGunReload();
	~CMiniGunReload() override;
	bool Reload(CGun* gun) override;
private:
};
#endif