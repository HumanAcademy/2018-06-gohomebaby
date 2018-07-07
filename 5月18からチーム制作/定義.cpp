#include "XLibrary11.hpp"
#include<string>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
using namespace XLibrary11;

//モード分け
enum Mode
{
	Title,
	game1,
	game2,
	game3,
	clear1,
	clear2,
	clear3,
	clear4,
	clear5,
	clear6,

	bad,
};

int main()
{
	int stage = 1;      //タイトルで選択できるステージの数
	int STAGE = 1;		//現在のステージ
	int x;				//永遠に増える数
	int i = 0;			//ランダムな数
	int chara1a = 0;	//aキャラクターが振り向く予定の方向
	int chara1b = 0;	//bキャラクターが振り向く予定の方向
	int chara2a = 0;	//aキャラクターが向いている方向
	int chara2b = 0;	//bキャラクターが向いている方向
	int chara2c = 0;	//cキャラクターが向いている方向
	int chara3a = 0;	//aリアクションするまでの時間
	int chara3b = 0;	//bリアクションするまでの時間
	int chara4a = 0;	//aリアクションしてから振り向くまでの時間
	int chara4b = 0;	//bリアクションしてから振り向くまでの時間
	int chara5 = 0;		//ランダムで決まるキャラクターの向き
	int mouse = 0;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
	int lifetime = 0;	//キャラクターのHPを減らすまでの時間
	int life = 0;	    //キャラクターのHP.恐怖ゲージの画像のための数
	int life2 = 0;		//プレイヤーのHP
	int time = 0; //制限時間
	int timea = 0; //制限時間の画像の表示
	int time2a = 0; //Velocityの管理時間
	int time3a = 0; //物が動いてから次動くまでの待機時間
	int time2b = 0; //Velocityの管理時間
	int time3b = 0; //物が動いてから次動くまでの待機時間
	int time2c = 0; //Velocityの管理時間
	int time3c = 0; //物が動いてから次動くまでの待機時間
	int time2d = 0; //Velocityの管理時間
	int time3d = 0; //物が動いてから次動くまでの待機時間
	float Velocity = 0.5; //エフェクトの動き
	float Velocitya = 2; //物の動き
	float Velocityb = 2; //物の動き
	float Velocityc = 2; //物の動き
	float Velocityd = 2; //物の動き
	App::SetWindowSize(1200, 800);

	Sprite charaa[4];	//人間aの画像
	Sprite charab[4];	//人間bの画像
	Sprite charac[4];	//人間cの画像

	Sprite timea1[21];
	Sprite lifea[19];  //ライフの画像
	int objectspeed = 1;

	Sprite mode1(L"mode1.png");
	mode1.scale = 7;
	mode1.position.y = -480;
	mode1.position.x = 130;

	Sprite mode2(L"mode2.png");
	mode2.scale = 7;
	mode2.position.y = -480;
	mode2.position.x = 130;

	Sprite mode3(L"mode3.png");
	mode3.scale = 7;
	mode3.position.y = -480;
	mode3.position.x = 130;

	Sprite mode4(L"mode4.png");
	mode4.scale = 7;
	mode4.position.y = -480;
	mode4.position.x = 130;

	Sprite mode5(L"mode5.png");
	mode5.scale = 7;
	mode5.position.y = -480;
	mode5.position.x = 130;

	Sprite mode6(L"mode6.png");
	mode6.scale = 7;
	mode6.position.y = -480;
	mode6.position.x = 130;

	//プレイ中の画面上のステージの名前
	Text STAGE1Text(L"STAGE1 - 1", 100.0);
	STAGE1Text.position.y = 350;
	STAGE1Text.position.x = -30;

	Text STAGE2Text(L"STAGE1 - 2", 100.0);
	STAGE2Text.position.y = 350;
	STAGE2Text.position.x = -30;

	Text STAGE3Text(L"STAGE1 - 3", 100.0);
	STAGE3Text.position.y = 350;
	STAGE3Text.position.x = -30;

	Text STAGE4Text(L"STAGE2 - 1", 100.0);
	STAGE4Text.position.y = 350;
	STAGE4Text.position.x = -30;

	Text STAGE5Text(L"STAGE2 - 2", 100.0);
	STAGE5Text.position.y = 350;
	STAGE5Text.position.x = -30;

	Text STAGE6Text(L"FINAL STAGE", 100.0);
	STAGE6Text.position.y = 350;
	STAGE6Text.position.x = -30;

	Sprite titlepng(L"タイトル.png");
	titlepng.position.x = 556;
	titlepng.position.y = 354;
	titlepng.scale = 2.0;
	
	Text mouseposition;
	mouseposition.position.y = 100;
	mouseposition.scale = 3.0;

	Sprite reaction1(L"!.png");
	reaction1.scale = 1.5;
	reaction1.position.y = 50;
	reaction1.position.x = 50;

	Sprite reaction2(L"!1.png");
	reaction2.scale = 1.5;
	reaction2.position.y = 50;
	reaction2.position.x = -50;

	Sprite reaction3(L"!2.png");
	reaction3.scale = 1.5;
	reaction3.position.y = 250;

	charaa[0].Load(L"charaa.png");
	charaa[0].scale = 2.0;
	charaa[0].position.x = 50;

	charaa[1].Load(L"charab.png");
	charaa[1].scale = 2.0;
	charaa[1].position.x = 50;

	charaa[2].Load(L"charac.png");
	charaa[2].scale = 2.0;
	charaa[2].position.x = 50;

	charaa[3].Load(L"charad.png");
	charaa[3].scale = 2.0;
	charaa[3].position.x = 50;

	charab[0].Load(L"chara1.png");
	charab[0].scale = 2.0;
	charab[0].position.x = -50;

	charab[1].Load(L"chara2.png");
	charab[1].scale = 2.0;
	charab[1].position.x = -50;

	charab[2].Load(L"chara3.png");
	charab[2].scale = 2.0;
	charab[2].position.x = -50;

	charab[3].Load(L"chara4.png");
	charab[3].scale = 2.0;
	charab[3].position.x = -50;

	charac[0].Load(L"chara6.png");
	charac[0].scale = 2.0;
	charac[0].position.y = 100;

	charac[1].Load(L"chara7.png");
	charac[1].scale = 2.0;
	charac[1].position.y = 100;

	charac[2].Load(L"chara8.png");
	charac[2].scale = 2.0;
	charac[2].position.y = 100;

	charac[3].Load(L"chara5.png");
	charac[3].scale = 2.0;
	charac[3].position.y = 100;

	Text pgText(L"PG中だよ", 100.0);
	pgText.position.y = -300;
	pgText.color = Float4(1.0, 0.0, 0.0, 1.0);

	Sprite ef1(L"effect.png");		//エフェクトの画像
	ef1.position.x = -240;
	ef1.position.y = -100;

	Sprite ef2(L"effect.png");		//エフェクトの画像
	ef2.position.x = 240;
	ef2.position.y = 200;

	Sprite ef3(L"effect.png");		//エフェクトの画像
	ef3.position.x = 240;
	ef3.position.y = -100;

	Sprite ef4(L"effect.png");		//エフェクトの画像
	ef4.position.x = -240;
	ef4.position.y = 200;



	Sprite objecta(L"7.png");		//静止オブジェクトaの画像
	objecta.scale = 1.0;
	objecta.position.x = -230;
	objecta.position.y = -150;

	Sprite objectb(L"7.png");		//静止オブジェクトbの画像
	objectb.scale = 1.0;
	objectb.position.x = 230;
	objectb.position.y = 150;

	Sprite objectc(L"7.png");		//静止オブジェクトcの画像
	objectc.scale = 1.0;
	objectc.position.x = 230;
	objectc.position.y = -150;

	Sprite objectd(L"7.png");		//静止オブジェクトdの画像
	objectd.scale = 1.0;
	objectd.position.x = -230;
	objectd.position.y = 150;

	Sprite map1(L"6.png");		//map1の画像
	map1.scale.x = 10.0;
	map1.scale.y = 17.0;
	map1.position.x = 65;
	map1.position.y = -180;

	Sprite time4(L"6.png");		//制限時間の画像
	time4.scale.x = 3.0;
	time4.position.x = -450;
	time4.position.y = 250;

	lifea[0].Load(L"life1.png"); //ライフの画像
	lifea[0].position.x = 500;
	lifea[0].position.y = 150;
	lifea[0].scale = 4.5;

	lifea[1].Load(L"life2.png"); //ライフの画像
	lifea[1].position.x = 500;
	lifea[1].position.y = 150;
	lifea[1].scale = 4.5;

	lifea[2].Load(L"life3.png"); //ライフの画像
	lifea[2].position.x = 500;
	lifea[2].position.y = 150;
	lifea[2].scale = 4.5;

	lifea[3].Load(L"life4.png"); //ライフの画像
	lifea[3].position.x = 500;
	lifea[3].position.y = 150;
	lifea[3].scale = 4.5;

	lifea[4].Load(L"life5.png"); //ライフの画像
	lifea[4].position.x = 500;
	lifea[4].position.y = 150;
	lifea[4].scale = 4.5;
	
	lifea[5].Load(L"life6.png"); //ライフの画像
	lifea[5].position.x = 500;
	lifea[5].position.y = 150;
	lifea[5].scale = 4.5;

	lifea[6].Load(L"life7.png"); //ライフの画像
	lifea[6].position.x = 500;
	lifea[6].position.y = 150;
	lifea[6].scale = 4.5;

	lifea[7].Load(L"life8.png"); //ライフの画像
	lifea[7].position.x = 500;
	lifea[7].position.y = 150;
	lifea[7].scale = 4.5;

	lifea[8].Load(L"life9.png"); //ライフの画像
	lifea[8].position.x = 500;
	lifea[8].position.y = 150;
	lifea[8].scale = 4.5;

	lifea[9].Load(L"life10.png"); //ライフの画像
	lifea[9].position.x = 500;
	lifea[9].position.y = 150;
	lifea[9].scale = 4.5;

	lifea[10].Load(L"life11.png"); //ライフの画像
	lifea[10].position.x = 500;
	lifea[10].position.y = 150;
	lifea[10].scale = 4.5;

	lifea[11].Load(L"life12.png"); //ライフの画像
	lifea[11].position.x = 500;
	lifea[11].position.y = 150;
	lifea[11].scale = 4.5;

	lifea[12].Load(L"life13.png"); //ライフの画像
	lifea[12].position.x = 500;
	lifea[12].position.y = 150;
	lifea[12].scale = 4.5;

	lifea[13].Load(L"life14.png"); //ライフの画像
	lifea[13].position.x = 500;
	lifea[13].position.y = 150;
	lifea[13].scale = 4.5;

	lifea[14].Load(L"life15.png"); //ライフの画像
	lifea[14].position.x = 500;
	lifea[14].position.y = 150;
	lifea[14].scale = 4.5;

	lifea[15].Load(L"life16.png"); //ライフの画像
	lifea[15].position.x = 500;
	lifea[15].position.y = 150;
	lifea[15].scale = 4.5;

	lifea[16].Load(L"life17.png"); //ライフの画像
	lifea[16].position.x = 500;
	lifea[16].position.y = 150;
	lifea[16].scale = 4.5;

	lifea[17].Load(L"life18.png"); //ライフの画像
	lifea[17].position.x = 500;
	lifea[17].position.y = 150;
	lifea[17].scale = 4.5;

	lifea[18].Load(L"life19.png"); //ライフの画像
	lifea[18].position.x = 500;
	lifea[18].position.y = 150;
	lifea[18].scale = 4.5;
	
	timea1[1].Load(L"6a1.png");		//制限時間の中の画像
	timea1[1].scale.x = 3.0;
	timea1[1].position.x = -450;
	timea1[1].position.y = 250;

	timea1[2].Load(L"6a2.png");		//制限時間の中の画像
	timea1[2].scale.x = 3.0;
	timea1[2].position.x = -450;
	timea1[2].position.y = 250;

	timea1[3].Load(L"6a3.png");		//制限時間の中の画像
	timea1[3].scale.x = 3.0;
	timea1[3].position.x = -450;
	timea1[3].position.y = 250;

	timea1[4].Load(L"6a4.png");		//制限時間の中の画像
	timea1[4].scale.x = 3.0;
	timea1[4].position.x = -450;
	timea1[4].position.y = 250;

	timea1[5].Load(L"6a5.png");		//制限時間の中の画像
	timea1[5].scale.x = 3.0;
	timea1[5].position.x = -450;
	timea1[5].position.y = 250;

	timea1[6].Load(L"6a6.png");		//制限時間の中の画像
	timea1[6].scale.x = 3.0;
	timea1[6].position.x = -450;
	timea1[6].position.y = 250;

	timea1[7].Load(L"6a7.png");		//制限時間の中の画像
	timea1[7].scale.x = 3.0;
	timea1[7].position.x = -450;
	timea1[7].position.y = 250;

	timea1[8].Load(L"6a8.png");		//制限時間の中の画像
	timea1[8].scale.x = 3.0;
	timea1[8].position.x = -450;
	timea1[8].position.y = 250;

	timea1[9].Load(L"6a9.png");		//制限時間の中の画像
	timea1[9].scale.x = 3.0;
	timea1[9].position.x = -450;
	timea1[9].position.y = 250;

	timea1[10].Load(L"6a10.png");		//制限時間の中の画像
	timea1[10].scale.x = 3.0;
	timea1[10].position.x = -450;
	timea1[10].position.y = 250;

	timea1[11].Load(L"6a1.png");		//制限時間の中の画像
	timea1[11].scale.x = 3.0;
	timea1[11].position.x = -360;
	timea1[11].position.y = 250;

	timea1[12].Load(L"6a2.png");		//制限時間の中の画像
	timea1[12].scale.x = 3.0;
	timea1[12].position.x = -360;
	timea1[12].position.y = 250;

	timea1[13].Load(L"6a3.png");		//制限時間の中の画像
	timea1[13].scale.x = 3.0;
	timea1[13].position.x = -360;
	timea1[13].position.y = 250;

	timea1[14].Load(L"6a4.png");		//制限時間の中の画像
	timea1[14].scale.x = 3.0;
	timea1[14].position.x = -360;
	timea1[14].position.y = 250;

	timea1[15].Load(L"6a5.png");		//制限時間の中の画像
	timea1[15].scale.x = 3.0;
	timea1[15].position.x = -360;
	timea1[15].position.y = 250;

	timea1[16].Load(L"6a6.png");		//制限時間の中の画像
	timea1[16].scale.x = 3.0;
	timea1[16].position.x = -360;
	timea1[16].position.y = 250;

	timea1[17].Load(L"6a7.png");		//制限時間の中の画像
	timea1[17].scale.x = 3.0;
	timea1[17].position.x = -360;
	timea1[17].position.y = 250;

	timea1[18].Load(L"6a8.png");		//制限時間の中の画像
	timea1[18].scale.x = 3.0;
	timea1[18].position.x = -360;
	timea1[18].position.y = 250;

	timea1[19].Load(L"6a9.png");		//制限時間の中の画像
	timea1[19].scale.x = 3.0;
	timea1[19].position.x = -360;
	timea1[19].position.y = 250;

	timea1[20].Load(L"6a10.png");		//制限時間の中の画像
	timea1[20].scale.x = 3.0;
	timea1[20].position.x = -360;
	timea1[20].position.y = 250;

	Text GAMEOVERText(L"GAME OVER", 100.0);
	GAMEOVERText.scale = 1.5;
	GAMEOVERText.color = Float4(1.0, 0.0, 0.0, 1.0);

	/*Text MOuseText(L"", 100);*/  //マウス座標の把握用

	Text titleText(L"GO HOME", 100.0);
	titleText.position.x = 0.0;
	titleText.position.y = 250.0;
	titleText.scale = 1.5;
	titleText.color = Float4(1.0, 0.0, 0.0, 1.0);

	Text title1Text(L"BABY", 100.0);
	title1Text.position.x = 0.0;
	title1Text.position.y = 100.0;
	title1Text.scale = 1.4;
	title1Text.color = Float4(1.0, 0.0, 0.0, 1.0);
	App::SetTitle(L"GO HOME BABY");

	Text title2Text(L"S  P  A  C  E　START", 100.0);
	title2Text.position.x = 0.0;
	title2Text.position.y = -120.0;
	title2Text.scale = 0.8;
	title2Text.color = Float4(1.0, 0.0, 0.0, 1.0);

	Text title3Text(L"ＳＥＬＥＣＴ", 100.0);
	title3Text.position.x = -30.0;
	title3Text.position.y = -220.0;
	title3Text.scale = 0.4;
	title3Text.color = Float4(0.0, 0.0, 1.0, 1.0);

	Text clear1Text(L"ステージ 1 - 2 へ", 100);
	clear1Text.color = Float4(1.0, 0.0, 0.0, 1.0);

	Text clear2Text(L"ステージ 1 - 3 へ", 100);
	clear2Text.color = Float4(1.0, 0.0, 0.0, 1.0);

	Text clear3Text(L"ステージ 2 - 1 へ", 100);
	clear3Text.color = Float4(1.0, 0.0, 0.0, 1.0);

	Text clear4Text(L"ステージ 2 - 2 へ", 100);
	clear4Text.color = Float4(1.0, 0.0, 0.0, 1.0);

	Text clear5Text(L"ステージ FINAL へ", 100);
	clear5Text.color = Float4(1.0, 0.0, 0.0, 1.0);

	Text clear0Text(L"ゲームクリア", 100);
	clear0Text.color = Float4(1.0, 0.0, 0.0, 1.0);
	
	App::SetTitle(L"GO HOME BABY");
	
	Camera camera;

	Mode mode = Title; 

	
	while (App::Refresh())
	{
		camera.Update();
		//マウス座標の把握用
		/*MOuseText.Create(std::to_wstring(App::GetMousePosition().x) +　　
			L"," + std::to_wstring(App::GetMousePosition().y));
		MOuseText.Draw();*/
		switch (mode)
		{
		case Title:
			if (App::GetKey('0') &&			//サンプルお試し用
				App::GetKey('1'))
			{
				stage = 6;
			}

			//マウスでのＳＴＡＧＥ選択
			if (stage >= 2)
			{
				if (App::GetKeyDown(VK_LBUTTON) &&
					-521 <= App::GetMousePosition().x &&
					App::GetMousePosition().x <= -368 &&
					-354 <= App::GetMousePosition().y &&
					App::GetMousePosition().y <= -275)
				{
					STAGE = 1;
				}

				if (App::GetKeyDown(VK_LBUTTON) &&
					-353 <= App::GetMousePosition().x &&
					App::GetMousePosition().x <= -186 &&
					-354 <= App::GetMousePosition().y &&
					App::GetMousePosition().y <= -275)
				{
					STAGE = 2;
				}
				title3Text.Draw();
				mode2.Draw();
				mode1.Draw();
				if (stage >= 3)
				{
					if (App::GetKeyDown(VK_LBUTTON) &&
						-185 <= App::GetMousePosition().x &&
						App::GetMousePosition().x <= -18 &&
						-354 <= App::GetMousePosition().y &&
						App::GetMousePosition().y <= -275)
					{
						STAGE = 3;
					}
					mode3.Draw();
					if (stage >= 4)
					{
						if (App::GetKeyDown(VK_LBUTTON) &&
							-17 <= App::GetMousePosition().x &&
							App::GetMousePosition().x <= 150 &&
							-354 <= App::GetMousePosition().y &&
							App::GetMousePosition().y <= -275)
						{
							STAGE = 4;
						}
						mode4.Draw();
						if (stage >= 5)
						{
							if (App::GetKeyDown(VK_LBUTTON) &&
								151 <= App::GetMousePosition().x &&
								App::GetMousePosition().x <= 318 &&
								-354 <= App::GetMousePosition().y &&
								App::GetMousePosition().y <= -275)
							{
								STAGE = 5;
							}
							mode5.Draw();
							if (stage >= 6)
							{
								if (App::GetKeyDown(VK_LBUTTON) &&
								319 <= App::GetMousePosition().x &&
									App::GetMousePosition().x <= 486 &&
									-354 <= App::GetMousePosition().y &&
									App::GetMousePosition().y <= -275)
								{
									STAGE = 6;
								}
									mode6.Draw();
							}
						}
					}
				}
			}	
			titleText.Draw();
			title1Text.Draw();
			title2Text.Draw();
			STAGE1Text.position.y = -25;
			STAGE2Text.position.y = -25;
			STAGE3Text.position.y = -25;
			STAGE4Text.position.y = -25;
			STAGE5Text.position.y = -25;
			STAGE6Text.position.y = -25;
			if (STAGE == 1)
			{
				STAGE1Text.Draw();
			}
			if (STAGE == 2)
			{
				STAGE2Text.Draw();
			}
			if (STAGE == 3)
			{
				STAGE3Text.Draw();
			}
			if (STAGE == 4)
			{
				STAGE4Text.Draw();
			}
			if (STAGE == 5)
			{
				STAGE5Text.Draw();
			}
			if (STAGE == 6)
			{
				STAGE6Text.Draw();
			}
			//ゲーム画面へ＋初期化
			if (App::GetKeyDown(VK_SPACE))
			{
				//初期化
				x = 0; 
				STAGE1Text.position.y = 350;
				STAGE2Text.position.y = 350;
				STAGE3Text.position.y = 350;
				STAGE4Text.position.y = 350;
				STAGE5Text.position.y = 350;
				STAGE6Text.position.y = 350;
				ef1.position.x = -240;
				ef1.position.y = -100;
				ef2.position.x = 240;
				ef2.position.y = 200;
				ef3.position.x = 240;
				ef3.position.y = -100;
				ef4.position.x = -240;
				ef4.position.y = 200;
				objecta.position.x = -230;
				objecta.position.y = -150;
				objectb.position.x = 230;
				objectb.position.y = 150;
				objectc.position.x = 230;
				objectc.position.y = -150;
				objectd.position.x = -230;
				objectd.position.y = 150;
				mouse = 0;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
				chara1a = 0;	//aキャラクターが振り向く予定の方向
				chara1b = 0;	//bキャラクターが振り向く予定の方向
				chara2a = 0;	//aキャラクターが向いている方向
				chara2b = 0;	//bキャラクターが向いている方向
				chara2c = 0;	//cキャラクターが向いている方向
				chara3a = 0;	//aリアクションするまでの時間
				chara3b = 0;	//bリアクションするまでの時間
				chara4a = 0;	//aリアクションしてから振り向くまでの時間
				chara4b = 0;	//bリアクションしてから振り向くまでの時間
				lifetime = 0;	//キャラクターのHPを減らすまでの時間
				life = 0;	   //キャラクターのHP.恐怖ゲージ
				time = 0; //制限時間
				timea = 0; //制限時間の画像の表示
				time2a = 0; //Velocityの管理時間
				time3a = 0; //物が動いてから次動くまでの待機時間
				time2b = 0; //Velocityの管理時間
				time3b = 0; //物が動いてから次動くまでの待機時間
				time2c = 0; //Velocityの管理時間
				time3c = 0; //物が動いてから次動くまでの待機時間
				time2d = 0; //Velocityの管理時間
				time3d = 0; //物が動いてから次動くまでの待機時間
				Velocity = 0.5; //エフェクトの動き
				Velocitya = 2; //物の動き
				Velocityb = 2; //物の動き
				Velocityc = 2; //物の動き
				Velocityd = 2; //物の動き
				if (STAGE == 1 ||
					STAGE == 4)
				{
					mode = game1;
				}
				if (STAGE == 2||
					STAGE == 5)
				{
					mode = game2;
				}
				if (STAGE == 3||
					STAGE == 6)
				{
					mode = game3;
				}
			}
			break;

		case bad:
			GAMEOVERText.Draw();
			if (App::GetKeyDown(VK_SPACE))
			{
				mode = Title;
			}

			break;
		case clear1:
			clear1Text.Draw();
			if (App::GetKeyDown(VK_SPACE))
			{
				if (stage <= 2)
				{
					stage = 2;
				}
				STAGE = 2;
				//初期化
				x = 0;
				ef1.position.x = -240;
				ef1.position.y = -100;
				ef2.position.x = 240;
				ef2.position.y = 200;
				ef3.position.x = 240;
				ef3.position.y = -100;
				ef4.position.x = -240;
				ef4.position.y = 200;
				objecta.position.x = -230;
				objecta.position.y = -150;
				objectb.position.x = 230;
				objectb.position.y = 150;
				objectc.position.x = 230;
				objectc.position.y = -150;
				objectd.position.x = -230;
				objectd.position.y = 150;
				mouse = 0;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
				chara1a = 0;	//aキャラクターが振り向く予定の方向
				chara1b = 0;	//bキャラクターが振り向く予定の方向
				chara2a = 0;	//aキャラクターが向いている方向
				chara2b = 0;	//bキャラクターが向いている方向
				chara3a = 0;	//aリアクションするまでの時間
				chara3b = 0;	//bリアクションするまでの時間
				chara4a = 0;	//aリアクションしてから振り向くまでの時間
				chara4b = 0;	//bリアクションしてから振り向くまでの時間
				lifetime = 0;	//キャラクターのHPを減らすまでの時間
				life = 0;	   //キャラクターのHP.恐怖ゲージ
				time = 0; //制限時間
				timea = 0; //制限時間の画像の表示
				time2a = 0; //Velocityの管理時間
				time3a = 0; //物が動いてから次動くまでの待機時間
				time2b = 0; //Velocityの管理時間
				time3b = 0; //物が動いてから次動くまでの待機時間
				time2c = 0; //Velocityの管理時間
				time3c = 0; //物が動いてから次動くまでの待機時間
				time2d = 0; //Velocityの管理時間
				time3d = 0; //物が動いてから次動くまでの待機時間
				Velocity = 0.5; //エフェクトの動き
				Velocitya = 2; //物の動き
				Velocityb = 2; //物の動き
				Velocityc = 2; //物の動き
				Velocityd = 2; //物の動き
				mode = game2;
			}

			break;

		case clear2:
			clear2Text.Draw();
			if (App::GetKeyDown(VK_SPACE))
			{
				if (stage <= 3)
				{
					stage = 3;
				}
				STAGE = 3;
				//初期化
				x = 0;
				ef1.position.x = -240;
				ef1.position.y = -100;
				ef2.position.x = 240;
				ef2.position.y = 200;
				ef3.position.x = 240;
				ef3.position.y = -100;
				ef4.position.x = -240;
				ef4.position.y = 200;
				objecta.position.x = -230;
				objecta.position.y = -150;
				objectb.position.x = 230;
				objectb.position.y = 150;
				objectc.position.x = 230;
				objectc.position.y = -150;
				objectd.position.x = -230;
				objectd.position.y = 150;
				mouse = 0;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
				chara1a = 0;	//aキャラクターが振り向く予定の方向
				chara1b = 0;	//bキャラクターが振り向く予定の方向
				chara2a = 0;	//aキャラクターが向いている方向
				chara2b = 0;	//bキャラクターが向いている方向
				chara3a = 0;	//aリアクションするまでの時間
				chara3b = 0;	//bリアクションするまでの時間
				chara4a = 0;	//aリアクションしてから振り向くまでの時間
				chara4b = 0;	//bリアクションしてから振り向くまでの時間
				lifetime = 0;	//キャラクターのHPを減らすまでの時間
				life = 0;	   //キャラクターのHP.恐怖ゲージ
				time = 0; //制限時間
				timea = 0; //制限時間の画像の表示
				time2a = 0; //Velocityの管理時間
				time3a = 0; //物が動いてから次動くまでの待機時間
				time2b = 0; //Velocityの管理時間
				time3b = 0; //物が動いてから次動くまでの待機時間
				time2c = 0; //Velocityの管理時間
				time3c = 0; //物が動いてから次動くまでの待機時間
				time2d = 0; //Velocityの管理時間
				time3d = 0; //物が動いてから次動くまでの待機時間
				Velocity = 0.5; //エフェクトの動き
				Velocitya = 2; //物の動き
				Velocityb = 2; //物の動き
				Velocityc = 2; //物の動き
				Velocityd = 2; //物の動き
				mode = game3;
			}

			break;

		case clear3:
			clear3Text.Draw();
			if (App::GetKeyDown(VK_SPACE))
			{
				stage = 4;
				STAGE = 4;
				//初期化
				x = 0;
				ef1.position.x = -240;
				ef1.position.y = -100;
				ef2.position.x = 240;
				ef2.position.y = 200;
				ef3.position.x = 240;
				ef3.position.y = -100;
				ef4.position.x = -240;
				ef4.position.y = 200;
				objecta.position.x = -230;
				objecta.position.y = -150;
				objectb.position.x = 230;
				objectb.position.y = 150;
				objectc.position.x = 230;
				objectc.position.y = -150;
				objectd.position.x = -230;
				objectd.position.y = 150;
				mouse = 0;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
				chara1a = 0;	//aキャラクターが振り向く予定の方向
				chara1b = 0;	//bキャラクターが振り向く予定の方向
				chara2a = 0;	//aキャラクターが向いている方向
				chara2b = 0;	//bキャラクターが向いている方向
				chara3a = 0;	//aリアクションするまでの時間
				chara3b = 0;	//bリアクションするまでの時間
				chara4a = 0;	//aリアクションしてから振り向くまでの時間
				chara4b = 0;	//bリアクションしてから振り向くまでの時間
				lifetime = 0;	//キャラクターのHPを減らすまでの時間
				life = 0;	   //キャラクターのHP.恐怖ゲージ
				time = 0; //制限時間
				timea = 0; //制限時間の画像の表示
				time2a = 0; //Velocityの管理時間
				time3a = 0; //物が動いてから次動くまでの待機時間
				time2b = 0; //Velocityの管理時間
				time3b = 0; //物が動いてから次動くまでの待機時間
				time2c = 0; //Velocityの管理時間
				time3c = 0; //物が動いてから次動くまでの待機時間
				time2d = 0; //Velocityの管理時間
				time3d = 0; //物が動いてから次動くまでの待機時間
				Velocity = 0.5; //エフェクトの動き
				Velocitya = 2; //物の動き
				Velocityb = 2; //物の動き
				Velocityc = 2; //物の動き
				Velocityd = 2; //物の動き
				mode = game1;
			}

			break;

		case clear4:
			clear4Text.Draw();
			if (App::GetKeyDown(VK_SPACE))
			{
				if (stage <= 5)
				{
					stage = 5;
				}
				STAGE = 5;
				//初期化
				x = 0;
				ef1.position.x = -240;
				ef1.position.y = -100;
				ef2.position.x = 240;
				ef2.position.y = 200;
				ef3.position.x = 240;
				ef3.position.y = -100;
				ef4.position.x = -240;
				ef4.position.y = 200;
				objecta.position.x = -230;
				objecta.position.y = -150;
				objectb.position.x = 230;
				objectb.position.y = 150;
				objectc.position.x = 230;
				objectc.position.y = -150;
				objectd.position.x = -230;
				objectd.position.y = 150;
				mouse = 0;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
				chara1a = 0;	//aキャラクターが振り向く予定の方向
				chara1b = 0;	//bキャラクターが振り向く予定の方向
				chara2a = 0;	//aキャラクターが向いている方向
				chara2b = 0;	//bキャラクターが向いている方向
				chara3a = 0;	//aリアクションするまでの時間
				chara3b = 0;	//bリアクションするまでの時間
				chara4a = 0;	//aリアクションしてから振り向くまでの時間
				chara4b = 0;	//bリアクションしてから振り向くまでの時間
				lifetime = 0;	//キャラクターのHPを減らすまでの時間
				life = 0;	   //キャラクターのHP.恐怖ゲージ
				time = 0; //制限時間
				timea = 0; //制限時間の画像の表示
				time2a = 0; //Velocityの管理時間
				time3a = 0; //物が動いてから次動くまでの待機時間
				time2b = 0; //Velocityの管理時間
				time3b = 0; //物が動いてから次動くまでの待機時間
				time2c = 0; //Velocityの管理時間
				time3c = 0; //物が動いてから次動くまでの待機時間
				time2d = 0; //Velocityの管理時間
				time3d = 0; //物が動いてから次動くまでの待機時間
				Velocity = 0.5; //エフェクトの動き
				Velocitya = 2; //物の動き
				Velocityb = 2; //物の動き
				Velocityc = 2; //物の動き
				Velocityd = 2; //物の動き
				mode = game2;
			}

			break;

		case clear5:
			clear5Text.Draw();
			if (App::GetKeyDown(VK_SPACE))
			{
				if (stage <= 6)
				{
					stage = 6;
				}
				STAGE = 6;
				//初期化
				x = 0;
				ef1.position.x = -240;
				ef1.position.y = -100;
				ef2.position.x = 240;
				ef2.position.y = 200;
				ef3.position.x = 240;
				ef3.position.y = -100;
				ef4.position.x = -240;
				ef4.position.y = 200;
				objecta.position.x = -230;
				objecta.position.y = -150;
				objectb.position.x = 230;
				objectb.position.y = 150;
				objectc.position.x = 230;
				objectc.position.y = -150;
				objectd.position.x = -230;
				objectd.position.y = 150;
				mouse = 0;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
				chara1a = 0;	//aキャラクターが振り向く予定の方向
				chara1b = 0;	//bキャラクターが振り向く予定の方向
				chara2a = 0;	//aキャラクターが向いている方向
				chara2b = 0;	//bキャラクターが向いている方向
				chara3a = 0;	//aリアクションするまでの時間
				chara3b = 0;	//bリアクションするまでの時間
				chara4a = 0;	//aリアクションしてから振り向くまでの時間
				chara4b = 0;	//bリアクションしてから振り向くまでの時間
				lifetime = 0;	//キャラクターのHPを減らすまでの時間
				life = 0;	   //キャラクターのHP.恐怖ゲージ
				time = 0; //制限時間
				timea = 0; //制限時間の画像の表示
				time2a = 0; //Velocityの管理時間
				time3a = 0; //物が動いてから次動くまでの待機時間
				time2b = 0; //Velocityの管理時間
				time3b = 0; //物が動いてから次動くまでの待機時間
				time2c = 0; //Velocityの管理時間
				time3c = 0; //物が動いてから次動くまでの待機時間
				time2d = 0; //Velocityの管理時間
				time3d = 0; //物が動いてから次動くまでの待機時間
				Velocity = 0.5; //エフェクトの動き
				Velocitya = 2; //物の動き
				Velocityb = 2; //物の動き
				Velocityc = 2; //物の動き
				Velocityd = 2; //物の動き
				mode = game3;
			}	

			break;

		case clear6:

			clear0Text.Draw();
			if (App::GetKeyDown(VK_SPACE))
			{
				mode = Title;
			}
			break;

		case game1:
			if (STAGE == 1)
			{
				STAGE1Text.Draw();
			}
			else
			{
				STAGE4Text.Draw();
			}
			if (App::GetKeyDown(VK_LBUTTON) &&
				App::GetMousePosition().y >= 350 &&
				App::GetMousePosition().x >= 486)
			{
				mode = Title;
			}

			titlepng.Draw();
			x++;

			i += time + lifetime * timea + time2d;
			i++;
			if (i > 100000)
			{
				i = 0;
			}

			//エフェクトの動き
			ef1.position += Velocity;
			ef2.position += Velocity;
			ef3.position += Velocity;
			ef4.position += Velocity;

			//制限時間の処理
			time++;
			if (STAGE == 1)
			{
				if (time >= 80)
				{
					time = 0;
					timea++;
				}
			}
			else
			{
				if (time >= 40)
				{
					time = 0;
					timea++;
				}
			}
			//向いている方向とマウスの場所が同じとき
			if (chara2b == mouse)
			{
				time += 10;
			}

			//制限時間が来たらタイトルへ
			if (timea == 20)
			{
				mode = bad;
			}

			if (App::GetKey(VK_LBUTTON))
			{
				chara3b++;
				pgText.Draw();//エフェクトの文字の描画
			}
			else//マウスを押してないとき
			{
				//リアクションしてすぐマウスを離すと向く位置がランダムになる
				if (chara4b <= 1)
				{
					chara1b = i % 4;
				}
				mouse = 4;
			}

			//bリアクションの時間管理
			if (chara3b < 300)
			{
				chara3b++;
			}
			if (chara3b >= 150)
			{
				reaction2.Draw();
				chara4b++;
				if (mouse == 4)
				{
				}
				else
				{
					chara1b = mouse;
				}
			}
			if (chara4b >= 30)
			{
				chara2b = chara1b;
				chara3b = 0;
				chara4b = 0;
			}


			//エフェクトの向きを変える処理
			if (x % 20 == 0)
			{
				Velocity = -Velocity;
			}

			//画像が点滅しないようにする処理
			if (timea < 21)
			{
				if (timea >= 1)
				{
					timea1[1].Draw();
				}
				if (timea >= 2)
				{
					timea1[2].Draw();
				}
				if (timea >= 2)
				{
					timea1[2].Draw();
				}
				if (timea >= 3)
				{
					timea1[3].Draw();
				}
				if (timea >= 4)
				{
					timea1[4].Draw();
				}
				if (timea >= 5)
				{
					timea1[5].Draw();
				}
				if (timea >= 6)
				{
					timea1[6].Draw();
				}
				if (timea >= 6)
				{
					timea1[6].Draw();
				}
				if (timea >= 7)
				{
					timea1[7].Draw();
				}
				if (timea >= 8)
				{
					timea1[8].Draw();
				}
				if (timea >= 9)
				{
					timea1[9].Draw();
				}
				if (timea >= 10)
				{
					timea1[10].Draw();
				}
				if (timea >= 11)
				{
					timea1[11].Draw();
				}
				if (timea >= 12)
				{
					timea1[12].Draw();
				}
				if (timea >= 13)
				{
					timea1[13].Draw();
				}
				if (timea >= 14)
				{
					timea1[14].Draw();
				}
				if (timea >= 15)
				{
					timea1[15].Draw();
				}
				if (timea >= 16)
				{
					timea1[16].Draw();
				}
				if (timea >= 17)
				{
					timea1[17].Draw();
				}
				if (timea >= 18)
				{
					timea1[18].Draw();
				}
				if (timea >= 19)
				{
					timea1[19].Draw();
				}
				if (timea >= 20)
				{
					timea1[20].Draw();
				}
			}

			charab[chara2b].Draw();
			lifea[0].Draw();
			lifea[life].Draw();
			map1.Draw();
			timea1[timea].Draw();
			objecta.Draw();
			objectb.Draw();
			objectc.Draw();
			objectd.Draw();
			time4.Draw();


			//ここからオブジェクトを動かす処理
			//マウスが左下にある時
			if (App::GetMousePosition().y < 0 &&
				App::GetMousePosition().x < 0 &&
				App::GetKey(VK_LBUTTON))
			{
				if (chara4b == 0)
				{
					chara1b = 0;
				}
				mouse = 0;

				ef1.Draw();//エフェクトの表示
				lifetime++;
				time2a++;
				if (time3a < 4)
				{
					objecta.position.x += Velocitya;
					objecta.position.x += Velocitya;
					objecta.position.y += Velocitya;
					objecta.position.x += Velocitya;
					objecta.position.x += Velocitya;
				}
			}
			//マウスが右上にあるとき
			if (App::GetMousePosition().y > 0 &&
				App::GetMousePosition().x > 0 &&
				App::GetKey(VK_LBUTTON))
			{
				if (chara4b == 0)
				{
					chara1b = 1;
				}
				mouse = 1;
				ef2.Draw();//エフェクトの表示
				lifetime++;
				time2b++;
				if (time3b < 4)
				{
					objectb.position.x += Velocityb;
					objectb.position.x += Velocityb;
					objectb.position.y += Velocityb;
					objectb.position.x += Velocityb;
					objectb.position.x += Velocityb;

				}
			}
			//マウスが右下にあるとき
			if (App::GetMousePosition().y < 0 &&
				App::GetMousePosition().x > 0 &&
				App::GetKey(VK_LBUTTON))
			{
				if (chara4b == 0)
				{
					chara1b = 2;
				}
				mouse = 2;
				ef3.Draw();//エフェクトの表示
				lifetime++;
				time2c++;
				if (time3c < 4)
				{
					objectc.position.x += Velocityc;
					objectc.position.x += Velocityc;
					objectc.position.y += Velocityc;
					objectc.position.x += Velocityc;
					objectc.position.x += Velocityc;
				}
			}

			//マウスが左上にある時
			if (App::GetMousePosition().y > 0 &&
				App::GetMousePosition().x < 0 &&
				App::GetKey(VK_LBUTTON))
			{
				if (chara4b == 0)
				{
					chara1b = 3;
				}
				mouse = 3;
				ef4.Draw();//エフェクトの表示
				lifetime++;
				time2d++;
				if (time3d < 4)
				{
					objectd.position.x += Velocityd;
					objectd.position.x += Velocityd;
					objectd.position.y += Velocityd;
					objectd.position.x += Velocityd;
					objectd.position.x += Velocityd;
				}
			}



			if (time2a == 2)
			{
				time3a++;
				Velocitya = -Velocitya;
				time2a = 0;
			}
			if (time3a == 40)
			{
				Velocitya = -Velocitya;
				time3a = 0;
			}
			if (time2b == 2)
			{
				time3b++;
				Velocityb = -Velocityb;
				time2b = 0;
			}
			if (time3b == 40)
			{
				Velocityb = -Velocityb;
				time3b = 0;
			}


			if (time2c == 2)
			{
				time3c++;
				Velocityc = -Velocityc;
				time2c = 0;
			}
			if (time3c == 40)
			{
				Velocityc = -Velocityc;
				time3c = 0;
			}

			if (time2d == 2)
			{
				time3d++;
				Velocityd = -Velocityd;
				time2d = 0;
			}
			if (time3d == 40)
			{
				Velocityd = -Velocityd;
				time3d = 0;
			}

			//恐怖ゲージが満タンの時にclear画面へ
			if (lifetime >= 500)
			{
				if(STAGE == 1)
				{
					mode = clear1;
				}
				else
				{
					mode = clear4;
				}
			}
			//ライフ画像を表示する処理
			if (lifetime <= 501)
			{
				if (lifetime == 50)
				{
					life = 1;
				}
				if (lifetime == 100)
				{
					life = 2;
				}
				if (lifetime == 150)
				{
					life = 3;
				}
				if (lifetime == 200)
				{
					life = 4;
				}
				if (lifetime == 250)
				{
					life = 5;
				}
				if (lifetime == 300)
				{
					life = 6;
				}
				if (lifetime == 350)
				{
					life = 7;
				}
				if (lifetime == 400)
				{
					life = 8;
				}
				if (lifetime == 450)
				{
					life = 9;
				}
			}

			break;


		case game2:
		
			if (STAGE == 2)
			{
				STAGE2Text.Draw();
			}
			else
			{
				STAGE5Text.Draw();
			}
			if (App::GetKeyDown(VK_LBUTTON) &&
				App::GetMousePosition().y >= 350 &&
				App::GetMousePosition().x >= 486)
			{
				mode = Title;
			}

			titlepng.Draw();
			x++;

			i += time + lifetime * timea + time2d;
			i++;
			if (i > 100000)
			{
				i = 0;
			}

			//エフェクトの動き
			ef1.position += Velocity;
			ef2.position += Velocity;
			ef3.position += Velocity;
			ef4.position += Velocity;

			//制限時間の処理
			time++;
			if (STAGE == 2)
			{
				if (time >= 150)
				{
					time = 0;
					timea++;
				}
			}
			else
			{
				if (time >= 40)
				{
					time = 0;
					timea++;
				}
			}

			//向いている方向とマウスの場所が同じとき
			if (chara2a == mouse)
			{
				time += 10;
			}
			if (chara2b == mouse)
			{
				time += 15;
			}

			//制限時間が来たらタイトルへ
			if (timea == 20)
			{
				mode = bad;
			}

			if (App::GetKey(VK_LBUTTON))
			{
				chara3a++;
				chara3b++;
				pgText.Draw();//エフェクトの文字の描画
			}
			else//マウスを押してないとき
			{
				//リアクションしてすぐマウスを離すと向く位置がランダムになる
				if (chara4a <= 20)
				{
					chara1a = i % 4;
				}
				mouse = 4;
			}

			//aリアクションの時間管理
			if (chara3a < 200)
			{
				chara3a++;
			}
			if (chara3a >= 70)
			{
				reaction1.Draw();
				chara4a++;
			}
			if (chara4a >= 50)
			{
				chara2a = chara1a;
				chara3a = 0;
				chara4a = 0;
			}

			//bリアクションの時間管理
			if (chara3b < 300)
			{
				chara3b++;
			}
			if (chara3b >= 300)
			{
				reaction2.Draw();
				chara4b++;
				if (mouse == 4)
				{
				}
				else
				{
					chara1b = mouse;
				}
			}
			if (chara4b >= 30)
			{
				chara2b = chara1b;
				chara3b = 0;
				chara4b = 0;
			}

			
			//エフェクトの向きを変える処理
			if (x % 20 == 0)
			{
				Velocity = -Velocity;
			}

			//画像が点滅しないようにする処理
			if (timea < 21)
			{
				if (timea >= 1)
				{
					timea1[1].Draw();
				}
				if (timea >= 2)
				{
					timea1[2].Draw();
				}
				if (timea >= 2)
				{
					timea1[2].Draw();
				}
				if (timea >= 3)
				{
					timea1[3].Draw();
				}
				if (timea >= 4)
				{
					timea1[4].Draw();
				}
				if (timea >= 5)
				{
					timea1[5].Draw();
				}
				if (timea >= 6)
				{
					timea1[6].Draw();
				}
				if (timea >= 6)
				{
					timea1[6].Draw();
				}
				if (timea >= 7)
				{
					timea1[7].Draw();
				}
				if (timea >= 8)
				{
					timea1[8].Draw();
				}
				if (timea >= 9)
				{
					timea1[9].Draw();
				}
				if (timea >= 10)
				{
					timea1[10].Draw();
				}
				if (timea >= 11)
				{
					timea1[11].Draw();
				}
				if (timea >= 12)
				{
					timea1[12].Draw();
				}
				if (timea >= 13)
				{
					timea1[13].Draw();
				}
				if (timea >= 14)
				{
					timea1[14].Draw();
				}
				if (timea >= 15)
				{
					timea1[15].Draw();
				}
				if (timea >= 16)
				{
					timea1[16].Draw();
				}
				if (timea >= 17)
				{
					timea1[17].Draw();
				}
				if (timea >= 18)
				{
					timea1[18].Draw();
				}
				if (timea >= 19)
				{
					timea1[19].Draw();
				}
				if (timea >= 20)
				{
					timea1[20].Draw();
				}
			}
			
			charaa[chara2a].Draw();
			charab[chara2b].Draw();
			lifea[0].Draw();
			lifea[life].Draw();
			map1.Draw();
			timea1[timea].Draw();
			objecta.Draw();
			objectb.Draw();
			objectc.Draw();
			objectd.Draw();
			time4.Draw();
	

			//ここからオブジェクトを動かす処理
			//マウスが左下にある時
			if (App::GetMousePosition().y < 0 &&
				App::GetMousePosition().x < 0 &&
				App::GetKey(VK_LBUTTON))
			{
				if (chara4a == 0)
				{
					chara1a = 0;
				}
				if (chara4b == 0)
				{
					chara1b = 0;
				}
				mouse = 0;

				ef1.Draw();//エフェクトの表示
				lifetime++;
				time2a++;
				if (time3a < 4)
				{
					objecta.position.x += Velocitya;
					objecta.position.x += Velocitya;
					objecta.position.y += Velocitya;
					objecta.position.x += Velocitya;
					objecta.position.x += Velocitya;
				}
			}
			//マウスが右上にあるとき
			if (App::GetMousePosition().y > 0 &&
				App::GetMousePosition().x > 0 && 
				App::GetKey(VK_LBUTTON))
			{
				if (chara4a == 0)
				{
					chara1a = 1;
				}

				if (chara4b == 0)
				{
					chara1b = 1;
				}
				mouse = 1;
				ef2.Draw();//エフェクトの表示
				lifetime++;
				time2b++;
				if (time3b < 4)
				{
					objectb.position.x += Velocityb;
					objectb.position.x += Velocityb;
					objectb.position.y += Velocityb;
					objectb.position.x += Velocityb;
					objectb.position.x += Velocityb;

				}
			}
			//マウスが右下にあるとき
			if (App::GetMousePosition().y < 0 &&
				App::GetMousePosition().x > 0 &&
				App::GetKey(VK_LBUTTON))
			{
				if (chara4a == 0)
				{
					chara1a = 2;
				}

				if (chara4b == 0)
				{
					chara1b = 2;
				}
				mouse = 2;
				ef3.Draw();//エフェクトの表示
				lifetime++;
				time2c++;
				if (time3c < 4)
				{
					objectc.position.x += Velocityc;
					objectc.position.x += Velocityc;
					objectc.position.y += Velocityc;
					objectc.position.x += Velocityc;
					objectc.position.x += Velocityc;
				}
			}

			//マウスが左上にある時
			if (App::GetMousePosition().y > 0 &&
				App::GetMousePosition().x < 0 &&
				App::GetKey(VK_LBUTTON))
			{
				if (chara4a == 0)
				{
					chara1a = 3;
				}

				if (chara4b == 0)
				{
					chara1b = 3;
				}
				mouse = 3;
				ef4.Draw();//エフェクトの表示
				lifetime++;
				time2d++;
				if (time3d < 4)
				{
					objectd.position.x += Velocityd;
					objectd.position.x += Velocityd;
					objectd.position.y += Velocityd;
					objectd.position.x += Velocityd;
					objectd.position.x += Velocityd;
				}
			}
			
			

			if (time2a == 2)
			{
				time3a++;
				Velocitya = -Velocitya;
				time2a = 0;
			}
			if (time3a == 40)
			{
				Velocitya = -Velocitya;
				time3a = 0;
			}
			if (time2b == 2)
			{
				time3b++;
				Velocityb = -Velocityb;
				time2b = 0;
			}
			if (time3b == 40)
			{
				Velocityb = -Velocityb;
				time3b = 0;
			}

			
			if (time2c == 2)
			{
				time3c++;
				Velocityc = -Velocityc;
				time2c = 0;
			}
			if (time3c == 40)
			{
				Velocityc = -Velocityc;
				time3c = 0;
			}

			if (time2d == 2)
			{
				time3d++;
				Velocityd = -Velocityd;
				time2d = 0;
			}
			if (time3d == 40)
			{
				Velocityd = -Velocityd;
				time3d = 0;
			}
			
			//恐怖ゲージが満タンの時にclear画面へ
			if (lifetime >= 500)
			{
				if (STAGE == 2)
				{
					mode = clear2;
				}
				else
				{
					mode = clear5;
				}
			}
			//ライフ画像を表示する処理
			if (lifetime <= 501)
			{
				if (lifetime == 50)
				{
					life = 1;
				}
				if (lifetime == 100)
				{
					life = 2;
				}
				if (lifetime == 150)
				{
					life = 3;
				}
				if (lifetime == 200)
				{
					life = 4;
				}
				if (lifetime == 250)
				{
					life = 5;
				}
				if (lifetime == 300)
				{
					life = 6;
				}
				if (lifetime == 350)
				{
					life = 7;
				}
				if (lifetime == 400)
				{
					life = 8;
				}
				if (lifetime == 450)
				{
					life = 9;
				}
			}

			break;

			//3ステージ
			case game3:

				if (STAGE == 3)
				{
					STAGE3Text.Draw();
				}
				else
				{
					STAGE6Text.Draw();
				}

				if (App::GetKeyDown(VK_LBUTTON) &&
					App::GetMousePosition().y >= 350 &&
					App::GetMousePosition().x >= 486)
				{
					mode = Title;
				}

				titlepng.Draw();
				x++;

				i += time + lifetime * timea + time2d;
				i++;
				if (i > 10000000)
				{
					i = 0;
				}

				//エフェクトの動き
				ef1.position += Velocity;
				ef2.position += Velocity;
				ef3.position += Velocity;
				ef4.position += Velocity;

				//制限時間の処理
				time++;
				if (STAGE == 3)
				{
					if (time >= 610)
					{
						time = 0;
						timea++;
					}
				}
				else
				{
					if (time >= 285)
					{
						time = 0;
						timea++;
					}
				}
				//向いている方向とマウスの場所が同じとき
				if (chara2a == mouse)
				{
					time += 10;
				}
				if (chara2b == mouse)
				{
					time += 15;
				}
				if (chara2c == mouse)
				{
					time += 20;
				}

				//制限時間が来たらタイトルへ
				if (timea == 20)
				{
					mode = bad;
				}

				if (App::GetKey(VK_LBUTTON))
				{
					chara3a++;
					chara3b++;
					pgText.Draw();//エフェクトの文字の描画
				}
				else//マウスを押してないとき
				{
					//リアクションしてすぐマウスを離すと向く位置がランダムになる
					if (chara4a <= 20)
					{
						chara1a = i % 4;
					}
					mouse = 4;
				}

				//aリアクションの時間管理
				if (chara3a < 200)
				{
					chara3a++;
				}
				if (chara3a >= 70)
				{
					reaction1.Draw();
					chara4a++;
				}
				if (chara4a >= 50)
				{
					chara2a = chara1a;
					chara3a = 0;
					chara4a = 0;
				}

				//bリアクションの時間管理
				if (chara3b < 300)
				{
					chara3b++;
				}
				if (chara3b >= 300)
				{
					reaction2.Draw();
					chara4b++;
					if (mouse == 4)
					{
					}
					else
					{
						chara1b = mouse;
					}
				}
				if (chara4b >= 30)
				{
					chara2b = chara1b;
					chara3b = 0;
					chara4b = 0;
				}

				if (x % 100 == 0)
				{
					chara2c++;
				}
				if (chara2c >= 4)
				{
					chara2c = 0;
				}

				//エフェクトの向きを変える処理
				if (x % 20 == 0)
				{
					Velocity = -Velocity;
				}

				//画像が点滅しないようにする処理
				if (timea < 21)
				{
					if (timea >= 1)
					{
						timea1[1].Draw();
					}
					if (timea >= 2)
					{
						timea1[2].Draw();
					}
					if (timea >= 2)
					{
						timea1[2].Draw();
					}
					if (timea >= 3)
					{
						timea1[3].Draw();
					}
					if (timea >= 4)
					{
						timea1[4].Draw();
					}
					if (timea >= 5)
					{
						timea1[5].Draw();
					}
					if (timea >= 6)
					{
						timea1[6].Draw();
					}
					if (timea >= 6)
					{
						timea1[6].Draw();
					}
					if (timea >= 7)
					{
						timea1[7].Draw();
					}
					if (timea >= 8)
					{
						timea1[8].Draw();
					}
					if (timea >= 9)
					{
						timea1[9].Draw();
					}
					if (timea >= 10)
					{
						timea1[10].Draw();
					}
					if (timea >= 11)
					{
						timea1[11].Draw();
					}
					if (timea >= 12)
					{
						timea1[12].Draw();
					}
					if (timea >= 13)
					{
						timea1[13].Draw();
					}
					if (timea >= 14)
					{
						timea1[14].Draw();
					}
					if (timea >= 15)
					{
						timea1[15].Draw();
					}
					if (timea >= 16)
					{
						timea1[16].Draw();
					}
					if (timea >= 17)
					{
						timea1[17].Draw();
					}
					if (timea >= 18)
					{
						timea1[18].Draw();
					}
					if (timea >= 19)
					{
						timea1[19].Draw();
					}
					if (timea >= 20)
					{
						timea1[20].Draw();
					}
				}

				charaa[chara2a].Draw();
				charab[chara2b].Draw();
				charac[chara2c].Draw();
				lifea[0].Draw();
				lifea[life].Draw();
				map1.Draw();
				timea1[timea].Draw();
				objecta.Draw();
				objectb.Draw();
				objectc.Draw();
				objectd.Draw();
				time4.Draw();


				//ここからオブジェクトを動かす処理
				//マウスが左下にある時
				if (App::GetMousePosition().y < 0 &&
					App::GetMousePosition().x < 0 &&
					App::GetKey(VK_LBUTTON))
				{
					if (chara4a == 0)
					{
						chara1a = 0;
					}
					if (chara4b == 0)
					{
						chara1b = 0;
					}
					mouse = 0;

					ef1.Draw();//エフェクトの表示
					lifetime++;
					time2a++;
					if (time3a < 4)
					{
						objecta.position.x += Velocitya;
						objecta.position.x += Velocitya;
						objecta.position.y += Velocitya;
						objecta.position.x += Velocitya;
						objecta.position.x += Velocitya;
					}
				}
				//マウスが右上にあるとき
				if (App::GetMousePosition().y > 0 &&
					App::GetMousePosition().x > 0 &&
					App::GetKey(VK_LBUTTON))
				{
					if (chara4a == 0)
					{
						chara1a = 1;
					}

					if (chara4b == 0)
					{
						chara1b = 1;
					}
					mouse = 1;
					ef2.Draw();//エフェクトの表示
					lifetime++;
					time2b++;
					if (time3b < 4)
					{
						objectb.position.x += Velocityb;
						objectb.position.x += Velocityb;
						objectb.position.y += Velocityb;
						objectb.position.x += Velocityb;
						objectb.position.x += Velocityb;

					}
				}
				//マウスが右下にあるとき
				if (App::GetMousePosition().y < 0 &&
					App::GetMousePosition().x > 0 &&
					App::GetKey(VK_LBUTTON))
				{
					if (chara4a == 0)
					{
						chara1a = 2;
					}

					if (chara4b == 0)
					{
						chara1b = 2;
					}
					mouse = 2;
					ef3.Draw();//エフェクトの表示
					lifetime++;
					time2c++;
					if (time3c < 4)
					{
						objectc.position.x += Velocityc;
						objectc.position.x += Velocityc;
						objectc.position.y += Velocityc;
						objectc.position.x += Velocityc;
						objectc.position.x += Velocityc;
					}
				}

				//マウスが左上にある時
				if (App::GetMousePosition().y > 0 &&
					App::GetMousePosition().x < 0 &&
					App::GetKey(VK_LBUTTON))
				{
					if (chara4a == 0)
					{
						chara1a = 3;
					}

					if (chara4b == 0)
					{
						chara1b = 3;
					}
					mouse = 3;
					ef4.Draw();//エフェクトの表示
					lifetime++;
					time2d++;
					if (time3d < 4)
					{
						objectd.position.x += Velocityd;
						objectd.position.x += Velocityd;
						objectd.position.y += Velocityd;
						objectd.position.x += Velocityd;
						objectd.position.x += Velocityd;
					}
				}



				if (time2a == 2)
				{
					time3a++;
					Velocitya = -Velocitya;
					time2a = 0;
				}
				if (time3a == 40)
				{
					Velocitya = -Velocitya;
					time3a = 0;
				}
				if (time2b == 2)
				{
					time3b++;
					Velocityb = -Velocityb;
					time2b = 0;
				}
				if (time3b == 40)
				{
					Velocityb = -Velocityb;
					time3b = 0;
				}


				if (time2c == 2)
				{
					time3c++;
					Velocityc = -Velocityc;
					time2c = 0;
				}
				if (time3c == 40)
				{
					Velocityc = -Velocityc;
					time3c = 0;
				}

				if (time2d == 2)
				{
					time3d++;
					Velocityd = -Velocityd;
					time2d = 0;
				}
				if (time3d == 40)
				{
					Velocityd = -Velocityd;
					time3d = 0;
				}

				//恐怖ゲージが満タンの時にclear画面へ
				if (lifetime >= 1900)
				{
					if (STAGE == 3)
					{
						mode = clear3;
					}
					else
					{
						mode = clear6;
					}
				}
				//ライフ画像を表示する処理
				if (lifetime <= 10000)
				{
					if (lifetime == 1000)
					{
						life = 1;
					}
					if (lifetime == 1100)
					{
						life = 2;
					}
					if (lifetime == 1200)
					{
						life = 3;
					}
					if (lifetime == 1300)
					{
						life = 4;
					}
					if (lifetime == 1400)
					{
						life = 5;
					}
					if (lifetime == 1500)
					{
						life = 6;
					}
					if (lifetime == 1600)
					{
						life = 7;
					}
					if (lifetime == 1700)
					{
						life = 8;
					}
					if (lifetime == 1800)
					{
						life = 9;
					}
					if (lifetime == 0)
					{
						life = 10;
					}
					if (lifetime == 100)
					{
						life = 11;
					}
					if (lifetime == 200)
					{
						life = 12;
					}
					if (lifetime == 300)
					{
						life = 13;
					}
					if (lifetime == 400)
					{
						life = 14;
					}
					if (lifetime == 500)
					{
						life = 15;
					}
					if (lifetime == 600)
					{
						life = 16;
					}
					if (lifetime == 700)
					{
						life = 17;
					}
					if (lifetime == 800)
					{
						life = 18;
					}
					if (lifetime == 900)
					{
						life = 0;
					}

				}

				break;
		}
	}
	return 0;
}
