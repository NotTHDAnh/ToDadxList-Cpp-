#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include "ITEM.cpp"
#pragma once

class StoreData{
private:
    list<Todoitem> TodoitemList;
    list<Todoitem>::iterator it;
    bool check[10001];
public:
    virtual void ReadData(list <Todoitem> &TodoitemList){
        string data;
        ifstream fi("data.txt");
        while(getline(fi,data)){
            string tmp = "";
            vector<string> row;
            for(char c : data){
                if(c == '|'){
                    row.push_back(tmp);
                    tmp = "";
                    continue;
                }
                tmp += c;
            }
            row.push_back(tmp);
            if(!check[stoi(row[1])]){
                // row 0 is task descriptions
                // row 1 is ID of the task
                // row 2 is status of the task
                // row 3 is date of the task
                Todoitem DATA; DATA.create(row[0], stoi(row[1]), stoi(row[2]), row[3], row[4], stoi(row[5]));
                TodoitemList.push_back(DATA);
                check[stoi(row[1])] = 1;
            }
        }
        fi.close();
    }

    void setTodoitemList(list <Todoitem> TodoitemList){
        this->TodoitemList = TodoitemList;
    }

    virtual void Store(list<Todoitem> &TodoitemList){
        ofstream fo("data.txt");
        setTodoitemList(TodoitemList);
        for(it = TodoitemList.begin();it != TodoitemList.end();++it){
            fo << it->getDescription() << "|"  << it->getID() << "|" << it->IsCompleted() << "|" << it->getCategory() << "|" << it->getDeadline() << "|" << it->IsImportant() << endl;
        } // Stored data in "data.txt"
        fo.close();
    }
};
