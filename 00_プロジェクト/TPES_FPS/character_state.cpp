//=============================================
//
//キャラクターのステートパターン[character_state.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character_state.h"

//=============================================
//最初に呼ばれる関数
//=============================================
void CCharacterState::Start(CCharacter* character)
{
}

//=============================================
//キャラクターのショット
//=============================================
void CCharacterState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
}

//=============================================
//キャラクターのスタン
//=============================================
void CCharacterState::Stan(CCharacter* character)
{
}


//=============================================
//キャラクターの混乱
//=============================================
void CCharacterState::Confusion(CCharacter* character)
{
}

//=============================================
//キャラクターの動き
//=============================================
void CCharacterState::Move(CCharacter* character)
{
}

//=============================================
//キャラクターのショット
//=============================================
void CShotState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type, CCharacter* character)
{
	character->m_pGunAttack->GunAttack(Allegiance,type,character);
}

//=============================================
//キャラクターの動き
//=============================================
void CMoveState::Move(CCharacter* character)
{
	if (character->m_pMove != nullptr)
	{
		character->m_pMove->Move(character);
	}
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CStanState::Start(CCharacter* character)
{
	//カウントリセット
	m_StanCnt = 0;
}

//=============================================
//キャラクターのスタン状態
//=============================================
void CStanState::Stan(CCharacter* character)
{
	const int StanFrame = character->GetStanFrame();

	if (m_StanCnt < StanFrame)
	{
		++m_StanCnt;

		if (character->m_pStan != nullptr)
		{
			character->m_pStan->Stan(character);
		}
	}
	if (m_StanCnt >= StanFrame)
	{
		m_StanCnt = 0;

		//射撃状態に遷移
		character->ChangeState(new CShotState);
	}
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CConfusionState::Start(CCharacter* character)
{
	m_StartRot = character->GetRot().y;
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
//キャラクターの混乱状態
//=============================================
void CConfusionState::Confusion(CCharacter* character)
{
	if (character->m_pConfusion != nullptr)
	{
		character->m_pConfusion->Confusion(character, m_StartRot);
	}
}
