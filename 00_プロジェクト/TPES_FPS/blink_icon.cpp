//=============================================
//
//ブリンクの表記[blink_icon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "blink_icon.h"
#include "manager.h"

//テクスチャ初期化
const std::string CBlinkIcon::TEXTURE_NAME = "data\\TEXTURE\\blink.png";

//=============================================
//コンストラクタ
//=============================================
CBlinkIcon::CBlinkIcon(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBlinkIcon::~CBlinkIcon()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlinkIcon::Init()
{
	//初期化
	CObject2D::Init();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	SetVtx(1.0f);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlinkIcon::Uninit()
{
	//終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CBlinkIcon::Update()
{
	//更新
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CBlinkIcon::Draw()
{
	//描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CBlinkIcon* CBlinkIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CBlinkIcon* pBlinkIcon = new CBlinkIcon;

	if (pBlinkIcon == nullptr) { return nullptr; }

	pBlinkIcon->SetPos(pos);
	pBlinkIcon->SetSize(size);
	pBlinkIcon->SetColor(col);

	pBlinkIcon->Init();

	return pBlinkIcon;
}
