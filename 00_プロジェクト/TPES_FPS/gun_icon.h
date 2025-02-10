//=============================================
//
//銃の表記[gun_icon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GUN_ICON_H_ //これが定義されてないとき

#define _GUN_ICON_H_
#include "main.h"
#include "object2D.h"

//銃の表記クラス
class CGunIcon : public CObject2D
{
public:
	static const int GUN_ICON_PRIORITY = 25;  //描画順

	enum ICON_TYPE
	{
		ICON_TYPE_AR,
		ICON_TYPE_MAX,
	};
	CGunIcon(int nPriority = GUN_ICON_PRIORITY);
	~CGunIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CGunIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ICON_TYPE type);
private:
};

class CARIcon : public CGunIcon
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	CARIcon(int nPriority = GUN_ICON_PRIORITY);
	~CARIcon()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif