/*
    自由制作
    744771  Tsuji Kenichiro
*/

#include <stdio.h>
#include <handy.h>
#include <stdlib.h>
#include <time.h>

#define B_SIZE 40

// 色を扱う
#define BALLET 7
hgcolor Color[BALLET] = {HG_SKYBLUE, HG_BLUE, HG_ORANGE, HG_GREEN, HG_RED, HG_YELLOW, HG_PURPLE};
int color;

// ブロック座標の管理
typedef struct Posi{
    int X;
    int Y;
}  Posi;

// 2個目以降に生成されるブロックについて
int ForBlock[2] = {};

Posi move[4]  = {}; // 操作ブロックの座標管理
int i = 0; // ループカウント変数
int count = 0;

// イベント処理
hgevent *event;
int B_Type;

// レイヤー処理
doubleLayer layers;
int windowID;
int layerID;
int setID;

// 次にくるブロックを描画
void NextBlock(){
    HgWSetWidth(1, 2.25); // 線の太さ指定
    HgWSetFont(1, HG_G, 35);
    HgWText(1, 5, 150, "Next Block");
    HgWSetFillColor(1, Color[ForBlock[1]]);
    // 棒ブロック
    if(ForBlock[1] == 0){
        HgWBoxFill(1, 82.5, 5, 35, 35, 1);
        HgWBoxFill(1, 82.5, 40, 35, 35, 1);
        HgWBoxFill(1, 82.5, 75, 35, 35, 1);
        HgWBoxFill(1, 82.5 ,110, 35, 35, 1);
    // Lブロック
    } else if(ForBlock[1] == 1){
        HgWBoxFill(1, 55, 10, 45, 45, 1);
        HgWBoxFill(1, 55, 55, 45, 45, 1);
        HgWBoxFill(1, 55, 100, 45, 45, 1);
        HgWBoxFill(1, 100 ,10, 45, 45, 1);
    // 逆Lブロック
    } else if(ForBlock[1] == 2){
        HgWBoxFill(1, 100, 10, 45, 45, 1);
        HgWBoxFill(1, 100, 55, 45, 45, 1);
        HgWBoxFill(1, 100, 100, 45, 45, 1);
        HgWBoxFill(1, 55,10, 45, 45, 1);
    // Zブロック
    } else if(ForBlock[1] == 3){
        HgWBoxFill(1, 32.5, 20, 45, 45, 1);
        HgWBoxFill(1, 77.5, 20, 45, 45, 1);
        HgWBoxFill(1, 77.5, 65, 45, 45, 1);
        HgWBoxFill(1, 122.5, 65, 45, 45, 1);
    // 逆Zブロック
    } else if(ForBlock[1] == 4){
        HgWBoxFill(1, 32.5, 65, 45, 45, 1);
        HgWBoxFill(1, 77.5, 65, 45, 45, 1);
        HgWBoxFill(1, 77.5, 20, 45, 45, 1);
        HgWBoxFill(1, 122.5, 20, 45, 45, 1);
    // 正方形ブロック
    } else if(ForBlock[1] == 5){
        HgWBoxFill(1, 55, 20, 45, 45, 1);
        HgWBoxFill(1, 100, 20, 45, 45, 1);
        HgWBoxFill(1, 55, 65, 45, 45, 1);
        HgWBoxFill(1, 100, 65, 45, 45, 1);
    // 凸ブロック
    } else {
        HgWBoxFill(1, 32.5, 20, 45, 45, 1);
        HgWBoxFill(1, 77.5, 20, 45, 45, 1);
        HgWBoxFill(1, 122.5, 20, 45, 45, 1);
        HgWBoxFill(1, 77.5 ,65, 45, 45, 1);
    }
    ForBlock[0] = ForBlock[1];
}

