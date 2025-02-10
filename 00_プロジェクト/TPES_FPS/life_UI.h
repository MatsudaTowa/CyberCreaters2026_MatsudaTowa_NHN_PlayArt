//=============================================
//
//体力表示「life_UI.h」
// Author松田永久
//
//=============================================
#ifndef _LIFE_UI_H_ //これが定義されてないとき
#define _LIFE_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_UI_box.h"
#include "gauge.h"

//=============================================
//体力表示クラス
//=============================================
class CLife_UI
{
public:
	static const int NUM_DIGIT = 3;  //桁数
	static const float DIGIT_SHIFT;  //桁ごとに座標をずらす

	CLife_UI();
	~CLife_UI();
	HRESULT Init();
	void Uninit();
	void Update();
	int m_nLife; //体力の値
	void SetLife_UI(int nLife);

	void SetNumber(int nLife);

private:
	static const D3DXVECTOR3 BOX_POS; //枠の位置
	static const D3DXVECTOR2 BOX_SIZE; //枠のサイズ

	static const D3DXVECTOR3 GAUGE_POS; //ゲージの位置
	static const D3DXVECTOR2 GAUGE_SIZE; //ゲージのサイズ

	static const D3DXVECTOR3 NUM_POS; //数字の位置
	static const D3DXVECTOR2 NUM_SIZE; //数字のサイズ
	CNumber_2D* m_pNumber[NUM_DIGIT];
	CPlayerUIBox* m_pUIBox;
	CGauge_2D*m_pGauge;
	D3DXVECTOR3 m_NumPos;
};

#endif // DEBUG