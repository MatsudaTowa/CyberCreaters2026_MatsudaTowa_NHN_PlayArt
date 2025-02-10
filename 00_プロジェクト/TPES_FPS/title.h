//=============================================
//
//3DTemplate[title.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TITLE_H_ //これが定義されてないとき

#define _TITLE_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include "block.h"
#include "title_screen.h"
class CTitle :public CScene
{
public:
	static const int BLOCK_TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	static const std::string BLOCK_FILE;	//エネミーのファイル

	//読み込むときに必要なブロックの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	}LOAD_BLOCK;

	CTitle();
	~CTitle() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	void LoadBlock(const std::string* pFileName);

	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報

	//プレイヤー
	CPlayer*m_pPlayer;

	CTitle_Screen*m_pTitleScreen[2];
};
#endif