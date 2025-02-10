//=============================================
//
//ヒット時のカメラエフェクト(軽傷時)「hit_camera_effect_mild.cpp」
// Author松田永久
//
//=============================================
#include "hit_camera_effect_mild.h"
#include "manager.h"

const std::string CHitCameraEffectMild::TEXTURE_NAME = "data\\TEXTURE\\hit_camera_effect000.png";

//=============================================
//コンストラクタ
//=============================================
CHitCameraEffectMild::CHitCameraEffectMild(int nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CHitCameraEffectMild::~CHitCameraEffectMild()
{
}

//=============================================
//初期化
//=============================================
HRESULT CHitCameraEffectMild::Init()
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
void CHitCameraEffectMild::Uninit()
{
	//親クラスの終了
	CHitCameraEffect::Uninit();
}

//=============================================
//更新
//=============================================
void CHitCameraEffectMild::Update()
{
	//親クラスの更新
	CHitCameraEffect::Update();
}

//=============================================
//描画
//=============================================
void CHitCameraEffectMild::Draw()
{
	//親クラスの描画
	CHitCameraEffect::Draw();
}
