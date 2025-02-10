//=============================================
//
//3DTemplate[tutorial.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TUTORIAL_H_ //これが定義されてないとき

#define _TUTORIAL_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include"block.h"
#include "wave.h"
#include "score.h"
#include"wave_result.h"
#include "tutorial_UI.h"

class CTutorial:public CScene
{
public:
	//読み込むときに必要なエネミーの構造体
	struct LOAD_ENEMY
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CEnemy::ENEMY_TYPE type;
	};

	//読み込むときに必要なブロックの構造体
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	//読み込むときに必要な壁の構造体
	struct LOAD_WALL
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
	};

	static const std::string ENEMY_FILE;	//エネミーのファイル
	static const std::string BLOCK_FILE;	//ブロックのファイル
	static const std::string WALL_FILE;		//壁のファイル
	static const int TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	CTutorial();
	~CTutorial() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	LOAD_ENEMY m_LoadEnemy; //読み込むときに必要なエネミーの情報
	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報
	LOAD_WALL m_LoadWall; //読み込むときに必要な壁の情報

	CTutorial_UI* m_pTutorial_UI;

	void LoadBlock(const std::string* pFileName);
	void LoadWall(const std::string* pFileName);
	void LoadEnemy(const std::string* pFileName);
};
#endif