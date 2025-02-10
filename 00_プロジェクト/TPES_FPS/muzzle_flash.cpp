//=============================================
// 
//マズルフラッシュ[muzzle_flash.h]
//Auther Matsuda Towa
//
//=============================================
#include "muzzle_flash.h"
#include "manager.h"

const std::string CMuzzleFlash::TEXTURE_NAME = "data\\TEXTURE\\flash.png";
const D3DXVECTOR3 CMuzzleFlash::SIZE = { 10.0f,10.0f,0.0f };
//=============================================
//コンストラクタ
//=============================================
CMuzzleFlash::CMuzzleFlash(int nPriority):CBillboard(nPriority),
m_nLife(0)
{
}

//=============================================
//デストラクタ
//=============================================
CMuzzleFlash::~CMuzzleFlash()
{
}

//=============================================
//初期化
//=============================================
HRESULT CMuzzleFlash::Init()
{
	//親の初期化
	CBillboard::Init();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//テクスチャ読み込み
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CMuzzleFlash::Uninit()
{
	//親の終了
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CMuzzleFlash::Update()
{

	--m_nLife; //体力減少
	if (m_nLife > 0)
	{
		//親の更新
		CBillboard::Update();

		//頂点座標
		SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	}
	else if(m_nLife <= 0)
	{
		m_nLife = 0;
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CMuzzleFlash::Draw()
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
CMuzzleFlash* CMuzzleFlash::Create(D3DXVECTOR3 pos)
{
	CMuzzleFlash* pMuzzleFlash = new CMuzzleFlash;
	if (pMuzzleFlash == nullptr) { return nullptr; }

	//位置代入
	pMuzzleFlash->SetPos(pos);

	//サイズ代入
	pMuzzleFlash->SetSize(SIZE);

	//体力設定
	pMuzzleFlash->m_nLife = LIFE;

	pMuzzleFlash->Init();

	pMuzzleFlash->SetType(OBJECT_TYPE_MUZZLE_FLUSH);

	return pMuzzleFlash;
}
