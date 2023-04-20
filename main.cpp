#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Card {
    int num;
    string face;
    string rank;
    Card *next;
};
Card *fullDeck=NULL;
Card* cardAt(int );
string faces[13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
string ranks[4]={"♣","♠","♥","♦"};

class Player {
    private:
        Card *Top;
        
    public:
        string name;
        Player(string name="Abebe"){
            this->name = name;
        }
        void fillDeck(){
            srand(time(0));
            for (int i=0;i<26;i++){
                int n = rand()%51;
                Card* temp = cardAt(n);
                insert(temp);
            }
        }
        void insert(Card *card){
            if (Top==NULL){
                    Top = card;
            } else {
                Card *temp = Top;
                while(temp->next!=NULL){
                    temp = temp->next;
                }
                temp->next = card;
                }
        }
        void remove(){
            Card *temp = Top;
            Top = Top->next;
            delete temp;
        }
        Card *topCard(){
            if (Top==NULL) return Top;
            Card* temp = Top;
            remove();
            return temp;
        }
        void displayCards(){
            cout<<Top->face<<" "<<Top->rank<<"\t";
        }

};
void billboard(Player *, Player *);
void billboard(Card *, Card *);
int compareCards(Card *, Card*);
void War(Player *, Player *);

void addCard(Card **,int , string , string );
void addCard(Card *, Card *);
void Play(Player *one, Player *two){
    billboard(one,two);
    Card *first = one->topCard();
    Card *second = two->topCard();
    if (first==NULL) {cout<<two->name<<" Wins the Game!";
        return;
    }
    else if (second==NULL){
        cout<<one->name<<" Wins the Game!";
        return;
    }
    int res = compareCards(first,second);
    switch (res)
    {
    case 0:
        one->insert(first);
        one->insert(second);
        cout<<one->name<<" Wins this round!"<<endl;
        break;
    case 1:
        two->insert(first);
        two->insert(second);
        cout<<two->name<<" Wins this round!"<<endl;
        break;
    case 2:
        War(one,two);
        break;
    default:
        break;
    }
}
void billboard(Player *one, Player *two){
    one->displayCards();
    cout<<"VS"<<"\t";
    two->displayCards();
    cout<<endl;
}
void billboard(Card *first, Card *second){
    cout<<first->face<<" "<<first->rank<<"\t";
    cout<<"VS"<<"\t";
    cout<<second->face<<" "<<second->rank<<"\t";
    cout<<endl;
}
int compareCards(Card *first, Card*second){
    if (first->num ==second->num){
        return 2;
    } else if ((((first->num)%13>(second->num)%13) || (first->num ==13)) && (second->num !=13)){
        return 0;
    } else return 1;

}
void War(Player *one, Player *two){
    Card *tempone=NULL;
    Card *temptwo=NULL;
    Card *lastone=NULL;
    Card *lasttwo =NULL;
    for (int i=0;i<4;i++){
        if (tempone==NULL &&temptwo==NULL){
            tempone = one->topCard();
            temptwo = two->topCard();
        } else {
            lastone = one->topCard();
            lasttwo = two->topCard();
            addCard(tempone,lastone);
            addCard(temptwo,lasttwo);
        }
    }
    billboard(lastone,lasttwo);
    int res = compareCards(lastone,lasttwo);
    switch (res)
    {
    case 0:
        while(temptwo!=NULL){
            one->insert(temptwo);
            temptwo = temptwo->next;
        }
        while(tempone!=NULL){
            one->insert(tempone);
            tempone = tempone->next;
        }
        cout<<one->name<<" Wins this War round!"<<endl;
        break;
    case 1:
        while(tempone!=NULL){
            two->insert(tempone);
            tempone = tempone->next;
        }
        while(temptwo!=NULL){
            two->insert(temptwo);
            temptwo = temptwo->next;
        }
        cout<<two->name<<" Wins this War round!"<<endl;
        break;
    default:
        break;
    }
}
Card* cardAt(int num){
    Card *temp;
    temp = fullDeck;
    for (int i=0; i<num;i++){
        fullDeck=fullDeck->next;
    }
    Card *wanted;
    wanted = fullDeck->next;
    fullDeck->next=fullDeck->next->next;
    fullDeck = temp;
    wanted->next = NULL;
    delete temp;
    return wanted;
}
void addCard(Card **Head,int num, string face, string rank){
    Card *newCard= new Card;
    newCard->num = num;
    newCard->face = face;
    newCard->rank = rank;
    newCard->next = NULL;
    if (*Head==NULL){
        (*Head) = newCard;
    } else {
        Card *temp = *Head;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newCard;
    }
}
void addCard(Card *Head, Card *card){
    while(Head->next!=NULL){
            Head = Head->next;
        }
        Head->next = card;
}
void display(Card *Head){
     while(Head->next!=NULL){
            cout<<Head->face<<endl;
            Head = Head->next;
        }
        cout<<Head->num<<endl;

}
int main(){
    
    for (int i=0;i<4;i++){
        for (int j=0;j<13;j++){
            addCard(&fullDeck,(13*i)+(j+1),faces[j],ranks[i]);
        }
    }
    Player *one = new Player;
    Player *two = new Player;
    one->name  = "Chala";
    Play(one,two);
    // display(fullDeck);
    return 0;
}