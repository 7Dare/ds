//
// Created by 任 on 2024/1/3.
//

#ifndef DS_WORK_GRAPH_H
#define DS_WORK_GRAPH_H
#include <bits/stdc++.h>
#include "state.h"

using std :: vector;
using std :: pair;
using std :: map;
using std :: string;
using std :: set;
using std :: stack;
//如果想做返回的操作，那么状态也是我们需要封装的一个东西
//可以通过栈的操作来实现反悔的操作
//同时得记录
//如果考虑复活功能，那么就得考虑图上每个点，是否走过，
//放在类里面做move操作

class Graph {

    using PII = pair<int,int>;

    //使得下标从0开始

public:
        int n,m;//图中的节点数量和边的数量
        vector<PII> g[100];//临界表的存储
        int matrix[100][100];//临界举证存储
        int v_val[100];//每个点的val
        int idx;//记录字母的标号
        map<char , int> c_to_num;//用来做字母到点的映射；
        map<int , char> num_to_c;//用来做点到字母的映射；
        /*---------------------------------------------*/
        //以上是图的基本信息，以下为游戏图的一些额外功能
        //按理来说应该写个新类对其进行继承
        /*---------------------------------------------*/

    Graph(int a , int b){

        n = a , m = b;
        idx = -1;
        memset(matrix , -0x3f, sizeof matrix);
    }
    Graph(){};

    void clear(){
        idx = -1;
        memset(matrix , 0x3f , sizeof matrix);
        for(int i = 0 ; i < n ; i++)g[i].clear();
    }


    //读取每个点的val,同时记录字母到数字的映射
    void read_val(char c , int val){
        if(c_to_num.find(c) != c_to_num.end()) return;
        c_to_num[c] = ++idx;
        num_to_c[idx] = c;
        v_val[idx] = val;
        return;
    }

    //用来加入边
    void add_edge(int a, int b, int w){
        g[a].push_back({b , w});
        g[b].push_back({a , w});
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
    /*
     * ————————————————————————————————————————————————————
     * 以上为普通图的基本
     * 以下为游戏图中的功能
     *
     *
     * */
    vector<int> find_Adjacent(int x){
        vector<int> s;
        for(auto p : g[x]){
            s.push_back(p.first);
        }
        return s;
    }
};

namespace Way{
    using VI = vector<int>;
    using PII = pair<int,int>;
    /*---------------------*/
    int vis[100][100];
    int tre[100];
    //作为求最大价值的变量存储
    /*---------------------*/
    int dis[100];
    int from[100];//记录当前的点是从哪一个点转移而来的
    //int vis2[100];
    /*---------------------*/
    void dfs(int now , int life , int myVal , VI myPath , VI &resPath , int &res , Graph g){

        myPath.push_back(now);
        if(now == g.n - 1 ){
            if(myVal > res){
                resPath = myPath;
                res = myVal;
            }
            return;
        }

        tre[now]++;
        for(auto x : g.g[now]){
            int to = x.first;
            int cost = x.second;
            if(vis[now][to] + vis[to][now] != 2 && life > cost){
                vis[now][to] += 1;
                int v = myVal + (tre[to] ? 0 : g.v_val[to]);
                dfs(to , life - cost , v , myPath , resPath , res , g);
                vis[now][to] -= 1;
            }
        }
        myPath.pop_back();
        tre[now]--;
        return;

    }
    //返回一个键值对 ， 第一个元素代表路劲，第二个元素代表最大值
    pair<VI , int> maxValue(Graph g){
        VI resPath , a;
        int res = 0;
        memset(vis , 0 , sizeof vis);
        memset(tre , 0 , sizeof tre);
        dfs( 0 ,100 , 0 , a , resPath , res , g);
        return {resPath , res};
    }

    pair<VI , int> maxHp(Graph g){
        memset(from , -1 , sizeof from);
        memset(dis , 0x3f , sizeof dis);
        using namespace std;
        priority_queue<pair<int ,int> , vector<PII> , greater<PII>> q;
        //VI hasVis(g.n + 1 , 0);
        dis[0] = 0;
        q.push({dis[0]  , 0});
        while(q.size()){
            auto u = q.top();
            q.pop();
            int now = u.second;
            if(u.first > dis[now]) continue;
            for(auto x : g.g[now]){
                int to = x.first;
                int cost = x.second;
                if(dis[to] > dis[now] + cost){
                    dis[to] = dis[now] + cost;
                    from[to]  = now;
                    q.push({dis[to] , to});
                }
            }
        }
        VI resPath;
        int x = g.n - 1;
        //resPath.push_back(x);
        while(x != -1){
            resPath.push_back(x);
            x = from[x];

        }

        reverse(resPath.begin()  ,resPath.end());
        return {resPath , 100 - dis[g.n - 1]};
    }
}

#endif //DS_WORK_GRAPH_H
