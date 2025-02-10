//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "smoke_grenade.h"
#include "camera_state.h"

//スポーン位置
const D3DXVECTOR3 CPlayer::PLAYER_SPAWN_POS = { 0.0f, 0.5f, -400.0f };

//スポーン方向
const D3DXVECTOR3 CPlayer::PLAYER_SPAWN_ROT = { 0.0f, 3.14f, 0.0f};

//当たり判定無効フレーム数
const int CPlayer::IGNORE_COLLISION_FRAME = 150;

//スモーク復活フレーム数
const int CPlayer::SMOKE_RECAST_FRAME = 900;

//通常の移動抵抗
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//プレイヤーをリスポーンされる座標
const float CPlayer::DEADZONE_Y = -100.0f;

//影のサイズ
const D3DXVECTOR3 CPlayer::SHADOW_SIZE = { 20.0f, 0.0, 20.0f };

//スタミナのサイズ
const D3DXVECTOR3 CPlayer::STAMINA_GAUGE_SIZE = { 5.0f,20.0f,0.0f };

CAmmo_UI* CPlayer::m_pAmmoUI = nullptr;
CLife_UI* CPlayer::m_pLifeUI = nullptr;

//=============================================
//コンストラクタ
//=============================================
CPlayer::CPlayer(int nPriority) :CCharacter(nPriority),
m_Raticle(),				//レティクルのポインタ初期化
m_IgnoreColisionCnt(0),		//当たり判定無効カウントリセット
m_SmokeRecastCnt(0),		//スモーク復活カウントリセット
m_DeathCnt(0),				//死亡カウントリセット
m_Stamina(0),				//スタミナ
m_isRelorad(false),			//リロードしていない状態に
m_isSmoke(false),			//スモークを使っていない状態に
m_isEnemyColision(true),	//エネミーと判定をとる状態に
m_pHitCameraEffect(),		//カメラのエフェクトのポインタ初期化
m_pGunIcon(),				//銃のアイコンのポインタ初期化
m_pUlt(),					//ウルトのポインタ初期化 
m_pPlayerState(),			//プレイヤーのステート初期化
m_pUltUI(),					//ウルトのUI初期化
m_pSmokeUI(),				//スモークのUI初期化
m_pBlinkUI(),				//ブリンクのUI初期化
m_pStaminaGauge()			//スタミナのゲージ初期化
{//イニシャライザーでメンバ変数初期化
	if (m_pSliding == nullptr)
	{
		m_pSliding = new CPlayerSliding;
	}
	if (m_pAvoidance == nullptr)
	{
		m_pAvoidance = new CPlayerAvoidance;
	}
	if (m_pMove == nullptr)
	{
		m_pMove = new CPlayerMove;
	}
	if (m_pGunAttack == nullptr)
	{
		m_pGunAttack = new CPlayerAttack;
	}
}

//=============================================
//デストラクタ
//=============================================
CPlayer::~CPlayer()
{
	if (m_pAvoidance != nullptr)
	{
		delete m_pAvoidance;
		m_pAvoidance = nullptr;
	}
	if (m_pPlayerState != nullptr)
	{
		delete m_pPlayerState;
	}
}

