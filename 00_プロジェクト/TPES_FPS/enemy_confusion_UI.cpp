//=============================================
//
//敵の混乱のUI[enemy_wandering_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_confusion_UI.h"
#include "manager.h"

const std::string CEnemy_Confusion_UI::TEXTURE_NAME = "data\\TEXTURE\\wandering_UI.png";

//=============================================
//コンストラクタ
//=============================================
CEnemy_Confusion_UI::CEnemy_Confusion_UI(int nPriority):CEnemy_Reaction_UI(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CEnemy_Confusion_UI::~CEnemy_Confusion_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy_Confusion_UI::Init()
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
void CEnemy_Confusion_UI::Uninit()
{
	CEnemy_Reaction_UI::Uninit();
}

//=============================================
//更新
//=============================================
void CEnemy_Confusion_UI::Update()
{
	CEnemy_Reaction_UI::Update();
}

//=============================================
//描画
//=============================================
void CEnemy_Confusion_UI::Draw()
{
	CEnemy_Reaction_UI::Draw();
}
