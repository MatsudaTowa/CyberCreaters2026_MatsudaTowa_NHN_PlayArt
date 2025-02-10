//=============================================
//
//アルティメット[ult.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "ult.h"
#include "ult_range.h"

//=============================================
//コンストラクタ
//=============================================
CUlt::CUlt():
m_CoolTimeCnt(0),	//カウント0に
m_CoolTime(0),		//クールタイム0に
m_isFinish(false)	//終わっていない状態に
{
}

//=============================================
//デストラクタ
//=============================================
CUlt::~CUlt()
{
}

//=============================================
//初期化
//=============================================
HRESULT CUlt::Init()
{
	return S_OK;
}

//=============================================
//終了
//=============================================
void CUlt::Uninit()
{
	delete this;
}

//=============================================
//更新
//=============================================
void CUlt::Update()
{
	if (m_CoolTimeCnt < m_CoolTime)
	{
		++m_CoolTimeCnt;
	}
	else if (m_CoolTimeCnt >= m_CoolTime)
	{//クールタイムに到達したら
		//終了してない状態に
		m_isFinish = false;
	}
}

const float CMediumUlt::FLYING_HIGHT = 400.0f;
const D3DXVECTOR3 CMediumUlt::SPEED = {14.0f,16.0f,14.0f};

//=============================================
//コンストラクタ
//=============================================
CMediumUlt::CMediumUlt():m_move_y(0.0f), m_pUltRange(), m_pUltCameraEffect()
{
}

//=============================================
//デストラクタ
//=============================================
CMediumUlt::~CMediumUlt()
{
}

//=============================================
//初期化
//=============================================
HRESULT CMediumUlt::Init()
{
	//親クラスの初期化
	CUlt::Init();

	SetCoolTime(MEDIUM_ULT_COOL_TIME);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CMediumUlt::Uninit()
{
	if (m_pUltRange != nullptr)
	{//ウルトの判定が破棄されていなければ
		m_pUltRange->Uninit();
		m_pUltRange = nullptr;
	}

	if (m_pUltCameraEffect != nullptr)
	{//破棄されていなければ
		m_pUltCameraEffect->Uninit();
		m_pUltCameraEffect = nullptr;
	}

	//親クラスの終了
	CUlt::Uninit();
}

//=============================================
//更新
//=============================================
void CMediumUlt::Update()
{
	//親クラスの更新
	CUlt::Update();

	if (m_pUltRange != nullptr)
	{//ウルトの判定が生成されていれば
		m_pUltRange->Update();
		if (m_pUltRange->GetLife() <= 0)
		{
			m_pUltRange->Uninit();
			m_pUltRange = nullptr;
		}
	}
}

//=============================================
//ウルトの実行処理
//=============================================
bool CMediumUlt::Action(CPlayer* player)
{
	float rot = CManager::GetInstance()->GetCamera()->GetRot().y;

	if (!m_isFinish)
	{
		if (m_move_y < FLYING_HIGHT)
		{
			if (m_pUltCameraEffect == nullptr)
			{
				m_pUltCameraEffect = CUltCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f });
			}
			player->SetMove({ sinf(rot) * SPEED.x,SPEED.y,cosf(rot) * SPEED.z });
			m_move_y += SPEED.y;
		}
		if (m_move_y >= FLYING_HIGHT)
		{
			player->SetMove({ sinf(rot) * SPEED.x,-SPEED.y * 2.0f,cosf(rot) * SPEED.z });

			if (player->GetLaunding())
			{//着地したら終了
				if (m_pUltRange == nullptr)
				{
					m_pUltRange = CUltRange::Create(player->GetPos());

					if (m_pUltCameraEffect != nullptr)
					{//破棄されていなければ
						m_pUltCameraEffect->Uninit();
						m_pUltCameraEffect = nullptr;
					}
				}
				m_isFinish = true;
				m_move_y = 0;

				//クールタイムリセット
				SetCoolTimeCnt(0);
			}
		}
	}
	return m_isFinish;
}
