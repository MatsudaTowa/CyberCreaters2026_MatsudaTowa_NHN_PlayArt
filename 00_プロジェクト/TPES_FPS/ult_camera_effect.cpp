//=============================================
//
//ウルト時のカメラエフェクト「ult_camera_effect.cpp」
// Author松田永久
//
//=============================================
#include "ult_camera_effect.h"
#include "manager.h"

const std::string CUltCameraEffect::TEXTURE_NAME = "data\\TEXTURE\\syutyu90.png";

//=============================================
//コンストラクタ
//=============================================
CUltCameraEffect::CUltCameraEffect(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CUltCameraEffect::~CUltCameraEffect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CUltCameraEffect::Init()
{
	CObject2D::Init();

	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	//サイズを代入
	SetSize(size);

	//カラー取得
	D3DXCOLOR col = GetColor();

	col = D3DXCOLOR(0.5f, 0.0f, 0.0f, m_alpha);

	//カラーを代入
	SetColor(col);

	//テクスチャ設定
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	//頂点設定
	SetVtx(1.0f);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CUltCameraEffect::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CUltCameraEffect::Update()
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
void CUltCameraEffect::Draw()
{
	CObject2D::Draw();

}

//=============================================
//生成
//=============================================
CUltCameraEffect* CUltCameraEffect::Create(D3DXVECTOR3 pos)
{
	CUltCameraEffect* pUltCameraEffect = new CUltCameraEffect;
	//CObject *pObject = Getobject();

	if (pUltCameraEffect == nullptr) { return nullptr; }

	pUltCameraEffect->SetPos(pos); //pos設定

	pUltCameraEffect->m_alpha = 0.8f;

	pUltCameraEffect->SetType(OBJECT_TYPE_ULT_CAMERA_EFFECT); //タイプ設定

	pUltCameraEffect->Init();

	return pUltCameraEffect;
}

//=============================================
//アルファ値減少
//=============================================
void CUltCameraEffect::SubAlpha()
{
	m_alpha -= 0.01f;
}
