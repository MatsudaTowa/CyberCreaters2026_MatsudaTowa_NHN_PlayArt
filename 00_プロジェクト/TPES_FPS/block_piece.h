//=============================================
//
//ブロックの破片[block_piece.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLOCK_PIECE_H_ //これが定義されてないとき

#define _BLOCK_PIECE_H_
#include "main.h"
#include "objectX.h"
#include "manager.h"

class CBlock_Piece : public CObjectX
{
public:
	static const int BLOCK_PRIORITY = 10; //描画順

	enum PIECE_TYPE
	{
		PIECE_TYPE_0 = 0,
		PIECE_TYPE_1,
		PIECE_TYPE_2,
		PIECE_TYPE_MAX,
	};

	static const char* MODEL_NAME[PIECE_TYPE_MAX];	//モデルの名前

	CBlock_Piece(int nPriority = BLOCK_PRIORITY);
	~CBlock_Piece()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//ブロック作成
	static CBlock_Piece* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 scale,bool isMove);
private:
	PIECE_TYPE m_type;
};

class CMove_Piece :public CBlock_Piece
{
public:
	CMove_Piece(int nPriority = BLOCK_PRIORITY);
	~CMove_Piece()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static const int LIFE = 120;
	D3DXVECTOR3 m_move;
	int m_nLife;
};

class CStack_Piece :public CBlock_Piece
{
public:
	CStack_Piece(int nPriority = BLOCK_PRIORITY);
	~CStack_Piece()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif