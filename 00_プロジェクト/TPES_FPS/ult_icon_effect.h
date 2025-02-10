//=============================================
//
//ultが溜まったときにアイコンから出すエフェクト[ult_icon_effect.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "Object2D_anim.h"

#ifndef _ULT_ICON_EFFECT_H_ //これが定義されてないとき

#define _ULT_ICON_EFFECT_H_

class CUltIconEffect : public CObject2D_Anim
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int PRIORITY = 20; //描画順
	static const int TEX_SPLIT_X = 4; //テクスチャの分割数
	static const int TEX_SPLIT_Y = 1; //テクスチャの分割数
	static const int ANIMATION_FRAME = 10; //アニメーションフレーム数

	CUltIconEffect(int nPriority = PRIORITY);
	~CUltIconEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//弾作成
	static CUltIconEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
};
#endif