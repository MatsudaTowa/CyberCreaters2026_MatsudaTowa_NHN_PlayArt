//=============================================
//
//スモークの表記[smoke_icon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _SMOKE_ICON_H_ //これが定義されてないとき

#define _SMOKE_ICON_H_
#include "main.h"
#include "object2D.h"

//スモークの表記クラス
class CSmokeIcon : public CObject2D
{
public:
	static const int SMOKE_ICON_PRIORITY = 21;  //描画順

	CSmokeIcon(int nPriority = SMOKE_ICON_PRIORITY);
	~CSmokeIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CSmokeIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif