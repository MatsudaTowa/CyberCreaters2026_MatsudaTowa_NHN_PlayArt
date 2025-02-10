//=============================================
//
//ブリンクの数字の背景[blink_back_UI.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLINK_BACK_UI_H_ //これが定義されてないとき

#define _BLINK_BACK_UI_H_
#include "main.h"
#include "object2D.h"

//スモークの表記クラス
class CBlinkBackUI : public CObject2D
{
public:
	static const int PRIORITY = 20;  //描画順

	CBlinkBackUI(int nPriority = PRIORITY);
	~CBlinkBackUI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlinkBackUI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif