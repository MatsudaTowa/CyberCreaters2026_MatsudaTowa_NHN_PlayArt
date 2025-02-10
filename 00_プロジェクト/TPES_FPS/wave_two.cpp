//=============================================
//
//2ウェーブ処理[wave_two.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_two.h"

const std::string CWave_Two::WAVE_2_ENEMY_FILE = "data\\FILE\\enemy_001.txt";
const std::string CWave_Two::WAVE_2_BLOCK_FILE = "data\\FILE\\block_data000.bin";
const std::string CWave_Two::WAVE_2_WALL_FILE = "data\\FILE\\wall_001.txt";

//=============================================
//コンストラクタ
//=============================================
CWave_Two::CWave_Two()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_Two::~CWave_Two()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Two::Init()
{
	CWave::Init();

	CWave::LoadBlock(&WAVE_2_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_2_ENEMY_FILE);
	CWave::LoadWall(&WAVE_2_WALL_FILE);
	//地面生成
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 1000.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Two::Uninit()
{
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_Two::Update()
{
	CWave::Update();
}
