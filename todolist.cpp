#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <fstream>
#include <ctime>
#include "KMP.cpp"


using namespace std;

string version = "v.0.0";

class Todoitem{
    private:
        int id;
        string description;
        bool isDone;
    public:

        Todoitem(): id(0), description(""), isDone(false) {}
        ~Todoitem() = default;
        
        bool IsCompleted(){return isDone;}
        string getDescription() {return description;}
        int getId(){return id;}

        void create(string new_description){
            id = rand() % 1000 + 30000;
            description = new_description;
        }

        void create(string description,int id,bool isDone) {
            this-> id = id;
            this->description = description;
            this->isDone = isDone;
        }

        void mark(bool done){
            this->isDone = done;
        }
};

class Todolist_Menu{
private:
    list<Todoitem> TodoitemList;
    list<Todoitem>::iterator it;
public:
    Todolist_Menu(list<Todoitem> TodoitemList){
        this->TodoitemList = TodoitemList;
        system("cls");
        cout << "Welcome to To D[adx] list " << version << endl;
        // SHOWING REMAINING TASKS
        for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
            string status = (it->IsCompleted() ? "Done" : "Not Done");
            cout << it->getId() << " | " << it->getDescription() << " | " << status << endl;
        }
        cout << endl << endl;

        // SHOW IF THERE'S NO TASK REMAINING
        if(TodoitemList.empty()){
            cout << "Add your first to do" << endl;
        }
        cout << endl << endl;

        // MENU

        cout << "------------------------------------\n";
        cout << "[a]dd new to do" << endl;
        cout << "[m]ark the task is done"<<endl;
        cout << "[f]ind note by keyword:" <<endl;
        cout << "[d]elete tasks:" << endl;
        cout << "[q]uit" << endl;

        cout << "Choose your choice: ";
    }
};

class StoreData{
private:
    list<Todoitem> TodoitemList;
    list<Todoitem>::iterator it;
public:
    void ReadData(list <Todoitem> &TodoitemList){
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
            Todoitem DATA; DATA.create(row[0], stoi(row[1]), stoi(row[2]));
            TodoitemList.push_back(DATA);
        }
        fi.close();
    }

    void setTodoitemList(list <Todoitem> TodoitemList){
        this->TodoitemList = TodoitemList;
    }

    void Store(list<Todoitem> &TodoitemList){
        ofstream fo("data.txt");
        setTodoitemList(TodoitemList);
        for(it = TodoitemList.begin();it != TodoitemList.end();++it){
            fo << it->getDescription() << "|"  << it->getId() << "|" << it->IsCompleted() << endl;
        } // Stored data in "data.txt"
        fo.close();
    }

};

class Menu_Options : StoreData{
private:
    list <Todoitem> TodoitemList;
    list<Todoitem>::iterator it;
    KMP findword;
    int mark;
    string data;
    vector<int> listToDelete;
public:
    Menu_Options(){
        this->mark = 1;
    }

    void printMENU(){
        Todolist_Menu MENU(TodoitemList);
    }

    void getstarted(){
        ReadData(TodoitemList);
    }
    bool getmark(){
        return this->mark;
    }
    void QUIT(){
        Store(this->TodoitemList);
        mark = 0;
    }

    void ADDNOTE(){
        string input_add;
        cout << "Write down your note! : ";
        cin.clear();
        getline(cin,input_add);
        Todoitem Add;
        Add.create(input_add);
        TodoitemList.push_back(Add);
    }

    void MARK_NOTE(){
        int input_mark;
        char input_delete;

        cout << "Choose the task's ordered you want to mark:";
        cin >> input_mark;
        for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
            if(input_mark == it->getId()){
                if(it->IsCompleted() == true){
                    cout << "Do you want to unmark it?[Y]es or [No]: ";
                    char option; 
                    cin >> option;
                    if(option == 'Y' || option == 'y'){
                        it->mark(false);
                        return;
                    }
                    cout << "Do you want to delete this task?[Y]es or [N]o:";
                    cin >> input_delete;
                }
                else it->mark(true);

                if(input_delete == 'Y' || input_delete == 'y'){
                    TodoitemList.erase(it);
                    break;
                }
            }
        }
    }

    void Find_by_Keyword(){
        string find_input;

        system("cls");
        cout << "Type the notes you want to find:" ;
        cin >> find_input; 
        cout << "Here some notes we've found: \n";
        for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
            string tmp = it->getDescription();
            if(findword.find(tmp, find_input)){
                cout << "|" << it->getId() << "|" << it->getDescription() << "|" << endl;
            }
        }
        system("pause");
    }

    void Delete_Options(){
        char input_deletion_choice;

        cout << "Do you want to delete all the notes [1] or just the finished notes [2]:";
        cin >> input_deletion_choice;
        if(input_deletion_choice == '1'){
            TodoitemList.clear();
        }
        else if(input_deletion_choice == '2'){
            for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
                if(it->IsCompleted()){
                    listToDelete.push_back(it->getId());
                }
            }
            for(int x : listToDelete){
                for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
                    if(x == it->getId()){
                        TodoitemList.erase(it);
                        break;
                    }
                }
            }
        }
    }
};

int main(){
    srand(time(NULL));

    string input_user;
    // read the data 

    Menu_Options OPTIONS;
    OPTIONS.getstarted();

    while(OPTIONS.getmark()){
        system("cls");

        OPTIONS.printMENU();
        getline(cin,input_user);

        // QUIT THE PROGRAM

        if(input_user == "q"){
            OPTIONS.QUIT();
        }


        // ADD NOTES

        else if(input_user == "a"){ 
            OPTIONS.ADDNOTE();
        }

        // MARK AND DELETE NOTE

        else if(input_user == "m"){
            OPTIONS.MARK_NOTE();
        }

        // FIND FILES

        else if(input_user == "f"){
            OPTIONS.Find_by_Keyword();
            continue;
        }

        // DELETE ALL TASKS

        else if(input_user == "d"){
            OPTIONS.Delete_Options();
        }

    }
    return 0;
}
