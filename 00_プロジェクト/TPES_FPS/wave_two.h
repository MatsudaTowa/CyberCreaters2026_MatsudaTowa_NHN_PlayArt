//=============================================
//
//2ウェーブ処理[wave_two.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_TWO_H_ //これが定義されてないとき

#define _WAVE_TWO_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"

//=============================================
//  2ウェーブクラス定義
//=============================================
class CWave_Two :public CWave
{
public:
	static const std::string WAVE_2_ENEMY_FILE;	//ウェーブ2のエネミーのファイル
	static const std::string WAVE_2_BLOCK_FILE;	//ウェーブ2のブロックのファイル
	static const std::string WAVE_2_WALL_FILE;	//ウェーブ2の壁のファイル

	CWave_Two();
	~CWave_Two()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
};

#endif

