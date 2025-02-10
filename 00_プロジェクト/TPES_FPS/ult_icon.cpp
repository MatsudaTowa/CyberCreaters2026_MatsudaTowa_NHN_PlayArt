//=============================================
//
//ウルトのマークの表記[ult_icon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "ult_icon.h"
#include "manager.h"

const D3DXCOLOR CUltIcon::START_COLOR = {0.2f,0.2f,0.2f,1.0f};

//=============================================
//コンストラクタ
//=============================================
CUltIcon::CUltIcon(int nPriority):CObject2D(nPriority),
m_isAddColor(true),	//加算状態に
m_AddColor(0.0f),	//色の加算値初期化
m_pIconEffect()		//アイコンのエフェクトポインター初期化
{
}

//=============================================
//デストラクタ
//=============================================
CUltIcon::~CUltIcon()
{
}

//=============================================
//初期化
//=============================================
HRESULT CUltIcon::Init()
{
	CObject2D::Init();

	//頂点生成
	SetVtx(1.0f);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CUltIcon::Uninit()
{
	if (m_pIconEffect != nullptr)
	{
		m_pIconEffect->Uninit();
		m_pIconEffect = nullptr;
	}
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CUltIcon::Update()
{
	CObject2D::Update();

	D3DXCOLOR col = GetColor();

	if (m_isAddColor)
	{
		col.r += m_AddColor;
		col.g += m_AddColor;
		col.b += m_AddColor;

		if (col.r >= 1.0f
			&& col.g >= 1.0f
			&& col.b >= 1.0f)
		{
			col = { 1.0f,1.0f,1.0f,1.0f };
			m_isAddColor = false; //加算終了

			if (m_pIconEffect == nullptr)
			{
				m_pIconEffect = CUltIconEffect::Create(GetPos(), { 75.0f,75.0f }, { 1.0f,0.8f,0.0f,0.75f });
			}
		}
	}

	SetColor(col);

	//頂点生成
	SetVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CUltIcon::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CUltIcon* CUltIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, float add_col, ULT_TYPE type)
{
	CUltIcon* pUltIcon = nullptr;

	switch (type)
	{
	case CUltIcon::ULT_TYPE_MEDIUM:
		pUltIcon = new CMediumIcon;
		break;
	default:
		assert(false);
		break;
	}

	//代入の前にreturn
	if(pUltIcon == nullptr) {return nullptr;}

	pUltIcon->SetPos(pos);

	pUltIcon->SetSize(size);

	pUltIcon->m_AddColor = add_col;

	pUltIcon->SetType(OBJECT_TYPE_ULT_ICON);

	pUltIcon->Init();

	return pUltIcon;
}

//=============================================
//ウルトを使った際に呼ばれる
//=============================================
void CUltIcon::Reset()
{
	SetColor(START_COLOR); //色を初期の色に
	m_isAddColor = true; //加算状態に

	if (m_pIconEffect != nullptr)
	{
		m_pIconEffect->Uninit();
		m_pIconEffect = nullptr;
	}
}

//テクスチャ初期化
const std::string CMediumIcon::TEXTURE_NAME = "data\\TEXTURE\\ult_icon_000.png";
//=============================================
//コンストラクタ
//=============================================
CMediumIcon::CMediumIcon(int nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CMediumIcon::~CMediumIcon()
{
}

//=============================================
//初期化
//=============================================
HRESULT CMediumIcon::Init()
{
	SetColor(START_COLOR);
	//テクスチャ設定
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CUltIcon::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CMediumIcon::Uninit()
{
	CUltIcon::Uninit();

}

//=============================================
//更新
//=============================================
void CMediumIcon::Update()
{
	CUltIcon::Update();
}

//=============================================
//描画
//=============================================
void CMediumIcon::Draw()
{
	CUltIcon::Draw();
}
