//=============================================
//
//ウェーブごとの結果[wave_result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wave_result.h"
#include "manager.h"
#include "game.h"

//=============================================
//コンストラクタ
//=============================================
CWave_Result::CWave_Result(): m_pScreen(),m_nScore()
{
}

//=============================================
//デストラクタ
//=============================================
CWave_Result::~CWave_Result()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWave_Result::Init()
{
	m_pScreen = nullptr;

	if (m_pScreen == nullptr)
	{
		m_pScreen = CWave_Result_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	LoadScore(m_ResultFile);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CWave_Result::Uninit()
{
	if (m_pScreen != nullptr)
	{
		m_pScreen->Uninit();
		m_pScreen = nullptr;
	}
	CWave::Uninit();
}

//=============================================
//更新
//=============================================
void CWave_Result::Update()
{
	if (m_pScreen != nullptr)
	{
		m_pScreen->Update();
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN)
		|| CManager::GetInstance()->GetMouse()->GetTrigger(0))
	{
		if (m_next != WAVE::NONE)
		{
			CGame::SetWave(m_next);
		}
		else
		{
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_RESULT);
		}
	}
	CWave::Update();
}

//=============================================
//次のウェーブ設定
//=============================================
void CWave_Result::SetNextWave(CWave::WAVE wave)
{
	m_next = wave;
}

//=============================================
//スコアロード
//=============================================
void CWave_Result::LoadScore(const char* pFileName)
{
	//ファイルの読み込み
	FILE* pFile = fopen(pFileName, "rb");

	int nScore = 0; //返すスコア

	if (pFile != NULL)
	{
		//スコアの読み込み
		fread(&nScore, sizeof(int), 1, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}

	else
	{
		return;
	}

	m_nScore = nScore;

	m_pScore->AddScore(m_nScore);
}
