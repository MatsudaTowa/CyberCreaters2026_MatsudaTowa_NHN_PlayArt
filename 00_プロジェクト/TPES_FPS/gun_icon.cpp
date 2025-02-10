//=============================================
//
//銃の表示[gun_icon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gun_icon.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CGunIcon::CGunIcon(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGunIcon::~CGunIcon()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGunIcon::Init()
{
	//初期化
	CObject2D::Init();

	SetVtx(1.0f);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGunIcon::Uninit()
{
	//終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGunIcon::Update()
{
	//更新
	CObject2D::Update();

	SetVtx(1.0f);
}

//=============================================
//描画
//=============================================
void CGunIcon::Draw()
{
	//描画
	CObject2D::Draw();
}

//=============================================
//描画
//=============================================
CGunIcon* CGunIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ICON_TYPE type)
{
	CGunIcon* pGunIcon = nullptr;

	switch (type)
	{
	case CGunIcon::ICON_TYPE_AR:
		pGunIcon = new CARIcon;
		break;
	default:
		break;
	}

	if(pGunIcon == nullptr) {return nullptr;}

	pGunIcon->SetPos(pos);
	pGunIcon->SetSize(size);
	pGunIcon->SetColor(col);

	pGunIcon->Init();

	return pGunIcon;
}

//テクスチャ初期化
const std::string CARIcon::TEXTURE_NAME = "data\\TEXTURE\\ak.png";
//=============================================
//コンストラクタ
//=============================================
CARIcon::CARIcon(int nPriority):CGunIcon(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CARIcon::~CARIcon()
{
}

//=============================================
//初期化
//=============================================
HRESULT CARIcon::Init()
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	//初期化
	CGunIcon::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CARIcon::Uninit()
{
	//終了
	CGunIcon::Uninit();
}

//=============================================
//更新
//=============================================
void CARIcon::Update()
{
	//更新
	CGunIcon::Update();
}

//=============================================
//描画
//=============================================
void CARIcon::Draw()
{
	//描画
	CGunIcon::Draw();
}
