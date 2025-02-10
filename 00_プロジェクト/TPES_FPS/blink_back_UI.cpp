//=============================================
//
//ブリンクの数字の背景[blink_back_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "blink_back_UI.h"
#include "manager.h"

//テクスチャ初期化
const std::string CBlinkBackUI::TEXTURE_NAME = "data\\TEXTURE\\blink_back.png";

//=============================================
//コンストラクタ
//=============================================
CBlinkBackUI::CBlinkBackUI(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBlinkBackUI::~CBlinkBackUI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlinkBackUI::Init()
{
	CObject2D::Init();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	SetVtx(1.0f);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlinkBackUI::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CBlinkBackUI::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CBlinkBackUI::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CBlinkBackUI* CBlinkBackUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CBlinkBackUI* pBlinkBackUI = new CBlinkBackUI;

	if (pBlinkBackUI == nullptr) { return nullptr; }

	pBlinkBackUI->SetPos(pos);
	pBlinkBackUI->SetSize(size);
	pBlinkBackUI->SetColor(col);

	pBlinkBackUI->Init();

	return pBlinkBackUI;
}
