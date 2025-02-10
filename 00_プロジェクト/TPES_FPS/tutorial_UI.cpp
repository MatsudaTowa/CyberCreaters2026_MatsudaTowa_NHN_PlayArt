//=============================================
//
//チュートリアル表示「tutorial_UI.cpp」
// Author松田永久
//
//=============================================
#include "tutorial_UI.h"

const D3DXVECTOR3 CTutorial_UI::KEY_UI_POS = { 1050.0f,200.0f,0.0f };
const D3DXVECTOR2 CTutorial_UI::KEY_UI_SIZE = { 30.0f, 30.0f };

const D3DXVECTOR3 CTutorial_UI::RELOAD_TXT_POS = { 1160.0f,200.0f,0.0f };
const D3DXVECTOR2 CTutorial_UI::RELOAD_TXT_SIZE = { 100.0f, 50.0f };

const D3DXVECTOR3 CTutorial_UI::SHOT_MODE_TXT_POS = { 1170.0f,300.0f,0.0f };
const D3DXVECTOR2 CTutorial_UI::SHOT_MODE_TXT_SIZE = { 95.0f, 50.0f };

const D3DXVECTOR3 CTutorial_UI::SHOT_TXT_POS = { 1170.0f,400.0f,0.0f };
const D3DXVECTOR2 CTutorial_UI::SHOT_TXT_SIZE = { 90.0f, 40.0f };

const D3DXVECTOR3 CTutorial_UI::MOUSE_SHOT_MODE_UI_POS = { 1050.0f,300.0f,0.0f };
const D3DXVECTOR3 CTutorial_UI::MOUSE_SHOT_UI_POS = { 1050.0f,400.0f,0.0f };
const D3DXVECTOR2 CTutorial_UI::MOUSE_UI_SIZE = { 30.0f, 30.0f };
//=============================================
//コンストラクタ
//=============================================
CTutorial_UI::CTutorial_UI():m_pKeyboardReload_UI(), m_pReloadUI(), m_pMouseshot_UI(), m_pMouseshotmode_UI()
, m_pShotUI(), m_pShotModeUI()
{
}

//=============================================
//デストラクタ
//=============================================
CTutorial_UI::~CTutorial_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTutorial_UI::Init()
{
	//UIの枠生成
	if (m_pKeyboardReload_UI == nullptr)
	{
		m_pKeyboardReload_UI = CKeyboard_UI::Create(KEY_UI_POS, KEY_UI_SIZE, {1.0f,1.0f,1.0f,1.0f}, CKeyboard_UI::KEY_R);
	}

	if (m_pReloadUI == nullptr)
	{
		m_pReloadUI = CAction_UI::Create(RELOAD_TXT_POS, RELOAD_TXT_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CAction_UI::ACTION_RELOAD);
	}

	if (m_pShotModeUI == nullptr)
	{
		m_pShotModeUI = CAction_UI::Create(SHOT_MODE_TXT_POS, SHOT_MODE_TXT_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CAction_UI::ACTION_SHOTMODE);
	}

	if (m_pShotUI == nullptr)
	{
		m_pShotUI = CAction_UI::Create(SHOT_TXT_POS, SHOT_TXT_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CAction_UI::ACTION_SHOT);
	}

	if (m_pMouseshotmode_UI == nullptr)
	{
		m_pMouseshotmode_UI = CMouse_UI::Create(MOUSE_SHOT_MODE_UI_POS, MOUSE_UI_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CMouse_UI::MOUSE_L);
	}

	if (m_pMouseshot_UI == nullptr)
	{
		m_pMouseshot_UI = CMouse_UI::Create(MOUSE_SHOT_UI_POS, KEY_UI_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CMouse_UI::MOUSE_R);
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CTutorial_UI::Uninit()
{
	if (m_pKeyboardReload_UI != nullptr)
	{
		m_pKeyboardReload_UI->Uninit();
		m_pKeyboardReload_UI = nullptr;
	}

	if (m_pReloadUI != nullptr)
	{
		m_pReloadUI->Uninit();
		m_pReloadUI = nullptr;
	}

	if (m_pMouseshotmode_UI != nullptr)
	{
		m_pMouseshotmode_UI->Uninit();
		m_pMouseshotmode_UI = nullptr;
	}

	if (m_pMouseshot_UI != nullptr)
	{
		m_pMouseshot_UI->Uninit();
		m_pMouseshot_UI = nullptr;
	}
	delete this;
}

//=============================================
//更新
//=============================================
void CTutorial_UI::Update()
{
	if (m_pKeyboardReload_UI != nullptr)
	{
		m_pKeyboardReload_UI->Update();
	}

	if (m_pReloadUI != nullptr)
	{
		m_pReloadUI->Update();
	}

	if (m_pMouseshotmode_UI != nullptr)
	{
		m_pMouseshotmode_UI->Update();
	}

	if (m_pMouseshot_UI != nullptr)
	{
		m_pMouseshot_UI->Update();
	}
}
