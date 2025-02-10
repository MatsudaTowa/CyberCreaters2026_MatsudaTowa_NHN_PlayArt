//=============================================
//
//敵の混乱のUI[enemy_stan_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_stan_UI.h"
#include "manager.h"

const std::string CEnemy_Stan_UI::TEXTURE_NAME = "data\\TEXTURE\\stan_UI.png";

//=============================================
//コンストラクタ
//=============================================
CEnemy_Stan_UI::CEnemy_Stan_UI(int nPriority) :CEnemy_Reaction_UI(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CEnemy_Stan_UI::~CEnemy_Stan_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy_Stan_UI::Init()
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//テクスチャ読み込み
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CEnemy_Reaction_UI::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy_Stan_UI::Uninit()
{
	CEnemy_Reaction_UI::Uninit();
}

//=============================================
//更新
//=============================================
void CEnemy_Stan_UI::Update()
{
	CEnemy_Reaction_UI::Update();
}

//=============================================
//描画
//=============================================
void CEnemy_Stan_UI::Draw()
{
	CEnemy_Reaction_UI::Draw();
}
