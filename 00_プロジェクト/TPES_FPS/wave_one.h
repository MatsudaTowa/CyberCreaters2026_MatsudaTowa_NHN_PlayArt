//=============================================
//
//1ウェーブ処理[wave_one.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_ONE_H_ //これが定義されてないとき

#define _WAVE_ONE_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"

//=============================================
//  1ウェーブクラス定義
//=============================================
class CWave_One :public CWave
{
public:
	static const std::string WAVE_1_ENEMY_FILE;	//ウェーブ1のエネミーのファイル
	static const std::string WAVE_1_BLOCK_FILE;	//ウェーブ1のブロックのファイル
	static const std::string WAVE_1_WALL_FILE;	//ウェーブ1の壁のファイル

	CWave_One();
	~CWave_One()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
};

#endif

