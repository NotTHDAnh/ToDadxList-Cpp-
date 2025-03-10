#include "MyDay.cpp"
#include "STORE.cpp"
#include "Calendar.cpp"

class Planned : public Calendar, StoreData{
private:
    list<Todoitem> List;
    list<Todoitem>::iterator it;
public: 
    void setList(list<Todoitem> List){
        this->List = List;
    }
    void printTask(Todoitem item){
        cout << "==========================================================================================\n";
        cout << "                                                                                         |\n";
        cout << "ID: " << item.getID() << endl;
        cout << "TASK: ";
        cout << item.getDescription();
        if(item.IsImportant()) cout << "*\n";
        cout << endl;
        string isDone = (item.IsCompleted())?"DONE":"NOT DONE";
        cout << "STATUS:" << isDone << endl;
        cout << "DEAD LINE:" << item.getDeadline() << " - " << countHowManyDaysTillDeadline(item.getDeadline())<< endl;

        cout << "                                                                                         |\n";
        cout << "==========================================================================================\n";
    }
    void print(){
        ReadData(List);
        system("cls");
        string TITLE = {
                "  ____  _                            _ \n"
                " |  _ \\| | __ _ _ __  _ __   ___  __| |\n"
                " | |_) | |/ _` | '_ \\| '_ \\ / _ \\/ _` |\n"
                " |  __/| | (_| | | | | | | |  __/ (_| |\n"
                " |_|   |_|\\__,_|_| |_|_| |_|\\___|\\__,_|\n"
                "                                       \n"
        };
        cout << TITLE;

        string Date[4] = {"Earlier", "Today","Tomorrow","Future"};
        for(int i = 1;i <= 4;++i){
            cout <<"--------------------"<< Date[i - 1] <<"--------------------" << endl;
            for(it = List.begin(); it != List.end();++it){
                if(i == 1){
                    if(Earlier(it->getDeadline())){
                        printTask(*it);
                    }
                }
                else if(i == 2){
                    if(Today(it->getDeadline())){
                        printTask(*it);
                    }
                }
                else if(i == 3){
                    if(Tomorrow(it->getDeadline())){
                        printTask(*it);
                    }
                }
                else if(i == 4){
                    string temp = it->getDeadline();
                    if(!Earlier(temp) && !Today(temp) && !Tomorrow(temp)){
                        printTask(*it);
                    }
                }
            }
        }
        system("pause");
    }
};
