//=============================================
//
//ヒット時のカメラエフェクト「hit_camera_effect.cpp」
// Author松田永久
//
//=============================================
#include "hit_camera_effect.h"
#include "hit_camera_effect_mild.h"
#include "hit_camera_effect_moderate.h"
#include "hit_camera_effect_severe.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CHitCameraEffect::CHitCameraEffect(int nPriority): CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CHitCameraEffect::~CHitCameraEffect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CHitCameraEffect::Init()
{
	CObject2D::Init();

	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.5f);

	//サイズを代入
	SetSize(size);

	//カラー取得
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(0.5f, 0.0f, 0.0f, m_alpha);

	//カラーを代入
	SetColor(col);

	//頂点設定
	SetVtx(1.0f);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CHitCameraEffect::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CHitCameraEffect::Update()
{
	//親クラスの終了
	CObject2D::Update();

	//カラー取得
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(0.5f, 0.0f, 0.0f, m_alpha);

	//カラーを代入
	SetColor(col);

	//頂点設定
	SetVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CHitCameraEffect::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CHitCameraEffect* CHitCameraEffect::Create(D3DXVECTOR3 pos, HIT_EFFECT_STAGE stage)
{
	CHitCameraEffect* pHitCameraEffect = nullptr;
	//CObject *pObject = Getobject();

	switch (stage)
	{
	case CHitCameraEffect::MILD:
		pHitCameraEffect = new CHitCameraEffectMild;
		break;
	case CHitCameraEffect::MODERATE:
		pHitCameraEffect = new CHitCameraEffectModerate;
		break;
	case CHitCameraEffect::SEVERE:
		pHitCameraEffect = new CHitCameraEffectSevere;
		break;
	default:
		assert(false);
		break;
	}

	if (pHitCameraEffect == nullptr) {return nullptr;}

	pHitCameraEffect->SetPos(pos); //pos設定

	pHitCameraEffect->m_alpha = 0.8f;

	pHitCameraEffect->SetType(OBJECT_TYPE_HIT_CAMERA_EFFECT); //タイプ設定

	pHitCameraEffect->Init();

	return pHitCameraEffect;
}

//=============================================
//アルファ値減算
//=============================================
void CHitCameraEffect::SubAlpha()
{
	m_alpha -= 0.01f;
}
