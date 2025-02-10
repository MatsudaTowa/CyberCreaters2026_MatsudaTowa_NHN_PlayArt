//=============================================
//
//ヒット時のカメラエフェクト「hit_camera_effect.h」
// Author松田永久
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_H_ //これが定義されてないとき
#define _HIT_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ヒット時のカメラエフェクトクラス
//=============================================
class CHitCameraEffect:public CObject2D
{
public:
	static const std::string TEXTURE_NAME_SEVERE;	//重症テクスチャの名前
	static const int PRIORITY = 28; //描画順

	enum HIT_EFFECT_STAGE
	{
		MILD, //軽度
		MODERATE, //中
		SEVERE, //重症
	};

	CHitCameraEffect(int nPriority = PRIORITY);
	~CHitCameraEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CHitCameraEffect* Create(D3DXVECTOR3 pos, HIT_EFFECT_STAGE stage);

	void SubAlpha();

	float& GetAlpha()
	{
		return m_alpha;
	}
private:
	float m_alpha; //アルファ値
};

#endif // _HIT_CAMERA_EFFECT_H_