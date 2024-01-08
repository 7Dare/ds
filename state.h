//
// Created by 任 on 2024/1/8.
//

#ifndef DS_WORK_STATE_H
#define DS_WORK_STATE_H
#include "bits/stdc++.h"
using std :: map;

class state {
public:
    int now;//记录在哪个点
    int hp;//记录血
    int val;//记录价值;
    map<int ,int> vis;//记录每个点经过了多少次，同时
    state(int n , int h , int v , map<int,int>s){
        now = n , hp = h ,val = v;
        vis = s;
    }
    state(){};

public:
    void restart(){
        now = 0;
        val = 0;
        hp = 100;
        vis.clear();
        vis[0] = 1;
    }

};


#endif //DS_WORK_STATE_H
