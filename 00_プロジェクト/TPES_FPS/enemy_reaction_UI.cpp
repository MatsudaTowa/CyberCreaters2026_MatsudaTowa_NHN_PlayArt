//=============================================
//
//敵のリアクションのUI[enemy_reaction_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "enemy_reaction_UI.h"
#include "enemy_confusion_UI.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CEnemy_Reaction_UI::CEnemy_Reaction_UI(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CEnemy_Reaction_UI::~CEnemy_Reaction_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy_Reaction_UI::Init()
{
	//親クラスの初期化
	CBillboard::Init();
	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy_Reaction_UI::Uninit()
{
	//親クラスの終了
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CEnemy_Reaction_UI::Update()
{
	//親クラスの更新
	CBillboard::Update();

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

//=============================================
//描画
//=============================================
void CEnemy_Reaction_UI::Draw()
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
CEnemy_Reaction_UI* CEnemy_Reaction_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, REACTION type)
{
	CEnemy_Reaction_UI* pReactionUI = nullptr;
	
	switch (type)
	{
	case CEnemy_Reaction_UI::REACTION_RELOAD:
		break;
	case CEnemy_Reaction_UI::REACTION_CONFUSION:
		pReactionUI = new CEnemy_Confusion_UI;
		break;
	case CEnemy_Reaction_UI::REACTION_STAN:
		break;
	default:
		assert(false);
		break;
	}
	if (pReactionUI == nullptr) { return nullptr; }

	pReactionUI->SetPos(pos);
	pReactionUI->SetSize(size);

	pReactionUI->Init();
	return pReactionUI;
}
