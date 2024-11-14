#include <Novice.h>
#include <time.h>

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

	Vector2 centerPos;

#pragma endregion

#pragma region 攻撃の判定

	Vector2 attackLeftTop;
	Vector2 attackRightTop;
	Vector2 attackLeftBottom;
	Vector2 attackRightBottom;

#pragma endregion

	int HP;
	int speed;

	int isJump;
	float jumpSpeed;

};

struct CARD {
	int leftTopX[5];
	int leftTopY[5];
	int rightTopX[5];
	int rightTopY[5];
	int leftBottomX[5];
	int leftBottomY[5];
	int rightBottomX[5];
	int rightBottomY[5];
};

int map(float playerPos)
{
	return static_cast<int>(playerPos / 32);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int scene = TITLE;

	int attack = 0;

	unsigned int currentTime = static_cast<int>(time(nullptr));
	srand(currentTime);

	const int mapChipsX = 62;
	const int mapChipsY = 17;
	int mapChips[mapChipsY][mapChipsX] =
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },//1
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//2
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//3
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//4
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//5
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//6
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//7
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//8
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//9
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//10
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//11
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//12
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//13
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//14
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//15
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//16
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } //17
	};

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
	player.centerPos = { 0,0 };

#pragma endregion

#pragma region 攻撃の判定

	player.attackLeftTop = { 0,0 };
	player.attackRightTop = { 0,0 };
	player.attackLeftBottom = { 0,0 };
	player.attackRightBottom = { 0,0 };

#pragma endregion

	player.HP = 0;
	player.speed = 5;

	player.isJump = false;
	int playerIsJump2 = false;
	player.jumpSpeed = 0.0f;
	int playerJumpTimer = 0;

	const int playerRed = 16;

	int spell1 = false;
	int spell2 = false;
	int spell3 = false;

	int playerDirection = 0;

#pragma endregion

#pragma region 敵

	OWNMACHINE boss;

#pragma region 自機の位置

	boss.leftTop = { 0,0 };
	boss.rightTop = { 0,0 };
	boss.leftBottom = { 0,0 };
	boss.rightBottom = { 0,0 };
	boss.centerPos = { 0,0 };

#pragma endregion

#pragma region 攻撃の判定

	boss.attackLeftTop = { 0,0 };
	boss.attackRightTop = { 0,0 };
	boss.attackLeftBottom = { 0,0 };
	boss.attackRightBottom = { 0,0 };

#pragma endregion

	boss.HP = 0;
	boss.speed = 5;

	const int bossRed = 16;

	int bossDirection = 0;

#pragma endregion

#pragma region カード

	const int MaxCard = 5;

	int cardSpoon[MaxCard] = { false };
	CARD card;
	for (int i = 0; i < MaxCard; i++)
	{
		card.leftTopX[i] = { 0 };
		card.leftTopY[i] = { 0 };
		card.leftBottomX[i] = { 0 };
		card.leftBottomY[i] = { 0 };
		card.rightTopX[i] = { 0 };
		card.rightTopY[i] = { 0 };
		card.rightBottomX[i] = { 0 };
		card.rightBottomY[i] = { 0 };
	}
	int cardMotionTimer[MaxCard] = { 0 };
	int cardMotionSecond[MaxCard] = { 0 };
	int cardKinds[MaxCard] = { 0 };
	int cardSpoonTimer = 10;

#pragma endregion

#pragma region ゲームクリアとゲームオーバー関係の関数



#pragma endregion

#pragma region 描画

	int white1x1GH =
		Novice::LoadTexture("./NoviceResources/white1x1.png");

#pragma region ステージ

	int blockGH =
		Novice::LoadTexture("./Resources/STAGE/block.png");
	int stageGH =
		Novice::LoadTexture("./Resources/STAGE/starg.png");

#pragma endregion

#pragma region カード

	int attackCardGH =
		Novice::LoadTexture("./Resources/CARD/attack.png");
	int buffCardGH =
		Novice::LoadTexture("./Resources/CARD/buff.png");
	int deBuffCardGH =
		Novice::LoadTexture("./Resources/CARD/debuff.png");

#pragma endregion

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
				startTimer = 20;

#pragma region プレイヤー

#pragma region 自機の位置

				player.leftTop = { 32,480 };
				player.rightTop = { 64,480 };
				player.leftBottom = { 32,512 };
				player.rightBottom = { 64,512 };
				player.centerPos = { 48,496 };