// ブロックをランダムで生成する関数(一番上に描く)
void RandomBlock(int block[][20]){
    i = 0;
    int x, y;
    int random;
    ForBlock[1] = rand() % 7; // 次に生成するブロックについて
    random = ForBlock[0];
    B_Type = random;
    color = random;
    HgSetFillColor(Color[color]);
    // 棒ブロック
    if(random == 0){
        block[5][19] = 1;
        block[5][18] = 1;
        block[5][17] = 1;
        block[5][16] = 1;
        for(y = 0; y < 20; y++){
            for(x = 0; x < 10; x++){
                if(block[x][y] == 1){
                    move[i].X = x;
                    move[i].Y = y;
                    i++;
                }
            }
        }
    // Lブロック
    } else if(random == 1){
        block[5][17] = 1;
        block[6][17] = 1;
        block[5][18] = 1;
        block[5][19] = 1;
        for(y = 0; y < 20; y++){
            for(x = 0; x < 10; x++){
                if(block[x][y] == 1){
                    move[i].X = x;
                    move[i].Y = y;
                    i++;
                }
            }
        }
    // 逆Lブロック
    } else if(random == 2){
        block[4][17] = 1;
        block[5][17] = 1;
        block[5][18] = 1;
        block[5][19] = 1;
        for(y = 0; y < 20; y++){
            for(x = 0; x < 10; x++){
                if(block[x][y] == 1){
                    move[i].X = x;
                    move[i].Y = y;
                    i++;
                }
            }
        }
    // Zブロック
    } else  if(random == 3){
        block[6][19] = 1;
        block[5][19] = 1;
        block[5][18] = 1;
        block[4][18] = 1;
        for(y = 0; y < 20; y++){
            for(x = 0; x < 10; x++){
                if(block[x][y] == 1){
                    move[i].X = x;
                    move[i].Y = y;
                    i++;
                }
            }
        }
    // 逆Zブロック
    } else if(random == 4){
        block[4][19] = 1;
        block[5][19] = 1;
        block[5][18] = 1;
        block[6][18] = 1;
        for(y = 0; y < 20; y++){
            for(x = 0; x < 10; x++){
                if(block[x][y] == 1){
                    move[i].X = x;
                    move[i].Y = y;
                    i++;
                }
            }
        }
    // 正方形ブロック
    } else if(random == 5){
        block[4][19] = 1;
        block[5][19] = 1;
        block[4][18] = 1;
        block[5][18] = 1;
        for(y = 0; y < 20; y++){
            for(x = 0; x < 10; x++){
                if(block[x][y] == 1){
                    move[i].X = x;
                    move[i].Y = y;
                    i++;
                }
            }
        }
    // 凸ブロック
    } else {
        block[5][19] = 1;
        block[4][18] = 1;
        block[5][18] = 1;
        block[6][18] = 1;
        for(y = 0; y < 20; y++){
            for(x = 0; x < 10; x++){
                if(block[x][y] == 1){
                    move[i].X = x;
                    move[i].Y = y;
                    i++;
                }
            }
        }
    }
}

// ブロックを描く関数(現在動かしているブロックについて)
void WriteBlock(int block[][20], int set[][20]){
    int x, y;
    i = 0;
    for(y = 0; y < 20; y++){
        for(x = 0; x < 10; x++){
            // 操作中のブロック描画
            if(block[x][y] != 0){
                HgWSetWidth(layerID, 2.25); // 線の太さ指定
                HgWSetFillColor(layerID,Color[color]);
                HgWBoxFill(layerID, x*40, y*40, B_SIZE, B_SIZE, 1);
                if(block[x][y] != 0){ // 動作位置確認
                    move[i].X = x; // 動かしているブロックがどこに位置しているか
                    move[i].Y = y;
                    i++;
                }
            }
        }
    }
}

// 既に置かれているブロックを描画
void PutBlock(int set[][20]){
    int x, y;
    HgWSetWidth(setID, 2.25); // 線の太さ指定
    for(y = 0; y < 20; y++){
        for(x = 0; x < 10; x++){
            if(set[x][y] != 0){
                if(set[x][y] == 1){ // 水色
                    HgWSetFillColor(setID, Color[set[x][y] - 1]);
                    HgWBoxFill(setID, x*40, y*40, B_SIZE, B_SIZE, 1);
                } else if(set[x][y] == 2){ // 青
                    HgWSetFillColor(setID, Color[set[x][y] - 1]);
                    HgWBoxFill(setID, x*40, y*40, B_SIZE, B_SIZE, 1);
                } else if(set[x][y] == 3){ // オレンジ色
                    HgWSetFillColor(setID,Color[set[x][y] - 1]);
                    HgWBoxFill(setID, x*40, y*40, B_SIZE, B_SIZE, 1);
                } else if(set[x][y] == 4){ // 緑色
                    HgWSetFillColor(setID, Color[set[x][y] - 1]);
                    HgWBoxFill(setID, x*40, y*40, B_SIZE, B_SIZE, 1);
                } else if(set[x][y] == 5){ // 赤色
                    HgWSetFillColor(setID, Color[set[x][y] - 1]);
                    HgWBoxFill(setID, x*40, y*40, B_SIZE, B_SIZE, 1);
                } else if(set[x][y] == 6){ // 黄色
                    HgWSetFillColor(setID,Color[set[x][y] - 1]);
                    HgWBoxFill(setID, x*40, y*40, B_SIZE, B_SIZE, 1);
                } else { // 紫色
                    HgWSetFillColor(setID, Color[set[x][y] - 1]);
                    HgWBoxFill(setID, x*40, y*40, B_SIZE, B_SIZE, 1);
                }
            }
        }
    }
}

