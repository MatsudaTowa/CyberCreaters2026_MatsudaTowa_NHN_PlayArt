//=============================================
// 
//マズルフラッシュ[muzzle_flash.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MUZZLE_FLASH_H_ //これが定義されてないとき

#define _MUZZLE_FLASH_H_
#include "main.h"
#include "billboard.h"

class CMuzzleFlash : public CBillboard
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int PRIORITY = 10; //描画順
	static const int LIFE = 10; //ライフ
	static const D3DXVECTOR3 SIZE; //サイズ

	CMuzzleFlash(int nPriority = PRIORITY);
	~CMuzzleFlash() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CMuzzleFlash* Create(D3DXVECTOR3 pos);
private:
	int m_nLife;
};
#endif