#pragma endregion

#pragma region 攻撃の判定

				player.attackLeftTop = { 0,0 };
				player.attackRightTop = { 0,0 };
				player.attackLeftBottom = { 0,0 };
				player.attackRightBottom = { 0,0 };

#pragma endregion

				player.HP = 0;
				player.speed = 10;

				player.isJump = false;
				playerIsJump2 = false;
				playerJumpTimer = 0;

				spell1 = false;
				spell2 = false;
				spell3 = false;

				playerDirection = 1;

#pragma endregion

#pragma region ボス

#pragma region 自機の位置

				boss.leftTop = { 1920,480 };
				boss.rightTop = { 1952,480 };
				boss.leftBottom = { 1920,512 };
				boss.rightBottom = { 1952,512 };

				boss.centerPos = { 1936,496 };

#pragma endregion

#pragma region 攻撃の判定

				boss.attackLeftTop = { 0,0 };
				boss.attackRightTop = { 0,0 };
				boss.attackLeftBottom = { 0,0 };
				boss.attackRightBottom = { 0,0 };

#pragma endregion

				boss.HP = 0;
				boss.speed = 5;

				bossDirection = 2;

#pragma endregion

#pragma region カード

				for (int i = 0; i < MaxCard; i++)
				{
					cardSpoon[i] = { false };
					card.leftTopX[i] = { 0 };
					card.leftTopY[i] = { 0 };
					card.leftBottomX[i] = { 0 };
					card.leftBottomY[i] = { 0 };
					card.rightTopX[i] = { 0 };
					card.rightTopY[i] = { 0 };
					card.rightBottomX[i] = { 0 };
					card.rightBottomY[i] = { 0 };
					cardMotionTimer[i] = { 0 };
					cardMotionSecond[i] = { 0 };
				}
				cardSpoonTimer = 10;

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

				if (keys[DIK_W] && !preKeys[DIK_W] ||
					keys[DIK_SPACE] && !preKeys[DIK_SPACE]
					)
				{
					if (playerJumpTimer <= 0)
					{
						if (!playerIsJump2)
						{
							if (!player.isJump)
							{
								player.jumpSpeed = -10.0f;
								player.isJump = true;
								playerJumpTimer = 10;
							}
							else if (!playerIsJump2)
							{
								player.jumpSpeed = -10.0f;
								playerIsJump2 = true;
							}
						}
					}
				}

				if (player.isJump)
				{
					player.centerPos.y += player.jumpSpeed;
					player.jumpSpeed += 0.2f;
				}

				if (playerJumpTimer > 0)
				{
					playerJumpTimer--;
				}

				if (player.centerPos.y > 496)
				{
					player.isJump = false;
					playerIsJump2 = false;
					player.centerPos.y = 496;
				}

				if (keys[DIK_A])
				{
					playerDirection = 2;
					player.leftTop.x = (player.centerPos.x - playerRed - player.speed);
					player.leftBottom.x = (player.centerPos.x - playerRed - player.speed);
					if (
						mapChips[map(player.leftBottom.y)][map(player.leftBottom.x)] == 0 &&
						mapChips[map(player.leftTop.y)][map(player.leftTop.x)] == 0
						)
					{
						player.centerPos.x -= player.speed;
					}
				}
				if (keys[DIK_D])
				{
					playerDirection = 1;
					player.rightTop.x = (player.centerPos.x + playerRed + player.speed - 1);
					player.rightBottom.x = (player.centerPos.x + playerRed + player.speed - 1);
					if (
						mapChips[map(player.rightBottom.y)][map(player.rightBottom.x)] == 0 &&
						mapChips[map(player.rightTop.y)][map(player.rightTop.x)] == 0
						)
					{
						player.centerPos.x += player.speed;
					}
				}
				if (
					mapChips[map(player.rightBottom.y)][map(player.rightBottom.x)] == 1 &&
					mapChips[map(player.leftBottom.y)][map(player.leftBottom.x)] == 1
					)
				{
					player.isJump = false;
				}
				if (
					mapChips[map(player.rightTop.y)][map(player.rightTop.x)] == 1 &&
					mapChips[map(player.leftTop.y)][map(player.leftTop.x)] == 1
					)
				{
					player.centerPos.y = 48.0f;
					player.jumpSpeed = 0.0f;
				}

#pragma endregion

