//=============================================
//
//センタードット[centerdot.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "centerdot.h"
#include "manager.h"

const std::string CCenterDot::CENTERDOT_TEXTURE_NAME = "data\\TEXTURE\\crosshair001.png";

//=============================================
//コンストラクタ
//=============================================
CCenterDot::CCenterDot(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CCenterDot::~CCenterDot()
{
}

//=============================================
//初期化
//=============================================
HRESULT CCenterDot::Init()
{
	CBillboard::Init();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//テクスチャ読み込み
	BindTexture(pTexture->GetAddress(pTexture->Regist(&CENTERDOT_TEXTURE_NAME)));

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CCenterDot::Uninit()
{
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CCenterDot::Update()
{
	CBillboard::Update();

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//描画
//=============================================
void CCenterDot::Draw()
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
CCenterDot* CCenterDot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CCenterDot* pCenterDot = new CCenterDot;

	if (pCenterDot == nullptr)
	{
		return nullptr;
	}

	pCenterDot->SetPos(pos); //pos設定
	pCenterDot->SetSize(size); //サイズ設定
	pCenterDot->SetRot(rot);
	pCenterDot->SetColor(col);

	pCenterDot->SetType(OBJECT_TYPE_RETICLE); //タイプ設定
	pCenterDot->Init();

	return pCenterDot;
}
