#include "Graph.h"
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include "game.h"
using namespace std;
using std :: cin;
using std :: cout;

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


int main(){
    system("chcp 65001");
    //Graph g = getMap();
    game game_play(getMap());
    while(1){
        printf(
                "1.开始游戏\n"
               "2.HP路线\n"
               "3.VAL路线\n");
        int op;
        cin>>op;
        game_play.get_PlayerOp(op);
        cout<<endl;
        //system("cls");
    }
}