#pragma region プレイヤー更新処理

				player.leftTop.x = (player.centerPos.x - playerRed);
				player.leftTop.y = (player.centerPos.y - playerRed);
				player.rightTop.x = (player.centerPos.x + playerRed - 1);
				player.rightTop.y = (player.centerPos.y - playerRed);
				player.leftBottom.x = (player.centerPos.x - playerRed);
				player.leftBottom.y = (player.centerPos.y + playerRed - 1);
				player.rightBottom.x = (player.centerPos.x + playerRed - 1);
				player.rightBottom.y = (player.centerPos.y + playerRed - 1);


#pragma endregion

#pragma region 攻撃処理

				if (keys[DIK_H] && !preKeys[DIK_H])//物理
				{
					if (playerDirection == 1)
					{
						if (
							boss.leftTop.x <= player.attackRightTop.x &&
							player.attackLeftTop.x <= boss.rightTop.x &&
							boss.leftTop.y <= player.attackLeftTop.y &&
							player.attackLeftBottom.y <= boss.leftBottom.y)
						{
							attack = 1;
						}
						else
						{
							attack = 0;
						}
					}
					if (playerDirection == 2)
					{
						if (
							boss.leftTop.x <= player.attackRightTop.x &&
							player.attackLeftTop.x <= boss.rightTop.x &&
							boss.rightTop.y <= player.attackLeftTop.y &&
							player.attackLeftBottom.y <= boss.rightBottom.y)
						{
							attack = 1;
						}
						else
						{
							attack = 0;
						}
					}
				}
				if (spell1)//カード１
				{
					if (keys[DIK_J] && !preKeys[DIK_J])
					{

					}
				}
				if (spell2)//カード2
				{
					if (keys[DIK_K] && !preKeys[DIK_K])
					{

					}
				}
				if (spell3)//カード3
				{
					if (keys[DIK_L] && !preKeys[DIK_L])
					{

					}
				}

#pragma endregion

#pragma endregion

#pragma region ボス処理

#pragma region 移動+攻撃処理

				if (boss.centerPos.x > player.centerPos.x)
				{
					bossDirection = 2;
					if (
						player.leftTop.x <= boss.attackRightTop.x &&
						boss.attackLeftTop.x <= player.rightTop.x &&
						player.rightTop.y <= boss.attackLeftTop.y &&
						boss.attackLeftBottom.y <= player.rightBottom.y
						)
					{
						attack = 1;
					}
					else
					{
						boss.leftTop.x = (boss.centerPos.x - bossRed - boss.speed);
						boss.leftBottom.x = (boss.centerPos.x - bossRed - boss.speed);
						if (
							mapChips[map(boss.leftBottom.y)][map(boss.leftBottom.x)] == 0 &&
							mapChips[map(boss.leftTop.y)][map(boss.leftTop.x)] == 0
							)
						{
							boss.centerPos.x -= boss.speed;
						}
						attack = 0;
					}


				}

				if (boss.centerPos.x < player.centerPos.x)
				{
					bossDirection = 1;
					if (
						player.leftTop.x <= boss.attackRightTop.x &&
						boss.attackLeftTop.x <= player.rightTop.x &&
						player.leftTop.y <= boss.attackRightTop.y &&
						boss.attackRightBottom.y <= player.leftBottom.y
						)
					{
						attack = 1;
					}
					else
					{
						boss.rightTop.x = (boss.centerPos.x + bossRed + boss.speed - 1);
						boss.rightBottom.x = (boss.centerPos.x + bossRed + boss.speed - 1);
						if (
							mapChips[map(boss.rightBottom.y)][map(boss.rightBottom.x)] == 0 &&
							mapChips[map(boss.rightTop.y)][map(boss.rightTop.x)] == 0
							)
						{
							boss.centerPos.x += boss.speed;
						}
						attack = 0;
					}
				}

#pragma endregion

#pragma region ボス更新処理

				boss.leftTop.x = (boss.centerPos.x - bossRed);
				boss.leftTop.y = (boss.centerPos.y - bossRed);
				boss.rightTop.x = (boss.centerPos.x + bossRed - 1);
				boss.rightTop.y = (boss.centerPos.y - bossRed);
				boss.leftBottom.x = (boss.centerPos.x - bossRed);
				boss.leftBottom.y = (boss.centerPos.y + bossRed - 1);
				boss.rightBottom.x = (boss.centerPos.x + bossRed - 1);
				boss.rightBottom.y = (boss.centerPos.y + bossRed - 1);


