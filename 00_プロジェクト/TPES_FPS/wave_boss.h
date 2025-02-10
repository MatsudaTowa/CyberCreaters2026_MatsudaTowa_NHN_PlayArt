//=============================================
//
//ボスウェーブ処理[wave_boss.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_BOSS_H_ //これが定義されてないとき

#define _WAVE_BOSS_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"
#include "move_point.h"

//=============================================
//  ボスウェーブクラス定義
//=============================================
class CWave_Boss :public CWave
{
public:
	static const std::string WAVE_BOSS_ENEMY_FILE;	//ウェーブボスのエネミーのファイル
	static const std::string WAVE_BOSS_BLOCK_FILE;	//ウェーブボスのブロックのファイル
	static const std::string WAVE_BOSS_WALL_FILE;	//ウェーブボスの壁のファイル
	static const std::string WAVE_BOSS_POINT_FILE;	//ウェーブボスポイントのファイル

	static const int NUM_POINT = 12;

	CWave_Boss();
	~CWave_Boss()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	//移動先取得
	static CMovePoint* GetMovePoint(int Idx);
private:
	void LoadPoint(const std::string* pFileName);
	static CMovePoint* m_pMovePoint[NUM_POINT];
};

#endif

