//=============================================
//
//ウェーブリザルト画面[wave_result_screen.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _WAVE_RESULT_SCREEN_H_ //これが定義されてないとき

#define _WAVE_RESULT_SCREEN_H_
#include "main.h"
#include "object2D.h"

//ウェーブリザルト
class CWave_Result_Screen : public CObject2D
{
public:
	static const int RESULT_SCREEN_PRIORITY = 15;  //描画順
	CWave_Result_Screen(int nPriority = RESULT_SCREEN_PRIORITY);
	~CWave_Result_Screen()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CWave_Result_Screen* Create(D3DXVECTOR3 pos);
private:
	//static const std::string TEXTURE_NAME;	//テクスチャの名前
	//static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif