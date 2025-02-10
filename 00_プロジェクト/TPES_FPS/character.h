//=============================================
//
//3DTemplate[character.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_H_ //これが定義されてないとき

#define _CHARACTER_H_
#include "main.h"
#include "objectX.h"
#include "model_parts.h"
#include "bullet.h"
#include "gun.h"
#include "character_behavior.h"
#include "character_state.h"
#include "wall.h"
#include "block.h"
#include "shadow.h"

//=============================================
//前方宣言
//=============================================
class CMove;
class CGunAttack;
class CStan;
class CConfusion;
class CCharacterState;

//プレイヤークラス
class CCharacter : public CObjectX
{
public:
	static const int MAX_KEY = 20; //キー最大数
	static const int CHARACTER_PRIORITY = 8;
	static const int MAX_MOTION = 100;
	static const int MAX_PARTS = 64; //最大パーツ数
	static const float  BOSS_FIELD_X; //ボス戦のX座標

	struct RayHitInfo
	{
		float distance;
		BOOL hit;
	};

	struct ColisionBlockInfo
	{
		bool bColision_X; //X軸に当たっている
		bool bColision_Y; //Y軸に当たっている
		bool bColision_Z; //Z軸に当たっている
		float radius;
	};

	enum CHARACTER_STATE
	{
		CHARACTER_NORMAL = 0, //通常状態
		CHARACTER_DAMAGE, //ダメージ状態
		CHARACTER_STATE_MAX,
	};

	CCharacter(int nPriority = CHARACTER_PRIORITY);
	~CCharacter()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void MotionDraw();

	void Load_Parts(const char* FileName);
	void Motion(int NumParts); //モーション処理
	void SetMotion(int Motion); //引数で指定したモーションに切り替える
	void Gravity(); //重力処理
	void Jump(); //ジャンプ処理
	virtual void HitBlock(int NumParts); //ブロック当たり判定(複数パーツ用)
	void HitField(); //床当たり判定
	void HitWall(); //壁当たり判定
	RayHitInfo PerformRaycast_Smoke(D3DXVECTOR3 vector, CCharacter* character);
	RayHitInfo PerformRaycast_Block(D3DXVECTOR3 vector, CCharacter* character);
	void ConversionMtxWorld();

	//移動量代入
	void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//oldpos代入
	void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	}

	//着地してるかどうかを代入
	void SetLanding(bool bLanding)
	{
		m_bLanding = bLanding;
	}

	//体力代入
	void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	//状態代入
	void SetState(CHARACTER_STATE state)
	{
		m_State = state;
	}

	void SetStanFrame(int StanFrame)
	{
		m_StanFrame = StanFrame;
	}

	//ステートカウント代入
	void SetStateCnt(int nStateCnt)
	{
		m_nStateCnt = nStateCnt;
	}

	//ジャンプ数代入
	void SetJumpCnt(int nJumpCnt)
	{
		m_nJumpCnt = nJumpCnt;
	}

	//終わった判定に
	void SetFinish(bool bFinish)
	{
		m_bLoopFinish = bFinish;
	}

	//影のサイズ設定
	void SetShadowSize(D3DXVECTOR3 shadow_size)
	{
		m_ShadowSize = shadow_size;
	}
	//移動量取得
	D3DXVECTOR3& GetMove();

	//過去の位置取得
	D3DXVECTOR3& GetOldPos();

	//影のサイズ取得
	D3DXVECTOR3& GetShadowSize();

	//着地してるかどうか取得
	bool& GetLaunding();

	//終わってるか取得
	bool& GetFinish();

	//体力取得
	int& GetLife();

	//パーツ数取得
	int& GetNumParts();

	float& GetSpeed();

	//状態取得
	CHARACTER_STATE& GetState();

	//ステートカウント取得
	int& GetStateCnt();

	//ジャンプ回数取得
	int& GetJumpCnt();

	int& GetStanFrame()
	{
		return m_StanFrame;
	}

	void ChangeState(CCharacterState* state);

	//パーツ
	CModel_Parts* m_apModel[MAX_PARTS];

	//銃
	CGun* m_pGun;

	CMove*m_pMove;

	CStan* m_pStan;

	CConfusion* m_pConfusion;

	CGunAttack*m_pGunAttack;

	//キャラクターのステートパターン
	CCharacterState* m_pCharacterState;

private:

	static const float GRAVITY_MOVE; //重力値
	static const float GRAVITY_MAX; //重力最大値

	void ColisionBlock_X(int PartsIdx,D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock);
	void ColisionBlock_Y(int PartsIdx,D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock);
	void ColisionBlock_Z(int PartsIdx,D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterOldPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CBlock* pBlock);
	//壁の判定
	void ColisionWall_X(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall);
	void ColisionWall_Z(D3DXVECTOR3& CharacterPos, const D3DXVECTOR3& CharacterMin, const D3DXVECTOR3& CharacterMax, CWall* pWall);

	D3DXVECTOR3 m_move; //速度
	D3DXVECTOR3 m_oldpos; //過去の位置
	bool m_bLanding; //着地してるかどうか
	bool m_bLoopFinish; //ループモーションが終わったか
	int m_nLife; //体力
	int m_nShotBullet; //撃った弾数
	int m_nStateCnt; //ステート切り替え計測カウント
	int m_PartsCnt; //パーツ数
	int m_nMotionFrameCnt; //切り替えフレームカウント
	int m_nKeySetCnt; //キー切り替えカウント
	int m_nJumpCnt; //ジャンプカウント
	int m_Motion; //モーション(各オブジェクトから列挙を受け取る)
	int m_StanFrame; //スタンのフレーム数
	float m_Speed; //スピード
	float m_Jump; //ジャンプ
	CHARACTER_STATE m_State; //プレイヤー状態
	D3DXCOLOR m_col; //カラー
	D3DXVECTOR3 m_ShadowSize; //影のサイズ

	CShadow* m_pShadow; //影

	//キー情報構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXVECTOR3 Trot;
	}Key;

	//キー設定構造体
	typedef struct
	{
		int nFrame; //フレーム数
		Key key[MAX_KEY];
	}KeySet;

	//モーション設定構造体
	typedef struct
	{
		int nLoop; //ループするかどうか
		int nNumKey; //キー数
		KeySet keySet[MAX_PARTS];
	}MotionSet;

	MotionSet m_MotionSet[MAX_MOTION]; //モーション設定
};
#endif