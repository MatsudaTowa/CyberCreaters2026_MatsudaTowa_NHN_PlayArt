//=============================================
//
//カメラのステートパターン[camera_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera_state.h"
#include "manager.h"

//=============================================
//自由視点
//=============================================
void CCameraState::FreeView(CCamera* camera)
{
}

//=============================================
//三人称の状態
//=============================================
void CCameraState::ThirdView(CCamera* camera)
{
}

//=============================================
//ウルトの状態
//=============================================
void CCameraState::Ult(CCamera* camera)
{
}

const float CFreeView::FREEVIEW_LENGTH = 200.0f;

//=============================================
//自由旋回状態
//=============================================
void CFreeView::FreeView(CCamera* camera)
{
	camera->SetLength(FREEVIEW_LENGTH);

	//入力
	camera->InputMove();
	
	//キーボード情報取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_V))
	{
		camera->ChangeCameraState(new CThirdView);
	}
}

//サードビュー時の距離
const float CThirdView::THIRDVIEW_LENGTH = 130.0f;

//=============================================
//三人称の状態
//=============================================
void CThirdView::ThirdView(CCamera* camera)
{
	camera->SetLength(THIRDVIEW_LENGTH);

	camera->ThirdViewCamera();


	//キーボード情報取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

#ifdef _DEBUG

	if (pKeyboard->GetTrigger(DIK_B))
	{
		camera->ChangeCameraState(new CFreeView);
	}

#endif // _DEBUG

}

//ULT時の距離
const float CUltCameraState::ULT_LENGTH = 200.0f;

//=============================================
//ウルトの状態
//=============================================
void CUltCameraState::Ult(CCamera* camera)
{
	camera->SetLength(ULT_LENGTH);
	camera->ThirdViewCamera();
}
