//=============================================
//
//ゲームスコア処理「game_scorer.cpp」
// Author松田永久
//
//=============================================
#include "game_score.h"
#include "player.h"

const float CGameScore::DIGIT_SHIFT = 40.0f;

const D3DXVECTOR3 CGameScore::BOX_POS = { 650.0f, 60.0f, 0.0f };
const D3DXVECTOR2 CGameScore::BOX_SIZE = { 400.0f, 80.0f };

const D3DXVECTOR3 CGameScore::DEATH_ICON_POS = { 750.0f, 55.0f, 0.0f };
const D3DXVECTOR2 CGameScore::DEATH_ICON_SIZE = { 50.0f, 30.0f };

const D3DXVECTOR3 CGameScore::NUM_DEATH_POS = { 845.0f, 55.0f, 0.0f };
const D3DXVECTOR2 CGameScore::NUM_DEATH_SIZE = { 20.0f, 30.0f };

const D3DXVECTOR3 CGameScore::SCORE_POS = { 650.0f, 55.0f, 0.0f };
const D3DXVECTOR2 CGameScore::SCORE_SIZE = { 20.0f, 30.0f };

//=============================================
//コンストラクタ
//=============================================
CGameScore::CGameScore():
m_pDeathCnt(),						//死亡数カウント数字ポインタ初期化
m_pPlayerUIBox(),					//UIボックスのポインタ初期化
m_pDeathIcon(),						//死亡アイコン初期化
m_DeathCntPos({0.0f,0.0f,0.0f})		//死亡数の位置
{
}

//=============================================
//デストラクタ
//=============================================
CGameScore::~CGameScore()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGameScore::Init()
{
	//初期位置代入
	m_DeathCntPos = NUM_DEATH_POS;
	//Uiの枠生成
	if (m_pPlayerUIBox == nullptr)
	{
		m_pPlayerUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE, { 1.0f,1.0f,1.0f,1.0f }, CPlayerUIBox::BOX_TYPE::BOX_TYPE_SCORE);
	}

	//死亡アイコン生成
	if (m_pDeathIcon == nullptr)
	{
		m_pDeathIcon = CDeathIcon::Create(DEATH_ICON_POS, DEATH_ICON_SIZE, { 1.0f,1.0f,1.0f,1.0f });
	}

	for (int nCnt = 0; nCnt < DEATH_DIGIT; nCnt++)
	{
		if (m_pDeathCnt[nCnt] == nullptr)
		{
			m_pDeathCnt[nCnt] = CNumber_2D::Create(m_DeathCntPos, NUM_DEATH_SIZE);
			//座標をずらす
			m_DeathCntPos.x -= DIGIT_SHIFT;
		}
	}

	CScore::SetPos(SCORE_POS);

	CScore::SetSize(SCORE_SIZE);

	CScore::SetDigitShift(DIGIT_SHIFT);

	CScore::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGameScore::Uninit()
{
	for (int nCnt = 0; nCnt < DEATH_DIGIT; nCnt++)
	{
		if (m_pDeathCnt[nCnt] != nullptr)
		{
			m_pDeathCnt[nCnt]->Uninit();
			m_pDeathCnt[nCnt] = nullptr;
		}
	}

	if (m_pPlayerUIBox != nullptr)
	{
		m_pPlayerUIBox->Uninit();
		m_pPlayerUIBox = nullptr;
	}

	if (m_pDeathIcon != nullptr)
	{
		m_pDeathIcon->Uninit();
		m_pDeathIcon = nullptr;
	}

	CScore::Uninit();
}

//=============================================
//更新
//=============================================
void CGameScore::Update()
{
	CScore::Update();

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

				SetDeathCntUI(pplayer->GetDeathCnt());
			}
		}
	}
}

//=============================================
//死亡数設定
//=============================================
void CGameScore::SetDeathCntUI(int nDeathCnt)
{
	//テクスチャ座標設定
	int a_PosTexU[DEATH_DIGIT];

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < DEATH_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = nDeathCnt / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = DEATH_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pDeathCnt[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
