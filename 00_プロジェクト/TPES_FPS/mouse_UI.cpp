#include "mouse_UI.h"
#include "manager.h"

//=============================================
//テクスチャパス
//=============================================
const std::string CMouse_UI::TEXTURE_NAME[CMouse_UI::MOUSE_MAX]
{
	"data\\TEXTURE\\mouseUI_L.png",
	"data\\TEXTURE\\mouseUI_R.png",
};

//=============================================
//コンストラクタ
//=============================================
CMouse_UI::CMouse_UI(int nPriority):CObject2D(nPriority), m_type()
{
}

//=============================================
//デストラクタ
//=============================================
CMouse_UI::~CMouse_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CMouse_UI::Init()
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
void CMouse_UI::Uninit()
{
	//終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CMouse_UI::Update()
{
	//更新
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CMouse_UI::Draw()
{
	//描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CMouse_UI* CMouse_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, MOUSE_TYPE type)
{
	CMouse_UI* pMouse_UI = new CMouse_UI;

	if (pMouse_UI == nullptr) { return nullptr; }

	pMouse_UI->SetPos(pos);
	pMouse_UI->SetSize(size);
	pMouse_UI->SetColor(col);
	pMouse_UI->m_type = type;

	pMouse_UI->Init();

	return pMouse_UI;
}
