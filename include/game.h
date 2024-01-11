//
// Created by 任 on 2024/1/8.
//

#ifndef DS_WORK_GANE_H
#define DS_WORK_GANE_H
#include <iostream>
#include <fstream>
#include "state.h"
#include "Graph.h"
#include "Way.h"
#include "stack.h"
using std :: cin;
using std :: cout;
using std :: ifstream;
using std :: ios;

class game {
public:
    Graph gameMap;
    int is_play = 0;
    stack<state> process;//记录过去的状态
    state now_st;
    Way w;
    game(){
        is_play = 0;
        process.clear();
        gameMap = getMap();
    }
private:
    Graph getMap(){
        ifstream infile;
        infile.open("E:\\mycode\\ds_work\\map.txt", ios::in);
        if (!infile.is_open()) {
            cout << "Error opening file\n";
            perror("Error");
            exit(0);
        }
        int n,m;
        infile>>n>>m;
        Graph g(n,m);
        for(int i = 0 ; i < n ; i++){
            char c;
            int val;
            infile>>c>>val;
            g.read_val(c,val);
        }
        for(int i = 0 ; i < m ; i++){
            int a,b,val;
            infile>>a>>b>>val;
            g.add_edge(a,b,val);
        }
        return g;
    }


public:
    void start_game(){
        process.clear();
        now_st.restart();
    }
    void get_PlayerOp(int choice){
        if(choice == 2){
            is_play = 2;
            auto way =  w.maxHp(gameMap , 0);
            //cout<<way.size();
            for(auto x : way){
                cout<<x<<" ";
            }
            printf("\n按任意键回到主菜单\n");
            system("pause");
            system("cls");
        }else if(choice == 3){
            is_play = 3;
            auto way = w.maxValue(gameMap , 0);
            for(auto x : way){
                cout<<x<<" ";
            }
            printf("\n按任意键回到主菜单\n");
            system("pause");
            system("cls");
        }else if(choice == 1){
            is_play = 1.;
            start_game();
            play();
            process.output();
            system("pause");
            system("cls");
        }
    }
    void play(){
        system("cls");
        process.push(now_st);
        if(now_st.hp <= 0){
            printf("您已死亡\n");
            printf("复活请按1，退出请按2\n");
            int t;
            while(cin >> t){
                if(t == 1 || t == 2) break;
                else printf("请正确输入\n");
            }
            if(t == 1){
                back();
                play();
                return;
            }else{
                system("cls");
                return;
            }
        }

        if(now_st.now == gameMap.n - 1){
            printf("你现在位于%d ,有 %d HP , 财富累计 %d\n", now_st.now,now_st.hp,now_st.val);
            printf("恭喜通关");
            return;
        }
        printf("你现在位于%d ,有 %d HP , 财富累计 %d\n", now_st.now,now_st.hp,now_st.val);
        printf("下面可去的点有:");
        auto x = gameMap.find_Adjacent(now_st.now);
        for(auto to : x){
            printf("%d " , to);
        }
        printf("\n");
        printf("选择路线:" "(-1退出) (-2回退)");
        int to;
        cin>>to;
        while(find(x.begin(), x.end() , to) == x.end()){
            if(to == -1) return;
            if(to == -2 && process.size() > 1){
                break;
            }
            printf("该点无法到达，重现选择");
            cin>>to;
        }
        if(to == -2) back();
        else move(to);
        play();
    }

    void move(int to){
        now_st.hp = now_st.hp - gameMap.matrix[now_st.now][to];
        now_st.val = (!now_st.vis[to]) ? gameMap.v_val[to] + now_st.val : now_st.val;
        now_st.now = to;
        now_st.vis[to] = 1;
    }

    void back(){
        process.pop();
        now_st = process.top();
        process.pop();
    }
};


#endif //DS_WORK_GANE_H
