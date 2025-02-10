//=============================================
//
//ボスのステートパターン[boss_state.h]
//Auther Matsuda Towa
//
//=============================================
#include "boss_state.h"
#include "player.h"

//=============================================
//コンストラクタ
//=============================================
CBossState::CBossState()
{
}

//=============================================
//デストラクタ
//=============================================
CBossState::~CBossState()
{
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CBossState::Start(CBossEnemy* boss)
{
}

//=============================================
//ボスの追跡状態(基底では何もしない)
//=============================================
void CBossState::Chase(CBossEnemy* boss)
{
}

//=============================================
//スタン状態
//=============================================
void CBossState::Stan(CBossEnemy* boss)
{
}

//=============================================
//ボスの徘徊状態(基底では何もしない)
//=============================================
void CBossState::Wandering(CBossEnemy* boss)
{
}

//=============================================
//ボスの混乱状態(基底では何もしない)
//=============================================
void CBossState::Confusion(CBossEnemy* boss)
{
}

//=============================================
//ボスのタックル状態(基底では何もしない)
//=============================================
void CBossState::Tackle(CBossEnemy* boss)
{
}

//=============================================
//ボスのプレイヤーを探す情報
//=============================================
void CBossState::Search(CBossEnemy* boss)
{
}

//=============================================
//ボスのデバッグ情報
//=============================================
void CBossState::DrawDebug()
{
}

//=============================================
//コンストラクタ
//=============================================
CChaseState::CChaseState() : m_PlayTackleCnt(0)
{
	m_PlayTackleCnt = 0;
}

//=============================================
//デストラクタ
//=============================================
CChaseState::~CChaseState()
{
}

//=============================================
//ボスの追跡状態
//=============================================
void CChaseState::Chase(CBossEnemy* boss)
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				if (boss->m_pChase != nullptr)
				{
					boss->m_pChase->Chase(boss, pObj);
				}
			}
		}
	}

	//TODO:ステートパターンで
	++m_PlayTackleCnt;

	if (m_PlayTackleCnt > PLAY_TACKLE_FLAME)
	{//タックル実行フレームに到達したら
		//ステート切り替え
		boss->ChangeState(new CTackleState);
		m_PlayTackleCnt = 0;
	}

	boss->m_pGunAttack->GunAttack(CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_NORMAL, boss);
}

//=============================================
//ボスの追跡状態デバッグ
//=============================================
void CChaseState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n追跡");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CBossStanState::Start(CBossEnemy* boss)
{
	m_StanCnt = 0;
}

//=============================================
//ボスのスタン状態
//=============================================
void CBossStanState::Stan(CBossEnemy* boss)
{
	if (m_StanCnt < STAN_FRAME)
	{
		++m_StanCnt;

		if (boss->m_pStan != nullptr)
		{
			boss->m_pStan->Stan(boss);
		}
	}
	if (m_StanCnt >= STAN_FRAME)
	{
		m_StanCnt = 0;

		//射撃状態に遷移
		boss->ChangeState(new CChaseState);
	}
}

//=============================================
//ボスのスタン状態デバッグ
//=============================================
void CBossStanState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\nスタン");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//コンストラクタ
//=============================================
CWanderingState::CWanderingState() :
	m_TransitionCnt(0),
	m_bDamage(false),
	m_TargetRot({0.0f,0.0f,0.0f})
{
}

//=============================================
//デストラクタ
//=============================================
CWanderingState::~CWanderingState()
{
}

//=============================================
//ボスの徘徊状態
//=============================================
void CWanderingState::Wandering(CBossEnemy* boss)
{
	if (boss->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		m_bDamage = true;

		for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//ヌルポインタじゃなければ
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				//敵との当たり判定
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
				{
					CPlayer* pplayer = dynamic_cast<CPlayer*>(pObj);

					//プレイヤーとの距離算出
					D3DXVECTOR3 Distance = pplayer->GetPos() - boss->GetPos();

					//プレイヤーに向ける角度を算出
					float fAngle = atan2f(Distance.x, Distance.z);

					//親クラスからrotを取得
					D3DXVECTOR3 rot = boss->GetRot();

					rot.y = fAngle + D3DX_PI;

					m_TargetRot = rot;
				}
			}
		}
	}

	if (m_bDamage)
	{
		++m_TransitionCnt;

		//親クラスからrotを取得
		D3DXVECTOR3 rot = boss->GetRot();

		//D3DXVECTOR3 RotDistance = m_TargetRot - rot;

		//D3DXVECTOR3 RotMove = RotDistance / TRANSITION_FRAME;

		//if (RotDistance > 0)
		//{
		//	rot.y -= RotMove.y;
		//}
		//if (RotDistance < 0)
		//{
		//	rot.y += RotMove.y;
		//}

		boss->SetRot(rot);

		if (m_TransitionCnt > TRANSITION_FRAME)
		{
			m_TransitionCnt = 0;
			boss->ChangeState(new CChaseState);
		}
	}
	else if(!m_bDamage)
	{
		if (boss->m_pWandering != nullptr)
		{
			boss->m_pWandering->Wandering(boss);
			//プレイヤーの位置への方向情報
			D3DXVECTOR3 Vector = boss->GetPos() + boss->GetMove() - boss->GetPos();

			if (boss->PerformRaycast_Player(Vector, boss).hit)
			{
				if (boss->PerformRaycast_Block(Vector, boss).hit)
				{//ブロックに当たっていたら
					if (boss->PerformRaycast_Block(Vector, boss).distance > boss->PerformRaycast_Player(Vector, boss).distance)
					{//ブロックより手前にいるときに
						boss->ChangeState(new CChaseState);
					}
				}
				else if (!boss->PerformRaycast_Block(Vector, boss).hit)
				{
					boss->ChangeState(new CChaseState);
				}
			}
		}
	}
}

