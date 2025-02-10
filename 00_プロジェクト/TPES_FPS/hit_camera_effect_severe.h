//=============================================
//
//ヒット時のカメラエフェクト(重傷時)「hit_camera_effect_severe.h」
// Author松田永久
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_SEVERE_H_ //これが定義されてないとき
#define _HIT_CAMERA_EFFECT_SEVERE_H_
#include "main.h"
#include "hit_camera_effect.h"

//=============================================
//ヒット時のカメラエフェクトクラス
//=============================================
class CHitCameraEffectSevere :public CHitCameraEffect
{
public:
	static const std::string TEXTURE_NAME;	//軽度テクスチャの名前

	CHitCameraEffectSevere(int nPriority = PRIORITY);
	~CHitCameraEffectSevere() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
};

#endif // _HIT_CAMERA_EFFECT_H_