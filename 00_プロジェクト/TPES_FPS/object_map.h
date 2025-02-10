//=============================================
//
//マップに配置するオブジェクトX[map_object.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MAP_OBJECT_H_ //これが定義されてないとき

#define _MAP_OBJECT_H_
#include "main.h"
#include "objectX.h"

class CObjectMap : public CObjectX
{
public:
	static const std::string MESH_MODEL_NAME;	//モデルの名前
	static const std::string WOOD_MODEL_NAME;	//モデルの名前
	static const std::string AZUMAYA_MODEL_NAME;	//モデルの名前
	static const std::string DANGOYA_MODEL_NAME;	//モデルの名前

	static const int OBJECT_MAP_PRIORITY = 3; //描画順
	typedef enum
	{
		OBJECT_MAP_TYPE_NONE = 0,
		OBJECT_MAP_TYPE_MESH,
		OBJECT_MAP_TYPE_WOOD,
		OBJECT_MAP_TYPE_AZUMAYA,
		OBJECT_MAP_TYPE_DANGOYA,
		OBJECT_MAP_TYPE_MAX,
	}OBJECT_MAP_TYPE;

	CObjectMap(int nPriority = OBJECT_MAP_PRIORITY);
	~CObjectMap()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//マップオブジェクト作成
	static CObjectMap* Create(OBJECT_MAP_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, bool bBreak);
private:
	OBJECT_MAP_TYPE m_type;
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif