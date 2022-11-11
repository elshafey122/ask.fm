#include <iostream>
#include<vector>
using namespace std;

int index=0;
int pos=0;
struct username
{
    int id;
    string name,email,password,username;
    bool anymous_que;
};

struct question
{
    int qid,askerid,askedid;
	string question_text, answer_text;
};

vector<struct username>users(100);
vector<question>questions(100);
void first_menu();
void sign_up(vector<username>&users);
void second_menu(int dd);


void sign_up()
{
    string name,password,usename,email;
    bool anymous_question;

    cout<<"enter user name.(no space): ";
    cin>>usename;
    users[index].username=usename;
    cout<<"enter password: ";
    cin>>password;
    users[index].password=password;
    cout<<"enter name.(no space): ";
    cin>>name;
    users[index].name=name;
    cout<<"enter email :";
    cin>>email;
    users[index].email=email;
    cout<<"allow anymous question: ";
    cin>>anymous_question;
    users[index].anymous_que=anymous_question;
    users[index].id=index+1;
    index++;
}

void answer_question(int pers_id)
{
    int d;
    cout<<"enter question id or -1 to cancel :";
    cin>>d;
    if(d!=-1)
    {
        int flag=0;
        for(int i=0;i<pos;i++)
        {
            if(questions[i].qid==d)
            {
                string answer;
                cout<<"enter answer: ";
                cin>>answer;
                questions[i].answer_text=answer;
                flag=1;
            }
        }
        if(flag==0)
        {
            cout<<"invalid question id try again \n";
            answer_question(pers_id);
        }
    }
    else
    {
        second_menu(pers_id);
    }
}

void delete_question(int per_id)
{
    int in;
    cout<<"enter question id or -1 :";
    cin>>in;
    if(in!=-1)
    {
        for(int i=0;i<pos;i++)
        {
             if(questions[i].qid==in)
             {
                 questions[i].qid=-1;
             }
        }
    }
    else
    {
        second_menu(per_id);
    }
}

void ask_question(int asker_id)
{
    string q;
   cout<<"enter user id or -1 to cancel :";
   int input;
   cin>>input;
   if(input!=-1)
   {
       for(int i=0;i<index;i++)
       {
           if(users[i].id==input)
           {
               if(users[i].anymous_que==0)
               {
                   cout<<"anonymous questions are not allowed for this user";
               }
               cout<<"enter question id or -1 to cancel :";
               int _qid;
               cin>>_qid;
               if(_qid==-1)
               {
                   first_menu();
               }
               else
               {
                   questions[pos].qid=_qid;
                   questions[pos].askerid=asker_id;
                   questions[pos].askedid=input;
                   cout<<"enter question text :";
                   cin>>q;
                   questions[pos].question_text=q;
                   pos++;
               }
           }
       }
   }
   else
   {
       second_menu(asker_id);
   }

}

void login()
{
    string username,password;
    cout<<"enter user name & password :";
    cin>>username>>password;
    for(int i=0;i<index;i++)
    {
        if(users[i].username==username&&users[i].password==password)
        {
            second_menu(users[i].id);
            cout<<users[i].id;
        }
    }
    cout<<"you are not a user \n";
    first_menu();
}

void list_system_users()
{
    for(int i=0;i<index;i++)
    {
        cout<<users[i].id<<" "<<users[i].username<<endl;
    }
}

void print_question_from_me(int person)
{
    for(int i=0;i<pos;i++)
    {
        if(questions[i].askerid==person && questions[i].qid!=-1)
        {
            cout<<"question id "<<"("<<questions[i].qid<<") "<<"to user id ("<<questions[i].askedid<<") "<<"\t";
            cout<<"question is :"<<questions[i].question_text<<endl;
            cout<<"answer is :"<<questions[i].answer_text<<endl;
        }
    }
}

void print_question_to_me(int person)
{
    for(int i=0;i<pos;i++)
    {
        if(questions[i].askedid==person && questions[i].qid!=-1)
        {
            cout<<"question id"<<" ("<<questions[i].qid<<") from user id ("<<questions[i].askerid<<") \t";
            cout<<"question is :"<<questions[i].question_text<<endl;
            cout<<"answer is :"<<questions[i].answer_text<<endl;
        }
    }
}

void feed()
{
    for(int i=0;i<pos;i++)
    {
        if(questions[i].qid!=-1)
        {
            cout<<"question id"<<" ("<<questions[i].qid<<") "<<"from user id ("<<questions[i].askerid<<
            ") to user id ("<<questions[i].askedid<<") \t";
            cout<<"question is :"<<questions[i].question_text<<endl;
            cout<<"answer is :"<<questions[i].answer_text<<endl;
        }
    }
}

void second_menu(int person)
{
    while(true)
    {
        int choice;
        cout<<"MENU\n";
        cout<<"\t\t 1)print question to me\n";
        cout<<"\t\t 2)print question from me\n";
        cout<<"\t\t 3)answer question\n";
        cout<<"\t\t 4)delete question\n";
        cout<<"\t\t 5)ask question\n";
        cout<<"\t\t 6)list system users\n";
        cout<<"\t\t 7)feed\n";
        cout<<"\t\t 8)logout\n";
        cout<<"enter choice: ";
        cin>>choice;
        if(choice<1||choice>8)
        {
            cout<<"invalid input try again";
            continue;
        }
        else
        {
            if(choice==1)
            {
                print_question_to_me(person);
            }
            else if(choice==2)
            {
                print_question_from_me(person);
            }
            else if(choice==3)
            {
                 answer_question(person);
            }
            else if(choice==4)
            {
                delete_question(person);
            }
            else if(choice==5)
            {
                ask_question(person);
            }
            else if(choice==6)
            {
                list_system_users();
            }
            else if(choice==7)
            {
                feed();
            }
            else if(choice==8)
            {
                first_menu();
            }
        }
    }
}

void first_menu()
{
    while (true)
    {
        int choice;
        cout<<"menu:"<<endl;
        cout<<"       "<<"1:login"<<endl;
        cout<<"       "<<"2:sign up"<<endl;
        cout<<"enter number in range 1 - 2 :"<<endl;
        cin>>choice;
        if(choice==1)
        {
            login();
            break;
        }
        else if(choice==2)
        {
            sign_up();
        }
        else
        {
            "invalid input try again ";
        }
    }
}

void ask_system()
{
    first_menu();
}

int main()
{
    ask_system();
}

