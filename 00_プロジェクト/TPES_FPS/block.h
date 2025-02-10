//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLOCK_H_ //これが定義されてないとき

#define _BLOCK_H_
#include "main.h"
#include "objectX.h"

class CBlock : public CObjectX
{
public:
	static const char* MODEL_NAME;	//モデルの名前
	static const char* WOOD_MODEL_NAME;	//モデルの名前
	static const char* AZUMAYA_MODEL_NAME;	//モデルの名前
	static const char* DANGOYA_MODEL_NAME;	//モデルの名前
	static const char* MESH_MODEL_NAME;	//モデルの名前

	static const int BLOCK_PRIORITY = 10; //描画順
	typedef enum
	{
		BLOCKTYPE_NONE = 0,
		BLOCKTYPE_DEFAULT,
		BLOCKTYPE_WOOD,
		BLOCKTYPE_AZUMAYA,
		BLOCKTYPE_DANGOYA,
		BLOCKTYPE_MESH,
		BLOCKTYPE_MAX,
	}BLOCKTYPE;

	CBlock(int nPriority = BLOCK_PRIORITY);
	~CBlock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void CreatePiece();
	void Draw()override;
	//ブロック作成
	static CBlock* Create(BLOCKTYPE type,D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,bool bBreak);
private:
	static const int NUM_PIECE = 5; //壊れた際に生成するピース数
	static const int NUM_SMOKE = 30; //壊れた際に生成するスモーク数
	BLOCKTYPE m_type;
	bool m_bBreak; //壊せるかどうか
	int m_nLife;
};
#endif