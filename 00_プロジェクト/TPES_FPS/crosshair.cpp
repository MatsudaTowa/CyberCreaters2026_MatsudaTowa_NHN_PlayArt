//=============================================
//
//クロスヘア[crosshair.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "crosshair.h"
#include "manager.h"

const std::string CCrossHair::CROSSHAIR_TEXTURE_NAME = "data\\TEXTURE\\crosshair000.png";

//=============================================
//コンストラクタ
//=============================================
CCrossHair::CCrossHair(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CCrossHair::~CCrossHair()
{
}

//=============================================
//初期化
//=============================================
HRESULT CCrossHair::Init()
{
	CBillboard::Init();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//テクスチャ読み込み
	BindTexture(pTexture->GetAddress(pTexture->Regist(&CROSSHAIR_TEXTURE_NAME)));

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CCrossHair::Uninit()
{
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CCrossHair::Update()
{
	CBillboard::Update();

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//描画
//=============================================
void CCrossHair::Draw()
{
	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//親クラスの描画
	CBillboard::Draw();
	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
//生成
//=============================================
CCrossHair* CCrossHair::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CCrossHair* pCroshair = new CCrossHair;

	if (pCroshair == nullptr)
	{
		return nullptr;
	}

	pCroshair->SetPos(pos); //pos設定
	pCroshair->SetSize(size); //サイズ設定
	pCroshair->SetRot(rot);
	pCroshair->SetColor(col);

	pCroshair->SetType(OBJECT_TYPE_RETICLE); //タイプ設定
	pCroshair->Init();

	return pCroshair;
}