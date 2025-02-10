//=============================================
//
//2DTemplate[move_texture.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MOVE_TEXTURE_H_ //これが定義されてないとき

#define _MOVE_TEXTURE_H_
#include "main.h"
#include "object2D.h"

//レンダラークラス
class CObject2D_Anim : public CObject2D
{
public:
	CObject2D_Anim(int nPriority);
	~CObject2D_Anim()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//アニメーション処理
	void AnimationTex(D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move);
	//アニメーションフレーム代入
	void SetAnimFrame(int nAnimFrame)
	{
		m_nAnimFrame = nAnimFrame;
	}

	//テクスチャ移動量の代入
	void SetTexMove(D3DXVECTOR2 tex_move)
	{
		m_tex_move = tex_move;
	}

	//アニメーションフレーム取得
	int GetAnimFrame();
	
	//テクスチャ移動量取得
	D3DXVECTOR2& GetTexMove();

private:
	//アニメーション
	int m_nAnimFrame; //アニメーションフレーム
	int m_nAnimCnt; //アニメーションカウント
	D3DXVECTOR2 m_tex_move; //tex移動量

};
#endif