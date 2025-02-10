//=============================================
//
//ブリンクの表記[blink_icon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLINK_ICON_H_ //これが定義されてないとき

#define _BLINK_ICON_H_
#include "main.h"
#include "object2D.h"

//スモークの表記クラス
class CBlinkIcon : public CObject2D
{
public:
	static const int ICON_PRIORITY = 21;  //描画順

	CBlinkIcon(int nPriority = ICON_PRIORITY);
	~CBlinkIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlinkIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif