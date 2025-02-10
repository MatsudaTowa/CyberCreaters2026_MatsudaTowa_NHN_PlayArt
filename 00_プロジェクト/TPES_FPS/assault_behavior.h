//=============================================
//
//アサルト銃のストラテジーパターン[assault_behavior.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ASSAULT_BEHAVIOR_
#define _ASSAULT_BEHAVIOR_
#include "gun_behavior.h"
#include "gun.h"

//=============================================
//アサルト弾発射ストラテジー
//=============================================
class CAssaultShot : public CShot
{
public:
	CAssaultShot();
	~CAssaultShot() override;
};

//=============================================
//リロードストラテジー
//=============================================
class CAssaultReload : public CReload
{
public:
	CAssaultReload();
	~CAssaultReload() override;
	bool Reload(CGun* gun) override;
private:
};
#endif