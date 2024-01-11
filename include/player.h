//
// Created by 任 on 2024/1/11.
//

#ifndef DS_WORK_PLAYER_H
#define DS_WORK_PLAYER_H
#include <vector>


class player {

private:
    std :: vector<state> s;
    int maxGrade = -1;

public:


    void update(int newGrade , std :: vector<state> path){
        if(maxGrade < newGrade){
            maxGrade = newGrade;
            s = path;
        }
    }

    int get_maxGrade(){
        return maxGrade;
    }
    std::vector<state> get_path(){
        return s;
    }
    void output_progress(){
        printf("对应路径");
        for(auto x : get_path()){
            //printf("1");
            printf("%d  " , x.now);
        }
        printf("\n");
    }

};


#endif //DS_WORK_PLAYER_H
