//=============================================
//
//チュートリアル表示「tutorial_UI.h」
// Author松田永久
//
//=============================================
#ifndef _TUTORIAL_UI_H_ //これが定義されてないとき
#define _TUTORIAL_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "action_UI.h"
#include "keyboard_UI.h"
#include "mouse_UI.h"

class CPlayer;
//=============================================
//チュートリアルUIクラス
//=============================================
class CTutorial_UI
{
public:
	CTutorial_UI();
	~CTutorial_UI();
	HRESULT Init();
	void Uninit();
	void Update();
private:
	static const float PARCENT_DIGIT_SHIFT;  //桁ごとに座標をずらす

	static const D3DXVECTOR3 RELOAD_TXT_POS; //リロードアイコンの位置
	static const D3DXVECTOR2 RELOAD_TXT_SIZE; //リロードアイコンのサイズ

	static const D3DXVECTOR3 SHOT_MODE_TXT_POS; //ショットの位置
	static const D3DXVECTOR2 SHOT_MODE_TXT_SIZE; //ショットのサイズ

	static const D3DXVECTOR3 SHOT_TXT_POS; //ショットの位置
	static const D3DXVECTOR2 SHOT_TXT_SIZE; //ショットのサイズ

	static const D3DXVECTOR3 RELOAD_TXT_POS; //リロードアイコンの位置
	static const D3DXVECTOR2 RELOAD_TXT_SIZE; //リロードアイコンのサイズ

	static const D3DXVECTOR3 KEY_UI_POS; //キーボードのUIの位置
	static const D3DXVECTOR2 KEY_UI_SIZE; //キーボードのUIのサイズ

	static const D3DXVECTOR3 MOUSE_SHOT_MODE_UI_POS; //マウスのUIの位置
	static const D3DXVECTOR2 MOUSE_UI_SIZE; //マウスのUIのサイズ

	static const D3DXVECTOR3 MOUSE_SHOT_UI_POS; //マウスのUIの位置
	
	CAction_UI* m_pReloadUI;
	CAction_UI* m_pShotModeUI;
	CAction_UI* m_pShotUI;
	CKeyboard_UI* m_pKeyboardReload_UI;
	CMouse_UI* m_pMouseshot_UI;
	CMouse_UI* m_pMouseshotmode_UI;
};

#endif // DEBUG