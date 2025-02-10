//=============================================
//
//敵の混乱のUI[enemy_confusion_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"
#include "enemy_reaction_UI.h"

#ifndef _ENEMY_WANDERING_UI_H_ //これが定義されてないとき

#define _ENEMY_WANDERING_UI_H_

class CEnemy_Confusion_UI : public CEnemy_Reaction_UI
{
public:
	CEnemy_Confusion_UI(int nPriority = PRIORITY);
	~CEnemy_Confusion_UI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

};

#endif