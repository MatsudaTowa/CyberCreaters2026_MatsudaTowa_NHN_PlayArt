//=============================================
//
//スモーク状況表示「smoke_UI.cpp」
// Author松田永久
//
//=============================================
#include "smoke_UI.h"

//桁ごとにずらす
const float CSmoke_UI::DIGIT_SHIFT = 35.0f;

const D3DXVECTOR3 CSmoke_UI::BOX_POS = { 1150.0f, 565.0f, 0.0f };
const D3DXVECTOR2 CSmoke_UI::BOX_SIZE = { 50.0f, 50.0f };

const D3DXVECTOR3 CSmoke_UI::ICON_POS = { 1150.0f,565.0f,0.0f };
const D3DXVECTOR2 CSmoke_UI::ICON_SIZE = { 40.0f, 40.0f };

const D3DXVECTOR3 CSmoke_UI::NUMBER_POS = { 1000.0f, 565.0f, 0.0f };
const D3DXVECTOR2 CSmoke_UI::NUMBER_SIZE = { 20.0f, 30.0f };

const D3DXVECTOR3 CSmoke_UI::KEY_UI_POS = { 1150.0f,600.0f,0.0f };
const D3DXVECTOR2 CSmoke_UI::KEY_UI_SIZE = { 18.0f, 18.0f };

//=============================================
//コンストラクタ
//=============================================
CSmoke_UI::CSmoke_UI():
m_SmokePos({0.0f,0.0f,0.0f}),	//スモークの位置初期化
m_NumSmoke(0),					//スモークの数初期化
m_pCurrentSmoke(),				//現在のスモークの数のポインタ初期化
m_pUIBox(),						//UIの枠初期化
m_pIcon(),						//アイコンの初期化
m_pkeyboard_UI()				//キーボードの初期化
{
}

//=============================================
//デストラクタ
//=============================================
CSmoke_UI::~CSmoke_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmoke_UI::Init(CPlayer* player)
{
	m_SmokePos = NUMBER_POS;

	//UIの枠生成
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CPlayerUIBox::BOX_TYPE::BOX_TYPE_LIFE);
	}

	//UIの枠生成
	if (m_pIcon == nullptr)
	{
		m_pIcon = CSmokeIcon::Create(ICON_POS, ICON_SIZE, { 1.0f,1.0f,1.0f,1.0f });
	}

	//キーボードUIの枠生成
	if (m_pkeyboard_UI == nullptr)
	{
		m_pkeyboard_UI = CKeyboard_UI::Create(KEY_UI_POS, KEY_UI_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CKeyboard_UI::KEY_Q);
	}

	//数字生成
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pCurrentSmoke[nCnt] == nullptr)
		{
			m_pCurrentSmoke[nCnt] = CNumber_2D::Create(m_SmokePos, NUMBER_SIZE);
			//座標をずらす
			m_SmokePos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmoke_UI::Uninit()
{
	//UIの枠破棄
	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Uninit();
		m_pUIBox = nullptr;
	}

	//キーボードUIのアイコン破棄
	if (m_pIcon != nullptr)
	{
		m_pIcon->Uninit();
		m_pIcon = nullptr;
	}

	//UIのアイコン破棄
	if (m_pkeyboard_UI != nullptr)
	{
		m_pkeyboard_UI->Uninit();
		m_pkeyboard_UI = nullptr;
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//数字破棄
		if (m_pCurrentSmoke[nCnt] != nullptr)
		{
			m_pCurrentSmoke[nCnt]->Uninit();
			m_pCurrentSmoke[nCnt] = nullptr;
		}
	}

	delete this;
}

//=============================================
//更新
//=============================================
void CSmoke_UI::Update()
{
}

//=============================================
//現在のUIの設定
//=============================================
void CSmoke_UI::SetCurrentSmoke_UI(CPlayer* player)
{
	if (player->GetSmoke())
	{//スモークを使っていたら
		m_pIcon->SetColor({ 0.2f,0.2f,0.2f,1.0f });
	}
	else if (!player->GetSmoke())
	{//スモークを使っていなかったら
		m_pIcon->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	}
}

//=============================================
//数字設定
//=============================================
void CSmoke_UI::SetNumber(int nParcent)
{
}

//=============================================
//初期状態に
//=============================================
void CSmoke_UI::Reset()
{
}
