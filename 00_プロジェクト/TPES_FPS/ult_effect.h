//=============================================
//
//ウルトエフェクト「ult_effect.h」
// Author松田永久
//
//=============================================
#ifndef _ULT_EFFECT_H_ //これが定義されてないとき

#define _ULT_EFFECT_H_
#include "main.h"
#include "object3D.h"

//ウルトエフェクトクラス
class CUltEffect : public CObject3D
{
public:

	static const int PRIORITY = 12; //描画順

	CUltEffect(int nPriority = PRIORITY);
	~CUltEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CUltEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif