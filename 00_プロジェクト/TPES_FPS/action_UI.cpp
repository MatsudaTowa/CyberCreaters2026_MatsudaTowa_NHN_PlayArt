//=============================================
//
//アクションUIの表記[action_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "action_UI.h"
#include "manager.h"

//=============================================
//テクスチャパス
//=============================================
const std::string CAction_UI::TEXTURE_NAME[CAction_UI::ACTION_MAX]
{
	"data\\TEXTURE\\move_txt.png",
	"data\\TEXTURE\\shotmode_txt.png",
	"data\\TEXTURE\\shot_txt.png",
	"data\\TEXTURE\\reload_txt.png",
	"data\\TEXTURE\\ult_txt.png",
	"data\\TEXTURE\\smoke_txt.png",
};

//=============================================
//コンストラクタ
//=============================================
CAction_UI::CAction_UI(int nPriority) :CObject2D(nPriority), m_type()
{
}

//=============================================
//デストラクタ
//=============================================
CAction_UI::~CAction_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CAction_UI::Init()
{
	//初期化
	CObject2D::Init();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME[m_type])));

	SetVtx(1.0f);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CAction_UI::Uninit()
{
	//終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CAction_UI::Update()
{
	//更新
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CAction_UI::Draw()
{
	//描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CAction_UI* CAction_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ACTION_TYPE type)
{
	CAction_UI* pAction_UI = new CAction_UI;

	if (pAction_UI == nullptr) { return nullptr; }

	pAction_UI->SetPos(pos);
	pAction_UI->SetSize(size);
	pAction_UI->SetColor(col);
	pAction_UI->m_type = type;

	pAction_UI->Init();

	return pAction_UI;
}
