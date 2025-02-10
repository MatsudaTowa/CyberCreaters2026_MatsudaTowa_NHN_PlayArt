//=============================================
//
//3DTemplate[game.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"
#include "dash_effect.h"
#include "player.h"

const std::string CGame::BLOCK_FILE = "data\\FILE\\block.txt";

//プレイヤー
CPlayer*CGame::m_pPlayer = nullptr;

//ウェーブ
CWave*CGame::m_pWave = nullptr;

CGame::GAME_STATE CGame::m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

//=============================================
//コンストラクタ
//=============================================
CGame::CGame():m_nResultDelay(0),m_bEdit(false), m_next_wave()
{//イニシャライザーでプライオリティ設定、エディットしてない状態に変更
	//読み込むブロックの情報初期化
	m_LoadBlock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.type = CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT;
}

//=============================================
//デストラクタ
//=============================================
CGame::~CGame()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGame::Init()
{
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
	m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

	if (m_pWave == nullptr)
	{
		m_pWave = new CWave;
		m_pWave->Init();
	}

	//プレイヤー生成
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	SetWave(CWave::WAVE::ONE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGame::Uninit()
{
	CManager::GetInstance()->GetSound()->StopSound();
	m_GameState = GAME_STATE_NORMAL;

	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		m_pWave = nullptr;
	}

	CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CGame::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	if (CEnemy::m_NumEnemy <= 0)
	{//敵がいなくなったらウェーブ遷移
		switch (CWave::GetCurrentWave())
		{
		case CWave::WAVE::ONE:
			m_next_wave = CWave::WAVE::TWO;
			break;
		case CWave::WAVE::TWO:
			m_next_wave = CWave::WAVE::THREE;
			break;
		case CWave::WAVE::THREE:
			m_next_wave = CWave::WAVE::BOSS;
			break;
		case CWave::WAVE::BOSS:
			m_next_wave = CWave::WAVE::NONE;
			break;
		case CWave::WAVE::NONE:

			break;
		default:
			break;
		}

		if (CWave::GetCurrentWave() != CWave::WAVE::RESULT)
		{
			m_nResultDelay++;
			if (m_nResultDelay > 60)
			{
				m_nResultDelay = 0;

				//死んだ数分だけスコアマイナス
				ApplyDeathPenalty();

				//現在のスコアを書き出し
				m_pWave->WaveResult(&CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1]);
				SetWave(CWave::WAVE::RESULT, m_next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
			}
		}
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_TAB))
	{
		m_next_wave = CWave::WAVE::BOSS;

		SetWave(CWave::WAVE::RESULT, m_next_wave, CManager::RESULT_SCORE_FILE[CWave::GetCurrentWave() - 1].c_str());
	}

#endif // _DEBUG

	
	if (m_pWave != nullptr)
	{
		m_pWave->Update();
	}
	
	//if (m_bEdit == false)
	//{


#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_F7))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TEST);
	}
#endif // _DEBUG

}

//=============================================
//死んだ数だけスコアマイナス
//=============================================
void CGame::ApplyDeathPenalty()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
		 //タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pplayer = dynamic_cast<CPlayer*>(pObj);

				for (int nCnt = 0; nCnt < pplayer->GetDeathCnt(); nCnt++)
				{
					CScore* pScore = CWave::GetScore();

					if (pScore->m_nScore > 0)
					{
						//TODO:ADDやめろ
						pScore->AddScore(-50);

						if (pScore->m_nScore <= 0)
						{//0を下回ったら
							//スコア0に
							pScore->m_nScore = 0;
						}
					}
				}
			}
		}
	}
}

//=============================================
//描画
//=============================================
void CGame::Draw()
{
}

//=============================================
//プレイヤー取得
//=============================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

//=============================================
//ウェーブ取得
//=============================================
CWave* CGame::GetWave()
{
	return m_pWave;
}

//=============================================
//ウェーブ設定
//=============================================
void CGame::SetWave(CWave::WAVE wave)
{
	//ウェーブ終了
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//ウェーブ切り替え
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave);
	}
}

//=============================================
//ウェーブ設定
//=============================================
void CGame::SetWave(CWave::WAVE wave, CWave::WAVE next_wave,const char* ResultFile)
{
	//ウェーブ終了
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//ウェーブ切り替え
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave, next_wave, ResultFile);
	}
}

//=============================================
//ゲームの状態取得
//=============================================
CGame::GAME_STATE& CGame::GetState()
{
	return m_GameState;
}

//=============================================
//ブロック読み込み
//=============================================
void CGame::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[BLOCK_TXT_MAX];
	char aEqual[BLOCK_TXT_MAX]; //[＝]読み込み用
	int nNumBlock; //ブロックの数

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

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumBlock);
		}
		if (!strcmp(aDataSearch, "BLOCKSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_BLOCKSET"))
				{
					//エネミー生成
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot,1,false);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.pos.x,
						&m_LoadBlock.pos.y,
						&m_LoadBlock.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.rot.x,
						&m_LoadBlock.rot.y,
						&m_LoadBlock.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadBlock.type);
				}
			}
		}
	}
}