#pragma endregion

#pragma endregion

#pragma region カード処理

#pragma region スポーン処理

				for (int i = 0; i < MaxCard; i++)
				{

					if (!cardSpoon[i])
					{
						if (cardSpoonTimer <= 0)
						{
							card.leftTopX[i] = rand() % 1856 + 32;
							card.leftTopY[i] = rand() % 352 + 32;
							cardSpoon[i] = true;
							cardKinds[i] = rand() % 5 + 1;
							cardSpoonTimer = 60;
							card.leftBottomX[i] = card.leftTopX[i];
							card.leftBottomY[i] = (card.leftTopY[i] + 64);
							card.rightTopX[i] = (card.leftTopX[i] + 64);
							card.rightTopY[i] = card.leftTopY[i];
							card.rightBottomX[i] = (card.leftTopX[i] + 64);
							card.rightBottomY[i] = (card.leftTopY[i] + 64);
							break;
						}

						if (cardSpoonTimer >= 0)
						{
							cardSpoonTimer--;
						}
					}
				}


				for (int i = 0; i < MaxCard; i++)
				{
					if (cardSpoon[i])
					{
						cardMotionTimer[i]++;
						if (cardMotionTimer[i] >= 20)
						{
							cardMotionTimer[i] = 0;
							cardMotionSecond[i] += 1;
						}
						if (cardMotionSecond[i] > 11)
						{
							cardMotionSecond[i] = 0;
						}
					}
				}

#pragma endregion

#pragma region 当たり判定処理

				for (int i = 0; i < MaxCard; i++)
				{
					if (cardSpoon[i])
					{
						if (card.leftTopX[i] <= player.rightTop.x &&
							player.leftTop.x <= card.rightTopX[i]
							)//ジャンプが出来たらY軸も足す
						{
							if (cardKinds[i] == 1 || cardKinds[i] == 2 || cardKinds[i] == 3)
							{

#pragma region 拾えるかの処理

								if (!spell1)
								{
									spell1 = true;
								}
								else if (!spell2)
								{
									spell2 = true;
								}
								else if (!spell3)
								{
									spell3 = true;
								}

#pragma endregion

							}
							else if (cardKinds[i] == 4)
							{

#pragma region 拾えるかの処理

								if (!spell1)
								{
									spell1 = true;
								}
								else if (!spell2)
								{
									spell2 = true;
								}
								else if (!spell3)
								{
									spell3 = true;
								}

#pragma endregion

							}
							else if (cardKinds[i] == 5)
							{

#pragma region 拾えるかの処理

								if (!spell1)
								{
									spell1 = true;
								}
								else if (!spell2)
								{
									spell2 = true;
								}
								else if (!spell3)
								{
									spell3 = true;
								}

#pragma endregion

							}
						}
					}
				}

#pragma endregion

#pragma endregion

			}

		}

#pragma region 攻撃範囲処理

		if (scene == GAMEPLAY)
		{

#pragma region プレイヤー

			if (playerDirection == 1)
			{
				player.attackLeftTop = player.rightTop;
				player.attackLeftBottom = player.rightBottom;
				player.attackRightTop.x = (player.rightTop.x + 32);
				player.attackRightTop.y = player.rightTop.y;
				player.attackRightBottom.x = (player.rightBottom.x + 32);
				player.attackRightBottom.y = player.rightBottom.y;
			}
			if (playerDirection == 2)
			{
				player.attackLeftTop.x = (player.leftTop.x - 32);
				player.attackLeftTop.y = player.leftTop.y;
				player.attackLeftBottom.x = (player.leftBottom.x - 32);
				player.attackLeftBottom.y = player.leftBottom.y;
				player.attackRightTop = player.leftTop;
				player.attackRightBottom = player.leftBottom;
			}

#pragma endregion

#pragma region ボス

			if (bossDirection == 1)
			{
				boss.attackLeftTop = boss.rightTop;
				boss.attackLeftBottom = boss.rightBottom;
				boss.attackRightTop.x = (boss.rightTop.x + 32);
				boss.attackRightTop.y = boss.rightTop.y;
				boss.attackRightBottom.x = (boss.rightBottom.x + 32);
				boss.attackRightBottom.y = boss.rightBottom.y;
			}
			if (bossDirection == 2)
			{
				boss.attackLeftTop.x = (boss.leftTop.x - 32);
				boss.attackLeftTop.y = boss.leftTop.y;
				boss.attackLeftBottom.x = (boss.leftBottom.x - 32);
				boss.attackLeftBottom.y = boss.leftBottom.y;
				boss.attackRightTop = boss.leftTop;
				boss.attackRightBottom = boss.leftBottom;
			}

#pragma endregion

		}

