//
// Created by 任 on 2024/1/8.
//

#ifndef DS_WORK_STATE_H
#define DS_WORK_STATE_H
class state {
public:
    int now;//记录在哪个点
    int hp;//记录血
    int val;//记录价值;
    int vis[100];//记录每个点经过了多少次，同时
    state(int n , int h , int v){
        now = n , hp = h ,val = v;
    }
    state(){};

    void restart(){
        now = 0;
        val = 0;
        hp = 100;
        for(int i = 0 ; i < 100 ; i++) vis[i] = 0;
        vis[0] = 1;
    }

};


#endif //DS_WORK_STATE_H
