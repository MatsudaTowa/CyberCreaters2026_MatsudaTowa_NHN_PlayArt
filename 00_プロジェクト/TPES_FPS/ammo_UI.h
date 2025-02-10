//=============================================
//
//残弾数表示「ammo_UI.h」
// Author松田永久
//
//=============================================
#ifndef _AMMO_UI_H_ //これが定義されてないとき
#define _AMMO_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player.h"
#include "player_UI_box.h"

//=============================================
//残弾数表示クラス
//=============================================
class CAmmo_UI
{
public:
	CAmmo_UI();
	~CAmmo_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCurrentAmmo_UI(int nAmmo);
	void SetDefaultAmmo_UI(int nAmmo);

private:
	static const int NUM_DIGIT = 2;  //桁数
	static const float CURRENT_AMMO_DIGIT_SHIFT;  //桁ごとに座標をずらす
	static const float DEFAULT_AMMO_DIGIT_SHIFT;  //桁ごとに座標をずらす

	static const D3DXVECTOR3 BOX_POS; //枠の位置
	static const D3DXVECTOR2 BOX_SIZE; //枠のサイズ

	static const D3DXVECTOR3 CURRENT_AMMO_POS; //現在の弾数の位置
	static const D3DXVECTOR2 CURRENT_AMMO_SIZE; //現在の弾数のサイズ

	static const D3DXVECTOR3 DEFAULT_AMMO_POS; //通常の弾数の位置
	static const D3DXVECTOR2 DEFAULT_AMMO_SIZE; //通常の弾数のサイズ

	int m_nDefaultAmmo; //残弾数の値
	D3DXVECTOR3 m_CurrentAmmoPos;
	D3DXVECTOR3 m_DefaultAmmoPos;
	CPlayerUIBox* m_pUIBox;
	CNumber_2D* m_pCurrentAmmo[NUM_DIGIT];
	CNumber_2D* m_pDefaultAmmo[NUM_DIGIT];
};

#endif // DEBUG