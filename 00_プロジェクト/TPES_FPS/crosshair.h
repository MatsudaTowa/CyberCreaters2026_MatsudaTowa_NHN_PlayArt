//=============================================
//
//クロスヘア[crosshair.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _CROSSHAIR_H_ //これが定義されてないとき

#define _CROSSHAIR_H_

//=============================================
//クロスヘアクラス
//=============================================
class CCrossHair : public CBillboard
{
public:
	static const std::string CROSSHAIR_TEXTURE_NAME;	//テクスチャの名前

	static const int RETICLE_PRIORITY = 20; //描画順

	CCrossHair(int nPriority = RETICLE_PRIORITY);
	~CCrossHair()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//クロスヘア作成
	static CCrossHair* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	D3DXVECTOR3 m_move; //移動量
};

#endif