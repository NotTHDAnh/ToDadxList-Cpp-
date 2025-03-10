#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <fstream>
#include <ctime>
#include "KMP.cpp"
#include "MENU.cpp"
#include "Important.cpp"
#include "MyDay.cpp"
#include "STORE.cpp"
#include "Planned.cpp"


using namespace std;

list <Todoitem> TodoItemList;
int status = 2;


string version = "v.1.0";

class Menu_Options : StoreData{
private:
    list <Todoitem> TodoitemList;
    list<Todoitem>::iterator it;
    KMP findword;
    int mark;
    string data;
    vector<int> listToDelete;
    Todolist_Menu MENU;
    int status;
    MyDay OPT1;
    Important OPT2;
    Planned OPT3;
public:
    Menu_Options(){
        this->mark = 1;
    }

    void MY_DAY_OPTION(){
        OPT1.setList(TodoItemList);
        OPT1.Started();
        OPT1.printMENU();
        OPT1.OPTIONS();
        status = OPT1.getStatus();
        OPT1.setStatus(1);
        TodoItemList = OPT1.getList();
    }

    void Important_OPTION(){
        OPT2.setList(TodoItemList);
        OPT2.Started();
        OPT2.printMENU();
        OPT2.OPTIONS();
        status = OPT2.getStatus();
        OPT2.setStatus(3);
        TodoItemList = OPT2.getList();
    }

    void Planned_OPTION(){
        OPT3.setList(TodoItemList);
        OPT3.print();
    }

    void SAVE(){
        OPT1.saveInSpecialCase();
    }

    void printMENU(){
        MENU.printDefaultMenu();
    }

    void getStarted(){
        ReadData(TodoitemList);
    }
    bool getMark(){
        return this->mark;
    }
    void QUIT(){
        status = 0;
    }
    int getStatus(){
        return this->status;
    }

};

int main(){
    srand(time(NULL));

    string input_user;
    // read the data 

    Menu_Options OPTIONS;
    // OPTIONS.getStarted();


    //1 is MY DAY
    //2 is home page
    //3 is favourite
    //4 is Planned
    OPTIONS.getStarted();

    while(status != 0){
        system("cls");
        // HOMEPAGE
        cin.clear();
        if(status == 2){
            OPTIONS.printMENU();
            cin >> input_user;
        }
        // QUITTING
        if(input_user == "q" || input_user == "Q"){
            status = 0;
            OPTIONS.SAVE();
        }
        // MY DAY TASKS
        else if(input_user == "d" || input_user == "D") {
            status = 1;
            while(status == 1){
                OPTIONS.MY_DAY_OPTION();
                status = OPTIONS.getStatus();
            }
        }
        else if(input_user == "I" || input_user == "i"){
            status = 3;
            while(status == 3){
                OPTIONS.Important_OPTION();
                status = OPTIONS.getStatus();
            }
        }
        else if(input_user == "p" || input_user == "P"){
            OPTIONS.Planned_OPTION();
        }
    }
    return 0;
}
