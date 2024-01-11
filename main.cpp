#include<iostream>
#include "include/game.h"
#include "easyx.h"
#include "graphics.h"
#include "conio.h"
using std :: cin;
using std :: cout;

static void menu1(){
    printf("1.开始游戏\n"
           "2.最优路线\n"
           "3.离开游戏\n");
}
static void menu2_1(){
    printf("1.生命值最高\n"
           "2.财富值最高\n"
           "3.返回上级菜单\n");
}






int main(){
    system("chcp 65001");
    //Graph g = getMap();


    initgraph(1280, 730);/*创建一个窗口*/
    IMAGE img;/*声明一个IMAGE变量*/
    loadimage(&img , "E:\\mycode\\ds_work\\graphMap.png");
    putimage(0,0,&img);
    game game_play;
    int op;
    while(1){
        menu1();
        cin>>op;
        if(op == 3)exit(0);
        else if(op == 1) {
            system("cls");
            game_play.get_PlayerOp(1);
        }else if(op == 2){
            system("cls");
            menu2_1();
            int op2;
            cin>>op2;
            game_play.get_PlayerOp(op2 + 1);
        }else{
            printf("请正确输入\n");
        }

        system("cls");
    }
}