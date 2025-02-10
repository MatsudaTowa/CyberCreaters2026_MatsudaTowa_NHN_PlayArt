//=============================================
//
//ゲームスコア処理「game_scorer.h」
// Author松田永久
//
//=============================================
#ifndef _GAME_SCORE_H_ //これが定義されてないとき
#define _GAME_SCORE_H_
#include "main.h"
#include "object2D.h"
#include "score.h"
#include "death_icon.h"

//=============================================
//スコアクラス
//=============================================
class CGameScore : public CScore
{
public:
	CGameScore();
	~CGameScore() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
private:
	static const float DIGIT_SHIFT;
	static const int DEATH_DIGIT = 2;

	static const D3DXVECTOR3 BOX_POS; //枠の位置
	static const D3DXVECTOR2 BOX_SIZE; //枠のサイズ

	static const D3DXVECTOR3 DEATH_ICON_POS; //死亡アイコンの位置
	static const D3DXVECTOR2 DEATH_ICON_SIZE; //死亡アイコンのサイズ

	static const D3DXVECTOR3 NUM_DEATH_POS; //死亡数の位置
	static const D3DXVECTOR2 NUM_DEATH_SIZE; //死亡数のサイズ

	static const D3DXVECTOR3 SCORE_POS; //スコアの位置
	static const D3DXVECTOR2 SCORE_SIZE; //スコアのサイズ

	void SetDeathCntUI(int nDeathCnt);

	CNumber_2D* m_pDeathCnt[DEATH_DIGIT];
	CPlayerUIBox* m_pPlayerUIBox;
	CDeathIcon* m_pDeathIcon;

	D3DXVECTOR3 m_DeathCntPos;
};

#endif // DEBUG
