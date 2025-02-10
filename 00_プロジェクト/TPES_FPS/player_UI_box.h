//=============================================
//
//プレイヤーのUIの枠[player_UI_box.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_UI_BOX_H_ //これが定義されてないとき

#define _PLAYER_UI_BOX_H_
#include "main.h"
#include "object2D.h"

//プレイヤーのUIの枠クラス
class CPlayerUIBox : public CObject2D
{
public:
	static const int UI_BOX_PRIORITY = 20;  //描画順

	enum BOX_TYPE
	{
		BOX_TYPE_LIFE,
		BOX_TYPE_AMMO,
		BOX_TYPE_SCORE,
		BOX_TYPE_MAX,
	};
	CPlayerUIBox(int nPriority = UI_BOX_PRIORITY);
	~CPlayerUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CPlayerUIBox* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,D3DXCOLOR col, BOX_TYPE type);
private:
};


//プレイヤーのUIの体力の枠クラス
class CLifeUIBox : public CPlayerUIBox
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	CLifeUIBox(int nPriority = UI_BOX_PRIORITY);
	~CLifeUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};

//プレイヤーのUIの残弾の枠クラス
class CAmmoUIBox : public CPlayerUIBox
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	CAmmoUIBox(int nPriority = UI_BOX_PRIORITY);
	~CAmmoUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};

//プレイヤーのUIのスコアの枠クラス
class CScoreUIBox : public CPlayerUIBox
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	CScoreUIBox(int nPriority = UI_BOX_PRIORITY);
	~CScoreUIBox()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};
#endif