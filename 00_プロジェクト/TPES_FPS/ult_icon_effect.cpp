//=============================================
//
//ultが溜まったときにアイコンから出すエフェクト[ult_icon_effect.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "ult_icon_effect.h"
#include "manager.h"

const std::string CUltIconEffect::TEXTURE_NAME = "data\\TEXTURE\\ult_icon_effect_anim.png";

//=============================================
// コンストラクタ
//=============================================
CUltIconEffect::CUltIconEffect(int nPriority):CObject2D_Anim(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CUltIconEffect::~CUltIconEffect()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CUltIconEffect::Init()
{
	//テクスチャ設定
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	//親クラスの初期化
	CObject2D::Init();

	//テクスチャ移動量取得
	D3DXVECTOR2 tex_move = GetTexMove();
	tex_move.x = 1.0f / (float)TEX_SPLIT_X;
	tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
	//テクスチャ移動量代入
	SetTexMove(tex_move);

	//テクスチャ座標取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//テクスチャ座標代入
	SetTexPos(tex_pos);

	//アニメーションフレーム代入
	SetAnimFrame(ANIMATION_FRAME);

	SetVtx(1.0f);

	//頂点座標
	AnimationTex(tex_pos, tex_move);

	return S_OK;
}

//=============================================
// 終了
//=============================================
void CUltIconEffect::Uninit()
{
	CObject2D_Anim::Uninit();
}

//=============================================
// 更新
//=============================================
void CUltIconEffect::Update()
{
	CObject2D_Anim::Update();

	//テクスチャ情報取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	D3DXVECTOR2 tex_move = GetTexMove();
	//アニメーション後のテクスチャ座標取得
	tex_pos = GetTexPos();
	//アニメーションを繰り返す
	if (tex_pos.x >= 1.0f)
	{
		tex_pos.x = 0.0f;
	}
	SetTexPos(tex_pos);

	SetVtx(1.0f);

	//頂点座標
	AnimationTex(tex_pos, tex_move);
}

//=============================================
// 描画
//=============================================
void CUltIconEffect::Draw()
{
	CObject2D_Anim::Draw();
}

//=============================================
// 生成
//=============================================
CUltIconEffect* CUltIconEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CUltIconEffect* pIconEffect = new CUltIconEffect;

	//中身がないなら代入の前にreturn
	if(pIconEffect == nullptr) {return nullptr;}

	pIconEffect->SetPos(pos);
	pIconEffect->SetSize(size);
	pIconEffect->SetColor(col);

	pIconEffect->Init();

	return pIconEffect;
}
