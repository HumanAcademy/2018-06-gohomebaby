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
	clear,
	clear2,
	chara,			//おまけモード
	bad,			//ゲームオーバー
	ruru,           //あそびかた
	pause,			//ポーズ画面
};

int main()
{
	int ruru1 = 0;		//タイトル→ルールかステージ→ルールを判別する方法（0 = タイトル　1 = ゲーム）
	int OBAKE = 0;      //お化けの画像の変更
	int stage = 1;      //タイトルで選択できるステージの数
	int STAGE = 1;		//現在のステージ
	int x;				//永遠に増える数
	int y = 0;			//pauseに使う数
	int i = 0;			//時計の処理に使う
	int clock1 = 0;		//aキャラクターのダメージ判定までの時間
	int clock2 = 0;		//bキャラクターのダメージ判定までの時間
	int clock3 = 0;		//cキャラクターのダメージ判定までの時間
	int barrier = 0;    //無敵かどうか0通常1無敵
	int button = 0;     //PGしているかどうか
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
	int mouse = 4;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
	int lifetime = 0;	//キャラクターのHPを減らすまでの時間
	int life = 0;	    //キャラクターのHP.恐怖ゲージの画像のための数
	int life2 = 2;		//プレイヤーのHP
	int time = 0; //barrier時間の管理
	int timea = 0; //制限時間の画像の表示
	int time2a = 0; //ピアノの管理時間
	int time2a1 = 0;//ピアノ覚醒の数
	int time2b = 0; //Velocityの管理時間
	int time3b = 0; //物が動いてから次動くまでの待機時間
	int time2c = 0; //Velocityの管理時間
	int time3c = 0; //物が動いてから次動くまでの待機時間
	float Velocity = 0.5; //エフェクトの動き
	float Velocitya = 2; //物の動き
	float Velocityb = 0.0001; //物の動き
	float Velocityc = 2; //物の動き
	float Velocityd = 2; //物の動き
	int piano1 = 0;		 //pianoの画像
	int piano2 = 0;		//ピアノが覚醒しているかどうか
	int chair1 = 0;		//花瓶が割れているとき1 割れてないとき0
	int chair2 = 0;		//花瓶を割るための変数
	int bin1 = 0;		//瓶空中 = 0 空中2 = 1 割れている = 2
	int bin2 = 0;		//bin1を変えるために使う数
	int HAND = 0;		//手の表示数
	int time4 = 0;		//手の表示のカウンター
	int time5 = 0;		//額縁のカウンター（時間回復）
	int timelife = 0;	//時間回復したかどうか
	int lifeup = 0;     //回復したかどうか
	App::SetWindowSize(1200, 800);

	Sprite charaa[4];	//人間aの画像
	Sprite charab[4];	//人間bの画像
	Sprite charac[4];	//人間cの画像
	Sprite HP[4];		//亡霊のHP左下
	Sprite HP2[4];      //亡霊のHP亡霊の中
	Sprite lifea[19];  //ライフの画像
	Sprite lifeb[19];  //ライフの画像
	Sprite obake[2];   //お化けの画像
	Sprite piano[4];   //pianoの画像
	Sprite clearText[2];
	int objectspeed = 1;

	HP[0].Load(L"life00.png");
	HP[1].Load(L"life01.png");
	HP[2].Load(L"life02.png");
	HP[3].Load(L"life03.png");
	HP[0].position.x = -400;
	HP[0].position.y = -230;
	HP[1].position.x = -400;
	HP[1].position.y = -230;
	HP[2].position.x = -400;
	HP[2].position.y = -230;
	HP[3].position.x = -400;
	HP[3].position.y = -230;
	HP[0].scale = 1;
	HP[1].scale = 1;
	HP[2].scale = 1;
	HP[3].scale = 1;

	HP2[0].Load(L"life00.png");
	HP2[1].Load(L"life01.png");
	HP2[2].Load(L"life02.png");
	HP2[3].Load(L"life03.png");
	HP2[0].position.x = 500;
	HP2[0].position.y = 40;
	HP2[1].position.x = 500;
	HP2[1].position.y = 40;
	HP2[2].position.x = 500;
	HP2[2].position.y = 40;
	HP2[3].position.x = 500;
	HP2[3].position.y = 40;
	HP2[0].scale = 0.055;
	HP2[1].scale = 0.055;
	HP2[2].scale = 0.055;
	HP2[3].scale = 0.055;

	Sound damageSound(L"damage.wav");
	Sound clearSound(L"clear.wav");
	Sound ok1Sound(L"ok1.wav");
	Sound ok2Sound(L"ok2.wav");
	Sound STARTSound(L"START.wav");
	Sound pianoSound(L"piano.wav");
	Sound pauseSound(L"pause.wav");
	Sound bgm1(L"bgm.wav");
	Sound bgm2(L"bgm.wav");
	Sound bgm3(L"bgm2.wav");
	Sound bgm4(L"bgm3.wav");
	Sound bgm5(L"bgm3.wav");
	Sound down(L"down.wav");
	Sound chairSound(L"chair.mp3");
	Sound lifeSound(L"life.wav");
	Sound timeWav(L"time.wav");
	Sound handSound(L"hand.wav");

	Sprite chair[2];			//0 = 割れてない椅子　　1 = 割れている椅子
	Sprite title2(L"タイトル1.png");
	Sprite title3(L"タイトル2.png");
	Sprite STAGE1(L"1クリア.png");
	Sprite STAGE2(L"2クリア.png");
	Sprite STAGE3(L"3クリア.png");
	Sprite STAGE4(L"4クリア.png");
	Sprite STAGE5(L"5クリア.png");
	Sprite mode1(L"1未達成.png");
	Sprite mode2(L"2未達成.png");
	Sprite mode3(L"3未達成.png");
	Sprite mode4(L"4未達成.png");
	Sprite mode5(L"5未達成.png");

	chair[0].Load(L"椅子+花瓶.png");
	chair[1].Load(L"椅子.png");
	chair[0].position.x = -498;
	chair[0].position.y = -140;
	chair[0].scale = 0.2;
	chair[1].position.x = -498;
	chair[1].position.y = -140;
	chair[1].scale = 0.2;

	Sprite bin[3];

	bin[0].Load(L"落ちてる花瓶.png");		//花瓶の画像
	bin[2].Load(L"割れた花瓶.png");
	bin[1].Load(L"落ちてる花瓶.png");
	bin[2].position.x = -410;
	bin[2].position.y = -200;
	bin[2].scale = 0.3;
	bin[0].position.x = -400;
	bin[0].position.y = -140;
	bin[0].scale = 0.3;
	bin[1].position.x = -400;
	bin[1].position.y = -180;
	bin[1].scale = 0.3;

	Sprite hand[5];
	hand[0].Load(L"hand1.png");
	hand[1].Load(L"hand2.png");
	hand[2].Load(L"hand3.png");
	hand[3].Load(L"hand4.png");
	hand[4].Load(L"hand5.png");
	hand[0].scale = 0.9;
	hand[0].scale.y = 0.8;
	hand[0].position.x = -50;
	hand[1].scale = 0.9;
	hand[1].scale.y = 0.8;
	hand[1].position.x = -50;
	hand[2].scale = 0.9;
	hand[2].scale.y = 0.8;
	hand[2].position.x = -50;
	hand[3].scale = 0.9;
	hand[3].scale.y = 0.8;
	hand[3].position.x = -50;
	hand[4].scale = 0.9;
	hand[4].scale.y = 0.8;
	hand[4].position.x = -50;

	Sprite game01(L"ゲーム画面1.png");
	Sprite game02(L"ゲーム画面2.png");
	Sprite game03(L"ゲーム画面3.png");

	Sprite pausepng(L"ポーズボタン.png");				//ポーズ画像
	pausepng.position.x = 540;
	pausepng.position.y = 337;
	pausepng.scale = 0.5;

	Sprite moya(L"moya2.png");
	moya.scale = 0.52;
	moya.position.x = 130;
	moya.position.y = 150;

	Sprite clock4(L"clock1.png");		//時計の画像
	clock4.position.x = -490;
	clock4.position.y = 320;
	clock4.scale = 0.1;
	

	Sprite clock5(L"clock2.png");		//針の画像
	clock5.position.x = -490;
	clock5.position.y = 320;
	clock5.scale = 0.1;

	Text obakeText(L"　ボンド君", 100);
	obakeText.color = Float4(1.0, 0.0, 0.0, 1.0);
	obakeText.position.x = -440;
	obakeText.position.y = -60;
	obakeText.scale = 0.3;

	Text omakeText(L"デフォルメキャラ", 100);
	omakeText.color = Float4(1.0, 0.0, 0.0, 1.0);
	omakeText.position.x = -170;
	omakeText.position.y = -80;
	omakeText.scale = 0.3;

	Text omake2Text(L"通称ボ〇バーマン", 100);
	omake2Text.color = Float4(1.0, 0.0, 0.0, 1.0);
	omake2Text.position.x = -170;
	omake2Text.position.y = -110;
	omake2Text.scale = 0.3;

	Text omake3Text(L"デフォルメキャラ(元祖）", 100);
	omake3Text.color = Float4(1.0, 0.0, 0.0, 1.0);
	omake3Text.position.x = 160;
	omake3Text.position.y = -80;
	omake3Text.scale = 0.3;

	Text omake4Text(L"通称ダンボール君", 100);
	omake4Text.color = Float4(1.0, 0.0, 0.0, 1.0);
	omake4Text.position.x = 130;
	omake4Text.position.y = -110;
	omake4Text.scale = 0.3;

	Text omake5Text(L"デバック源ちゃん", 100);
	omake5Text.color = Float4(1.0, 0.0, 0.0, 1.0);
	/*omake5Text.position.x = -170;*/
	omake5Text.position.y = 300;
	omake5Text.scale = 1.5;

	Text omake1Text(L"SPACE　もどる", 100.0);
	omake1Text.position.x = 0.0;
	omake1Text.position.y = -250.0;
	omake1Text.scale = 0.5;
	omake1Text.color = Float4(0.0, 0.0, 0.0, 1.0);


	obake[0].Load(L"obake1.png");
	obake[0].scale = 6;
	obake[0].position.x = 580;
	obake[0].position.y = -150;

	obake[1].Load(L"obake2.png");
	obake[1].scale = 6;
	obake[1].position.x = 580;
	obake[1].position.y = -150;

	Sprite obake1(L"obake2.png");
	obake1.scale = 8;
	obake1.position.x = 550;
	obake1.position.y = 0;

	Sprite obake2(L"obake2.png");
	obake2.scale = 8;
	obake2.position.x = -350;
	obake2.position.y = 0;

	Sprite obake3(L"obake3.png");
	obake3.scale = 8;
	obake3.position.x = -350;
	obake3.position.y = 40;

	Sprite obake4(L"obake3.png");
	obake4.scale = 8;
	obake4.position.x = 550;
	obake4.position.y = 40;

	Sprite obake5(L"obake3.png");
	obake5.scale = 8;
	obake5.position.x = 550;
	obake5.position.y = 40;

	//プレイ中の画面上のステージの名前
	Sprite STAGE1Text(L"stage01.png");
	STAGE1Text.position.y = 350;
	STAGE1Text.position.x = 20;


	Sprite STAGE2Text(L"stage02.png");
	STAGE2Text.position.y = 350;
	STAGE2Text.position.x = 20;

	Sprite STAGE3Text(L"stage03.png");
	STAGE3Text.position.y = 350;
	STAGE3Text.position.x = 20;

	Sprite STAGE4Text(L"stage04.png");
	STAGE4Text.position.y = 350;
	STAGE4Text.position.x = 20;

	Sprite STAGE5Text(L"stage05.png");
	STAGE5Text.position.y = 350;
	STAGE5Text.position.x = 20;

	Sprite pause1png(L"ポーズデフォ.png");		//タイトルへ戻るための画像
	Sprite pause2png(L"ポーズ1.png");
	Sprite pause3png(L"ポーズ2.png");
	Sprite pause4png(L"ポーズ3.png");

	Text mouseposition;
	mouseposition.position.y = 100;
	mouseposition.scale = 3.0;

	Sprite reaction1(L"!.png");
	reaction1.scale = 0.1;
	reaction1.position.x = 80;
	reaction1.position.y = -22;

	Sprite reaction2(L"!.png");
	reaction2.scale = 0.1;
	reaction2.position.x = -132;
	reaction2.position.y = -22;

	Sprite reaction3(L"!.png");
	reaction3.scale = 0.1;
	reaction3.position.y = 280;

	Sprite omake2(L"デフォルメ.png");
	omake2.scale = 3;
	omake2.position.x = -160;
	omake2.position.y = 60;

	Sprite omake3(L"デフォルメ2.png");
	omake3.scale = 2;
	omake3.position.x = 130;
	omake3.position.y = 60;

	charaa[0].Load(L"黄デフォルメ左下.png");
	charaa[0].scale = 0.2;
	charaa[0].position.x = 80;
	charaa[0].position.y = -130;

	charaa[1].Load(L"黄デフォルメ右上.png");
	charaa[1].scale = 0.2;
	charaa[1].position.x = 80;
	charaa[1].position.y = -130;

	charaa[2].Load(L"黄デフォルメ右下.png");
	charaa[2].scale = 0.2;
	charaa[2].position.x = 80;
	charaa[2].position.y = -130;

	charaa[3].Load(L"黄デフォルメ左上.png");
	charaa[3].scale = 0.2;
	charaa[3].position.x = 80;
	charaa[3].position.y = -130;

	charab[0].Load(L"青デフォルメ左下.png");
	charab[0].scale = 0.2;
	charab[0].position.x = -130;
	charab[0].position.y = -130;

	charab[1].Load(L"青デフォルメ右上.png");
	charab[1].scale = 0.2;
	charab[1].position.x = -130;
	charab[1].position.y = -130;

	charab[2].Load(L"青デフォルメ右下.png");
	charab[2].scale = 0.2;
	charab[2].position.x = -130;
	charab[2].position.y = -130;

	charab[3].Load(L"青デフォルメ左上.png");
	charab[3].scale = 0.2;
	charab[3].position.x = -130;
	charab[3].position.y = -130;

	charac[0].Load(L"赤デフォルメ左下.png");
	charac[0].scale = 0.2;
	charac[0].position.y = -30;
	charac[0].position.x = -30;

	charac[1].Load(L"赤デフォルメ右上.png");
	charac[1].scale = 0.2;
	charac[1].position.y = -30;
	charac[1].position.x = -30;

	charac[2].Load(L"赤デフォルメ右下.png");
	charac[2].scale = 0.2;
	charac[2].position.y = -30;
	charac[2].position.x = -30;

	charac[3].Load(L"赤デフォルメ左上.png");
	charac[3].scale = 0.2;
	charac[3].position.y = -30;
	charac[3].position.x = -30;

	/*Text pgText(L"PG中だよ", 100.0);
	pgText.position.y = -300;
	pgText.color = Float4(1.0, 0.0, 0.0, 1.0);*/

	piano[0].Load(L"piano1.png");		//piano1の画像(通常）(右下）
	piano[0].scale = 0.3;
	piano[0].position.x = 450;
	piano[0].position.y = -125;
	piano[0].angles.z = -5;

	piano[1].Load(L"piano2.png");		//piano2の画像（PG1)(閉まってる）
	piano[1].scale = 0.3;
	piano[1].position.x = 450;
	piano[1].position.y = -125;
	piano[1].angles.z = -5;

	piano[2].Load(L"piano3.png");		//piano1の画像(PG2)（あいている）
	piano[2].scale = 0.3;
	piano[2].position.x = 450;
	piano[2].position.y = -125;
	piano[2].angles.z = -5; 

	piano[3].Load(L"piano4.png");		//piano1の画像(PG3)（あいている覚醒）
	piano[3].scale = 0.3;
	piano[3].position.x = 450;
	piano[3].position.y = -125;
	piano[3].angles.z = -5;

	Sprite hand0(L"hand.png");
	hand0.scale = 0.9;
	hand0.scale.y = 0.8;
	hand0.position.x = -50;

	Sprite gaku(L"gaku.png");		//オブジェクト（額縁
	gaku.scale = 0.75;
	gaku.scale.y = 0.68;
	gaku.position.x = 230;
	gaku.position.y = 150;

	Sprite map1(L"room.png");		//部屋の画像
	map1.scale = 0.9;
	map1.scale.y = 0.8;
	map1.position.x = -50;

	lifea[0].Load(L"life1.png"); //ライフの画像
	lifea[0].position.x = -10;
	lifea[0].position.y = -300;
	lifea[0].scale = 0.2;

	lifea[1].Load(L"life2.png"); //ライフの画像
	lifea[1].position.x = -10;
	lifea[1].position.y = -300;
	lifea[1].scale = 0.2;

	lifea[2].Load(L"life3.png"); //ライフの画像
	lifea[2].position.x = -10;
	lifea[2].position.y = -300;
	lifea[2].scale = 0.2;

	lifea[3].Load(L"life4.png"); //ライフの画像
	lifea[3].position.x = -10;
	lifea[3].position.y = -300;
	lifea[3].scale = 0.2;

	lifea[4].Load(L"life5.png"); //ライフの画像
	lifea[4].position.x = -10;
	lifea[4].position.y = -300;
	lifea[4].scale = 0.2;
	
	lifea[5].Load(L"life6.png"); //ライフの画像
	lifea[5].position.x = -10;
	lifea[5].position.y = -300;
	lifea[5].scale = 0.2;

	lifea[6].Load(L"life7.png"); //ライフの画像
	lifea[6].position.x = -10;
	lifea[6].position.y = -300;
	lifea[6].scale = 0.2;

	lifea[7].Load(L"life8.png"); //ライフの画像
	lifea[7].position.x = -10;
	lifea[7].position.y = -300;
	lifea[7].scale = 0.2;

	lifea[8].Load(L"life9.png"); //ライフの画像
	lifea[8].position.x = -10;
	lifea[8].position.y = -300;
	lifea[8].scale = 0.2;

	lifea[9].Load(L"life10.png"); //ライフの画像
	lifea[9].position.x = -10;
	lifea[9].position.y = -300;
	lifea[9].scale = 0.2;

	lifea[10].Load(L"life11.png"); //ライフの画像
	lifea[10].position.x = -10;
	lifea[10].position.y = -300;
	lifea[10].scale = 0.2;

	lifea[11].Load(L"life12.png"); //ライフの画像
	lifea[11].position.x = -10;
	lifea[11].position.y = -300;
	lifea[11].scale = 0.2;

	lifea[12].Load(L"life13.png"); //ライフの画像
	lifea[12].position.x = -10;
	lifea[12].position.y = -300;
	lifea[12].scale = 0.2;

	lifea[13].Load(L"life14.png"); //ライフの画像
	lifea[13].position.x = -10;
	lifea[13].position.y = -300;
	lifea[13].scale = 0.2;

	lifea[14].Load(L"life15.png"); //ライフの画像
	lifea[14].position.x = -10;
	lifea[14].position.y = -300;
	lifea[14].scale = 0.2;

	lifea[15].Load(L"life16.png"); //ライフの画像
	lifea[15].position.x = -10;
	lifea[15].position.y = -300;
	lifea[15].scale = 0.2;

	lifea[16].Load(L"life17.png"); //ライフの画像
	lifea[16].position.x = -10;
	lifea[16].position.y = -300;
	lifea[16].scale = 0.2;

	lifea[17].Load(L"life18.png"); //ライフの画像
	lifea[17].position.x = -10;
	lifea[17].position.y = -300;
	lifea[17].scale = 0.2;

	lifea[18].Load(L"life19.png"); //ライフの画像
	lifea[18].position.x = -10;
	lifea[18].position.y = -300;
	lifea[18].scale = 0.2;

	lifeb[0].Load(L"life1.png"); //ライフの画像
	lifeb[0].position.x = -10;
	lifeb[0].position.y = -250;
	lifeb[0].scale = 0.3;

	lifeb[1].Load(L"life2.png"); //ライフの画像
	lifeb[1].position.x = -10;
	lifeb[1].position.y = -250;
	lifeb[1].scale = 0.3;

	lifeb[2].Load(L"life3.png"); //ライフの画像
	lifeb[2].position.x = -10;
	lifeb[2].position.y = -250;
	lifeb[2].scale = 0.3;

	lifeb[3].Load(L"life4.png"); //ライフの画像
	lifeb[3].position.x = -10;
	lifeb[3].position.y = -250;
	lifeb[3].scale = 0.3;

	lifeb[4].Load(L"life5.png"); //ライフの画像
	lifeb[4].position.x = -10;
	lifeb[4].position.y = -250;
	lifeb[4].scale = 0.3;

	lifeb[5].Load(L"life6.png"); //ライフの画像
	lifeb[5].position.x = -10;
	lifeb[5].position.y = -250;
	lifeb[5].scale = 0.3;

	lifeb[6].Load(L"life7.png"); //ライフの画像
	lifeb[6].position.x = -10;
	lifeb[6].position.y = -250;
	lifeb[6].scale = 0.3;

	lifeb[7].Load(L"life8.png"); //ライフの画像
	lifeb[7].position.x = -10;
	lifeb[7].position.y = -250;
	lifeb[7].scale = 0.3;

	lifeb[8].Load(L"life9.png"); //ライフの画像
	lifeb[8].position.x = -10;
	lifeb[8].position.y = -250;
	lifeb[8].scale = 0.3;

	lifeb[9].Load(L"life10.png"); //ライフの画像
	lifeb[9].position.x = -10;
	lifeb[9].position.y = -250;
	lifeb[9].scale = 0.3;

	lifeb[10].Load(L"life11.png"); //ライフの画像
	lifeb[10].position.x = -10;
	lifeb[10].position.y = -250;
	lifeb[10].scale = 0.3;

	lifeb[11].Load(L"life12.png"); //ライフの画像
	lifeb[11].position.x = -10;
	lifeb[11].position.y = -250;
	lifeb[11].scale = 0.3;

	lifeb[12].Load(L"life13.png"); //ライフの画像
	lifeb[12].position.x = -10;
	lifeb[12].position.y = -250;
	lifeb[12].scale = 0.3;

	lifeb[13].Load(L"life14.png"); //ライフの画像
	lifeb[13].position.x = -10;
	lifeb[13].position.y = -250;
	lifeb[13].scale = 0.3;

	lifeb[14].Load(L"life15.png"); //ライフの画像
	lifeb[14].position.x = -10;
	lifeb[14].position.y = -250;
	lifeb[14].scale = 0.3;

	lifeb[15].Load(L"life16.png"); //ライフの画像
	lifeb[15].position.x = -10;
	lifeb[15].position.y = -250;
	lifeb[15].scale = 0.3;

	lifeb[16].Load(L"life17.png"); //ライフの画像
	lifeb[16].position.x = -10;
	lifeb[16].position.y = -250;
	lifeb[16].scale = 0.3;

	lifeb[17].Load(L"life18.png"); //ライフの画像
	lifeb[17].position.x = -10;
	lifeb[17].position.y = -250;
	lifeb[17].scale = 0.3;

	lifeb[18].Load(L"life19.png"); //ライフの画像
	lifeb[18].position.x = -10;
	lifeb[18].position.y = -250;
	lifeb[18].scale = 0.3;

	Sprite kurisu(L"クリスさん.png");
	kurisu.position.x = 430;
	kurisu.scale = 0.5;

	Text kurisuText(L"幽霊はこの人です。", 100);
	kurisuText.color = Float4(1.0, 0.0, 0.0, 1.0);
	kurisuText.position.x = 450;
	kurisuText.position.y = -120;
	kurisuText.scale = 0.3;

	Text kurisu1Text(L"(クリストファー)", 100);
	kurisu1Text.color = Float4(1.0, 0.0, 0.0, 1.0);
	kurisu1Text.position.x = 450;
	kurisu1Text.position.y = -160;
	kurisu1Text.scale = 0.3;
	
	Sprite GAMEOVERText(L"ゲームオーバー.png");
	
	clearText[0].Load(L"2.png");

	clearText[1].Load(L"1.png");

	Sprite space00(L"3.png");

	Sprite clear0Text(L"ゲームクリア.png");
	
	App::SetTitle(L"GO HOME BABY");
	
	Camera camera;

	//Text MOuseText(L"", 100);  //マウス座標の把握用
	//MOuseText.scale = 2;
	//MOuseText.position.y = 300;

	Mode mode = Title; 

	
	while (App::Refresh())
	{
		camera.Update();
		camera.color = Float4(0.2, 0.2, 0.2, 0.4);
		/*マウス座標の把握用*/
		/*MOuseText.Create(std::to_wstring(App::GetMousePosition().x)+
			L"," + std::to_wstring(App::GetMousePosition().y));
		MOuseText.Draw();*/
		switch (mode)
		{
		case Title:
			x++;
			if (stage < 6)
			{
				if (x % 400 == 0 ||
					x == 1)
				{
					bgm4.Play();
				}
				else if (x % 200 == 0)
				{
					bgm5.Play();
				}
				if (x % 600 == 0)
				{
					bgm3.Play();
				}
				title2.Draw();
			}
			else
			{

				title3.Draw();
				if (x % 400 == 0 ||
					x == 1)
				{
					bgm1.Play();
				}
				else if (x % 200 == 0)
				{
					bgm2.Play();
				}
				if (x % 600 == 0)
				{
					bgm3.Play();
				}
			}
			//遊び方から戻った時用
			HP[0].position.x = -400;
			HP[0].position.y = -230;
			HP[1].position.x = -400;
			HP[1].position.y = -230;
			HP[2].position.x = -400;
			HP[2].position.y = -230;
			HP[0].scale = 0.2;
			HP[1].scale = 0.2;
			HP[2].scale = 0.2;
			HP[3].scale = 0.2;
			lifea[0].position.x = -10;
			lifea[0].position.y = -300;
			y = 0;
			//ここまで
			if (App::GetKey('Z') &&			//全クリコマンド
				App::GetKey('1'))
			{
				stage = 6;
			}

			//マウスでのＳＴＡＧＥ選択
			if (stage >= 2)
			{
				if (App::GetKeyDown(VK_LBUTTON) &&
					-325 <= App::GetMousePosition().x &&
					App::GetMousePosition().x <= -165 &&
					-181 <= App::GetMousePosition().y &&
					App::GetMousePosition().y <= -106&&
					STAGE != 1)
				{
					ok2Sound.Play();
					STAGE = 1;
				}

				if (App::GetKeyDown(VK_LBUTTON) &&
					-212 <= App::GetMousePosition().x &&
					App::GetMousePosition().x <= -52 &&
					-270 <= App::GetMousePosition().y &&
					App::GetMousePosition().y <= -195 &&
					STAGE != 2)
				{
					ok2Sound.Play();
					STAGE = 2;
				}
				mode2.Draw();
				mode1.Draw();
				if (stage >= 3)
				{
					if (App::GetKeyDown(VK_LBUTTON) &&
						-81 <= App::GetMousePosition().x &&
						App::GetMousePosition().x <= 79 &&
						-181 <= App::GetMousePosition().y &&
						App::GetMousePosition().y <= -106 &&
						STAGE != 3)
					{
						ok2Sound.Play();
						STAGE = 3;
					}
					mode3.Draw();
					if (stage >= 4)
					{
						if (App::GetKeyDown(VK_LBUTTON) &&
							53 <= App::GetMousePosition().x &&
							App::GetMousePosition().x <= 210 &&
							-270 <= App::GetMousePosition().y &&
							App::GetMousePosition().y <= -195 &&
							STAGE != 4)
						{
							ok2Sound.Play();
							STAGE = 4;
						}
						mode4.Draw();
						if (stage >= 5)
						{
							if (App::GetKeyDown(VK_LBUTTON) &&
								165 <= App::GetMousePosition().x &&
								App::GetMousePosition().x <= 322 &&
								-181 <= App::GetMousePosition().y &&
								App::GetMousePosition().y <= -106 &&
								STAGE != 5)
							{
								ok2Sound.Play();
								STAGE = 5;
							}
							mode5.Draw();
							if (stage >= 6)
							{
								obake1.Draw();
								obake2.Draw(); 
								if (App::GetKeyDown(VK_LBUTTON) &&
									App::GetMousePosition().x <= 106 &&
									App::GetMousePosition().x >= -113 &&
									App::GetMousePosition().y <= 153 &&
									App::GetMousePosition().y >= 0)
								{
									bgm1.Stop();
									bgm2.Stop();
									bgm3.Stop();
									bgm4.Stop();
									bgm5.Stop();
									ok1Sound.Play();
									mode = chara;
								}
							}
						}
					}
				}
			}	
			STAGE1Text.position.y = -25;
			STAGE2Text.position.y = -25;
			STAGE3Text.position.y = -25;
			STAGE4Text.position.y = -25;
			STAGE5Text.position.y = -25;
			if (App::GetKeyDown(VK_LBUTTON) &&
				478 <= App::GetMousePosition().x &&
				App::GetMousePosition().x <= 575 &&
				-380 <= App::GetMousePosition().y &&
				App::GetMousePosition().y <= -285)
			{
				bgm1.Stop();
				bgm2.Stop();
				bgm3.Stop();
				bgm4.Stop();
				bgm5.Stop();
				ruru1 = 0;
				mode = ruru;
			}
			if (STAGE == 1)
			{
				STAGE1.Draw();
			}
			if (STAGE == 2)
			{
				STAGE2.Draw();
			}
			if (STAGE == 3)
			{
				STAGE3.Draw();
			}
			if (STAGE == 4)
			{
				STAGE4.Draw();
			}
			if (STAGE == 5)
			{
				STAGE5.Draw();
			}
			
			//ゲーム画面へ＋初期化
			if (App::GetKeyDown(VK_SPACE))
			{
				//初期化
				obake[0].scale = 6;
				obake[0].position.x = 580;
				obake[0].position.y = 0;
				obake[1].scale = 6;
				obake[1].position.x = 580;
				obake[1].position.y = 0;
				x = 0; 
				y = 0;
				time2a1 = 0;
				clock5.angles.z = 0;
				chair1 = 0;		//花瓶が割れているとき1 割れてないとき0
				chair2 = 0;		//花瓶を割るための変数
				bin1 = 0;		//瓶空中 = 0 割れている = 1
				bin2 = 0;		//bin1を変えるために使う数
				barrier = 0;    //無敵かどうか0通常1無敵
				button = 0;     //PGしているかどうか
				STAGE1Text.position.y = 350;
				STAGE2Text.position.y = 350;
				STAGE3Text.position.y = 350;
				STAGE4Text.position.y = 350;
				STAGE5Text.position.y = 350;
				gaku.position.x = 130;
				gaku.position.y = 150;
				chair[0].position.x = -498;
				chair[0].position.y = -140;
				chair[0].scale = 0.2;
				chair[1].position.x = -498;
				chair[1].position.y = -140;
				chair[1].scale = 0.2;
				mouse = 4;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
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
				piano2 = 0;
				life2 = 2;
				time = 0; //制限時間
				timea = 0; //制限時間の画像の表示
				time2a = 0; //Velocityの管理時間
				time2b = 0; //Velocityの管理時間
				time3b = 0; //物が動いてから次動くまでの待機時間
				time2c = 0; //Velocityの管理時間
				time3c = 0; //物が動いてから次動くまでの待機時間
				Velocity = 0.5; //エフェクトの動き
				Velocityb = 2; //物の動き
				Velocityc = 2; //物の動き
				Velocityd = 2; //物の動き
				HAND = 0;		//手の表示数
				time4 = 0;		//手の表示のカウンター
				time5 = 0;		//額縁のカウンター（時間回復）
				timelife = 0;	//時間回復したかどうか
				lifeup = 0;
				bgm1.Stop();
				bgm2.Stop();
				bgm3.Stop();
				bgm4.Stop();
				bgm5.Stop();
				if (STAGE == 1)
				{
					STARTSound.Play();
					mode = game1;
				}
				if (STAGE == 2||
					STAGE == 3)
				{
					STARTSound.Play();
					mode = game2;
				}
				if (STAGE == 4||
					STAGE == 5)
				{
					STARTSound.Play();
					mode = game3;
				}
			}
			break;
		case pause:
			pause1png.Draw();
			if (App::GetKeyDown(VK_LBUTTON) &&
				App::GetMousePosition().x >= -200 &&
				App::GetMousePosition().x <= 192 &&
				App::GetMousePosition().y >= 179 &&
				App::GetMousePosition().y <= 265)
			{
				y = 1;
			}
			if (App::GetKeyUp(VK_LBUTTON) &&
				App::GetMousePosition().x >= -200 &&
				App::GetMousePosition().x <= 192 &&
				App::GetMousePosition().y >= 179 &&
				App::GetMousePosition().y <= 265&&
				y == 1)
			{
				ok1Sound.Play();
				mode = Title;
			}
			if (App::GetKeyDown(VK_LBUTTON) &&
				App::GetMousePosition().x >= -130 &&
				App::GetMousePosition().x <= 119 &&
				App::GetMousePosition().y >= -7 &&
				App::GetMousePosition().y <= 89)
			{
				y = 3;
			}
			if (App::GetKeyUp(VK_LBUTTON) &&
				App::GetMousePosition().x >= -130 &&
				App::GetMousePosition().x <= 119 &&
				App::GetMousePosition().y >= -7 &&
				App::GetMousePosition().y <= 89 &&
				y == 3)
			{
				ok1Sound.Play();
				ruru1 = 1;
				mode = ruru;
			}
			if (App::GetKeyDown(VK_LBUTTON) &&
				App::GetMousePosition().x >= -241 &&
				App::GetMousePosition().x <= 243 &&
				App::GetMousePosition().y <= -87 &&
				App::GetMousePosition().y >= -187)
			{
				y = 2;
			}
			if (App::GetKeyUp(VK_LBUTTON) &&
				App::GetMousePosition().x >= -241 &&
				App::GetMousePosition().x <= 243 &&
				App::GetMousePosition().y <= -87 &&
				App::GetMousePosition().y >= -187 &&
				y == 2)
			{
				ok1Sound.Play();
				if (STAGE == 1)
				{
					mode = game1;
				}
				if (STAGE == 2||
					STAGE == 3)
				{
					mode = game2;
				}
				if (STAGE == 4||
					STAGE == 5)
				{
					mode = game3;
				}
			}
			if (!App::GetKey(VK_LBUTTON))
			{
				y = 0;
			}
			if (App::GetMousePosition().x >= -200 &&
				App::GetMousePosition().x <= 192 &&
				App::GetMousePosition().y >= 179 &&
				App::GetMousePosition().y <= 265)
			{
				pause2png.Draw();
			}
			if (App::GetMousePosition().x >= -130 &&
				App::GetMousePosition().x <= 89 &&
				App::GetMousePosition().y >= -7 &&
				App::GetMousePosition().y <= 119)
			{
				pause3png.Draw();
			}
			if (App::GetMousePosition().x >= -241 &&
				App::GetMousePosition().x <= 87 &&
				App::GetMousePosition().y >= -187 &&
				App::GetMousePosition().y <= -87)
			{
				pause4png.Draw();
			}
			break;

		case ruru:
			if (y == 0)
			{
				game01.Draw();
			}
			if (App::GetKeyUp(VK_SPACE))
			{
				if (ruru1 == 0)
				{
					y = 1;
				}
				else
				{
					y = 2;
				}
			}
			if (y == 2)
			{
				game03.Draw();
				if (App::GetKeyDown(VK_SPACE))
				{
					mode = pause;
				}
			}
			if (y == 1)
			{
				game02.Draw();
				if (App::GetKeyDown(VK_SPACE))
				{
					mode = Title;
				}
			}
			break;

		case chara:

			if (App::GetKeyDown(VK_SPACE))
			{
				mode = Title;
			}
			x++;

			if (x % 120 == 0)
			{
				if (x != 0 && OBAKE == 0)
				{
					OBAKE = 1;
				}
				else
				{
					OBAKE = 0;
				}
			}
			kurisu.Draw();
			omake2.Draw();
			omakeText.Draw();
			omake3Text.Draw();
			omake4Text.Draw();
			omake5Text.Draw();
			omake2Text.Draw();
			omake1Text.Draw();
			obakeText.Draw();
			omake3.Draw();
			obake[0].scale = 6;
			obake[0].position.x = -350;
			obake[0].position.y = 0;
			obake[1].scale = 6;
			obake[1].position.x = -350;
			obake[1].position.y = 0;
			obake[OBAKE].Draw();
			obake5.scale = 6;
			obake5.position.x = -350;
			obake5.position.y = 30;
			obake5.Draw();
			kurisuText.Draw();
			kurisu1Text.Draw();

			break;

		case bad:
			GAMEOVERText.Draw();
			lifeb[life].Draw();
			if (App::GetKeyDown(VK_SPACE))
			{
				mode = Title;
			}

			break;
		case clear:
			x++;
			space00.position.y = 0;
			if (STAGE < 4)
			{
				clearText[0].Draw();
			}
			else
			{
				clearText[1].Draw();
			}
			if (x % 100 < 70)
			{
				space00.Draw();
			}
			if (App::GetKeyDown(VK_SPACE))
			{
				if (stage == STAGE)
				{
					stage++;
				}
				STAGE++;
				
				//初期化
				x = 0;
				clock5.angles.z = 0;
				gaku.position.x = 130;
				gaku.position.y = 150;
				chair1 = 0;		//花瓶が割れているとき1 割れてないとき0
				chair2 = 0;		//花瓶を割るための変数
				bin1 = 0;		//瓶空中 = 0 割れている = 1
				bin2 = 0;		//bin1を変えるために使う数
				barrier = 0;    //無敵かどうか0通常1無敵
				button = 0;     //PGしているかどうか
				time2a1 = 0;
				chair[0].position.x = -498;
				chair[0].position.y = -140;
				chair[0].scale = 0.2;
				chair[1].position.x = -498;
				chair[1].position.y = -140;
				chair[1].scale = 0.2;
				mouse = 4;		//マウスの場所（4＝押してない　0=左上　1＝右上　2＝右下　3＝左上）
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
				life2 = 2;
				time = 0; //制限時間
				timea = 0; //制限時間の画像の表示
				time2a = 0; //Velocityの管理時間
				time2b = 0; //Velocityの管理時間
				time3b = 0; //物が動いてから次動くまでの待機時間
				time2c = 0; //Velocityの管理時間
				time3c = 0; //物が動いてから次動くまでの待機時間
				Velocity = 0.5; //エフェクトの動き
				Velocityb = 2; //物の動き
				Velocityc = 2; //物の動き
				Velocityd = 2; //物の動き
				HAND = 0;		//手の表示数
				time4 = 0;		//手の表示のカウンター
				time5 = 0;		//額縁のカウンター（時間回復）
				timelife = 0;	//時間回復したかどうか
				lifeup = 0;
				piano2 = 0;
				STARTSound.Play();
				if (STAGE >= 4)
				{
					mode = game3;
				}
				else
				{
					mode = game2;
				}
			}

			break;

		case clear2:
			space00.position.y = -100;
			clear0Text.Draw();
			x++;
			if (x % 100 < 70)
			{
				space00.Draw();
			}
			if (App::GetKeyDown(VK_SPACE))
			{
				if (stage <= 6)
				{
					stage = 6;
				}
				mode = Title;
			}
			break;

		case game1:
			map1.Draw();
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			//ポーズ画面に行く処理
			if (STAGE == 1)
			{
				STAGE1Text.Draw();
			}
			if (App::GetKeyDown(VK_LBUTTON) &&
				App::GetMousePosition().y >= 286 &&
				App::GetMousePosition().x >= 486)
			{
				y = 1;
			}

			if (App::GetKeyUp(VK_LBUTTON) &&
				App::GetMousePosition().y >= 286 &&
				App::GetMousePosition().x >= 486&&
				y == 1)
			{
				pauseSound.Play();
				mode = pause;
			}
			if (!App::GetKey(VK_LBUTTON))
			{
				y = 0;
			}
			x++;
			clock2++;
			

			//時計の針を回転させる処理
			if (x % 5 == 0)
			{
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
			}
			if (x >= 3600)//時間制限
			{
				mode = bad;
			}
			if (life2 < 0)
			{
				mode = bad;
			}
			clock4.Draw();
			clock5.Draw();
			pausepng.Draw();
			chair[chair1].Draw();

			//向いている方向とマウスの場所が同じとき
			if (barrier == 1)
			{
				time++;
			}
			if (chara2b == mouse&&
				barrier == 0&&
				button == 1&&
				clock2 >= 70)
			{
				barrier = 1;
				if (life2 != 0)
				{
					damageSound.Play();
				}
				else
				{
					down.Play();
				}
				life2--; 
				
			}

			if (time >= 60)
			{
				time = 0;
				barrier = 0;
			}
			if (App::GetKey(VK_LBUTTON))
			{
				if (barrier != 0)
				{
					piano1 = 0;
					OBAKE = 0;
				}
			}
			else//マウスを押してないとき
			{
				OBAKE = 0;
			
				//リアクションしてすぐマウスを離すと向く位置がランダムになる
				if (chara4b <= 1)
				{
					chara1b = rand() % 4;
				}
				mouse = 4;
			}

			//bリアクションの時間管理
			if (chara3b < 300 &&
				rand() % 40 == 0)
			{
				chara3b++;
			}
			if (chara3b >= 3)
			{
				reaction2.Draw();
				chara4b++;
				if (mouse != 4)
				{
					chara1b = mouse;
				}
			}
			if (chara4b >= 30)
			{
				clock2 = 0;
				chara2b = chara1b;
				chara3b = 0;
				chara4b = 0;
			}


			//エフェクトの向きを変える処理
			if (x % 20 == 0)
			{
				Velocity = -Velocity;
			}
			
			obake[OBAKE].Draw();
			charab[chara2b].Draw();
			lifea[0].Draw();
			lifea[life].Draw();
			piano[piano1].Draw();
			gaku.Draw();
			if (life2 >= 0)
			{
				HP[life2].Draw();
				HP2[life2].Draw();
			}

			//ここからオブジェクトを動かす処理
			if (y == 0)
			{
				//マウスが左下にある時
				if (chair1 == 0)
				{
					if (barrier == 0 &&
						mouse == 4 ||
						mouse == 0)
					{
						if (App::GetMousePosition().y <= -50 &&
							App::GetMousePosition().x <= 0 &&
							App::GetKey(VK_LBUTTON))
						{
							button = 1;

							if (chara4b == 0)
							{
								chara1b = 0;
							}
							if (barrier == 0)
							{
								chair2++;
								OBAKE = 1;
								lifetime++;
								if (time3b < 4)
								{
									chair[0].position.x += Velocityb;
									chair[0].position.y += Velocityb;
									chair[0].position.x += Velocityb;
								}
							}
							mouse = 0;
							time2b++;
						}
						else
						{
							OBAKE = 0;
							button = 0;
						}
					}
				}
				//マウスが右上にあるとき
				if (App::GetMousePosition().y >= 295 &&
					App::GetMousePosition().x >= 480)
				{
				}
				else if (barrier == 0 &&
					mouse == 4 ||
					mouse == 1)
				{
					if (App::GetMousePosition().y >= -50 &&
						App::GetMousePosition().x >= 0 &&
						App::GetKey(VK_LBUTTON)&&
						App::GetMousePosition().y <= 286 &&
						App::GetMousePosition().x <= 486 )
					{
						button = 1;
						if (chara4b == 0)
						{
							chara1b = 1;
						}
						if (barrier == 0)
						{
							OBAKE = 1;
							lifetime++;
							moya.Draw();
							if (time3c < 4)
							{
								gaku.angles.z += Velocityc;
								gaku.angles.z += Velocityc;
								gaku.angles.z += Velocityc;
							}
						}
						mouse = 1;
						time2c++;
					}
					else
					{
						OBAKE = 0;
						button = 0;
					}
				}
				//マウスが右下にあるとき
				if (barrier == 0 &&
					mouse == 4 ||
					mouse == 2)
				{
					if (App::GetMousePosition().y <= -50 &&
						App::GetMousePosition().x >= 0 &&
						App::GetKey(VK_LBUTTON))
					{
						button = 1;
						if (chara4b == 0)
						{
							chara1b = 2;
						}
						if (barrier == 0)
						{
							OBAKE = 1;
							lifetime++;
							if (time2a % 60 == 0)
							{
								pianoSound.Play();
								piano1 = 1;
							}
							else if (time2a % 30 == 0)
							{
								piano1 = 2;
							}
							else if (piano1 != 2)
							{
								piano1 = 1;
								if (time2a == 2)
								{
									pianoSound.Play();
								}
							}
						}
						mouse = 2;
						time2a++;
					}
					else
					{
						OBAKE = 0;
						button = 0;
						piano1 = 0;
						time2a = 0;
					}
				}
				//マウスが左上にある時
				if (barrier == 0 &&
					mouse == 4 ||
					mouse == 3)
				{
					if (App::GetMousePosition().y >= -50 &&
						App::GetMousePosition().x <= 0 &&
						App::GetKey(VK_LBUTTON))
					{
						button = 1;
						if (chara4b == 0)
						{
							chara1b = 3;
						}
						if (barrier == 0)
						{
							OBAKE = 1;
							lifetime++;
							hand[HAND].Draw();
							time4++;
						}
						mouse = 3;
					}
					else
					{
						OBAKE = 0;
						button = 0;
					}
				}
			}

			if (time2b == 2)
			{
				time3b++;
				Velocityb = -Velocityb;
				time2b = 0;
			}
			if (time3b == 40)
			{
				/*Velocityb = -Velocityb;*/
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
			//手を増やす処理
			if (time4 == 40)
			{
				handSound.Play();
				HAND = 1;
				time4++;
			}
			if (time4 == 80)
			{
				handSound.Play();
				HAND = 2;
				time4++;
			}
			if (time4 == 120)
			{
				handSound.Play();
				HAND = 3;
				time4++;
			}
			if (time4 == 160)
			{
				HAND = 4;
			}
			if (HAND == 4 &&
				lifeup == 0)
			{
				lifeSound.Play();
				life2++;
				lifeup = 1;
			}
			//瓶を割る処理
			if (chair2 >= 180)
			{
				chair1 = 1;
				bin[bin1].Draw();
				bin2++;
			}
			if (bin2 >= 60&&
				bin2 < 80)
			{
				bin1 = 1;
			}
			if (bin2 == 80)
			{
				chairSound.Play();
				bin1 = 2;
				lifetime += 200;
				life += 2;
			}

			///恐怖ゲージが満タンの時にclear画面へ
			if (lifetime >= 350)
			{
				clearSound.Play();
				x = 0;
				mode = clear;
			}
			//ライフ画像を表示する処理
			if (lifetime <= 801)
			{
				if (lifetime == 35)
				{
					life = 1;
				}
				if (lifetime == 70)
				{
					life = 2;
				}
				if (lifetime == 105)
				{
					life = 3;
				}
				if (lifetime == 140)
				{
					life = 4;
				}
				if (lifetime == 175)
				{
					life = 5;
				}
				if (lifetime == 210)
				{
					life = 6;
				}
				if (lifetime == 245)
				{
					life = 7;
				}
				if (lifetime == 280)
				{
					life = 8;
				}
				if (lifetime == 315)
				{
					life = 9;
				}
			}
			break;

			//第2ステージ
		case game2:
			map1.Draw();
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			moya.angles.z += 0.1;
			if (STAGE == 2)
			{
				STAGE2Text.Draw();
			}
			else
			{
				STAGE3Text.Draw();
			}

			//ポーズ画面に行く処理
			if (App::GetKeyDown(VK_LBUTTON) &&
				App::GetMousePosition().y >= 286 &&
				App::GetMousePosition().x >= 486)
			{
				y = 1;
			}

			if (App::GetKeyUp(VK_LBUTTON) &&
				App::GetMousePosition().y >= 286 &&
				App::GetMousePosition().x >= 486 &&
				y == 1)
			{
				pauseSound.Play();
				mode = pause;
			}
			if (!App::GetKey(VK_LBUTTON))
			{
				y = 0;
			}

			//時計の針を回転させる処理
			if (x % 5 == 0)
			{
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
				clock5.angles.z -= 0.03125;
			}
			if (x >= 7200)//時間制限
			{
				mode = bad;
			}
			if (life2 < 0)
			{
				mode = bad;
			}
			clock4.Draw();
			clock5.Draw();
			pausepng.Draw();
			chair[chair1].Draw();
			x++;
			clock2++;
			clock1++;

			//向いている方向とマウスの場所が同じとき
			if (STAGE == 2)
			{
				if (piano2 == 0)
				{
					if (barrier == 1)
					{
						time++;
					}
					if (chara2a == mouse &&
						barrier == 0 &&
						button == 1 &&
						clock1 >= 50)
					{
						barrier = 1;
						if (life2 != 0)
						{
							damageSound.Play();
						}
						else
						{
							down.Play();
						}
						life2--;
					}
					if (chara2b == mouse &&
						barrier == 0 &&
						button == 1 &&
						clock2 >= 50)
					{
						barrier = 1;
						if (life2 != 0)
						{
							damageSound.Play();
						}
						else
						{
							down.Play();
						}
						life2--;
					}
					if (time >= 60)
					{
						time = 0;
						barrier = 0;
					}
				}
				if (piano2 == 1)
				{
					if (barrier == 1)
					{
						time++;
					}
					if (chara2a == mouse &&
						barrier == 0 &&
						button == 1 &&
						clock1 >= 70)
					{
						barrier = 1;
						if (life2 != 0)
						{
							damageSound.Play();
						}
						else
						{
							down.Play();
						}
						life2--;
					}
					if (chara2b == mouse &&
						barrier == 0 &&
						button == 1 &&
						clock2 >= 70)
					{
						barrier = 1;
						if (life2 != 0)
						{
							damageSound.Play();
						}
						else
						{
							down.Play();
						}
						life2--;
					}
					if (time >= 60)
					{
						time = 0;
						barrier = 0;
					}
				}
			}
			if (STAGE == 3)
			{
				if (piano2 == 0)
				{
					if (barrier == 1)
					{
						time++;
					}
					if (chara2a == mouse &&
						barrier == 0 &&
						button == 1 &&
						clock1 >= 20)
					{
						barrier = 1;
						if (life2 != 0)
						{
							damageSound.Play();
						}
						else
						{
							down.Play();
						}
						life2--;
					}
					if (chara2b == mouse &&
						barrier == 0 &&
						button == 1 &&
						clock2 >= 20)
					{
						barrier = 1;
						if (life2 != 0)
						{
							damageSound.Play();
						}
						else
						{
							down.Play();
						}
						life2--;
					}
					if (time >= 60)
					{
						time = 0;
						barrier = 0;
					}
				}
				if (piano2 == 1)
				{
					if (barrier == 1)
					{
						time++;
					}
					if (chara2a == mouse &&
						barrier == 0 &&
						button == 1 &&
						clock1 >= 40)
					{
						barrier = 1;
						if (life2 != 0)
						{
							damageSound.Play();
						}
						else
						{
							down.Play();
						}
						life2--;
					}
					if (chara2b == mouse &&
						barrier == 0 &&
						button == 1 &&
						clock2 >= 40)
					{
						barrier = 1;
						if (life2 != 0)
						{
							damageSound.Play();
						}
						else
						{
							down.Play();
						}
						life2--;
					}
					if (time >= 60)
					{
						time = 0;
						barrier = 0;
					}
				}
			}
			if (App::GetKey(VK_LBUTTON))
			{
				if (barrier != 0)
				{
					piano1 = 0;
					OBAKE = 0;
				}
			}
			else//マウスを押してないとき
			{
				OBAKE = 0;
				mouse = 4;
			}

			//bキャラは必ずマウスの向きになる
			if (rand() % 5 == 0)
			{
				if (mouse == 0)
				{
					chara1b = 0;
				}
				if (mouse == 1)
				{
					chara1b = 1;
				}
				if (mouse == 2)
				{
					chara1b = 2;
				}
				if (mouse == 3)
				{
					chara1b = 3;
				}
				if (mouse == 4)
				{
					chara1b = rand() % 4;
				}
			}

			if (rand() % 4 == 0)
			{
				//aキャラは必ずマウスの向きになる
				if (mouse == 0)
				{
					chara1a = 0;
				}
				if (mouse == 1)
				{
					chara1a = 1;
				}
				if (mouse == 2)
				{
					chara1a = 2;
				}
				if (mouse == 3)
				{
					chara1a = 3;
				}
				if (mouse == 4)
				{
					chara1a = rand() % 4;
				}
			}

			//リアクションしてすぐマウスを離すと向く位置がランダムになる
			if (chara4a <= 5)
			{
				chara1a = rand() % 4;
			}

			//aリアクションの時間管理
			if (STAGE == 2)
			{
				if (chara3a < 400)
				{
					chara3a++;
				}
				if (chara3a >= 200)
				{
					reaction1.Draw();
					chara4a++;
				}
				if (chara4a >= 65 &&
					rand() % 10 == 0)
				{
					clock1 = 0;
					chara2a = chara1a;
					chara3a = 0;
					chara4a = 0;
				}
			}
			if (STAGE == 3)
			{
				if (chara3a < 200)
				{
					chara3a++;
				}
				if (chara3a >= 80)
				{
					reaction1.Draw();
					chara4a++;
				}
				if (chara4a >= 25 &&
					rand() % 40 == 0)
				{
					clock1 = 0;
					chara2a = chara1a;
					chara3a = 0;
					chara4a = 0;
				}
			}

			//bリアクションの時間管理
			if (chara3b < 300 &&
				rand() % 40 == 0)
			{
				chara3b++;
			}
			if (chara3b >= 3)
			{
				if (rand() % 4 == 0)
				{
					chara1b = rand() % 4;
				}
				else if (mouse != 4)
				{
					chara1b = mouse;
				}
				else
				{
					chara1b = rand() % 4;
				}
				reaction2.Draw();
				chara4b++;
			}
			if (STAGE == 2)
			{
				if (chara4b >= 60)
				{
					clock2 = 0;
					chara2b = chara1b;
					chara3b = 0;
					chara4b = 0;
				}
			}
			else
			{
				if (chara4b >= 35)
				{
					clock2 = 0;
					chara2b = chara1b;
					chara3b = 0;
					chara4b = 0;
				}
			}

			
			//エフェクトの向きを変える処理
			if (x % 20 == 0)
			{
				Velocity = -Velocity;
			}
			
			obake[OBAKE].Draw();
			charaa[chara2a].Draw();
			charab[chara2b].Draw();
			lifea[0].Draw();
			lifea[life].Draw();
			piano[piano1].Draw();
			gaku.Draw();
			if (life2 >= 0)
			{
				HP[life2].Draw();
				HP2[life2].Draw();
			}
			//ここからオブジェクトを動かす処理
			//マウスが左下にある時
			if (y == 0)
			{
				if (chair1 == 0)
				{
					if (barrier == 0 &&
						mouse == 4 ||
						mouse == 0)
					{
						if (App::GetMousePosition().y <= -50 &&
							App::GetMousePosition().x <= 0 &&
							App::GetKey(VK_LBUTTON))
						{
							button = 1;
							if (barrier == 0)
							{
								OBAKE = 1;
								lifetime++;
								chair2++;
								if (time3b < 4)
								{
									chair[0].position.x += Velocityb;
									chair[0].position.y += Velocityb;
									chair[0].position.x += Velocityb;
								}
							}
							mouse = 0;
							time2b++;
						}
						else
						{
							OBAKE = 0;
							button = 0;
						}
					}
				}

				//マウスが右上にあるとき
				if (barrier == 0 &&
					mouse == 4 ||
					mouse == 1)
				{
					if (App::GetMousePosition().y >= -50 &&
						App::GetMousePosition().x >= 0 &&
						App::GetKey(VK_LBUTTON) &&
						App::GetMousePosition().y <= 286 &&
						App::GetMousePosition().x <= 486)
					{
						button = 1;
						if (barrier == 0)
						{
							OBAKE = 1;
							lifetime++;
							moya.Draw();
							if (time3c < 4)
							{
								gaku.angles.z += Velocityc;
								gaku.angles.z += Velocityc;
								gaku.angles.z += Velocityc;
							}
						}
						mouse = 1;
						time2c++;
					}
					else
					{
						piano1 = 0;
						time2a = 0;
						OBAKE = 0;
						button = 0;
					}
				}

				//マウスが右下にあるとき
				if (barrier == 0 &&
					mouse == 4 ||
					mouse == 2)
				{
					if (App::GetMousePosition().y <= -50 &&
						App::GetMousePosition().x >= 0 &&
						App::GetKey(VK_LBUTTON))
					{
						button = 1;
						if (barrier == 0)
						{
							OBAKE = 1;
							lifetime++;
							time2a1++;
							if (time2a % 100 == 0)
							{
								pianoSound.Play();
								piano1 = 1;
							}
							else if (time2a % 50 == 0)
							{
								piano1 = 2;
							}
							else if (piano1 != 2)
							{
								piano1 = 1;
								if (time2a == 2)
								{
									pianoSound.Play();
								}
							}
						}
						mouse = 2;
						time2a++;
					}
					else
					{
						OBAKE = 0;
						button = 0;
						time2a = 0;
						if (piano2 == 0)
						{
							piano1 = 0;
						}
						else if (piano2 == 1)
						{
							piano1 = 3;
						}
					}
				}

				//マウスが左上にある時
				if (barrier == 0 &&
					mouse == 4 ||
					mouse == 3)
				{
					if (App::GetMousePosition().y >= -50 &&
						App::GetMousePosition().x <= 0 &&
						App::GetKey(VK_LBUTTON))
					{
						button = 1;
						if (barrier == 0)
						{
							OBAKE = 1;
							lifetime++;
							time4++;
							hand[HAND].Draw();
						}
						mouse = 3;
					}
					else
					{
						OBAKE = 0;
						button = 0;
					}
				}
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
			//ピアノ覚醒の処理
			if (time2a1 >= 200)
			{
				piano2 = 1;
			}
			//手を増やす処理
			if (time4 == 60)
			{
				handSound.Play();
				HAND = 1;
				time4++;
			}
			if (time4 == 120)
			{
				handSound.Play();
				HAND = 2;
				time4++;
			}
			if (time4 == 180)
			{
				handSound.Play();
				HAND = 3;
				time4++;
			}
			if (time4 == 240)
			{
				HAND = 4;
			}
			if (HAND == 4 &&
				lifeup == 0)
			{
				lifeSound.Play();
				life2++;
				lifeup = 1;
			}
			//瓶を割る処理
			if (chair2 >= 350)
			{
				chair1 = 1;
				bin[bin1].Draw();
				bin2++;
			}
			if (bin2 >= 60 &&
				bin2 < 80)
			{
				bin1 = 1;
			}
			if (bin2 == 80)
			{
				chairSound.Play();
				bin1 = 2;
				lifetime += 300;
				life += 3;
			}
			//恐怖ゲージが満タンの時にclear画面へ
			if (lifetime >= 1000)
			{
				x = 0;
				clearSound.Play();
				mode = clear;
			}
			//ライフ画像を表示する処理
			if (lifetime <= 1600)
			{
				if (lifetime == 100)
				{
					life = 1;
				}
				if (lifetime == 200)
				{
					life = 2;
				}
				if (lifetime == 300)
				{
					life = 3;
				}
				if (lifetime == 400)
				{
					life = 4;
				}
				if (lifetime == 500)
				{
					life = 5;
				}
				if (lifetime == 600)
				{
					life = 6;
				}
				if (lifetime == 700)
				{
					life = 7;
				}
				if (lifetime == 800)
				{
					life = 8;
				}
				if (lifetime == 900)
				{
					life = 9;
				}
			}

			break;

			//3ステージ
			case game3:
				map1.Draw();
				moya.angles.z += 0.1;
				moya.angles.z += 0.1;
				moya.angles.z += 0.1;
				moya.angles.z += 0.1;
				moya.angles.z += 0.1;
				moya.angles.z += 0.1;
				moya.angles.z += 0.1;
				moya.angles.z += 0.1;
				moya.angles.z += 0.1;
				moya.angles.z += 0.1;
				if (STAGE == 4)
				{
					STAGE4Text.Draw();
				}
				else
				{
					STAGE5Text.Draw();
				}

				//ポーズ画面に行く処理
				if (App::GetKeyDown(VK_LBUTTON) &&
					App::GetMousePosition().y >= 286 &&
					App::GetMousePosition().x >= 486)
				{
					y = 1;
				}

				if (App::GetKeyUp(VK_LBUTTON) &&
					App::GetMousePosition().y >= 286 &&
					App::GetMousePosition().x >= 486 &&
					y == 1)
				{
					pauseSound.Play();
					mode = pause;
				}
				if (!App::GetKey(VK_LBUTTON))
				{
					y = 0;
				}

				chair[chair1].Draw();
				pausepng.Draw();
				x++;
				clock1++;
				clock2++;
				clock3++;
				//時計の針を回転させる処理
				if (x % 1 == 0)
				{
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
					clock5.angles.z -= 0.003125;
				}
				if (x >= 3600)//時間制限
				{
					mode = bad;
				}
				if (life2 < 0)
				{
					mode = bad;
				}
				clock4.Draw();
				clock5.Draw();
				//無敵時間の処理
				if (barrier == 1)
				{
					time++;
				}
				if (time >= 60)
				{
					time = 0;
					barrier = 0;
				}
				//向いている方向とマウスの場所が同じとき
				if (piano2 == 0)
				{
					if (chara2a == mouse &&
						barrier == 0 &&
						button == 1)
					{
						if (clock1 >= 25 &&
							STAGE == 4)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
						if (clock1 >= 15 &&
							STAGE == 5)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
					}
					if (chara2b == mouse &&
						barrier == 0 &&
						button == 1)
					{
						if (clock2 >= 25 &&
							STAGE == 4)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
						if (clock2 >= 15 &&
							STAGE == 5)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
					}
					if (chara2c == mouse &&
						barrier == 0 &&
						button == 1)
					{
						if (STAGE == 4 &&
							clock3 >= 35)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
						if (STAGE == 5 &&
							clock3 >= 25)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
					}
				}
				if (piano2 == 1)
				{
					if (chara2a == mouse &&
						barrier == 0 &&
						button == 1)
					{
						if (clock1 >= 50 &&
							STAGE == 4)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
						if (clock1 >= 45 &&
							STAGE == 5)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
					}
					if (chara2b == mouse &&
						barrier == 0 &&
						button == 1)
					{
						if (clock2 >= 50 &&
							STAGE == 4)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
						if (clock2 >= 40 &&
							STAGE == 5)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
					}
					if (chara2c == mouse &&
						barrier == 0 &&
						button == 1)
					{
						if (STAGE == 4 &&
							clock3 >= 55)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
						if (STAGE == 5 &&
							clock3 >= 40)
						{
							barrier = 1;
							if (life2 != 0)
							{
								damageSound.Play();
							}
							else
							{
								down.Play();
							}
							life2--;
						}
					}
				}
			
				if (App::GetKey(VK_LBUTTON))
				{
					if (barrier != 0)
					{
						piano1 = 0;
						OBAKE = 0;
					}
				}
				else//マウスを押してないとき
				{
					OBAKE = 0;
					mouse = 4;
				}


				//bキャラは必ずマウスの向きになる
				if (rand() % 5 == 0)
				{
					if (mouse == 0)
					{
						chara1b = 0;
					}
					if (mouse == 1)
					{
						chara1b = 1;
					}
					if (mouse == 2)
					{
						chara1b = 2;
					}
					if (mouse == 3)
					{
						chara1b = 3;
					}
					if (mouse == 4)
					{
						chara1b = rand() % 4;
					}
				}
				if (rand() % 4 == 0)
				{
					//aキャラは必ずマウスの向きになる
					if (mouse == 0)
					{
						chara1a = 0;
					}
					if (mouse == 1)
					{
						chara1a = 1;
					}
					if (mouse == 2)
					{
						chara1a = 2;
					}
					if (mouse == 3)
					{
						chara1a = 3;
					}
					if(mouse == 4)
					{
						chara1a = rand() % 4;
					}
				}
				//リアクションしてすぐマウスを離すと向く位置がランダムになる
				if (chara4a <= 15)
				{
					chara1a = rand() % 4;
				}

				//aリアクションの時間管理
				if (chara3a < 200)
				{
					chara3a++;
				}
				if (chara3a >= 120)
				{
					reaction1.Draw();
					chara4a++;
				}
				if (chara4a >= 30 &&
					rand() % 20 == 0&&
					STAGE == 4)
				{
					clock1 = 0;
					chara2a = chara1a;
					chara3a = 0;
					chara4a = 0;
				}
				if (chara4a >= 25 &&
					rand() % 30 == 0&&
					STAGE == 5)
				{
					clock1 = 0;
					chara2a = chara1a;
					chara3a = 0;
					chara4a = 0;
				}

				//bリアクションの時間管理
				if (lifetime <= 1400)
				{
					if (chara3b < 300 &&
						rand() % 35 == 0)
					{
						chara3b++;
					}
					if (chara3b >= 8)
					{
						if (rand() % 4 == 0)
						{
							chara1b = rand() % 4;
						}
						else if (mouse != 4)
						{
							chara1b = mouse;
						}
						else
						{
							chara1b = rand() % 4;
						}
						reaction2.Draw();
						chara4b++;

					}
				}
				if (lifetime > 1400)
				{
					if (chara3b < 150 &&
						rand() % 35 == 0)
					{
						chara3b++;
					}
					if (chara3b >= 6)
					{
						if (rand() % 4 == 0)
						{
							chara1b = rand() % 4;
						}
						else if (mouse != 4)
						{
							chara1b = mouse;
						}
						else
						{
							chara1b = rand() % 4;
						}
						reaction2.Draw();
						chara4b++;

					}
				}
				
				if (chara4b >= 40)
				{
					clock2 = 0;
					chara2b = chara1b;
					chara3b = 0;
					chara4b = 0;
				}
				
				//cキャラの管理
				if (140 <= clock3 &&
					clock3 != 0 &&
					STAGE == 4)
				{
					clock3 = 0;
					chara2c = rand() % 4;
				}
				if (clock3 >= 120 &&
					x != 0 && STAGE == 5&&
					lifetime <= 1400)
				{
					clock3 = 0;
					chara2c = rand() % 4;
				}
				if (clock3 >= 40 &&
					x != 0 && STAGE == 5 &&
					lifetime > 1000 &&
					lifetime < 1560 &&
					rand() % 40 == 0)
				{
					if (rand() % 5 < 4)
					{
						clock3 = 0;
						chara2c = rand() % 4;
					}
					else
					{
						mouse = chara2c;
						if (mouse = 4)
						{
							clock3 = 0;
							chara2c = rand() % 4;
						}
					}
				}
				else if (clock3 >= 40&&
					x != 0 && STAGE == 5 &&
					lifetime >= 1560 &&
					rand() % 10 == 0)
				{
					if (rand() % 3 < 2)
					{
						clock3 = 0;
						chara2c = rand() % 4;
					}
					else
					{
						mouse = chara2c;
						if (mouse = 4)
						{
							clock3 = 0;
							chara2c = rand() % 4;
						}
					}
				}
	
				//エフェクトの向きを変える処理
				obake[OBAKE].Draw();
				charaa[chara2a].Draw();
				charab[chara2b].Draw();
				charac[chara2c].Draw();
				lifea[0].Draw();
				lifea[life].Draw();
				piano[piano1].Draw();
				gaku.Draw(); 
				if (life2 >= 0)
				{
					HP[life2].Draw();
					HP2[life2].Draw();
				}

				//ここからオブジェクトを動かす処理
				//マウスが左下にある時
				if (y == 0)
				{
					if (chair1 == 0)
					{
						if (barrier == 0 &&
							mouse == 4 ||
							mouse == 0)
						{
							if (App::GetMousePosition().y <= -50 &&
								App::GetMousePosition().x <= 0 &&
								App::GetKey(VK_LBUTTON))
							{
								button = 1;
								if (chara4b == 0)
								{
									chara1b = 0;
								}
								if (chara4a == 0)
								{
									chara1a = 0;
								}
								if (barrier == 0)
								{
									chair2++;
									OBAKE = 1;
									lifetime++;
									if (time3b < 4)
									{
										chair[0].position.x += Velocityb;
										chair[0].position.y += Velocityb;
										chair[0].position.x += Velocityb;
									}
								}
								mouse = 0;
								time2b++;
							}
							else
							{
								OBAKE = 0;
								button = 0;
							}
						}
					}
					//マウスが右上にあるとき
					if (barrier == 0 &&
						mouse == 4 ||
						mouse == 1)
					{
						if (App::GetMousePosition().y >= -50 &&
							App::GetMousePosition().x >= 0 &&
							App::GetKey(VK_LBUTTON) &&
							App::GetMousePosition().y <= 286 &&
							App::GetMousePosition().x <= 486)
						{
							button = 1;
							if (chara4b == 0)
							{
								chara1b = 1;
							}
							if (chara4a == 0)
							{
								chara1a = 1;
							}
							if (barrier == 0)
							{
								OBAKE = 1;
								lifetime++;
								time5++;
								moya.Draw();
								if (time3c < 4)
								{
									gaku.angles.z += Velocityc;
									gaku.angles.z += Velocityc;
									gaku.angles.z += Velocityc;
								}
							}
							mouse = 1;
							time2c++;
						}
						else
						{
							OBAKE = 0;
							button = 0;
						}
					}

					//マウスが右下にあるとき
					if (barrier == 0 &&
						mouse == 4 ||
						mouse == 2)
					{
						if (App::GetMousePosition().y <= -50 &&
							App::GetMousePosition().x >= 0 &&
							App::GetKey(VK_LBUTTON))
						{
							button = 1;
							if (chara4b == 0)
							{
								chara1b = 2;
							}
							if (chara4a == 0)
							{
								chara1a = 2;
							}
							if (barrier == 0)
							{
								OBAKE = 1;
								lifetime++;
								time2a1++;
								if (time2a % 100 == 0)
								{
									pianoSound.Play();
									piano1 = 1;
								}
								else if (time2a % 50 == 0)
								{
									piano1 = 2;
								}
								else if (piano1 != 2)
								{
									piano1 = 1;
									if (time2a == 2)
									{
										pianoSound.Play();
									}
								}
							}
							mouse = 2;
							time2a++;
						}
						else
						{
							OBAKE = 0;
							button = 0;
							time2a = 0;
							if (piano2 == 0)
							{
								piano1 = 0;
							}
							else if (piano2 == 1)
							{
								piano1 = 3;
							}
						}
					}

					//マウスが左上にある時
					if (App::GetKeyDown(VK_LBUTTON) &&
						App::GetMousePosition().y >= 295 &&
						App::GetMousePosition().x >= 480)
					{
					}
					else if (barrier == 0 &&
						mouse == 4 ||
						mouse == 3)
					{
						if (App::GetMousePosition().y >= 50 &&
							App::GetMousePosition().x <= 0 &&
							App::GetKey(VK_LBUTTON))
						{
							button = 1;
							if (chara4b == 0)
							{
								chara1b = 3;
							}
							if (chara4a == 0)
							{
								chara1a = 3;
							}
							if (barrier == 0)
							{
								OBAKE = 1;
								lifetime++;
								hand[HAND].Draw();
								time4++;
							}
							mouse = 3;
						}
						else
						{
							OBAKE = 0;
							button = 0;
						}
					}
				}
				//時間回復の処理
				if (time5 % 100 == 0&&
					time5 != 0)
				{
					if (x <= 600)
					{
						x = 0;
						clock5.angles.z = 0;
						time5++;
					}
					else if (x > 600)
					{
						x -= 600;
						clock5.angles.z += 60;
						time5++;
					}
					timeWav.Play();
				}

				if (time2a1 >= 350)
				{
					piano2 = 1;
				}

				if (time4 == 100)
				{
					handSound.Play();
					HAND = 1;
					time4++;
				}
				if (time4 == 200)
				{
					handSound.Play();
					HAND = 2;
					time4++;
				}
				if (time4 == 300)
				{
					handSound.Play();
					HAND = 3;
					time4++;
				}
				if (time4 == 400)
				{
					HAND = 4;
				}
				if (HAND == 4 &&
					lifeup == 0)
				{
					lifeSound.Play();
					life2++;
					lifeup = 1;
				}


				if (time2b == 2)
				{
					time3b++;
					Velocityb = -Velocityb;
					time2b = 0;
				}
				if (time3b == 40)
				{
					/*Velocityb = -Velocityb;*/
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
				//瓶が割れる処理
				if (chair2 >= 450)
				{
					chair1 = 1;
					bin[bin1].Draw();
					bin2++;
				}
				if (bin2 >= 60 &&
					bin2 < 90)
				{
					bin1 = 1;
				}
				if (bin2 == 90)
				{
					chairSound.Play();
					bin1 = 2;
					if (STAGE == 4)
					{
						lifetime += 600;
					}
					if (STAGE == 5)
					{
						lifetime += 720;
					}
				}
				//恐怖ゲージが満タンの時にclear画面へ
				if (lifetime >= 1900&&
					STAGE == 4)
				{
					clearSound.Play();
					x = 0;
					mode = clear;
				}
				if (lifetime == 1560 &&
					STAGE == 5)
				{
					bgm4.Play();
				}
				if (lifetime >= 1560 &&
					STAGE == 5)
				{
					if (x % 400 == 0 ||
						x == 1)
					{
						bgm4.Play();
					}
					else if (x % 200 == 0)
					{
						bgm5.Play();
					}
					if (x % 600 == 0)
					{
						bgm3.Play();
					}
				}
				if (lifetime >= 2280&& 
					STAGE == 5)
				{
					clearSound.Play();
					x = 0;
					mode = clear2;
				}
				//ライフ画像を表示する処理
				if (lifetime <= 10000)
				{
					if (STAGE == 4)
					{
						if (lifetime >= 1100 &&
							lifetime < 1200)
						{
							life = 1;
						}
						if (lifetime >= 1100 &&
							lifetime < 1200)
						{
							life = 2;
						}
						if (lifetime >= 1200 &&
							lifetime < 1300)
						{
							life = 3;
						}
						if (lifetime >= 1300 &&
							lifetime < 1400)
						{
							life = 4;
						}
						if (lifetime >= 1400 &&
							lifetime < 1500)
						{
							life = 5;
						}
						if (lifetime >= 1500 &&
							lifetime < 1600)
						{
							life = 6;
						}
						if (lifetime >= 1600 &&
							lifetime < 1700)
						{
							life = 7;
						}
						if (lifetime >= 1700 &&
							lifetime < 1800)
						{
							life = 8;
						}
						if (lifetime >= 1800 &&
							lifetime <= 1900)
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
						if (lifetime >= 800 &&
							lifetime < 900)
						{
							life = 18;
						}
						if (lifetime >= 900 &&
							lifetime < 1000)
						{
							life = 0;
						}
							
					}
					if (STAGE == 5)
					{
						if (lifetime >= 1200 &&
							lifetime < 1320)
						{
							life = 1;
						}
						if (lifetime >= 1320 &&
							lifetime < 1440)
						{
							life = 2;
						}
						if (lifetime >= 1440 &&
							lifetime < 1560)
						{
							life = 3;
						}
						if (lifetime >= 1560 &&
							lifetime < 1680)
						{
							life = 4;
						}
						if (lifetime >= 1680 &&
							lifetime < 1800)
						{
							life = 5;
						}
						if (lifetime >= 1800 &&
							lifetime < 1920)
						{
							life = 6;
						}
						if (lifetime >= 1920 &&
							lifetime < 2040)
						{
							life = 7;
						}
						if (lifetime >= 2040 &&
							lifetime < 2160)
						{
							life = 8;
						}
						if (lifetime >= 2160 &&
							lifetime <= 2280)
						{
							life = 9;
						}
						if (lifetime == 0)
						{
							life = 10;
						}
						if (lifetime == 120)
						{
							life = 11;
						}
						if (lifetime == 240)
						{
							life = 12;
						}
						if (lifetime == 360)
						{
							life = 13;
						}
						if (lifetime == 480)
						{
							life = 14;
						}
						if (lifetime == 600)
						{
							life = 15;
						}
						if (lifetime == 720)
						{
							life = 16;
						}
						if (lifetime == 840)
						{
							life = 17;
						}
						if (lifetime >= 960 &&
							lifetime < 1080)
						{
							life = 18;
						}
						if (lifetime >= 1080 &&
							lifetime < 1200)
						{
							life = 0;
						}
					}
				}

				break;
		}
	}
	return 0;
}
