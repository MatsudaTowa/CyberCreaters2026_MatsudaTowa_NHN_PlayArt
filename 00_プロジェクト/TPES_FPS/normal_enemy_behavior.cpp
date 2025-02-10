//=============================================
//
//ノーマルエネミーのストラテジーパターン[normal_enemy_behavior.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "normal_enemy_behavior.h"
#include "smoke_range.h"
#include "player.h"

//=============================================
//コンストラクタ
//=============================================
CNormalMove::CNormalMove():m_TransitionCnt(0),m_nStateChangeCnt(0), m_nStayCnt(0), m_bRandom(), m_nLeft(), m_nRight(),m_bDamage(false)
{
	m_nLeft = LEFT_PARCENT;
	m_nRight = RIGHT_PARCENT;
}

//=============================================
//デストラクタ
//=============================================
CNormalMove::~CNormalMove()
{
}

//=============================================
//移動
//=============================================
void CNormalMove::Move(CCharacter* character)
{
	if (m_bDamage)
	{
		++m_TransitionCnt;
		if (m_TransitionCnt > TRANSITION_FRAME)
		{
			m_bDamage = false;
			m_TransitionCnt = 0;

			//射撃状態に
			character->ChangeState(new CShotState);
		}
	}
	if (m_nStateChangeCnt < MOVE_FRAME)
	{
		float move_x = 0.0f;

		if (m_bRandom)
		{
			move_x = 1.0f;
		}
		if (!m_bRandom)
		{
			move_x = -1.0f;
		}

		//横にしか移動しないのでxに値代入
		SetMoveVec({ move_x,0.0f,0.0f });

		//親クラスの移動を呼ぶ
		CEnemyMove::Move(character);

		++m_nStateChangeCnt;
	}
	if (m_nStateChangeCnt >= MOVE_FRAME)
	{
		Stay(character);
	}

	//自分の方向を取得
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };
	CCharacter::RayHitInfo HitPlayerInfo = PerformRaycast_Player(vec, character);
	CCharacter::RayHitInfo HitBlockInfo = character->PerformRaycast_Block(vec, character);
	CCharacter::RayHitInfo HitSmokeInfo = character->PerformRaycast_Smoke(vec, character);

	if ((HitPlayerInfo.hit
	&&!HitBlockInfo.hit))
	{//ダメージ状態もしくはレイがプレイヤーに当たっていたら
		character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);

		//射撃状態に
		character->ChangeState(new CShotState);
	}

	if (character->GetState() == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		m_bDamage = true;
	}
}

//=============================================
//レイがプレイヤーに当たっていたら
//=============================================
CCharacter::RayHitInfo CNormalMove::PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character)
{
	CCharacter::RayHitInfo Info;

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

				//レイを原点からの差分から飛ばす(yはエネミーから飛ばす際の高さ調整)
				D3DXVECTOR3 StartRay = { character->GetPos().x - pPlayer->GetPos().x,character->GetPos().y,character->GetPos().z - pPlayer->GetPos().z };
				for (int nParts = 0; nCnt < CPlayer::NUM_PARTS; nCnt++)
				{
					//レイを飛ばしプレイヤーと当たるかチェック
					D3DXIntersect(pPlayer->m_apModel[nCnt]->GetModelInfo(nCnt).pMesh, &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);
					if (Info.hit == true)
					{
						return Info;
					}
				}
			}
		}
	}
	return Info;
}

//=============================================
//正面を見て止まる
//=============================================
void CNormalMove::Stay(CCharacter* character)
{
	character->SetRot({0.0f,0.0f,0.0f});

	if (m_nStayCnt < STAY_FRAME)
	{
		character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);
		++m_nStayCnt;
	}
	if (m_nStayCnt >= STAY_FRAME)
	{
		m_nStateChangeCnt = 0;
		m_nStayCnt = 0;
		NextMove_X(character);
	}
}

//=============================================
//動く処理が終わったら次の方向を抽選
//=============================================
void CNormalMove::NextMove_X(CCharacter* character)
{
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, 100);

	//どっちに行くかの確率
	if (number(random) <= m_nRight)
	{
		m_bRandom = true;
		if (m_nRight > 0)
		{//右に進む確率を下げる
			m_nRight -= 5;
		}
	}
	else if (number(random) > m_nRight && number(random) <= m_nLeft)
	{
		m_bRandom = false;
		if (m_nRight < 100)
		{//右に進む確率をあげる
			m_nRight += 5;
		}
	}
}

//=============================================
//コンストラクタ
//=============================================
CNormalAttack::CNormalAttack():m_nLostCnt(0)
{
}

//=============================================
//デストラクタ
//=============================================
CNormalAttack::~CNormalAttack()
{
}

//=============================================
//攻撃
//=============================================
void CNormalAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	LookAtPlayer(character);

	//自分の方向を取得
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };

	//D3DXVec3Normalize(&vec, &vec);

	if (PerformRaycast_Player(vec, character).hit)
	{
		if (character->PerformRaycast_Block(vec, character).hit)
		{//ブロックに当たっていたら
			if (character->PerformRaycast_Block(vec, character).distance > PerformRaycast_Player(vec, character).distance)
			{//ブロックより手前にいるときに
				CEnemyGunAttack::GunAttack(Allegiance, type, character);
			}
			else if (character->PerformRaycast_Block(vec, character).distance < PerformRaycast_Player(vec, character).distance)
			{
				++m_nLostCnt;
			}
		}
		else if (!character->PerformRaycast_Block(vec, character).hit)
		{
			m_nLostCnt = 0;
			CEnemyGunAttack::GunAttack(Allegiance, type, character);
		}
	}

	if (character->PerformRaycast_Smoke(vec, character).hit || m_nLostCnt > LOST_FRAME)
	{//スモークに当たってたら
		character->ChangeState(new CConfusionState);
	}
}

//=============================================
//レイがプレイヤーに当たっていたら
//=============================================
CCharacter::RayHitInfo CNormalAttack::PerformRaycast_Player(D3DXVECTOR3 vector, CCharacter* character)
{
	CCharacter::RayHitInfo Info;

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

				//レイを原点からの差分から飛ばす(yはエネミーから飛ばす際の高さ調整)
				D3DXVECTOR3 StartRay = { character->GetPos().x - pPlayer->GetPos().x,character->GetPos().y,character->GetPos().z - pPlayer->GetPos().z };
				for (int nParts = 0; nCnt < CPlayer::NUM_PARTS; nCnt++)
				{
					//レイを飛ばしプレイヤーと当たるかチェック
					D3DXIntersect(pPlayer->m_apModel[nCnt]->GetModelInfo(nCnt).pMesh, &StartRay, &vector, &Info.hit, NULL, NULL, NULL, &Info.distance, NULL, NULL);
					if (Info.hit == true)
					{
						return Info;
					}
				}
			}
		}
	}
	return Info;
}
