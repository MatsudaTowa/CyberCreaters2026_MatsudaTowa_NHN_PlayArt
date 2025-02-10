//=============================================
//
//ウルト範囲処理[ult_range.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "ult_effect.h"

#ifndef _ULT_RANGE_H_ //これが定義されてないとき

#define _ULT_RANGE_H_

class CUltRange
{
public:

	CUltRange();
	~CUltRange();
	HRESULT Init();
	void Uninit();
	void Update();

	//ウルト範囲作成
	static CUltRange* Create(D3DXVECTOR3 pos);

	int& GetLife()
	{
		return m_nLife;
	}
private:
	static const int LIFE = 10;
	static const int MAX_DAMAGE =10;
	static const float RADIUS;
	D3DXVECTOR3 m_pos;
	int m_nLife;

	CUltEffect* m_pUltEffect;
};

#endif