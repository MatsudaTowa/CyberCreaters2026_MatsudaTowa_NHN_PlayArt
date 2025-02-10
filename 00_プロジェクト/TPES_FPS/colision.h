//=============================================
//
//当たり判定管理[colision.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _COLISION_H_ //これが定義されてないとき

#define _COLISION_H_

//=============================================
//当たり判定クラス
//=============================================
class CColision
{
public:
	enum COLISION
	{
		COLISON_NONE = 0, //何にも当たってない
		COLISON_X, //X方向に当たってる
		COLISON_Z, //X方向に当たってる
		COLISON_UNDER_Y, //Y方向(下)に当たってる
		COLISON_TOP_Y, //X方向(上)当たってる
		COLISION_CIRCLE,
	};

	struct CIRCLE
	{
		COLISION colision; //どう当たったか
		float CenterDistance; //中心点との距離
	};
	CColision();
	~CColision();
	COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //ポリゴン同士当たり判定チェック関数
	COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //モデルとポリゴン当たり判定チェック関数
	COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos,D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //モデル同士当たり判定チェック関数

	COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //ポリゴン同士当たり判定チェック関数
	COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //モデルとポリゴン当たり判定チェック関数
	COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //モデル同士当たり判定チェック関数

	COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //ポリゴン同士当たり判定チェック関数
	COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //モデルとポリゴン当たり判定チェック関数
	COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //モデル同士当たり判定チェック関数

	COLISION CheckColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //モデル同士当たり判定チェック関数_球
	CIRCLE CheckColisionCircle(D3DXVECTOR3 Apos, float Radius, D3DXVECTOR3 Bpos);
	
	COLISION CheckPolygonModelColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //ポリゴンとモデル当たり判定チェック関数_球
	COLISION CheckPolygonModelColision_X(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //ポリゴンとモデル当たり判定チェック関数
	COLISION CheckPolygonModelColision_Z(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //ポリゴンとモデル当たり判定チェック関数
	COLISION CheckPolygonFillColision(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //ポリゴンとモデル当たり判定(埋まってるか)チェック関数

	COLISION CheckPolygonModelPenetration_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //ポリゴンとモデル貫通判定チェック関数
	COLISION CheckPolygonModelPenetration_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //ポリゴンとモデル貫通判定チェック関数
};
#endif