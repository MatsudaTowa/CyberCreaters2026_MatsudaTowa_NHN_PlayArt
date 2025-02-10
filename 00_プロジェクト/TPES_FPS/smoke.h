//=============================================
//
//スモーク処理[somoke.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _SMOKE_H_ //これが定義されてないとき

#define _SMOKE_H_

class CSmoke : public CBillboard
{
public:
	static const std::string SMOKE_TEXTURE_NAME; //テクスチャの名前
	static const int SMOKE_LIFE = 300; //スモークの持続時間

	static const int SMOKE_PRIORITY = 10; //描画順

	CSmoke(int nPriority = SMOKE_PRIORITY);
	~CSmoke()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void ColisionRange();
	void Draw()override;

	//スモーク作成
	static CSmoke* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,D3DXVECTOR3 size,D3DXCOLOR col);

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	int m_nLife;
	D3DXVECTOR3 m_move;
	//TODO:何個old作るつもり＾＾
	D3DXVECTOR3 m_oldpos;
};

#endif