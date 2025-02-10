//=============================================
//
//スモークグレネード処理[somoke_grenade.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "smoke_grenade.h"
#include "manager.h"
#include "smoke_range.h"
#include "field.h"

//モデルパス
const char* CSmokeGrenade::MODEL_NAME = "data\\MODEL\\jett.x";

//=============================================
//コンストラクタ
//=============================================
CSmokeGrenade::CSmokeGrenade(int nPriority) : CObjectX(nPriority),m_move({0.0f,0.0f,0.0f}), m_oldpos({ 0.0f,0.0f,0.0f }), m_bBoot(false)
{
}

//=============================================
//デストラクタ
//=============================================
CSmokeGrenade::~CSmokeGrenade()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSmokeGrenade::Init()
{
	m_bBoot = false;
	CObjectX::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSmokeGrenade::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CSmokeGrenade::Update()
{
	CObjectX::Update();

	D3DXVECTOR3 pos = GetPos();

	m_oldpos = pos;

	pos += m_move;

	SetPos(pos);

	//床との判定
	HitField();

	if (m_bBoot)
	{//炸裂したら
		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SMOKE);

		std::random_device seed;
		std::mt19937 random(seed());
		std::uniform_int_distribution<int> number_x(-3, 3);
		std::uniform_int_distribution<int> number_y(0, 3);
		std::uniform_int_distribution<int> number_z(0, 1);
		for (int nCnt = 0; nCnt < CREATE_SMOKE_NUM; nCnt++)
		{
			CSmoke::Create(GetPos(), { number_x(random) * 0.1f,number_y(random) * 0.1f,number_z(random) * 0.1f }, { 0.0f,0.0f,0.0f }, { 30.0f,30.0f,0.0f }, {1.0f,1.0f,1.0f,1.0f});
		}
		CSmokeRange::Create(GetPos(),{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f});
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CSmokeGrenade::Draw()
{
	CObjectX::Draw();
}

//=============================================
//生成
//=============================================
CSmokeGrenade* CSmokeGrenade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	CSmokeGrenade* pSmokeGrenade = new CSmokeGrenade;

	if (pSmokeGrenade == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();

	//Xファイル読み込み
	pSmokeGrenade->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pSmokeGrenade->SetPos(pos);
	pSmokeGrenade->m_move = move;
	pSmokeGrenade->SetRot(rot);
	pSmokeGrenade->Init();
	pSmokeGrenade->SetType(OBJECT_TYPE_SMOKE_GRENADE);

	return pSmokeGrenade;
}

//=============================================
//床との判定
//=============================================
void CSmokeGrenade::HitField()
{
	D3DXVECTOR3 pos = GetPos();

	//サイズ取得
	D3DXVECTOR3 min = GetMinPos();
	D3DXVECTOR3 max = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CField::FIELD_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//ブロックとの当たり判定
			//床との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = dynamic_cast<CField*>(pObj);

				//床のみだけローカルで
				CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColision_Y(m_oldpos, pos, min, max, pField->GetPos(), pField->GetSize());

				if (colision == CColision::COLISION::COLISON_TOP_Y)
				{//y(上)方向に当たってたら
					pos.y = m_oldpos.y;
					m_move = {0.0f,0.0f,0.0f};
					m_bBoot = true;
				}

				//TODO:壁の当たり判定やったらこれを使う必要なくなる
				{
					if (m_oldpos.x > pField->GetPos().x - pField->GetSize().x
						&& pos.x < pField->GetPos().x - pField->GetSize().x)
					{
						pos.x = m_oldpos.x;
						m_move = { 0.0f,0.0f,0.0f };
						m_bBoot = true;
					}

					if (m_oldpos.x < pField->GetPos().x + pField->GetSize().x
						&& pos.x > pField->GetPos().x + pField->GetSize().x)
					{
						pos.x = m_oldpos.x;
						m_move = { 0.0f,0.0f,0.0f };
						m_bBoot = true;
					}

					if (m_oldpos.z > pField->GetPos().z - pField->GetSize().z
						&& pos.z < pField->GetPos().z - pField->GetSize().z)
					{
						pos.z = m_oldpos.z;
						m_move = { 0.0f,0.0f,0.0f };
						m_bBoot = true;
					}

					if (m_oldpos.z < pField->GetPos().z + pField->GetSize().z
						&& pos.z > pField->GetPos().z + pField->GetSize().z)
					{
						pos.z = m_oldpos.z;
						m_move = { 0.0f,0.0f,0.0f };
						m_bBoot = true;
					}
				}
			}
		}
	}
	SetPos(pos);

}
