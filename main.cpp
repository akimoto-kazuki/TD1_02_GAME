#include <Novice.h>

const char kWindowTitle[] = "LC1C_02_アキモト_カズキ";

struct Vector2 {
	float x;
	float y;
};

enum SCENE
{
	TITLE,
	TUTORIAL,
	GAMEPLAY,
	GAMECLEAR,
	GAMEOVER,
	NOWLOADING,
};

struct OWNMACHINE {

#pragma region 自機の位置

	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;

#pragma endregion

#pragma region 攻撃の判定

	Vector2 attackLeftTop;
	Vector2 attackRightTop;
	Vector2 attackLeftBottom;
	Vector2 attackRightBottom;

#pragma endregion

	int HP;
	int speed;
	

};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int scene = TITLE;

#pragma region タイトル関係の関数



#pragma endregion

#pragma region チュートリアル関係の関数



#pragma endregion

#pragma region ゲーム関係の関数

#pragma region プレイヤー

	OWNMACHINE player;

#pragma region 自機の位置

	player.leftTop = { 0,0 };
	player.rightTop = { 0,0 };
	player.leftBottom = { 0,0 };
	player.rightBottom = { 0,0 };

#pragma endregion

#pragma region 攻撃の判定

	player.attackLeftTop = { 0,0 };
	player.attackRightTop = { 0,0 };
	player.attackLeftBottom = { 0,0 };
	player.attackRightBottom = { 0,0 };

#pragma endregion

	player.HP = 0;
	player.speed = 5;

	int spell1 = false;
	int spell2 = false;
	int spell3 = false;

#pragma endregion

#pragma region 敵

	OWNMACHINE enemy;

#pragma region 自機の位置

	enemy.leftTop = { 0,0 };
	enemy.rightTop = { 0,0 };
	enemy.leftBottom = { 0,0 };
	enemy.rightBottom = { 0,0 };

#pragma endregion

#pragma region 攻撃の判定

	enemy.attackLeftTop = { 0,0 };
	enemy.attackRightTop = { 0,0 };
	enemy.attackLeftBottom = { 0,0 };
	enemy.attackRightBottom = { 0,0 };

#pragma endregion

	enemy.HP = 0;
	enemy.speed = 5;

#pragma endregion

	int startTimer = 0;
	int startSecond = 0;

#pragma endregion

#pragma region ゲームクリアとゲームオーバー関係の関数



#pragma endregion

#pragma region 描画

	int white1x1GH =
		Novice::LoadTexture("./white1x1.png");

#pragma endregion

#pragma region BGM



#pragma endregion

#pragma region SE



#pragma endregion

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

#pragma region scene

		switch (scene)
		{
		case TITLE:
			break;
		case TUTORIAL:
			break;
		case GAMEPLAY:
			break;
		case GAMECLEAR:
			break;
		case GAMEOVER:
			break;
		case NOWLOADING:
			break;
		}

#pragma endregion

		if (scene == TITLE)
		{
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				//scene = TUTORIAL;
				scene = GAMEPLAY;
				//startTimer = 180;
				startTimer = 0;

#pragma region プレイヤー

#pragma region 自機の位置

				player.leftTop = { 10,10 };
				player.rightTop = { 30,10 };
				player.leftBottom = { 10,30 };
				player.rightBottom = { 30,30 };

#pragma endregion

#pragma region 攻撃の判定

				player.attackLeftTop = { 0,0 };
				player.attackRightTop = { 0,0 };
				player.attackLeftBottom = { 0,0 };
				player.attackRightBottom = { 0,0 };

#pragma endregion

				player.HP = 0;
				player.speed = 5;

				spell1 = false;
				spell2 = false;
				spell3 = false;

#pragma endregion
			}
		}

		if (scene == TUTORIAL)
		{

		}

		if (scene == GAMEPLAY)
		{

#pragma region スタート処理

			if (startTimer > 0)
			{
				startTimer--;

				if (startTimer <= 60)
				{
					startSecond = 0;
				}
				else if (startTimer <= 120)
				{
					startSecond = 1;
				}
				else if (startTimer <= 180)
				{
					startSecond = 2;
				}
				else if (startTimer <= 240)
				{
					startSecond = 3;
				}
			}

#pragma endregion

			if (startTimer <= 0)
			{

#pragma region プレイヤー処理

#pragma region 移動処理

				if (keys[DIK_W] && !preKeys[DIK_W] || keys[DIK_SPACE] && !preKeys[DIK_SPACE])
				{

				}
				if (keys[DIK_A])
				{
					player.leftTop.x -= player.speed;
					player.rightTop.x -= player.speed;
					player.leftBottom.x -= player.speed;
					player.rightBottom.x -= player.speed;
				}
				if (keys[DIK_S] && !preKeys[DIK_S])
				{

				}
				if (keys[DIK_D])
				{
					player.leftTop.x += player.speed;
					player.rightTop.x += player.speed;
					player.leftBottom.x += player.speed;
					player.rightBottom.x += player.speed;
				}

#pragma endregion

#pragma region 攻撃処理

				if (keys[DIK_J] && !preKeys[DIK_J])//物理
				{

				}
				if (spell1)//カード１
				{
					if (keys[DIK_K] && !preKeys[DIK_K])
					{

					}
				}
				if (spell2)//カード2
				{
					if (keys[DIK_L] && !preKeys[DIK_L])
					{

					}
				}
				if (spell3)//カード3
				{
					if (keys[DIK_SEMICOLON] && !preKeys[DIK_SEMICOLON])//+キー
					{

					}
				}

#pragma endregion

#pragma endregion

#pragma region 敵処理



#pragma endregion

			}

		}

		if (scene == GAMECLEAR)
		{
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				scene = TITLE;
			}
		}

		if (scene == GAMEOVER)
		{
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE])
			{
				scene = TITLE;
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

#pragma region scene

		switch (scene)
		{
		case TITLE:
			break;
		case TUTORIAL:
			break;
		case GAMEPLAY:
			break;
		case GAMECLEAR:
			break;
		case GAMEOVER:
			break;
		case NOWLOADING:
			break;
		}

#pragma endregion

		if (scene == TITLE)
		{

		}

		if (scene == TUTORIAL)
		{

		}

		if (scene == GAMEPLAY)
		{
			if (startTimer > 0)
			{
				if (startSecond == 3)
				{

				}
				if (startSecond == 2)
				{

				}
				if (startSecond == 1)
				{

				}
				if (startSecond == 0)
				{

				}
			}
			Novice::DrawQuad(
				static_cast<int>(player.leftTop.x), static_cast<int>(player.leftTop.y),
				static_cast<int>(player.rightTop.x), static_cast<int>(player.rightTop.y),
				static_cast<int>(player.leftBottom.x), static_cast<int>(player.leftBottom.y),
				static_cast<int>(player.rightBottom.x), static_cast<int>(player.rightBottom.y),
				1, 1, 10, 10, white1x1GH, 0xffffffff);
			Novice::DrawQuad(
				static_cast<int>(enemy.leftTop.x), static_cast<int>(enemy.leftTop.y),
				static_cast<int>(enemy.rightTop.x), static_cast<int>(enemy.rightTop.y),
				static_cast<int>(enemy.leftBottom.x), static_cast<int>(enemy.leftBottom.y),
				static_cast<int>(enemy.rightBottom.x), static_cast<int>(enemy.rightBottom.y),
				1, 1, 10, 10, white1x1GH, 0xffffffff);
		}

		if (scene == GAMECLEAR)
		{

		}

		if (scene == GAMEOVER)
		{

		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