//=============================================
//初期化
//=============================================
HRESULT CPlayer::Init()
{
	CCharacter::Init();

	//スタンフレーム数代入
	SetStanFrame(STAN_FRAME);

	//スタミナ初期化
	m_Stamina = PLAYER_STAMINA;

	if (m_pPlayerState == nullptr)
	{
		m_pPlayerState = new CDefaultState;
	}

	//銃初期化
	if (m_pGun == nullptr)
	{
		m_pGun = new CAssultRifle;

		m_pGun->SetReloadFrame(DEFAULT_AR_RELOAD_FRAME);
		m_pGun->SetDamage(DEFAULT_AR_DAMAGE);

		m_pGun->Init();
	}

	if (m_pUlt == nullptr)
	{
		m_pUlt = new CMediumUlt;
		m_pUlt->Init();
	}

	m_BlinkCnt = PLAYER_STAMINA / AVOIDANCE_COST;

	//カメラ情報取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	//現在のシーンを取得 TODO:シーン参照するな
	CScene::MODE pScene = CScene::GetSceneMode();
	if (pScene != CScene::MODE::MODE_TITLE)
	{
		if (m_pGunIcon == nullptr)
		{
			m_pGunIcon = CGunIcon::Create({ 1150.0f, 665.0f, 0.0f }, { 70.0f,30.0f }, { 1.0f,1.0f,1.0f,1.0f }, CGunIcon::ICON_TYPE::ICON_TYPE_AR);
		}

		if (m_pStaminaGauge == nullptr)
		{
			m_pStaminaGauge = CGauge_3D::Create(D3DXVECTOR3(pCamera->GetPosR().x + 20.0f + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 80.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)),
				STAMINA_GAUGE_SIZE, CGauge_3D::GAUGE_TYPE_STAMINA, { 1.0f,1.0f,0.0f,1.0f });
		}
		//残弾数初期化
		if (m_pAmmoUI == nullptr)
		{
			m_pAmmoUI = new CAmmo_UI;

			m_pAmmoUI->Init();

			m_pAmmoUI->SetDefaultAmmo_UI(m_pGun->GetAmmo());
		}
		//体力UI初期化
		if (m_pLifeUI == nullptr)
		{
			m_pLifeUI = new CLife_UI;

			m_pLifeUI->Init();
		}
		//ブリンクUI初期化
		if (m_pBlinkUI == nullptr)
		{
			m_pBlinkUI = new CBlink_UI;

			m_pBlinkUI->Init(this);
		}
		//ウルトUI初期化
		if (m_pUltUI == nullptr)
		{
			m_pUltUI = new CUlt_UI;

			m_pUltUI->Init(this);
		}

		if (m_pSmokeUI == nullptr)
		{
			m_pSmokeUI = new CSmoke_UI;
			m_pSmokeUI->Init(this);
		}
	}

	CRenderer* pRender = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		CModel* pModel = CManager::GetInstance()->GetModel();
	}

	pCamera->SetRot({0.0f,0.0f,0.0f});

	//ムーブ値代入
	SetMove(move);

	//初期モーション設定
	SetMotion(MOTION_NEUTRAL);

	//影のサイズ設定
	SetShadowSize(SHADOW_SIZE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CPlayer::Uninit()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->Uninit();
		m_pAmmoUI = nullptr;
	}
	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->Uninit();
		m_pLifeUI = nullptr;
	}
	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->Uninit();
		m_pBlinkUI = nullptr;
	}
	if (m_pUltUI != nullptr)
	{
		m_pUltUI->Uninit();
		m_pUltUI = nullptr;
	}
	if (m_pUltUI != nullptr)
	{
		m_pStaminaGauge->Uninit();
		m_pStaminaGauge = nullptr;
	}
	if (m_pGunIcon != nullptr)
	{
		m_pGunIcon->Uninit();
		m_pGunIcon = nullptr;
	}
	if (m_pUlt != nullptr)
	{
		m_pUlt->Uninit();
		m_pUlt = nullptr;
	}
	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->Uninit();
		m_pSmokeUI = nullptr;
	}
	if (m_pSliding != nullptr)
	{
		delete m_pSliding;
		m_pSliding = nullptr;
	}
	if (m_pAvoidance != nullptr)
	{
		delete m_pAvoidance;
		m_pAvoidance = nullptr;
	}
	if (m_Raticle != nullptr)
	{
		m_Raticle->Uninit();
		m_Raticle = nullptr;
	}

	//親クラスの終了処理を呼ぶ
	CCharacter::Uninit();
}

