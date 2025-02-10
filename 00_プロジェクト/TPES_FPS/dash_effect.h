//=============================================
//
//ダッシュ時にキャラクターの前方に出すエフェクト[dash_effect.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _DASH_EFFECT_H_ //これが定義されてないとき

#define _DASH_EFFECT_H_
#include "main.h"
#include "objectX.h"

class CDashEffect : public CObjectX
{
public:
	static const char* MODEL_NAME;	//モデルの名前

	static const int PRIORITY = 11; //描画順

	CDashEffect(int nPriority = PRIORITY);
	~CDashEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//ブロック作成
	static CDashEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:
};
#endif