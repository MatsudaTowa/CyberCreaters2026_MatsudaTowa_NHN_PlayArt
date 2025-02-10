//=============================================
//
//ウルトエフェクト「ult_effect.cpp」
// Author松田永久
//
//=============================================
#include "ult_effect.h"
#include "manager.h"

const std::string CUltEffect::TEXTURE_NAME = "data\\TEXTURE\\ult_effect.png";
//=============================================
//コンストラクタ
//=============================================
CUltEffect::CUltEffect(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CUltEffect::~CUltEffect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CUltEffect::Init()
{
	CObject3D::Init();
	SetColor({ 1.0f,0.0f,0.0f, 0.75f });
	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CUltEffect::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CUltEffect::Update()
{
	CObject3D::Update();
	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
//描画
//=============================================
void CUltEffect::Draw()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//生成
//=============================================
CUltEffect* CUltEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CUltEffect* pUltEffect = new CUltEffect;

	// nullならnullを返す
	if (pUltEffect == nullptr) { return nullptr; }

	//テクスチャ取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	pUltEffect->SetPos(pos); //pos設定
	pUltEffect->SetSize(size); //サイズ設定
	pUltEffect->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャ設定
	pUltEffect->SetType(OBJECT_TYPE_ULT_EFFECT); //タイプ設定
	pUltEffect->Init(); //初期化処理

	return pUltEffect;
}
