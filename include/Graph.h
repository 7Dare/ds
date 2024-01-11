//
// Created by 任 on 2024/1/3.
//

#ifndef DS_WORK_GRAPH_H
#define DS_WORK_GRAPH_H
#include <vector>
#include <utility>
#include <string.h>
#include <algorithm>
#include "state.h"
const int MAX_INT = 0x3f3f3f3f;
using std :: vector;
using std :: pair;
//如果想做返回的操作，那么状态也是我们需要封装的一个东西
//可以通过栈的操作来实现反悔的操作
//同时得记录
//如果考虑复活功能，那么就得考虑图上每个点，是否走过，
//放在类里面做move操作

class Graph {
    //使得下标从0开始

public:
        int n,m;//图中的节点数量和边的数量
        vector<pair<int,int>> g[100];//临界表的存储
        //vector<int> gv[100];//临界表的存储
        int matrix[100][100];//临界举证存储
        int v_val[100];//每个点的val
        int idx;//记录字母的标号
        int c_to_num[100];//用来做字母到点的映射；
        char num_to_c[100];//用来做点到字母的映射；
        /*---------------------------------------------*/
        //以上是图的基本信息，以下为游戏图的一些额外功能
        //按理来说应该写个新类对其进行继承
        /*---------------------------------------------*/

    Graph(int a , int b){

        n = a , m = b;
        idx = -1;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                matrix[i][j] = MAX_INT;
            }
        }
    }
    Graph(){

    };

    //虽然有这个设计，但好像没啥用
   /* void clear(){
        idx = -1;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                matrix[i][j] = MAX_INT;
            }
        }
    }*/


    //读取每个点的val,同时记录字母到数字的映射
    void read_val(char c , int val){
        c_to_num[c] = ++idx;
        num_to_c[idx] = c;
        v_val[idx] = val;
        return;
    }

    //用来加入边
    void add_edge(int a, int b, int w){
        g[a].push_back({b,w});
        g[b].push_back({a,w});
        matrix[a][b] = w;
        matrix[b][a] = w;
    }


    //用来做数字到字母的映射
    char to_c(int a){
        return num_to_c[a];
    }
    //用来做字母到数字的映射
    int to_num(char c){
        return c_to_num[c];
    }

    vector<int> find_Adjacent(int x){
        vector<int> s;
        for(auto p : g[x]){
            s.push_back(p.first);
        }
        return s;
    }
};

#endif //DS_WORK_GRAPH_H