//=============================================
//更新
//=============================================
void CPlayer::Update()
{
	//現在のシーンを取得
	CScene::MODE pScene = CScene::GetSceneMode();

	CCharacter::Update();

	//ダメージステートの切り替えTODO:これもステートパターンで
	ChangeDamageState();

	if (m_pPlayerState != nullptr)
	{
		m_pPlayerState->Default(this);
		m_pPlayerState->Ult(this);
		m_pPlayerState->Blown(this);
	}

	if (m_pHitCameraEffect != nullptr)
	{//使われていたら
		m_pHitCameraEffect->SubAlpha();

		if (m_pHitCameraEffect->GetAlpha() < 0.0f)
		{
			m_pHitCameraEffect->Uninit();
			m_pHitCameraEffect = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		m_apModel[nCnt]->SetOldPos(m_apModel[nCnt]->GetPos());
	}

	if (!m_isBlown)
	{//吹っ飛ばし状態じゃなければ
	//入力処理
		//Input();
	}
	else if (m_isBlown)
	{
		if (GetLaunding())
		{//着地したら
			//スタン状態に
			m_isBlown = false;
		}
	}

	//敵と判定をとる場合だったらとる
	//とらない場合はカウントアップ
	CanDetectEnemyCollision();

	//UI設定
	SetUI();

	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//状態を取得
		CCharacter::CHARACTER_STATE state = GetState();

		if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
		{
			//状態のカウント数取得
			int nStateCnt = GetStateCnt();

			//ステート変更カウント進める
			++nStateCnt;

			//ステートカウント代入
			SetStateCnt(nStateCnt);
		}

		if (m_isSmoke)
		{//スモークが使った状態だったら
			++m_SmokeRecastCnt;
			if (m_SmokeRecastCnt > SMOKE_RECAST_FRAME)
			{
				m_SmokeRecastCnt = 0;
				m_isSmoke = false;
			}
		}

		if (m_Stamina < PLAYER_STAMINA)
		{//スタミナが減ってたら

			++m_StaminaRecoveryCnt;
			if (m_StaminaRecoveryCnt >= STAMINA_RECOVERY_FRAME)
			{//カウントが到達したら

				//カウントリセット
				m_StaminaRecoveryCnt = 0;

				//スタミナ回復
				m_Stamina += STAMINA_RECOVERY;

				int nStaminaPer = m_Stamina % AVOIDANCE_COST;
				if (nStaminaPer == 0)
				{
					++m_BlinkCnt;
				}

				if (m_Stamina >= PLAYER_STAMINA)
				{//スタミナがデフォルト値に到達したら
					//スタミナ代入
					m_Stamina = PLAYER_STAMINA;
				}
			}
		}

		//カメラ情報取得
		CCamera* pCamera = CManager::GetInstance()->GetCamera();

		if(m_Raticle != nullptr)
		{
			m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 16.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
			m_Raticle->Update();
		}

		if (m_isRelorad)
		{//リロード中だったら
			m_isRelorad = m_pGun->Reload(); //リロードし終わったらfalseが返ってくる
		}

		Motion(NUM_PARTS); //モーション処理
	}

	//CCharacter::HitBlock(NUM_PARTS);
}

//=============================================
//UI設定
//=============================================
void CPlayer::SetUI()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetCurrentAmmo_UI(m_pGun->GetAmmo());
	}

	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->SetLife_UI(GetLife());
	}

	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->SetCurrentBlink_UI(this);
	}

	if (m_pUltUI != nullptr)
	{
		m_pUltUI->SetCurrentUlt_UI(this);
	}

	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->SetCurrentSmoke_UI(this);
	}
}

//=============================================
//敵との判定
//=============================================
void CPlayer::CanDetectEnemyCollision()
{
	if (m_isEnemyColision)
	{//敵との当たり判定をとる状態だったら
		ColisionEnemy();
	}
	else if (!m_isEnemyColision)
	{//敵との当たり判定をとらない状態だったら
		++m_IgnoreColisionCnt;

		if (m_IgnoreColisionCnt > IGNORE_COLLISION_FRAME)
		{//フレームに到達したら
		 //当たり判定をとる状態に
			m_IgnoreColisionCnt = 0;
			m_isEnemyColision = true;
		}
	}
}

//=============================================
//描画
//=============================================
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスのポインタ
	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// 比較参照値を設定する
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	// ステンシルマスクを指定する
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// ステンシル比較関数を指定する
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// ステンシル結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);	// Zテスト・ステンシルテスト成功
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Zテスト・ステンシルテスト失敗
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zテスト失敗・ステンシルテスト成功

	//親クラスのモーション用の描画を呼ぶ
	MotionDraw();
	// ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	//プレイヤーのデバッグ表示
	DebugPos();
}