// 下に動かす関数
void DownMove(int block[][20],Posi move[4]){
    for(i = 0; i < 4; i++){
        block[move[i].X][move[i].Y] = 0;
        block[move[i].X][(move[i].Y) - 1 ] = 1;
    }
}

// 右に動かす関数
void RightMove(int block[][20],Posi move[4]){
    for(i = 3; i >= 0; i--){
        block[move[i].X][move[i].Y] = 0;
        block[(move[i].X) + 1][move[i].Y] = 1;
    }
}

// 左に動かす関数
void LeftMove(int block[][20],Posi move[4]){
    for(i = 0; i < 4; i++){
        block[move[i].X][move[i].Y] = 0;
        block[(move[i].X) - 1][move[i].Y] = 1;
    }
}

// 回転させる関数
void RotationChange(int B_Type,int block[][20], int set[][20], Posi move[4]){
    // 棒ブロック
    if(B_Type == 0){
        for(i = 0; i < 4; i++){
            block[move[i].X][move[i].Y] = 0;
        }
        if(count == 0){ // 横向きに変更
            if((set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y - 1] == 0 && set[move[3].X - 2][move[3].Y - 2] == 0)
               && (move[1].X != 0 && move[1].X != 1 && move[1].X != 9)){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y - 1] = 1;
                block[move[3].X - 2][move[3].Y - 2] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 1){ // 縦向きに変更
            if(set[move[0].X + 2][move[0].Y - 2] == 0 && set[move[1].X + 1][move[1].Y - 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y + 1] == 0){
                block[move[0].X + 2][move[0].Y - 2] = 1;
                block[move[1].X + 1][move[1].Y - 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y + 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 2){ // 横向きに変更
            if((set[move[0].X + 2][move[0].Y + 2] == 0 && set[move[1].X + 1][move[1].Y + 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0)
               && (move[3].X != 8 && move[3].X != 9 && move[3].X != 0)){
                block[move[0].X + 2][move[0].Y + 2] = 1;
                block[move[1].X + 1][move[1].Y + 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 3){ // 縦向きに変更
            if(set[move[0].X + 1][move[0].Y - 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y + 1] == 0 && set[move[3].X - 2][move[3].Y + 2] == 0){
                block[move[0].X + 1][move[0].Y - 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y + 1] = 1;
                block[move[3].X - 2][move[3].Y + 2] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        }
    // Lブロック
    } else if(B_Type == 1){
        for(i = 0; i < 4; i++){
            block[move[i].X][move[i].Y] = 0;
        }
        if(count == 0){ // 横向きに変更
            if((set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X][move[1].Y + 2] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0)
               && (move[3].X != 0)){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X][move[1].Y + 2] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 1){ // 縦向きに変更
            if(set[move[0].X + 1][move[0].Y - 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y + 1] == 0 && set[move[3].X - 2][move[3].Y] == 0){
                block[move[0].X + 1][move[0].Y - 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y + 1] = 1;
                block[move[3].X - 2][move[3].Y] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 2){ // 横向きに変更
            if((set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X][move[2].Y - 2] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0)
               && (move[3].X != 9)){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X][move[2].Y - 2] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 3){ // 縦向きに変更
            if(set[move[0].X + 2][move[0].Y] == 0 && set[move[1].X + 1][move[1].Y - 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y + 1] == 0){
                block[move[0].X + 2][move[0].Y] = 1;
                block[move[1].X + 1][move[1].Y - 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y + 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        }
    // 逆Lブロック
    } else if(B_Type == 2){
        for(i = 0; i < 4; i++){
            block[move[i].X][move[i].Y] = 0;
        }
        if(count == 0){ // 横向きに変更
            if((set[move[0].X + 2][move[0].Y] == 0 && set[move[1].X + 1][move[1].Y + 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0)
               && (move[3].X != 9)){
                block[move[0].X + 2][move[0].Y] = 1;
                block[move[1].X + 1][move[1].Y + 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 1){ // 縦向きに変更
            if(set[move[0].X][move[0].Y + 2] == 0 && set[move[1].X + 1][move[1].Y - 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y + 1] == 0){
                block[move[0].X][move[0].Y + 2] = 1;
                block[move[1].X + 1][move[1].Y - 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y + 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 2){ // 横向きに変更
            if((set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y - 1] == 0 && set[move[3].X - 2][move[3].Y] == 0)
               && (move[2].X != 0)){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y - 1] = 1;
                block[move[3].X - 2][move[3].Y] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 3){ // 縦向きに変更
            if(set[move[0].X + 1][move[0].Y - 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y + 1] == 0 && set[move[3].X][move[3].Y + 2] == 0){
                block[move[0].X + 1][move[0].Y - 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y + 1] = 1;
                block[move[3].X][move[3].Y - 2] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        }
    // 逆Zブロック
    } else if(B_Type == 3){
        for(i = 0; i < 4; i++){
            block[move[i].X][move[i].Y] = 0;
        }
        if(count == 0){ // 縦向きに変更
            if(set[move[0].X + 1][move[0].Y - 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y - 1] == 0 && set[move[3].X - 2][move[3].Y] == 0){
                block[move[0].X + 1][move[0].Y - 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y - 1] = 1;
                block[move[3].X - 2][move[3].Y] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 1){ // 横向きに変更
            if((set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X + 1][move[1].Y - 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X][move[3].Y - 2] == 0)
               && move[2].X != 9){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X + 1][move[1].Y - 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X][move[3].Y - 2] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 2){ // 縦向きに変更
            if(set[move[0].X + 2][move[0].Y] == 0 && set[move[1].X + 1][move[1].Y + 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y + 1] == 0){
                block[move[0].X + 2][move[0].Y] = 1;
                block[move[1].X + 1][move[1].Y + 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y + 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 3){ // 横向きに変更
            if((set[move[0].X][move[0].Y + 2] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y + 1] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0)
               && move[1].X != 0){
                block[move[0].X][move[0].Y + 2] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y + 1] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        }
    // Zブロック
    } else if(B_Type == 4){
        for(i = 0; i < 4; i++){
            block[move[i].X][move[i].Y] = 0;
        }
        if(count == 0){ // 縦向きに変更
            if(set[move[0].X][move[0].Y] == 0 && set[move[1].X - 1][move[1].Y + 1] == 0 && set[move[2].X][move[2].Y - 2] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0){
                block[move[0].X][move[0].Y] = 1;
                block[move[1].X - 1][move[1].Y + 1] = 1;
                block[move[2].X][move[2].Y - 2] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 1){ // 横向きに変更
            if((set[move[0].X + 2][move[0].Y] == 0 && set[move[1].X + 1][move[1].Y - 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0)
               && move[2].X != 9){
                block[move[0].X + 2][move[0].Y] = 1;
                block[move[1].X + 1][move[1].Y - 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 2){ // 縦向きに変更
            if(set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X][move[1].Y + 2] == 0 && set[move[2].X + 1][move[2].Y - 1] == 0 && set[move[3].X][move[3].Y] == 0){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X][move[1].Y + 2] = 1;
                block[move[2].X + 1][move[2].Y - 1] = 1;
                block[move[3].X][move[3].Y] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 3){ // 横向きに変更
            if((set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y + 1] == 0 && set[move[3].X - 2][move[3].Y] == 0)
               && move[1].X !=  0){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y + 1] = 1;
                block[move[3].X - 2][move[3].Y] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        }
    // 正方形ブロック
    } else if(B_Type == 5){
        
    // 凸ブロック
    } else {
        for(i = 0; i < 4; i++){
            block[move[i].X][move[i].Y] = 0;
        }
        if(count == 0){ // 縦向きに変更
            if(set[move[0].X + 1][move[0].Y - 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y + 1] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0){
                block[move[0].X + 1][move[0].Y - 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y + 1] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 1){ // 横向きに変更
            if((set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X + 1][move[1].Y - 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0)
               && (move[2].X != 9)){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X + 1][move[1].Y - 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 2){ // 縦向きに変更
            if(set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X + 1][move[1].Y - 1] == 0 && set[move[2].X][move[2].Y] == 0 && set[move[3].X - 1][move[3].Y + 1] == 0){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X + 1][move[1].Y - 1] = 1;
                block[move[2].X][move[2].Y] = 1;
                block[move[3].X - 1][move[3].Y + 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        } else if(count == 3){ // 横向きに変更
            if((set[move[0].X + 1][move[0].Y + 1] == 0 && set[move[1].X][move[1].Y] == 0 && set[move[2].X - 1][move[2].Y + 1] == 0 && set[move[3].X - 1][move[3].Y - 1] == 0)
               && (move[1].X != 0)){
                block[move[0].X + 1][move[0].Y + 1] = 1;
                block[move[1].X][move[1].Y] = 1;
                block[move[2].X - 1][move[2].Y + 1] = 1;
                block[move[3].X - 1][move[3].Y - 1] = 1;
            } else {
                for(i = 0; i < 4; i++){
                    block[move[i].X][move[i].Y] = 1;
                }
                count--;
            }
        }
    }
}

// 主な操作処理
int main(){

    int x, y;
    int stair;
    int gameover;
    int score;
    int flag; // ループを抜け出す
    int block[10][20] = {}; // 操作するブロック管理
    int set[10][20] = {}; // 既に置かれているブロック座標管理

    // 一列揃ったかどうか判別
    int judgecount = 0;
    int judge[20] = {};
    int complete = 0;
    int staircount = 0;
    int num = 0;

    srand(time(NULL));

    HgOpen(400, 800); // GameWindow
    HgSetTitle("GameWindow");

    ForBlock[0] = rand() % 7; // 一番最初のブロックについてのみここで処理

    HgSetFillColor(HG_DRED); // ここにブロックが置かれたらgameover
    HgBoxFill(200, 760, 40, 40, 0);

    layers = HgWAddDoubleLayer(layerID); // ダブルバッファを作成
    setID = HgWAddLayer(0);

    HgWOpen(930, 1480, 200, 200); // NextWindow
    HgWSetTitle(1, "NextWindow");
    
    HgSetEventMask(HG_KEY_DOWN | HG_TIMER_FIRE); // イベントはキー入力と時間しか受けつけない

    HgSetIntervalTimer(0.5); // 指定秒ごとにイベント発生

    RandomBlock(block);
    NextBlock();

    while(1){ // ゲーム処理

        while(1){ // 一番下に置かれるまでのブロック操作
            layerID = HgLSwitch(&layers); // レイヤー切り替え
            HgLClear(layerID); // 裏の描画消去

            event = HgEventNonBlocking(); // イベント(キー入力)受け付け

            // 以下イベント処理
            if(event != NULL){ 
                // キー入力における処理
                if(event->type == HG_KEY_DOWN){
                    switch(event->ch){
                    case HG_D_ARROW : // 下キー
                        // いずれかのブロックが一番下につく
                        if(move[0].Y == 0 || move[1].Y == 0 || move[2].Y == 0 || move[3].Y == 0){
                            flag = 1;
                        // 操作中のブロックの下にブロックがある
                        } else if(set[move[0].X][move[0].Y - 1] != 0 || set[move[1].X][move[1].Y - 1] != 0 || set[move[2].X][move[2].Y - 1] != 0 || set[move[3].X][move[3].Y - 1] != 0){
                            flag = 1;
                        } else {
                         DownMove(block, move);
                        }
                        break;
                    case HG_R_ARROW : // 右キー
                        // 画面外にいかないか、または操作中のブロックの右にブロックがないか
                        if((move[0].X != 9 && move[1].X != 9 && move[2].X != 9 && move[3].X != 9) && (set[(move[0].X) + 1][move[0].Y] == 0 && set[(move[1].X) + 1][move[1].Y] == 0 && set[(move[2].X) + 1][move[2].Y] == 0 && set[(move[3].X) + 1][move[3].Y] == 0)) RightMove(block, move);
                        break;
                    case HG_L_ARROW : // 左キー
                        // 画面外にいかないか、または操作中のブロックの左にブロックがないか
                        if((move[0].X != 0 && move[1].X != 0 && move[2].X != 0 && move[3].X != 0) && (set[(move[0].X) - 1][move[0].Y] == 0 && set[(move[1].X) - 1][move[1].Y] == 0 && set[(move[2].X) - 1][move[2].Y] == 0 && set[(move[3].X) - 1][move[3].Y] == 0)) LeftMove(block, move);
                        break;
                    case ' ' : // スペースキー(回転)
                        if(count == 4) count = 0;
                        // 一番下に位置している場合は回転させない
                        if(move[0].Y != 0 || move[1].Y != 0 || move[2].Y != 0 || move[3].Y != 0) RotationChange(B_Type, block, set, move);
                        count++;
                    default :
                        break;
                    }
                // 指定秒ごとに自動下降
                } else if(event->type == HG_TIMER_FIRE){
                    if((set[move[0].X][move[0].Y - 1] == 0 || set[move[1].X][move[1].Y - 1] == 0 || set[move[2].X][move[2].Y - 1] == 0) 
                         && (move[0].Y != 0 && move[1].Y != 0 && move[2].Y != 0 && move[3].Y != 0)){
                        for(i = 0; i < 4; i++){
                            block[move[i].X][move[i].Y] = 0;
                            block[move[i].X][move[i].Y - 1 ] = 1;
                        }
                    }
                }
            }
            WriteBlock(block, set);  // 現時点でのブロックを描画
            // ブロックが一番下に置かれた
            if(flag == 1){
                for(y = 0; y < 20; y++){
                    for(x = 0; x < 10; x++){
                        if(block[x][y] == 1){
                            set[x][y] = color + 1; // 0は何もない状態,1を加えて判別
                        }
                        block[x][y] = 0; // 操作ブロックの情報を初期化
                    }
                }
                if(set[5][19] != 0) gameover = 1;
                HgWClear(1); // NextBlockウインドウを切り替える
                count = 0; // 回転数をリセット
                flag = 0; // フラグをリセット
                HgLClear(setID);
                PutBlock(set);
                RandomBlock(block); // 次にくるブロックを生成
                NextBlock(); // NextBlockウインドウに描画
                break;
            }
        } // while内のブロック操作ここまで

        if(gameover == 1) break;
        // 毎回(一つのブロックが置かれるたび)一列揃っているか判定
        for(y = 0; y < 20; y++){
            for(x = 0; x < 10; x++){
                if(set[x][y] != 0) judgecount++;
            }
            // 一列揃っていた場合
            if(judgecount == 10){
                HgLClear(setID); // setIDに描かれている描画を消去
                for(x = 0; x < 10; x++){ // 揃った段に関して消去
                    set[x][y] = 0;
                    judge[y]++; // 何段目が揃っていたか
                    score += (y+1) * 100; // スコア計算
                }
                complete++;
            }
            judgecount = 0;
        }
        // 一列でも揃っていた場合以下の処理を行う
        if(complete != 0){
            for(y = 0; y < 18; y++){
                if(judge[y] != 0 && judge[y + 1] != 0 && judge[y + 2] != 0 && judge[y + 3] != 0){ // 連続して揃っていた場合の処理
                    staircount++;
                    judge[y] = 0;
                    for(int y2 = y; y2 < 16; y2++){
                        for(x = 0; x < 10; x++){
                            set[x][y2] = set[x][y2 + 4];
                        }
                    }
                    y = 0;
                } else if(judge[y] != 0 && judge[y + 1] != 0 && judge[y + 2] != 0){
                    staircount++;
                    judge[y] = 0;
                    for(int y2 = y; y2 < 17; y2++){
                        for(x = 0; x < 10; x++){
                            set[x][y2] = set[x][y2 + 3];
                        }
                    }
                    y = 0;
                } else if(judge[y] != 0 && judge[y + 1] != 0){
                    staircount++;
                    judge[y] = 0;
                    for(int y2 = y; y2 < 18; y2++){
                        for(x = 0; x < 10; x++){
                            set[x][y2] = set[x][y2 + 2];
                        }
                    }
                    y = 0;
                } else if(judge[y] != 0){
                    staircount++;
                    judge[y] = 0;
                    for(int y2 = y; y2 < 19; y2++){
                        for(x = 0; x < 10; x++){
                            set[x][y2] = set[x][y2 + 1];
                        }
                    }
                    y = 0;
                }
            }
            for(y = 19; y > 20 - staircount; y--){ // 一番上から何段揃ったかによって初期化
                for(x = 0; x < 10; x++){
                    set[x][y] = 0;
                }
            }
            complete = 0;
            staircount = 0;
            num = 0;   
            PutBlock(set); // 上記の計算より現段階で残ってるブロックを描画
        }
    }

    HgCloseAll();
    printf("GAME OVER\n");
    printf("SCORE : %d\n", score);

    return 0;

}