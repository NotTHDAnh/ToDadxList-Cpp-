#include "MyDay.cpp"

class Important : public MyDay{
private:
    list <Todoitem> TodoitemList;
    list <Todoitem>::iterator it; 
    string MyDayInput;
    int status = 3;
    int unfinsied_task = 0;
    KMP findKeyWord;
public:
    const string category = "Important";
    Important(){
        this->status = 3;
    }
    Important(list <Todoitem> TodoitemList){
        this->TodoitemList = TodoitemList;
        this->status = 3;
    }
    void setStatus(int status){
        this->status = status;
    }

    void setList(list <Todoitem> TodoitemList){
        this->TodoitemList = TodoitemList;
    }
    
    void Started(){
        MyDay::Started();
    }
void init(){
        MyDay::init();
    }
    void printMENU(){
        system("cls");
        ReadData(TodoitemList);
        init();
        string TITLE = {
            "  ___                            _              _     _ \n"
            " |_ _|_ __ ___  _ __   ___  _ __| |_ __ _ _ __ | |_  | |\n"
            "  | || '_ ` _ \\| '_ \\ / _ \\| '__| __/ _` | '_ \\| __| | |\n"
            "  | || | | | | | |_) | (_) | |  | || (_| | | | | |_  |_|\n"
            " |___|_| |_| |_| .__/ \\___/|_|   \\__\\__,_|_| |_|\\__| (_)\n"
            "               |_|                                     "
        };
        cout << TITLE;
        if(unfinsied_task != 0) cout << "[" << unfinsied_task << "]\n";
        cout << endl;
        for(it = TodoitemList.begin(); it != TodoitemList.end();it++){
            if(it->IsImportant()){
                 cout << "==========================================================================================\n";
                cout << "                                                                                         |\n";
                cout << "ID: " << it->getID() << endl;
                cout << "TASK: ";
                cout << it->getDescription();
                cout << "*\n";
                string isDone = (it->IsCompleted())?"DONE":"NOT DONE";
                cout << "STATUS:" << isDone << endl;
                cout << "DEAD LINE:" << it->getDeadline() << " - " << countHowManyDaysTillDeadline(it->getDeadline())<< endl;
    
                cout << "                                                                                         |\n";
                cout << "==========================================================================================\n";

            }
        }
        cout << "\n";
        cout << "\n";
        cout << "[+]ADD A TASK  ";
        cout << "[M]ARK A TASK\n";
        cout << "[F]ind task by keyword\n";
        cout << "[D]elete task\n";
        cout << "[E]diting task\n";
        cout << "[B]ack\n";
        cout << "Choose your option:";
    }

    void addNewTask(){
        system("cls");
        string Task_input;
        cout << "Write your task here:";
        getline(cin, Task_input);

        Todoitem Data;
        Data.create(Task_input, category);

        addADeadline(Data);
        // ADD DEADLINE
        TodoitemList.push_back(Data);
        list<Todoitem> StoreData;
        Store(StoreData);
        MyDay::addNewTask();
    }

    void markAsDone(){
        MyDay::markAsDone();
    }

    void deleteTask(){
        int ID;
        cout << "ID of the task you want to delete:";
        cin >> ID;
        for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
            if(it->getID() == ID){
                it->setImportant(!it->IsImportant());
                break;
            }
        }
    }
    
    
    void keywordFinding(){
        MyDay::keywordFinding();
    }

    int getStatus(){
        return this->status;
    }

    list<Todoitem> getList(){
        return this->TodoitemList;
    }
    
    void editingTask(){
        cout << "ID of the task you want to edit: ";
        string ID;
        getline(cin, ID);
        system("cls");
        for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
            if(it->getID() == stoi(ID)){
                string newDescription;
                getline(cin,newDescription);
                system("cls");
                Todoitem newData;
                newData.create(newDescription,it->getID(), it->IsCompleted(), it->getCategory(), it->getDeadline());

                addADeadline(newData);
                *it = newData;
                break;
            }
        }
    }

    void backToTheHomePage(){
        this->status = 2;
        unfinsied_task = 0;
    }

    void OPTIONS(){
        getline(cin, MyDayInput);
        if(MyDayInput == "+"){
            addNewTask();
        }
        else if(MyDayInput == "B" || MyDayInput == "b"){
            backToTheHomePage();
        }
        else if(MyDayInput == "M" || MyDayInput == "m"){
            markAsDone();
        }
        else if(MyDayInput == "D" || MyDayInput == "d"){
            deleteTask();
        }
        else if(MyDayInput == "F" || MyDayInput == "f"){
            keywordFinding();
        }
        else if(MyDayInput == "E" || MyDayInput == "e"){
            editingTask();
        }

    }
};
