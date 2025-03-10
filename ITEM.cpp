#include <iomanip>
#include <sstream>
#include "Calendar.cpp"
#pragma once
using namespace std;
class Todoitem : public Calendar{
    private:
        int id;
        string description;
        bool isDone;
        string category;
        string deadline;
        bool Important;
    public:

        Todoitem(): id(0), description(""), isDone(false), deadline("NULL") {}
        ~Todoitem() = default;
        
        bool IsCompleted(){return isDone;}
        string getDescription() {return description;}
        int getID(){return id;}
        string getCategory(){return category;}
        string getDeadline(){return deadline;}
        bool IsImportant(){ return Important;}

        void create(string new_description){
            id = rand() % 100 + 100;
            description = new_description;
        }

        void create(string new_description,string category){
            id = rand() % 100 + 100;
            description = new_description;
            this->category = category;
        }

        void create(string description,int id,bool isDone) {
            this-> id = id;
            this->description = description;
            this->isDone = isDone;
        }

        void create(string description, int id, bool isDone, string category){
            this-> id = id;
            this->description = description;
            this->isDone = isDone;
            this->category = category;
        }

        void create(string description, int id, bool isDone, string category, string deadlines, bool Important = 0){
            this-> id = id;
            this->description = description;
            this->isDone = isDone;
            this->category = category;
            //set deadline
            this->deadline = deadlines;
            this->Important = Important;
        }
        void setDeadline(string deadlines){
            this->deadline = deadlines;
        }

        void setImportant(bool ip){
            this->Important = ip;
        }

        void mark(bool done){
            this->isDone = done;
        }
};


