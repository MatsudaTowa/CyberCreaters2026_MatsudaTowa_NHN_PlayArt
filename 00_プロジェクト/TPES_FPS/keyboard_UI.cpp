//=============================================
//
//キーボードUIの表記[keyboard_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "keyboard_UI.h"
#include "manager.h"

//=============================================
//テクスチャパス
//=============================================
const std::string CKeyboard_UI::TEXTURE_NAME[CKeyboard_UI::KEY_MAX]
{
	"data\\TEXTURE\\keyboard_W.png",
	"data\\TEXTURE\\keyboard_A.png",
	"data\\TEXTURE\\keyboard_S.png",
	"data\\TEXTURE\\keyboard_D.png",
	"data\\TEXTURE\\keyboard_Q.png",
	"data\\TEXTURE\\keyboard_X.png",
	"data\\TEXTURE\\keyboard_R.png",
	"data\\TEXTURE\\keyboard_LSHIFT.png",
};

//=============================================
//コンストラクタ
//=============================================
CKeyboard_UI::CKeyboard_UI(int nPriority):CObject2D(nPriority),m_type()
{
}

//=============================================
//デストラクタ
//=============================================
CKeyboard_UI::~CKeyboard_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CKeyboard_UI::Init()
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
void CKeyboard_UI::Uninit()
{
	//終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CKeyboard_UI::Update()
{
	//更新
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CKeyboard_UI::Draw()
{
	//描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CKeyboard_UI* CKeyboard_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, KEY_TYPE key)
{
	CKeyboard_UI* pKeyboard_UI = new CKeyboard_UI;

	if (pKeyboard_UI == nullptr) { return nullptr; }

	pKeyboard_UI->SetPos(pos);
	pKeyboard_UI->SetSize(size);
	pKeyboard_UI->SetColor(col);
	pKeyboard_UI->m_type = key;

	pKeyboard_UI->Init();

	return pKeyboard_UI;
}
