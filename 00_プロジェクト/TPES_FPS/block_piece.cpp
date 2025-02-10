//=============================================
//
//ブロックの破片[block_piece.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "block_piece.h"

const char* CBlock_Piece::MODEL_NAME[CBlock_Piece::PIECE_TYPE_MAX]
{
	"data\\MODEL\\piece_000.x",
	"data\\MODEL\\piece_001.x",
	"data\\MODEL\\piece_002.x",
};
//=============================================
// コンストラクタ
//=============================================
CBlock_Piece::CBlock_Piece(int nPriority):CObjectX(nPriority),
m_type()
{
}

//=============================================
// デストラクタ
//=============================================
CBlock_Piece::~CBlock_Piece()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CBlock_Piece::Init()
{
	//親クラスの初期化処理
	CObjectX::Init();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CBlock_Piece::Uninit()
{
	//親クラスの終了処理
	CObjectX::Uninit();
}

//=============================================
// 更新
//=============================================
void CBlock_Piece::Update()
{
	//親クラスの更新処理
	CObjectX::Update();
}

//=============================================
// 描画
//=============================================
void CBlock_Piece::Draw()
{
	//親クラスの描画処理
	CObjectX::Draw();
}

//=============================================
// 生成
//=============================================
CBlock_Piece* CBlock_Piece::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, bool isMove)
{
	CBlock_Piece* pPiece = nullptr;

	if (isMove)
	{
		pPiece = new CMove_Piece;
	}
	else if (!isMove)
	{
		pPiece = new CStack_Piece;
	}

	//nullならnullを返す
	if (pPiece == nullptr) { return nullptr; }

	CModel* pModel = CManager::GetInstance()->GetModel();
	CTexture* pTex = CManager::GetInstance()->GetTexture();

	int nType = 0;
	//pPiece->m_type = type;
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, CBlock_Piece::PIECE_TYPE_MAX - 1);
	//ランダムでタイプ指定
	nType = number(random);

	//元の位置からからどれだけ動かすか
	std::uniform_int_distribution<int> pos_shift_x(-50, 50);
	std::uniform_int_distribution<int> pos_shift_z(-50, 50);

	pPiece->m_type = (CBlock_Piece::PIECE_TYPE)nType;
	pPiece->SetPos({ pos .x + pos_shift_x(random),0.2f,pos.z + pos_shift_z(random)}); //pos設定
	pPiece->SetRot(rot); //rot設定
	pPiece->SetScale(scale); //スケール設定
	//pPiece->BindTexture(m_pTextureTemp);

	//Xファイル読み込み
	pPiece->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_type])).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_type])).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME[pPiece->m_type])).pMesh);

	pPiece->SetType(OBJECT_TYPE_BLOCK_PIECE); //タイプ設定
	pPiece->Init();

	return pPiece;
}

//=============================================
// コンストラクタ
//=============================================
CMove_Piece::CMove_Piece(int nPriority):CBlock_Piece(nPriority),
m_nLife(0),
m_move({0.0f,0.0f,0.0f})
{
}

//=============================================
// デストラクタ
//=============================================
CMove_Piece::~CMove_Piece()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CMove_Piece::Init()
{
	CBlock_Piece::Init();

	float fVertex;
	float fMove;

	//放射状にランダム
	fVertex = (float)(rand() % 629 - 314) / 100.0f;

	//移動量1以上2.0以下に
	fMove = (float)(rand() % 101) / 10.0f + 5.0f;

	m_nLife = LIFE;

	m_move.x = sinf(fVertex) * fMove;
	m_move.y = fMove;
	m_move.z = cosf(fVertex) * fMove;
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CMove_Piece::Uninit()
{
	CBlock_Piece::Uninit();
}

//=============================================
// 更新
//=============================================
void CMove_Piece::Update()
{
	CBlock_Piece::Update();

	//位置取得
	D3DXVECTOR3 pos = GetPos();
	//移動処理
	pos += m_move;
	//位置代入
	SetPos(pos);

	--m_nLife;
	if (m_nLife <= 0)
	{//ライフ切れたら
		m_nLife = 0;
		//破棄
		Uninit();
	}
}

//=============================================
// 描画
//=============================================
void CMove_Piece::Draw()
{
	CBlock_Piece::Draw();
}

//=============================================
// コンストラクタ
//=============================================
CStack_Piece::CStack_Piece(int nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CStack_Piece::~CStack_Piece()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CStack_Piece::Init()
{
	CBlock_Piece::Init();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CStack_Piece::Uninit()
{
	CBlock_Piece::Uninit();
}

//=============================================
// 更新
//=============================================
void CStack_Piece::Update()
{
	CBlock_Piece::Update();
}

//=============================================
// 描画
//=============================================
void CStack_Piece::Draw()
{
	CBlock_Piece::Draw();
}
