//=============================================
//
//体力表示「life_UI.cpp」
// Author松田永久
//
//=============================================
#include "life_UI.h"
#include "manager.h"
#include "player.h"
//桁ごとにずらす
const float CLife_UI::DIGIT_SHIFT = 18.0f;

const D3DXVECTOR3 CLife_UI::BOX_POS ={ 200.0f, 665.0f, 0.0f };
const D3DXVECTOR2 CLife_UI::BOX_SIZE ={ 180.0f, 50.0f };

const D3DXVECTOR3 CLife_UI::GAUGE_POS = { 50.0f, 700.0f, 0.0f };
const D3DXVECTOR2 CLife_UI::GAUGE_SIZE = { 300.0f,30.0f };

const D3DXVECTOR3 CLife_UI::NUM_POS = { 100.0f, 650.0f, 0.0f };
const D3DXVECTOR2 CLife_UI::NUM_SIZE = { 10.0f, 18.0f };

//=============================================
//コンストラクタ
//=============================================
CLife_UI::CLife_UI() :m_nLife(0), m_pNumber(), m_pUIBox(), m_NumPos(), m_pGauge()
{
}

//=============================================
//デストラクタ
//=============================================
CLife_UI::~CLife_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CLife_UI::Init()
{
	m_NumPos = NUM_POS;

	//UIの枠生成
	if (m_pUIBox == nullptr)
	{
		m_pUIBox = CPlayerUIBox::Create(BOX_POS, BOX_SIZE,{ 1.0f,1.0f,1.0f,1.0f },CPlayerUIBox::BOX_TYPE::BOX_TYPE_LIFE);
	}

	//体力ゲージ生成
	if (m_pGauge == nullptr)
	{
		m_pGauge = CGauge_2D::Create(GAUGE_POS, GAUGE_SIZE, CGauge_2D::GAUGE2D_TYPE::GAUGE_TYPE_LIFE,{0.0f,1.0f,0.0f,1.0f});
	}

	//数字生成
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_NumPos, NUM_SIZE);
			//座標をずらす
			m_NumPos.x -= DIGIT_SHIFT;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CLife_UI::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}
	
	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Uninit();
		m_pUIBox = nullptr;
	}

	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}
}

//=============================================
//更新
//=============================================
void CLife_UI::Update()
{
	if (m_pUIBox != nullptr)
	{
		m_pUIBox->Update();
	}

	if (m_pGauge != nullptr)
	{
		m_pGauge->Update();
	}
}

//=============================================
//UIに設定
//=============================================
void CLife_UI::SetLife_UI(int nLife)
{
	SetNumber(nLife);

	float gaugeWidth = (nLife * GAUGE_SIZE.x) / CPlayer::PLAYER_LIFE;

	m_pGauge->SetGauge({ gaugeWidth , m_pGauge->GetSize().y});

	if (nLife >= CPlayer::PLAYER_LIFE * 0.6f)
	{
		m_pGauge->SetColor({ 0.0f,1.0f,0.0f,1.0f });
	}
	else if (nLife >= CPlayer::PLAYER_LIFE * 0.3f && nLife < CPlayer::PLAYER_LIFE * 0.6f)
	{
		m_pGauge->SetColor({ 1.0f,1.0f,0.0f,1.0f });
	}
	else if (nLife < CPlayer::PLAYER_LIFE * 0.3f)
	{
		m_pGauge->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	}
}

//=============================================
//数字設定
//=============================================
void CLife_UI::SetNumber(int nLife)
{
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = nLife / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
