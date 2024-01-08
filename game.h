//
// Created by 任 on 2024/1/8.
//

#ifndef DS_WORK_GANE_H
#define DS_WORK_GANE_H
#include "bits/stdc++.h"
#include "state.h"
#include "Graph.h"
using std :: cin;
using std :: cout;
class game {
public:
    Graph gameMap;
    int is_play;//0代表还未选选择，1，2，3分别代表对应的
    stack<state> process;//记录过去的状态
    state now_st;
    game(Graph g){
        is_play = 0;
        process = stack<state>();
        gameMap = g;
    }
    void start_game(){
        process = stack<state>();
        now_st.restart();
    }


    void get_PlayerOp(int choice){
        if(choice == 2){
            is_play = 2;
            auto way =  Way::maxHp(gameMap);
            for(auto x : way.first){
                cout<<x<<" ";
            }
            printf("\n");


        }else if(choice == 3){
            is_play = 3;
            auto way = Way::maxValue(gameMap);
            for(auto x : way.first){
                cout<<x<<" ";
            }
            printf("\n");
        }else if(choice == 1){
            start_game();
            play();
        }
    }
    void play(){



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
                process.pop();
                now_st = process.top();
            }else{
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
            printf("%d  " , to);
        }
        printf("\n");
        printf("选择路线:");
        int to;
        cin>>to;
        while(find(x.begin(), x.end() , to) == x.end()){
            printf("该点无法到达，重现选择");
            cin>>to;
        }
        move(to);
        play();


    }


    void move(int to){
        now_st.hp = now_st.hp - gameMap.matrix[now_st.now][to];
        now_st.val = (!now_st.vis[to]) ? gameMap.v_val[to] + now_st.val : now_st.val;
        now_st.now = to;
        now_st.vis[to] = 1;
    }







};


#endif //DS_WORK_GANE_H
