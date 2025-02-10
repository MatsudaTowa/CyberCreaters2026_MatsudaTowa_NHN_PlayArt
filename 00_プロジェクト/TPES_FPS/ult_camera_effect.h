//=============================================
//
//ウルト時のカメラエフェクト「ult_camera_effect.h」
// Author松田永久
//
//=============================================
#ifndef _ULT_CAMERA_EFFECT_H_ //これが定義されてないとき
#define _ULT_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ウルト時のカメラエフェクトクラス
//=============================================
class CUltCameraEffect :public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int PRIORITY = 25; //描画順

	CUltCameraEffect(int nPriority = PRIORITY);
	~CUltCameraEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CUltCameraEffect* Create(D3DXVECTOR3 pos);

	void SubAlpha();

	float& GetAlpha()
	{
		return m_alpha;
	}
private:
	float m_alpha; //アルファ値
};

#endif // _ULT_CAMERA_EFFECT_H_