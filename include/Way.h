//
// Created by 任 on 2024/1/10.
//

#ifndef DS_WORK_WAY_H
#define DS_WORK_WAY_H
#include <vector>
#include <utility>
#include <queue>
#include "Graph.h"
class Way {
    using VI = vector<int>;
    using PII = pair<int,int>;
    /*---------------------*/
private:
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
public:
     VI maxValue(Graph g , int now){
        VI resPath , a;
        int res = 0;
        memset(vis , 0 , sizeof vis);
        memset(tre , 0 , sizeof tre);
        dfs(now ,100 , 0 , a , resPath , res , g);
        return resPath ;
    }

    VI maxHp(Graph g, int now){
        memset(from , -1 , sizeof from);
        memset(dis , 0x3f , sizeof dis);
        using namespace std;
        priority_queue<pair<int ,int> , vector<PII> , greater<PII>> q;
        //VI hasVis(g.n + 1 , 0);
        dis[now] = 0;
        q.push({dis[now]  , now});
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
        return resPath;
    }

};


#endif //DS_WORK_WAY_H
