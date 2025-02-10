//=============================================
//
//ゲージ管理[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge.h"
#include "manager.h"

const std::string CGauge_2D::TEXTURE_NAME = "data\\TEXTURE\\gauge.png";

//=============================================
//コンストラクタ
//=============================================
CGauge_2D::CGauge_2D(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_2D::~CGauge_2D()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_2D::Init()
{
	//親クラスの初期化を呼ぶ
	CObject2D::Init();

	//テクスチャ座標設定
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//頂点設定
	SetGaugeVtx(1.0f);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_2D::Uninit()
{
	//親クラスの終了呼ぶ
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_2D::Update()
{
	//親クラスの更新呼ぶ
	CObject2D::Update();

	//頂点設定
	SetGaugeVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CGauge_2D::Draw()
{
	//親クラスの描画呼ぶ
	CObject2D::Draw();
}


//=============================================
//ゲージ設定
//=============================================
void CGauge_2D::SetGauge(D3DXVECTOR2 size)
{
	SetSize(size);
}

//=============================================
//生成
//=============================================
CGauge_2D* CGauge_2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE2D_TYPE type, D3DXCOLOR col)
{
	CGauge_2D* pGauge = nullptr;

	switch (type)
	{
	case GAUGE_TYPE_LIFE:
		pGauge = new CGauge_Life;
		break;
	case GAUGE_TYPE_STAMINA:
		pGauge = new CGauge_Stamina;
		break;
	default:
		assert(false);
		break;
	}

	// nullならnullを返す
	if (pGauge == nullptr) { return nullptr; }

	pGauge->SetPos(pos); //pos設定

	pGauge->SetSize(size); //size設定

	pGauge->SetColor(col);

	pGauge->m_type = type; //ゲージのタイプ設定

	pGauge->SetType(OBJECT_TYPE_GAUGE); //タイプ設定

	pGauge->Init();

	return pGauge;
}

//=============================================
//コンストラクタ
//=============================================
CGauge_3D::CGauge_3D(int nPriority) :CBillboard(nPriority),
m_type(),
m_isVisible(false)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_3D::~CGauge_3D()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_3D::Init()
{
	//親クラスの初期化を呼ぶ
	CBillboard::Init();

	//テクスチャ座標設定
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//頂点設定
	SetGaugeVtx(m_ReferencePos, {0.0f,0.0f,-1.0f});

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_3D::Uninit()
{
	//親クラスの終了を呼ぶ
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_3D::Update()
{
	//親クラスの更新を呼ぶ
	CBillboard::Update();

	//頂点設定
	SetGaugeVtx(m_ReferencePos,{ 0.0f,0.0f,-1.0f });
}

//=============================================
//描画
//=============================================
void CGauge_3D::Draw()
{
	if (m_isVisible)
	{
		//親クラスの描画を呼ぶ
		CBillboard::Draw();
	}
}

//=============================================
//生成
//=============================================
CGauge_3D* CGauge_3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, GAUGE3D_TYPE type, D3DXCOLOR col)
{
	CGauge_3D* pGauge = nullptr;

	switch (type)
	{
	case GAUGE_TYPE_STAMINA:
		//pGauge = new CGauge_Stamina;
		break;
	default:
		assert(false);
		break;
	}

	// nullならnullを返す
	if (pGauge == nullptr) { return nullptr; }

	pGauge->SetPos(pos); //pos設定

	pGauge->m_ReferencePos = pos;

	pGauge->SetSize(size); //size設定

	pGauge->SetColor(col);

	pGauge->m_type = type; //ゲージのタイプ設定

	pGauge->SetType(OBJECT_TYPE_GAUGE); //タイプ設定

	pGauge->Init();

	return pGauge;
}


//=============================================
//コンストラクタ
//=============================================
CGauge_Life::CGauge_Life(int nPriority) :CGauge_2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_Life::~CGauge_Life()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_Life::Init()
{
	//親クラスの初期化
	CGauge_2D::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_Life::Uninit()
{
	//親クラスの終了
	CGauge_2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_Life::Update()
{
	//親クラスの更新
	CGauge_2D::Update();
}

//=============================================
//描画
//=============================================
void CGauge_Life::Draw()
{
	//親クラスの描画
	CGauge_2D::Draw();
}

//=============================================
//コンストラクタ
//=============================================
CGauge_Stamina::CGauge_Stamina(int nPriority):CGauge_2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_Stamina::~CGauge_Stamina()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_Stamina::Init()
{
	//親クラスの初期化
	CGauge_2D::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_Stamina::Uninit()
{
	//親クラスの終了
	CGauge_2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_Stamina::Update()
{
	//親クラスの更新
	CGauge_2D::Update();
}

//=============================================
//描画
//=============================================
void CGauge_Stamina::Draw()
{
	//親クラスの描画
	CGauge_2D::Draw();
}
