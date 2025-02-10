//=============================================
//
//ヒットマーカー[hitmaker.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "hitmaker.h"
#include "manager.h"

const std::string CHitMaker::HITMARKER_DOT_TEXTURE_NAME = "data\\TEXTURE\\hitmarker.png";


//=============================================
//コンストラクタ
//=============================================
CHitMaker::CHitMaker(int nPriority):CBillboard(nPriority),
m_nLife(0)
{
}

//=============================================
//デストラクタ
//=============================================
CHitMaker::~CHitMaker()
{
}

//=============================================
//初期化
//=============================================
HRESULT CHitMaker::Init()
{
	CBillboard::Init();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//テクスチャ読み込み
	BindTexture(pTexture->GetAddress(pTexture->Regist(&HITMARKER_DOT_TEXTURE_NAME)));

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CHitMaker::Uninit()
{
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CHitMaker::Update()
{
	CBillboard::Update();

	D3DXCOLOR col = GetColor();
	col.a -= 0.05f;

	if (col.a <= 0.0f)
	{
		col.a = 0.0f;
	}

	SetColor(col);

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//描画
//=============================================
void CHitMaker::Draw()
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
//弾が当たったら色変更
//=============================================
void CHitMaker::HitColor(D3DXCOLOR col)
{
	SetColor(col);
}

//=============================================
//生成
//=============================================
CHitMaker* CHitMaker::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CHitMaker* pHitMaker = new CHitMaker;

	if (pHitMaker == nullptr)
	{
		return nullptr;
	}

	pHitMaker->SetPos(pos); //pos設定
	pHitMaker->SetSize(size); //サイズ設定
	pHitMaker->SetRot(rot);
	pHitMaker->SetColor(col);

	pHitMaker->SetType(OBJECT_TYPE_RETICLE); //タイプ設定
	pHitMaker->Init();

	return pHitMaker;
}