//=============================================
//生成
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	CPlayer* pPlayer = new CPlayer;

	// nullならnullを返す
	if (pPlayer == nullptr) { return nullptr; }

	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //rot設定
	pPlayer->SetLife(nLife); //体力代入

		//パーツ読み込み
	pPlayer->Load_Parts("data\\motion_soldier.txt");

	pPlayer->Init(); //初期化処理

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定

	return pPlayer;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CPlayer::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();

	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0 && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//ダメージ状態以外でHPが残ってたら

		if (m_pHitCameraEffect == nullptr)
		{
			if (nLife >= CPlayer::PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MILD);
			}
			else if (nLife >= CPlayer::PLAYER_LIFE * 0.3f && nLife < CPlayer::PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MODERATE);
			}
			else if (nLife < CPlayer::PLAYER_LIFE * 0.3f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::SEVERE);
			}
		}

		nLife -= nDamage;

		//ダメージ状態に変更
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//状態代入
		SetState(state);

		//体力代入
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HPが0以下だったら
		//リスポーン
		ReSpawn();
	}
}

//=============================================
//リスポーン
//=============================================
void CPlayer::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 PlayerPos = GetPos();

	//スポーン時の設定にもどす
	SetPos(CPlayer::PLAYER_SPAWN_POS);
	SetMove({0.0f,0.0f,0.0f});
	SetBlown(false);
	SetRot(CPlayer::PLAYER_SPAWN_ROT);
	SetLife(CPlayer::PLAYER_LIFE);
	SetStamina(CPlayer::PLAYER_STAMINA);
	m_BlinkCnt = PLAYER_STAMINA / AVOIDANCE_COST;
	m_StaminaRecoveryCnt = 0;
	m_isSmoke = true; //スモークを使った状態にし死んだ時のデメリットを
	m_SmokeRecastCnt = 0;
	//TODO:キャラが違う場合は子クラスで実装
	m_pGun->SetAmmo(CAssultRifle::DEFAULT_AR_MAG_SIZE);
	ChangePlayerState(new CDefaultState);

	++m_DeathCnt;
}

//=============================================
//移動処理
//=============================================
void CPlayer::Input()
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//移動の方向の単位ベクトル変数
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);
	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.z += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += 1.0f;
	}

	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	CPlayer::Motion_Type Motion;

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		Motion = CPlayer::Motion_Type::MOTION_NEUTRAL;
	}
	else
	{
		Motion = CPlayer::Motion_Type::MOTION_MOVE;
	}

	D3DXVECTOR3 move = GetMove();
	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		move.x += sinf(rotMoveY) * GetSpeed();
		move.z += cosf(rotMoveY) * GetSpeed();
	}
	//親クラスからrotを取得
	D3DXVECTOR3 rot = GetRot();
	rot.y = rotMoveY + D3DX_PI;
	//rotを代入
	SetRot(rot);
	//移動量代入
	SetMove(move);

	//モーション代入
	SetMotion(Motion);

	if (pKeyboard->GetTrigger(DIK_LSHIFT))
	{
		if (m_Stamina >= AVOIDANCE_COST)
		{//スタミナがあれば
			//ブリンクSEを鳴らす
			CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BLINK);
			m_pAvoidance->Avoidance(this);
			m_Stamina -= AVOIDANCE_COST;

			--m_BlinkCnt;

			if (m_Stamina <= 0)
			{//スタミナが0を下回ったら
				m_Stamina = 0;
			}
		}
	}

	if (pKeyboard->GetPress(DIK_X))
	{
		if (m_pUlt != nullptr)
		{
			if (m_pUlt->GetCoolTimeCnt() >= m_pUlt->GetCoolTime())
			{
				pCamera->ChangeCameraState(new CUltCameraState);
				ChangePlayerState(new CUltState);
				m_pUltUI->Reset(); //UIのリセット処理
				
				m_isEnemyColision = false;
			}
		}
	}
	
	if (pMouse->GetPress(1))
	{//マウスが押されてる間は
		//射撃状態に変更
		ChangeState(new CShotState);

		//モーションを変更 TODO:覗きこむモーションに
		SetMotion(MOTION_NEUTRAL);

		ResetRot(); //レティクルのほうを向きたいので

		if (m_Raticle == nullptr)
		{//使われていなかったら
			m_Raticle = new CReticle;

			//値を代入
			m_Raticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
			m_Raticle->SetSize({5.0f,5.0f,0.0f});

			m_Raticle->Init();
		}
		m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_PLAYER, CBullet::BULLET_TYPE_NORMAL, this);
	}

	if (pMouse->GetRelease(1))
	{//マウスが離されたら
		//移動状態に変更
		ChangeState(new CMoveState);

		if(m_Raticle != nullptr)
		{//使われていたら
			m_Raticle->Uninit();
			m_Raticle = nullptr;
		}
	}

	if (pKeyboard->GetTrigger(DIK_R) && !pMouse->GetPress(0))
	{
		if (m_pGun->GetAmmo() < CAssultRifle::DEFAULT_AR_MAG_SIZE)
		{
			//リロード
			m_isRelorad = true;
		}
	}

	if (!m_isSmoke)
	{
		if (pKeyboard->GetTrigger(DIK_Q))
		{
			m_isSmoke = true;
			CSmokeGrenade::Create({ GetPos().x,GetPos().y + 50.0f,GetPos().z }, { sinf(pCamera->GetRot().y + D3DX_PI) * -20.0f,
					sinf(pCamera->GetRot().x + D3DX_PI) * 20.0f,
					cosf(pCamera->GetRot().y + D3DX_PI) * -20.0f }, { 0.0f,0.0f,0.0f });
		}
	}
}

