//=============================================
//
//スモーク範囲処理[somoke_range.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "smoke.h"

#ifndef _SMOKE_RANGE_H_ //これが定義されてないとき

#define _SMOKE_RANGE_H_

class CSmokeRange : public CObjectX
{
public:
	static const int SMOKE_RANGE_PRIORITY = 15; //描画順

	CSmokeRange(int nPriority = SMOKE_RANGE_PRIORITY);
	~CSmokeRange()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//スモーク範囲作成
	static CSmokeRange* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

private:
	static const char* MODEL_NAME;	//モデルの名前
	int m_nLife;
};

#endif