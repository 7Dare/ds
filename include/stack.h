//
// Created by 任 on 2024/1/11.
//

#ifndef DS_WORK_STACK_H
#define DS_WORK_STACK_H


template <typename T>
class stack{
private:
    T s[100];
    int f;


public:
    stack(){
        f = 0;
    }
    int size(){
        return f;
    }
    void push(T a){
        s[++f] = a;
    }

    void pop(){
        if(size())f--;
    }
    T top(){
        return s[f];
    }
    void clear(){
        f = 0;
    }
    std ::vector<T> output(){
        std :: vector <T> a;
        for(int i = 1 ; i <= size() ; i++){
            printf("%d  " , s[i].now);
            a.push_back(s[i]);
        }
        return a;
    }


};



#endif //DS_WORK_STACK_H
