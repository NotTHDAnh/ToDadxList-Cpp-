#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <fstream>
#include <ctime>
#include "KMP.cpp"


using namespace std;

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

int main(){
    string version = "v.0.0";

    list <Todoitem> TodoitemList;
    list <Todoitem>::iterator it;
    ifstream fi("data.txt");
    srand(time(NULL));


    KMP findword;
    string input_user;
    string input_add;
    string input_mark_ok;
    int input_mark;
    char input_delete;
    string data;
    string find_input;

    // read the data 
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
    ofstream fo("data.txt");

    while(1){
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

        cout << "[a]dd new to do" << endl;
        cout << "[m]ark the task is done"<<endl;
        cout << "[f]ind note by keyword:" <<endl;
        cout << "[d]elete all the tasks:" << endl;
        cout << "[q]uit" << endl;

        cout << "Choose your choice: ";
        getline(cin,input_user);

        // QUIT THE PROGRAM

        if(input_user == "q"){
            for(it = TodoitemList.begin();it != TodoitemList.end();++it){
                fo << it->getDescription() << "|"  << it->getId() << "|" << it->IsCompleted() << endl;
            } // Stored data in "data.txt"
            fo.close();
            break;
        }


        // ADD NOTES

        else if(input_user == "a"){ 
            cout << "Node down your description:";
            cin.clear();
            getline(cin,input_add);
            Todoitem Add;
            Add.create(input_add);
            TodoitemList.push_back(Add);
        }

        // MARK AND DELETE NOTE

        else if(input_user == "m"){
            cout << "Choose the task's ordered you want to mark:";
            cin >> input_mark;
            cout << "[m]ark or [u]nmark:";
            cin >> input_mark_ok;
            if(input_mark_ok == "m"){
                cout << "Do you want to delete this task from the list([Y]es or [N]o):";
                cin >> input_delete;
            }
            for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
                if(input_mark == it->getId()){
                    if(input_mark_ok == "m") it->mark(true); else it->mark(false);
                    if(input_delete == 'Y' || input_delete == 'y'){
                        TodoitemList.erase(it);
                    }
                    break;
                }
            }
        }

        // FIND FILES

        else if(input_user == "f"){
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

        // DELETE ALL TASKS

        else if(input_user == "d"){
            TodoitemList.clear();
        }

        // ADVOID UNECESSARY WORDS

        else{
            if(input_user != "y" ||
               input_user != "Y" || 
               input_user != "N" ||
               input_user != "n" ) continue;

            system("cls");
            cout << "Please choose the correct letter!\n";
            system("pause");
        }
    }
    return 0;
}
