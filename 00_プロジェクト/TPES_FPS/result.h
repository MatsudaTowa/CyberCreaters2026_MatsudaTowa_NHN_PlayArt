//=============================================
//
//3DTemplate[result.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _RESULT_H_ //‚±‚ê‚ª’è‹`‚³‚ê‚Ä‚È‚¢‚Æ‚«

#define _RESULT_H_
#include "main.h"
#include "scene.h"
#include "score.h"
#include "manager.h"

class CResult :public CScene
{
public:
	CResult();
	~CResult() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	int LoadScore(const char* FileName);

private:
	static const char* WAVE_RESULT_FILE[CManager::NUM_RESULT_FILE];
	static const D3DXVECTOR3 SCORE_POS[CManager::NUM_RESULT_FILE + 1];
	static const D3DXVECTOR2 SCORE_SIZE[2];
	static const float DIGIT_SHIFT[2];
	CScore* m_pScore[CManager::NUM_RESULT_FILE + 1];
};
#endif