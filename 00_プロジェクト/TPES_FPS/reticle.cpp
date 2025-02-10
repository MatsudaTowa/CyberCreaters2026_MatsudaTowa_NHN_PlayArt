//=============================================
//
//レティクル[reticle.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "reticle.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CReticle::CReticle():
m_pCrosshair(nullptr),				//クロスヘアのポインター
m_pCenterDot(nullptr),				//センタードットのポインター
m_pHitMaker(nullptr),				//ヒットマーカーのポインター
m_ReticlePos({0.0f,0.0f,0.0f}),		//レティクルの位置
m_ReticleSize({0.0f,0.0f,0.0f}),	//レティクルのサイズ
m_ReticleCol({0.0f,1.0f,1.0f,1.0f})	//レティクルの色
{
}

//=============================================
//デストラクタ
//=============================================
CReticle::~CReticle()
{
	if (m_pCrosshair != nullptr)
	{
		m_pCrosshair->Uninit();
		m_pCrosshair = nullptr;
	}

	if (m_pCenterDot != nullptr)
	{
		m_pCenterDot->Uninit();
		m_pCenterDot = nullptr;
	}

	if (m_pHitMaker != nullptr)
	{
		m_pHitMaker->Uninit();
		m_pHitMaker = nullptr;
	}
}

//=============================================
//初期化
//=============================================
HRESULT CReticle::Init()
{
	if (m_pCrosshair == nullptr)
	{
		m_pCrosshair = CCrossHair::Create(m_ReticlePos, { 0.0f,0.0f,0.0f }, m_ReticleSize, m_ReticleCol);
	}

	if (m_pCenterDot == nullptr)
	{
		m_pCenterDot = CCenterDot::Create(m_ReticlePos, { 0.0f,0.0f,0.0f }, m_ReticleSize, m_ReticleCol);
	}

	if (m_pHitMaker == nullptr)
	{
		m_pHitMaker = CHitMaker::Create(m_ReticlePos, { 0.0f,0.0f,0.0f }, m_ReticleSize, {1.0f,1.0f,1.0f,0.0f});
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CReticle::Uninit()
{
	if (m_pCrosshair != nullptr)
	{
		m_pCrosshair->Uninit();
		m_pCrosshair = nullptr;
	}

	if (m_pCenterDot != nullptr)
	{
		m_pCenterDot->Uninit();
		m_pCenterDot = nullptr;
	}

	if (m_pHitMaker != nullptr)
	{
		m_pHitMaker->Uninit();
		m_pHitMaker = nullptr;
	}

	delete this;
}

//=============================================
//更新
//=============================================
void CReticle::Update()
{
	if (m_pCrosshair != nullptr)
	{
		m_pCrosshair->SetPos(m_ReticlePos);
	}

	if (m_pCenterDot != nullptr)
	{
		m_pCenterDot->SetPos(m_ReticlePos);
	}

	if (m_pHitMaker != nullptr)
	{
		m_pHitMaker->SetPos(m_ReticlePos);

	}
}