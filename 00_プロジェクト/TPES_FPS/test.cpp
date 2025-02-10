//=============================================
//
//テストシーン[test.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "test.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"

//読み込むブロック情報のファイル
const std::string CTest::BLOCK_FILE = "data\\FILE\\block_data_tutorial.bin";

//=============================================
// コンストラクタ
//=============================================
CTest::CTest()
{
}

//=============================================
// デストラクタ
//=============================================
CTest::~CTest()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CTest::Init()
{
	//ブロック生成
	LoadBlock(&CTest::BLOCK_FILE);

	CField::Create({ 0.0f,0.0f,0.0f }, { 1000.0f,0.0f,1000.0f });

	//プレイヤー生成
	CPlayer* pplayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 100);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CTest::Uninit()
{
	CObject::ReleaseAll();
}

//=============================================
// 更新
//=============================================
void CTest::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	//if (m_bEdit == false)
	//{

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_RESULT);
	}
}

//=============================================
// 描画
//=============================================
void CTest::Draw()
{
}

//=============================================
// ブロック読み込み
//=============================================
void CTest::LoadBlock(const std::string* pFileName)
{
	//生成するブロック数読み込み用
	int NumBlock = 0;

	//生成するブロック情報読み込み用
	LOAD_BLOCK Info[256];

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "rb");

	if (pFile != NULL)
	{
		//敵の使用してる数の読み込み
		fread(&NumBlock, sizeof(int), 1, pFile);

		//敵の使用数分、敵の読み込み
		fread(&Info[0], sizeof(LOAD_BLOCK), NumBlock, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		return;
	}

	for (int nCnt = 0; nCnt < NumBlock; nCnt++)
	{
		CBlock::Create(Info[nCnt].type, Info[nCnt].pos, Info[nCnt].rot, 1, false);
	}
}
