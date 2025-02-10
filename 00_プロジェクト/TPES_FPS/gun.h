//=============================================
//
//銃[gun.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "bullet.h"
#include "gun_behavior.h"

#ifndef _GUN_H_ //これが定義されてないとき

#define _GUN_H_

//=============================================
//前方宣言
//=============================================
class CShot;
class CReload;

//=============================================
//銃の基底クラス
//=============================================
class CGun
{
public:
	static const int DEFAULT_HG_MAG_SIZE = 20; //デフォルトのハンドガンのマガジンサイズ
	static const int DEFAULT_SG_MAG_SIZE = 6; //デフォルトのショットガンのマガジンサイズ

	static const int DEFAULT_HG_RELOAD_FRAME = 20; //デフォルトのハンドガンのリロードフレーム数
	static const int DEFAULT_SG_RELOAD_FRAME = 30; //デフォルトのハンドガンのリロードフレーム数

	CGun();
	virtual ~CGun();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual bool Reload();

	//弾数設定
	void SetAmmo(int Ammo)
	{
		m_Ammo = Ammo;
	}
	//レベル設定
	void SetLv(int Lv)
	{
		m_Lv = Lv;
	}
	//ダメージ設定
	void SetDamage(int Damage)
	{
		m_nDamage = Damage;
	}
	//リロードフレーム設定
	void SetReloadFrame(int ReloadFrame)
	{
		m_ReloadFrame = ReloadFrame;
	}
	//発射レート設定
	void SetFireRate(int FireRate)
	{
		m_FireRate = FireRate;
	}
	//発射レート設定
	void SetBulletSpeed(float BulletSpeed)
	{
		m_BulletSpeed = BulletSpeed;
	}
	
	//弾数取得
	int& GetAmmo();
	//レベル取得
	int& GetLv();
	//ダメージ取得
	int& GetDamage();
	//リロードフレーム
	int& GetReloadFrame();
	//発射レート取得
	int& GetFireRate();
	//弾速取得
	float& GetBulletSpeed();

	int m_nRateCnt;//レートカウント

	CShot* m_pShot; //弾発射処理
	CReload* m_pReload; //リロード処理

	D3DXVECTOR3 m_Size; //サイズ
private:
	int m_Ammo; //マガジン内の弾数
	int m_Lv; //銃のレベル
	int m_nDamage; //ダメージ
	int m_ReloadFrame; //リロードフレーム
	int m_FireRate; //発射レート
	float m_BulletSpeed; //弾速

};

//=============================================
//アサルトライフクラス
//=============================================
class CAssultRifle :public CGun
{
public:
	static const int DEFAULT_AR_MAG_SIZE = 28; //デフォルトのアサルトのマガジンサイズ
	static const int DEFAULT_AR_FIRE_RATE = 13; //デフォルトのアサルトの発射レート
	static const float DEFAULT_AR_BULLET_SPEED; //デフォルトのアサルトの弾のスピード
	static const D3DXVECTOR3 DEFAULT_AR_SIZE; //デフォルトのアサルトサイズ

	CAssultRifle();
	~CAssultRifle() override;
	HRESULT Init() override;
	void Uninit() override;
private:
};

//=============================================
//ミニガンクラス
//=============================================
class CMiniGun :public CGun
{
public:
	static const int DEFAULT_MINIGUN_MAG_SIZE = 120; //デフォルトのミニガンのマガジンサイズ
	static const int DEFAULT_MINIGUN_RELOAD_FRAME = 120; //デフォルトのミニガンのリロードフレーム数
	static const int DEFAULT_MINIGUN_FIRE_RATE = 2; //デフォルトのミニガンの発射レート
	static const int DEFAULT_MINIGUN_DAMAGE = 3; //デフォルトのミニガンのダメージ
	static const float DEFAULT_MINIGUN_BULLET_SPEED; //デフォルトのミニガンの弾のスピード
	static const D3DXVECTOR3 DEFAULT_MINIGUN_SIZE; //デフォルトのミニガンのサイズ

	CMiniGun();
	~CMiniGun() override;
	HRESULT Init() override;
	void Uninit() override;
private:
};
#endif