//=============================================
//
//ヒット時のカメラエフェクト(軽傷時)「hit_camera_effect_mild.h」
// Author松田永久
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_MILD_H_ //これが定義されてないとき
#define _HIT_CAMERA_EFFECT_MILD_H_
#include "main.h"
#include "hit_camera_effect.h"

//=============================================
//ヒット時のカメラエフェクトクラス
//=============================================
class CHitCameraEffectMild :public CHitCameraEffect
{
public:
	static const std::string TEXTURE_NAME;	//軽度テクスチャの名前

	CHitCameraEffectMild(int nPriority = PRIORITY);
	~CHitCameraEffectMild() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
};

#endif // _HIT_CAMERA_EFFECT_H_