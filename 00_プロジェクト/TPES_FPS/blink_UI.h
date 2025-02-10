//=============================================
//
//ブリンク表示「blink_UI.h」
// Author松田永久
//
//=============================================
#ifndef _BLINK_UI_H_ //これが定義されてないとき
#define _BLINK_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player.h"
#include "player_UI_box.h"
#include "blink_icon.h"
#include "keyboard_UI.h"
#include "blink_back_UI.h"

class CPlayer;
//=============================================
//残弾数表示クラス
//=============================================
class CBlink_UI
{
public:
	CBlink_UI();
	~CBlink_UI();
	HRESULT Init(CPlayer* player);
	void Uninit();
	void Update();
	void SetCurrentBlink_UI(CPlayer* player);

	void SetNumber(int nParcent);

	void Reset();

private:
	static const int NUM_DIGIT = 1;  //桁数
	static const float DIGIT_SHIFT;  //桁ごとに座標をずらす

	static const D3DXVECTOR3 BOX_POS; //枠の位置
	static const D3DXVECTOR2 BOX_SIZE; //枠のサイズ

	static const D3DXVECTOR3 BLINK_BACK_POS; //ブリンクのナンバーの背景の位置
	static const D3DXVECTOR2 BLINK_BACK_SIZE; //ブリンクのナンバーの背景のサイズ

	static const D3DXVECTOR3 ICON_POS; //スモークアイコンの位置
	static const D3DXVECTOR2 ICON_SIZE; //スモークアイコンのサイズ

	static const D3DXVECTOR3 NUMBER_POS; //数字の位置
	static const D3DXVECTOR2 NUMBER_SIZE; //数字のサイズ

	static const D3DXVECTOR3 KEY_UI_POS; //キーボードのUIの位置
	static const D3DXVECTOR2 KEY_UI_SIZE; //キーボードのUIのサイズ

	D3DXVECTOR3 m_BlinkUIPos;
	int m_NumBlink;
	CBlinkIcon* m_pIcon;
	CPlayerUIBox* m_pUIBox;
	CKeyboard_UI* m_pkeyboard_UI;
	CNumber_2D* m_pCurrentBlink[NUM_DIGIT];
	CBlinkBackUI* m_pBlinkBackUI;
};

#endif // DEBUG