//=============================================
//プレイヤーのステート変更
//=============================================
void CPlayer::ChangePlayerState(CPlayerState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pPlayerState != nullptr)
	{
		delete m_pPlayerState;
		m_pPlayerState = state;
	}
}

//=============================================
//プレイヤーの方向をカメラのほうへ
//=============================================
void CPlayer::ResetRot()
{
	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y;

	//親クラスからrotを取得
	D3DXVECTOR3 rot = GetRot();

	rot.y = rotMoveY + D3DX_PI;

	SetRot(rot);
}

//=============================================
//エネミーとの当たり判定
//=============================================
void CPlayer::ColisionEnemy()
{
	for (int nPartsCnt = 0; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//オブジェクトに要素が入っていたら
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				//ブロックとの当たり判定
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
				{
					//安全にダウンキャスト
					CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

					CheckColisionEnemy(pEnemy, nPartsCnt, pos, Minpos, Maxpos);
				}
			}
		}
	}
}

//=============================================
//ダメージ状態の切り替え
//=============================================
void CPlayer::ChangeDamageState()
{
	// 状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//状態のカウント数取得
		int nStateCnt = GetStateCnt();

		//ステート変更カウント進める
		nStateCnt++;

		if (nStateCnt >= 30)
		{
			//通常に戻す
			state = CCharacter::CHARACTER_STATE::CHARACTER_NORMAL;

			//ステートカウントリセット
			nStateCnt = 0;

			//状態代入
			SetState(state);
		}
		//ステートカウント代入
		SetStateCnt(nStateCnt);
	}
}

//=============================================
//敵との当たり判定
//=============================================
void CPlayer::CheckColisionEnemy(CEnemy* pEnemy, int nPartsCnt, const D3DXVECTOR3& pos, const D3DXVECTOR3& Minpos, const D3DXVECTOR3& Maxpos)
{
	for (int nEnemyPartsCnt = 0; nEnemyPartsCnt < pEnemy->GetNumParts(); nEnemyPartsCnt++)
	{
		D3DXVECTOR3 Enemypos = { pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._41,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._42,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._43 };

		D3DXVECTOR3 EnemyMinpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMin();
		D3DXVECTOR3 EnemyMaxpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMax();
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColisionSphere(pos, Minpos, Maxpos,
			Enemypos, EnemyMinpos, EnemyMaxpos);

		if (colision == CColision::COLISION::COLISON_X)
		{
			// X軸衝突時の処理
			SetPos({ GetOldPos().x, GetPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_TOP_Y)
		{
			// X軸衝突時の処理
			SetPos({ GetPos().x, GetOldPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_Z)
		{
			// X軸衝突時の処理
			SetPos({ GetPos().x, GetPos().y, GetOldPos().z });
		}
	}
}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void CPlayer::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n弾数:%d\n体力:%d\nスタミナ:%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z, m_pGun->GetAmmo(),GetLife(),GetStamina());
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