//=============================================
//ボスの徘徊状態デバッグ
//=============================================
void CWanderingState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n徘徊");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//最初の一回だけ呼ばれる関数
//=============================================
void CTackleState::Start(CBossEnemy* boss)
{

}

//=============================================
//ボスのタックル処理
//=============================================
void CTackleState::Tackle(CBossEnemy* boss)
{
	if (boss->m_pTackle != nullptr)
	{
		boss->m_pTackle->Tackle(boss);
	}
}

//=============================================
//ボスのタックル状態デバッグ
//=============================================
void CTackleState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n突進");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//コンストラクタ
//=============================================
CConfusionBossState::CConfusionBossState()
{
	m_pReaction = nullptr;
}

//=============================================
//デストラクタ
//=============================================
CConfusionBossState::~CConfusionBossState()
{
	if (m_pReaction != nullptr)
	{
		m_pReaction->Uninit();
		m_pReaction = nullptr;
	}
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CConfusionBossState::Start(CBossEnemy* boss)
{
	if (m_pReaction == nullptr)
	{
		m_pReaction = CEnemy_Reaction_UI::Create({ boss->m_apModel[1]->GetMtxWorld()._41,
			boss->m_apModel[1]->GetMtxWorld()._42 + 70.0f,
			boss->m_apModel[1]->GetMtxWorld()._43 }, { 40.0f,40.0f,0.0f }, CEnemy_Reaction_UI::REACTION::REACTION_CONFUSION);
	}

	m_StartRot = boss->GetRot().y;
	if (m_StartRot < D3DX_PI * 0.5f && m_StartRot > -D3DX_PI * 0.5f)
	{
		m_isRight = false;
	}
	else if (m_StartRot > D3DX_PI * 0.5f && m_StartRot < -D3DX_PI * 0.5f)
	{
		m_isRight = true;
	}
}

//=============================================
//ボスの混乱処理
//=============================================
void CConfusionBossState::Confusion(CBossEnemy* boss)
{
	if (boss->m_pConfusion != nullptr)
	{
		//自分の方向を取得
		D3DXVECTOR3 vec = { sinf(boss->GetRot().y + D3DX_PI), 0.0f, cosf(boss->GetRot().y + D3DX_PI) };

		// レイキャストを実行し、障害物があるか判定
		if (boss->PerformRaycast_Player(vec, boss).hit)
		{
			if (boss->PerformRaycast_Block(vec, boss).hit)
			{//ブロックに当たっていたら
				if (boss->PerformRaycast_Block(vec, boss).distance > boss->PerformRaycast_Player(vec, boss).distance)
				{//ブロックより手前にいるときに
					boss->ChangeState(new CChaseState);
				}
			}
			else if (boss->PerformRaycast_Smoke(vec, boss).hit)
			{
				if (boss->PerformRaycast_Smoke(vec, boss).distance > boss->PerformRaycast_Smoke(vec, boss).distance)
				{//ブロックより手前にいるときに
					boss->ChangeState(new CChaseState);
				}
			}
			else if (!boss->PerformRaycast_Block(vec, boss).hit && !boss->PerformRaycast_Smoke(vec, boss).hit)
			{
				boss->ChangeState(new CChaseState);
			}
		}

		boss->m_pConfusion->Confusion(boss, m_StartRot);
	}

	if (boss->GetState() == CCharacter::CHARACTER_DAMAGE)
	{
		if (m_pReaction != nullptr)
		{
			m_pReaction->Uninit();
			m_pReaction = nullptr;
		}
		boss->ChangeState(new CBossStanState);
	}
}

//=============================================
//ボスの混乱状態デバッグ
//=============================================
void CConfusionBossState::DrawDebug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n混乱");
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}

//=============================================
//最初の一回だけ呼ばれる関数
//=============================================
void CSearchState::Start(CBossEnemy* boss)
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
		 //タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);
				m_TargetPos = pPlayer->GetPos();
			}
		}
	}
}

//=============================================
//プレイヤー探索
//=============================================
void CSearchState::Search(CBossEnemy* boss)
{
	if (boss->m_pSearch != nullptr)
	{
		boss->m_pSearch->Search(boss, m_TargetPos);
	}
}

//=============================================
//ボスの探索状態デバッグ
//=============================================
void CSearchState::DrawDebug()
{
}
