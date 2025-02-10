//=============================================
//
//ダッシュ時にキャラクターの前方に出すエフェクト[dash_effect.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "dash_effect.h"
#include "manager.h"

const char* CDashEffect::MODEL_NAME = "data\\MODEL\\dash_effect.x";

//=============================================
//コンストラクタ
//=============================================
CDashEffect::CDashEffect(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CDashEffect::~CDashEffect()
{
}

//=============================================
//初期化
//=============================================
HRESULT CDashEffect::Init()
{
	//描画に必要な情報設定
	SetScale({ 10.0f, 10.0f, 10.0f });
	SetColor({ 1.0f, 1.0f, 1.0f,0.35f });
	CObjectX::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CDashEffect::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CDashEffect::Update()
{
	CObjectX::Update();
}

//=============================================
//描画
//=============================================
void CDashEffect::Draw()
{
	CObjectX::Draw();
}

//=============================================
//生成
//=============================================
CDashEffect* CDashEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CDashEffect* pEffect = new CDashEffect;
	if (pEffect == nullptr) { return nullptr; }

	pEffect->SetPos(pos);

	pEffect->SetRot(rot);

	CModel* pModel = CManager::GetInstance()->GetModel();

	//Xファイル読み込み
	pEffect->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pEffect->SetType(OBJECT_TYPE_DUSH_EFFECT); //タイプ設定

	pEffect->Init();

	return pEffect;
}
