//=============================================
//
//ヒット時のカメラエフェクト(重傷時)「hit_camera_effect_severe.h」
// Author松田永久
//
//=============================================
#include "hit_camera_effect_severe.h"
#include "manager.h"

const std::string CHitCameraEffectSevere::TEXTURE_NAME = "data\\TEXTURE\\hit_camera_effect002.png";

//=============================================
//コンストラクタ
//=============================================
CHitCameraEffectSevere::CHitCameraEffectSevere(int nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CHitCameraEffectSevere::~CHitCameraEffectSevere()
{
}

//=============================================
//初期化
//=============================================
HRESULT CHitCameraEffectSevere::Init()
{
	//親クラスの初期化
	CHitCameraEffect::Init();

	//テクスチャ設定
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CHitCameraEffectSevere::Uninit()
{
	//親クラスの終了
	CHitCameraEffect::Uninit();
}

//=============================================
//更新
//=============================================
void CHitCameraEffectSevere::Update()
{
	//親クラスの更新
	CHitCameraEffect::Update();
}

//=============================================
//描画
//=============================================
void CHitCameraEffectSevere::Draw()
{
	//親クラスの描画
	CHitCameraEffect::Draw();
}