#pragma endregion

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

		//ステージ
		if (scene == GAMEPLAY)
		{
			for (int y = 0; y < mapChipsY; y++)//y軸 縦
			{
				for (int x = 0; x < mapChipsX; x++)//x軸 横
				{
					if (mapChips[y][x] == 0) //特定のマップチップが0なら
					{
						Novice::DrawSprite((32 * x), (32 * y), blockGH, 1, 1, 0.0f, 0xffffffff);
					}
					if (mapChips[y][x] == 1) //特定のマップチップが1なら
					{
						Novice::DrawSprite((32 * x), (32 * y), blockGH, 1, 1, 0.0f, 0x808080ff);
					}
				}
			}

			Novice::DrawSprite(0, 0, stageGH, 1, 1, 0.0f, 0xffffffff);

		}


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

#pragma region プレイヤー

			Novice::DrawQuad(
				static_cast<int>(player.leftTop.x), static_cast<int>(player.leftTop.y),
				static_cast<int>(player.rightTop.x), static_cast<int>(player.rightTop.y),
				static_cast<int>(player.leftBottom.x), static_cast<int>(player.leftBottom.y),
				static_cast<int>(player.rightBottom.x), static_cast<int>(player.rightBottom.y),
				1, 1, 10, 10, white1x1GH, 0xffffffff);
			Novice::DrawQuad(
				static_cast<int>(player.attackLeftTop.x), static_cast<int>(player.attackLeftTop.y),
				static_cast<int>(player.attackRightTop.x), static_cast<int>(player.attackRightTop.y),
				static_cast<int>(player.attackLeftBottom.x), static_cast<int>(player.attackLeftBottom.y),
				static_cast<int>(player.attackRightBottom.x), static_cast<int>(player.attackRightBottom.y),
				1, 1, 10, 10, white1x1GH, RED);

#pragma endregion

#pragma region ボス

			Novice::DrawQuad(
				static_cast<int>(boss.leftTop.x), static_cast<int>(boss.leftTop.y),
				static_cast<int>(boss.rightTop.x), static_cast<int>(boss.rightTop.y),
				static_cast<int>(boss.leftBottom.x), static_cast<int>(boss.leftBottom.y),
				static_cast<int>(boss.rightBottom.x), static_cast<int>(boss.rightBottom.y),
				1, 1, 10, 10, white1x1GH, 0xffffffff);
			Novice::DrawQuad(
				static_cast<int>(boss.attackLeftTop.x), static_cast<int>(boss.attackLeftTop.y),
				static_cast<int>(boss.attackRightTop.x), static_cast<int>(boss.attackRightTop.y),
				static_cast<int>(boss.attackLeftBottom.x), static_cast<int>(boss.attackLeftBottom.y),
				static_cast<int>(boss.attackRightBottom.x), static_cast<int>(boss.attackRightBottom.y),
				1, 1, 10, 10, white1x1GH, RED);

#pragma endregion

#pragma region カード

			for (int i = 0; i < MaxCard; i++)
			{
				if (cardSpoon[i])
				{
					if (cardKinds[i] == 1 || cardKinds[i] == 2 || cardKinds[i] == 3)
					{
						Novice::DrawSpriteRect(
							card.leftTopX[i], card.leftTopY[i], (64 * (cardMotionSecond[i])), 0, 64, 64, attackCardGH, 0.08f, 1.0f, 0.0f, 0xffffffff
						);
					}
					if (cardKinds[i] == 4)
					{
						Novice::DrawSpriteRect(
							card.leftTopX[i], card.leftTopY[i], (64 * (cardMotionSecond[i])), 0, 64, 64, buffCardGH, 0.08f, 1.0f, 0.0f, 0xffffffff
						);
					}
					if (cardKinds[i] == 5)
					{
						Novice::DrawSpriteRect(
							card.leftTopX[i], card.leftTopY[i], (64 * (cardMotionSecond[i])), 0, 64, 64, deBuffCardGH, 0.08f, 1.0f, 0.0f, 0xffffffff
						);
					}
				}
			}




#pragma endregion

			Novice::ScreenPrintf(0, 0, "attack = %d", attack);
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
