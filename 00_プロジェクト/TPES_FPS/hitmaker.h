//=============================================
//
//ヒットマーカー[hitmaker.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _HITMAKER_H_ //これが定義されてないとき

#define _HITMAKER_H_

//=============================================
//クロスヘアクラス
//=============================================
class CHitMaker : public CBillboard
{
public:
	static const std::string HITMARKER_DOT_TEXTURE_NAME;	//テクスチャの名前

	static const int RETICLE_PRIORITY = 28; //描画順

	static const int HITMARKER_LIFE = 30; //体力

	CHitMaker(int nPriority = RETICLE_PRIORITY);
	~CHitMaker()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void HitColor(D3DXCOLOR col);

	//クロスヘア作成
	static CHitMaker* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	int m_nLife;
};

#endif