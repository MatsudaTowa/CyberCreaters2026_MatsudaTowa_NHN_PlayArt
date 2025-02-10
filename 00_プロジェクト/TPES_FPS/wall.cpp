//=============================================
//
//壁の処理[wall.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "wall.h"
#include "manager.h"

//texパス
const std::string CWall::TEXTURE_NAME = "data\\TEXTURE\\wall.jpg";

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CWall::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CWall::CWall(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CWall::~CWall()
{
}

//=============================================
//初期化
//=============================================
HRESULT CWall::Init()
{
	// 自身のサイズ取得
	D3DXVECTOR3 sizeThis = GetSize();

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	CObject3D::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CWall::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CWall::Update()
{
	CObject3D::Update();
}

//=============================================
//描画
//=============================================
void CWall::Draw()
{
	CObject3D::Draw();
}

//=============================================
//生成
//=============================================
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CWall* pWall = new CWall;

	// nullならnullを返す
	if (pWall == nullptr) { return nullptr; }

	//テクスチャ取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	pWall->SetPos(pos); //pos設定
	pWall->SetRot(rot); //rot設定
	pWall->SetSize(size); //サイズ設定
	pWall->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャ設定
	pWall->SetType(OBJECT_TYPE_WALL); //タイプ設定
	pWall->Init(); //床の初期化処理

	return pWall;
}
