//=============================================
//
//ゲージ管理[gauge.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_ //これが定義されてないとき

#define _GAUGE_H_
#include "main.h"
#include "object2D.h"
#include "object3D.h"
#include "billboard.h"

//=============================================
//2Dゲージクラス
//=============================================
class CGauge_2D : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	enum GAUGE2D_TYPE
	{
		GAUGE_TYPE_LIFE,
		GAUGE_TYPE_STAMINA,
		GAUGE_TYPE_MAX,
	};
	static const int GAUGE2D_PRIORITY = 28;  //描画順
	static const float MAX_GAUGE_WIDE;  //ゲージの最大値
	CGauge_2D(int nPriority = GAUGE2D_PRIORITY);
	~CGauge_2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetGauge(D3DXVECTOR2 size);
	static CGauge_2D* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE2D_TYPE type, D3DXCOLOR col);
private:
	GAUGE2D_TYPE m_type;
};

//=============================================
//3Dゲージクラス
//=============================================
class CGauge_3D : public CBillboard
{
public:
	enum GAUGE3D_TYPE
	{
		GAUGE_TYPE_STAMINA,
		GAUGE_TYPE_MAX,
	};
	static const int GAUGE3D_PRIORITY = 18;  //描画順
	CGauge_3D(int nPriority = GAUGE3D_PRIORITY);
	~CGauge_3D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CGauge_3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, GAUGE3D_TYPE type, D3DXCOLOR col);

	void SetVisible(bool isVisible)
	{
		m_isVisible = isVisible;
	}

	bool& GetVisible()
	{
		return m_isVisible;
	}
private:
	D3DXVECTOR3 m_ReferencePos;
	GAUGE3D_TYPE m_type;
	bool m_isVisible; //描画するか
};

//=============================================
//体力ゲージクラス
//=============================================
class CGauge_Life : public CGauge_2D
{
public:
	CGauge_Life(int nPriority = GAUGE2D_PRIORITY);
	~CGauge_Life()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

//=============================================
//スタミナゲージクラス
//=============================================
class CGauge_Stamina : public CGauge_2D
{
public:
	CGauge_Stamina(int nPriority = GAUGE2D_PRIORITY);
	~CGauge_Stamina()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif