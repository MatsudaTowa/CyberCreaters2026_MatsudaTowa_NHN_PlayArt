//=============================================
//
//3ウェーブ処理[wave_three.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_THREE_H_ //これが定義されてないとき

#define _WAVE_THREE_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"

//=============================================
//  3ウェーブクラス定義
//=============================================
class CWave_Three :public CWave
{
public:
	static const std::string WAVE_3_ENEMY_FILE;	//ウェーブ3のエネミーのファイル
	static const std::string WAVE_3_BLOCK_FILE;	//ウェーブ3のブロックのファイル
	static const std::string WAVE_3_WALL_FILE;	//ウェーブ3の壁のファイル

	CWave_Three();
	~CWave_Three()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
};

#endif

