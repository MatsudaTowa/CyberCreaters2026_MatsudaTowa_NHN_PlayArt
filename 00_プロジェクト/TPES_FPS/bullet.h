//=============================================
//
//3DTemplate[bullet.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _BULLET_H_ //‚±‚ê‚ª’è‹`‚³‚ê‚Ä‚È‚¢‚Æ‚«

#define _BULLET_H_

class CBullet : public CAttack_Manager
{
public:
	static const std::string BULLET_TEXTURE_NAME;	//ƒeƒNƒXƒ`ƒƒ‚Ì–¼‘O

	static const int BULLET_PRIORITY = 10; //•`‰æ‡

	//“G‚©©•ª‚©‚Ì”»’f‚·‚é—ñ‹“
	typedef enum
	{
		BULLET_ALLEGIANCE_PLAYER = 0,
		BULLET_ALLEGIANCE_ENEMY,
		BULLET_ALLEGIANCE_MAX,
	}BULLET_ALLEGIANCE;

	//’e‚Ìí—Ş
	typedef enum
	{
		BULLET_TYPE_NORMAL = 0,
		BULLET_TYPE_MAX,
	}BULLET_TYPE;

	CBullet(int nPriority = BULLET_PRIORITY);
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void OnActive();

	void SetHitMaker();

	//’eì¬
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR3 rot,
	D3DXVECTOR3 size,int nLife,int nDamage, BULLET_ALLEGIANCE Allegiance,BULLET_TYPE type);

	//ˆÚ“®—Êİ’è
	void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//ƒ^ƒCƒvİ’è
	void SetBulletType(BULLET_TYPE type)
	{
		m_type = type;
	}

	//“G‚©©•ª‚©‚Ìİ’è
	void SetBulletAllegiance(BULLET_ALLEGIANCE Allegiance)
	{
		m_Allegiance = Allegiance;
	}

	D3DXVECTOR3 GetMove();

	BULLET_ALLEGIANCE GetBulletAllegiance();
private:
	bool PenetrationBlock();
	BULLET_ALLEGIANCE m_Allegiance; //“G‚©©•ª‚©‚ğ”»’f‚·‚é—ñ‹“Œ^•Ï”
	BULLET_TYPE m_type; //’e‚Ìí—Ş
	D3DXVECTOR3 m_move; //ˆÚ“®—Ê
};

#endif