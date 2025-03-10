#include <string>
#include <list>
#include <vector>
#include "ITEM.cpp"
#include "STORE.cpp"
#include <algorithm>
#include "Calendar.cpp"
#include "KMP.cpp"
#pragma once

using namespace std;

class MyDay : public StoreData, public Calendar{
private:
    list <Todoitem> TodoitemList;
    list <Todoitem>::iterator it; 
    string MyDayInput;
    int status;
    int unfinsied_task = 0;
    KMP findKeyWord;
public:
    const string category = "Daily";
    MyDay(){
        this->status = 1;
    }
    MyDay(list <Todoitem> TodoitemList){
        this->TodoitemList = TodoitemList;
        this->status = 1;
    }
    void setStatus(int status){
        this->status = status;
    }

    void Started(){
        ReadData(TodoitemList);
    }

    void setList(list <Todoitem> TodoItemList){
        this->TodoitemList = TodoItemList;
    }

    void init(){
        unfinsied_task = 0;
        for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
            if(!it->IsCompleted()){
                ++unfinsied_task;
            }
        }
    }

    void saveInSpecialCase(){
        ReadData(TodoitemList);
        Store(TodoitemList);
    }

    void printMENU(){
        system("cls");
        ReadData(TodoitemList);
        init();
        string TITLE = {
                ".___  ___. ____    ____     _______       ___      ____    ____   \n"
                "|   \\/   | \\   \\  /   /    |       \\     /   \\     \\   \\  /   /        \n"
                "|  \\  /  |  \\   \\/   /     |  .--.  |   /  ^  \\     \\   \\/   /          \n"
                "|  |\\/|  |   \\_    _/      |  |  |  |  /  /_\\  \\     \\_    _/            \n"
                "|  |  |  |     |  |        |  '--'  | /  _____  \\      |  |                  \n"
                "|__|  |__|     |__|        |_______/ /__/     \\__\\     |__|"
        };
        cout << TITLE;
        if(unfinsied_task != 0) cout << "[" << unfinsied_task<< "]\n";
        cout << endl;


        for(it = TodoitemList.begin(); it != TodoitemList.end();it++){
            if(!it->IsCompleted()){
                cout << "==========================================================================================\n";
                cout << "                                                                                         |\n";
                cout << "ID: " << it->getID() << endl;
                cout << "TASK: ";
                cout << it->getDescription() << endl;
                if(it->IsImportant()) cout << "*\n";
                string isDone = (it->IsCompleted())?"DONE":"NOT DONE";
                cout << "STATUS:" << isDone << endl;
                cout << "DEAD LINE:" << it->getDeadline() << " - " << countHowManyDaysTillDeadline(it->getDeadline())<< endl;
    
                cout << "                                                                                         |\n";
                cout << "==========================================================================================\n";
            }
        }

        for(it = TodoitemList.begin(); it != TodoitemList.end();it++){
            if(it->IsCompleted()){
                cout << "==========================================================================================\n";
                cout << "                                                                                         |\n";
                cout << "ID: " << it->getID() << endl;
                cout << "TASK: ";
                cout << it->getDescription() << ((it->IsImportant())?"*":"")<< endl;
                string isDone = (it->IsCompleted())?"DONE":"NOT DONE";
                cout << "STATUS:" << isDone << endl;
                cout << "DEAD LINE:" << it->getDeadline() << " - " << countHowManyDaysTillDeadline(it->getDeadline())<< endl;
    
                cout << "                                                                                         |\n";
                cout << "==========================================================================================\n";

            }
        }
        cout << "\n";
        cout << "\n";
        cout << "[+]ADD A TASK\n";
        cout << "[M]ARK A TASK\n";
        cout << "[F]ind task by keyword\n";
        cout << "[D]elete task\n";
        cout << "[E]diting task\n";
        cout << "Mark as [I]mportant\n";
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
        Data.setImportant(0);
        // ADD DEADLINE
        TodoitemList.push_back(Data);
        list<Todoitem> StoreData;
        Store(StoreData);
    }

    void addADeadline(Todoitem &Data){
        cout << "Do you want to set a deadline to this task?(Yes or No):";
        string Deadline_choice;
        cin >> Deadline_choice;
        if(Deadline_choice == "Yes" || Deadline_choice == "y" || Deadline_choice == "yes" 
                || Deadline_choice == "YES" || Deadline_choice == "Y"){
            setDeadline(Data);
        }
    }
    
    void setDeadline(Todoitem &Data){
        string day,month,year;
        cout << "Set deadline\n";
        cout << "On day:";cin >> day;
        cout << "On month:";cin >> month;
        cout << "On year:";cin >> year;
        string date = day + "/" + month + "/" + year; 
        Data.setDeadline(date);
    }

    void markAsDone(){
        system("cls");
        cout << "ID OF THE TASK YOU WANT TO CHECK:";
        int id_to_mark;
        cin >> id_to_mark;
        for(it = TodoitemList.begin(); it != TodoitemList.end();it++){
            if(it->getID() == id_to_mark && it->getCategory() == category){
                bool sta = it->IsCompleted();
                it->mark(!sta);
            }
        }           
    }

    void deleteTask(){
        system("cls");
        cout << "ID of the task you want to delete: ";
        int id_to_delete;
        cin >> id_to_delete;
        for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
            if(it->getID() == id_to_delete){
                TodoitemList.erase(it);
                break;
            }
        }
    }

    void keywordFinding(){
        system("cls");
        cout << "What you want to find? :";
        string keyword;
        cin >> keyword;
        system("cls");
        for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
            string temp = it->getDescription();
            if(findKeyWord.find(temp, keyword)){
                cout << it->getID() <<  "|" << it->getDescription() << endl;
            }
        }
        system("pause");
    }

    void backToTheHomePage(){
        this->status = 2;
        unfinsied_task = 0;
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

    void markAsImportant(){
        int ID;
        cout << "ID of the task you want to mark:";
        cin >> ID;
        for(it = TodoitemList.begin(); it != TodoitemList.end();++it){
            if(it->getID() == ID){
                it->setImportant(!it->IsImportant());
                break;
            }
        }
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
        else if(MyDayInput == "I" || MyDayInput == "i"){
            markAsImportant();
        }
    }

    list<Todoitem> getList(){
        return this->TodoitemList;
    }
    
    int getStatus(){
        return this->status;
    }

};
