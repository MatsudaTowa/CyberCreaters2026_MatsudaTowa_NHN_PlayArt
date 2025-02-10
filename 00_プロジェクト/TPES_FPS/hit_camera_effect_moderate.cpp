//=============================================
//
//ヒット時のカメラエフェクト(中傷時)「hit_camera_effect_mild.cpp」
// Author松田永久
//
//=============================================
#include "hit_camera_effect_moderate.h"
#include "manager.h"

const std::string CHitCameraEffectModerate::TEXTURE_NAME = "data\\TEXTURE\\hit_camera_effect001.png";

//=============================================
//コンストラクタ
//=============================================
CHitCameraEffectModerate::CHitCameraEffectModerate(int nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CHitCameraEffectModerate::~CHitCameraEffectModerate()
{
}

//=============================================
//初期化
//=============================================
HRESULT CHitCameraEffectModerate::Init()
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
void CHitCameraEffectModerate::Uninit()
{
	//親クラスの終了
	CHitCameraEffect::Uninit();
}

//=============================================
//更新
//=============================================
void CHitCameraEffectModerate::Update()
{
	//親クラスの更新
	CHitCameraEffect::Update();
}

//=============================================
//描画
//=============================================
void CHitCameraEffectModerate::Draw()
{
	//親クラスの描画
	CHitCameraEffect::Draw();
}
