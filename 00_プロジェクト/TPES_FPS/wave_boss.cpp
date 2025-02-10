//=============================================
//
//ボスウェーブ処理[wave_boss.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_boss.h"

const std::string CWave_Boss::WAVE_BOSS_ENEMY_FILE = "data\\FILE\\enemy_003.txt";
const std::string CWave_Boss::WAVE_BOSS_BLOCK_FILE = "data\\FILE\\block_data_boss.bin";
const std::string CWave_Boss::WAVE_BOSS_WALL_FILE = "data\\FILE\\wall_003.txt";
const std::string CWave_Boss::WAVE_BOSS_POINT_FILE = "data\\FILE\\boss_move_point.txt";

CMovePoint* CWave_Boss::m_pMovePoint[NUM_POINT] = {};
//=============================================
//コンストラクタ
//=============================================
CWave_Boss::CWave_Boss()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_Boss::~CWave_Boss()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Boss::Init()
{
	CWave::Init();

	CWave::LoadBlock(&WAVE_BOSS_BLOCK_FILE);
	CWave::LoadEnemy(&WAVE_BOSS_ENEMY_FILE);
	CWave::LoadWall(&WAVE_BOSS_WALL_FILE);
	LoadPoint(&WAVE_BOSS_POINT_FILE);
	//地面生成
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(900.0f, 0.0f, 900.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Boss::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_POINT; ++nCnt)
	{
		if (m_pMovePoint[nCnt] != nullptr)
		{
			m_pMovePoint[nCnt]->Uninit();
			m_pMovePoint[nCnt] = nullptr;
		}
	}
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_Boss::Update()
{
	CWave::Update();
}

//=============================================
//位置取得
//=============================================
CMovePoint* CWave_Boss::GetMovePoint(int Idx)
{
	return m_pMovePoint[Idx];
}

//=============================================
//ポイントの位置をロード
//=============================================
void CWave_Boss::LoadPoint(const std::string* pFileName)
{
	char aDataSearch[CWave::TXT_MAX];
	char aEqual[CWave::TXT_MAX]; //[＝]読み込み用
	int nNumPoint; //ポイントの数
	int nCntPoint = 0;

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//種類の情報のデータファイルが開けなかった場合
		//処理を終了する
		return;
	}
	//ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //検索

		if (!strcmp(aDataSearch, "END"))
		{//読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_POINT"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumPoint);
		}
		if (!strcmp(aDataSearch, "POINTSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_POINTSET"))
				{
					//移動ポイント生成
					m_pMovePoint[nCntPoint] = CMovePoint::Create(m_LoadPoint.pos);
					++nCntPoint;
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadPoint.pos.x,
						&m_LoadPoint.pos.y,
						&m_LoadPoint.pos.z);
				}
			}
		}
	}
}
