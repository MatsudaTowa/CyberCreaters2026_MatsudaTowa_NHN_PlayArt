//=============================================
//
//カメラのステートパターン[camera_state.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CAMERA_STATE_H_
#define _CAMERA_STATE_H_

#include "camera.h"

//=============================================
//前方宣言
//=============================================
class CCamera;

//=============================================
//キャラクターのステートクラス
//=============================================
class CCameraState
{
public:
	virtual void FreeView(CCamera* camera);
	virtual void ThirdView(CCamera* camera);
	virtual void Ult(CCamera* camera);
};

//=============================================
//自由なカメラ
//=============================================
class CFreeView : public CCameraState
{
public:
	virtual void FreeView(CCamera* camera)override;
private:
	static const float FREEVIEW_LENGTH; //サードパーソンビュー時の距離
};

//=============================================
//キャラクターの通常状態
//=============================================
class CThirdView : public CCameraState
{
public:
	virtual void ThirdView(CCamera* camera)override;
private:
	static const float THIRDVIEW_LENGTH; //サードパーソンビュー時の距離
};

//=============================================
//キャラクターのウルト状態
//=============================================
class CUltCameraState : public CCameraState
{
public:
	virtual void Ult(CCamera* camera) override;
private:
	static const float ULT_LENGTH; //ウルト時の距離
};

#endif // !_PLAYER_STATE_H
