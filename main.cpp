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
Card* cardAt(int, Card * );
string faces[13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
// string ranks[4]={"♣","♠","♥","♦"};
string ranks[4]={"C","S","H","D"};
int size = 52;
class Player {
    private:
        
        
    public:
        Card *Top=NULL;
        string name;
        Player(string name="Abebe"){
            this->name = name;
        }
        void fillDeck(){
            srand(time(0));
            for (int i=0;i<26;i++){
                if (size==1){
                    insert(fullDeck);
                }
                else {
                int n = rand()%(size-1);
                Card* temp = cardAt(n,fullDeck);
                insert(temp);
                size--;
                }
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
            Top = Top->next;
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
int War(Card *, Card *, Player *,Player *);

void addCard(Card **,int , string , string );
void addCard(Card *, Card *);
void Play(Player *one, Player *two){
    billboard(one,two);
    Card *first = NULL;
    Card *second = NULL;
    first = one->topCard();
    second = two->topCard();
    if (first==NULL) {cout<<two->name<<" Wins the Game!";
        return;
    }
    else if (second==NULL){
        cout<<one->name<<" Wins the Game!";
        return;
    }
    // first->next =NULL;
    // second->next = NULL;
    
    int res = compareCards(first,second);
    switch (res)
    {
    case 0:
        first->next = second;
        second->next = NULL;
        one->insert(first);
        one->insert(second);
        cout<<one->name<<" Wins this round!"<<endl;
        break;
    case 1:
        second->next = first;
        first->next = NULL;
        two->insert(second);
        two->insert(first);
        cout<<two->name<<" Wins this round!"<<endl;
        break;
    case 2:
        cout<<"WAR!!!!"<<endl;
        
        switch (War(first,second,one,two))
        {
        case 0:
            one->insert(second);
            cout<<one->name<<" Wins this War round!"<<endl;
            break;
        case 1:
            two->insert(first);
            cout<<two->name<<" Wins this War round!"<<endl;
            break;
        default:
            cout<<"HI";
            break;
        }
        break;
    default:
        cout<<"Hello there";
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
    int fir = (first->num)%13;
    int sec = (second->num)%13;
    if (fir ==sec){
        return 2;
    // } else if (((((first->num)%13)>((second->num)%13)) || ((first->num%13)==0)) && (second->num%13!=0)){
    } else if (fir > sec){
        return 0;
    } else return 1;

}
int War(Card *first, Card *second,Player *one, Player *two){
    Card *tempone = first;
    Card *temptwo = second;
    Card *lastone=NULL;
    Card *lasttwo =NULL;
    for (int i=0;i<4;i++){
        tempone = one->topCard();
        temptwo = two->topCard();
    }
    lastone = tempone;
    lasttwo = temptwo;
    billboard(lastone,lasttwo);
    int res = compareCards(lastone,lasttwo);
    switch (res)
    {
    case 0:
        lasttwo->next = first;
        lastone->next = NULL;
        // while(second!=NULL){
        //     one->insert(second);
        //     second = second->next;
        // }
        // cout<<one->name<<" Wins this War round!"<<endl;
        break;
    case 1:
        lastone->next = second;
        lasttwo->next = NULL;
        // while(first!=NULL){
        //     two->insert(first);
        //     first = first->next;
        // }
        
        // cout<<two->name<<" Wins this War round!"<<endl;
        break;
    case 2:
        res = War(lastone,lasttwo,one,two);
        break;
    default:
        break;
    }
    return res;
}
Card* cardAt(int num, Card *Deck){
    
    for (int i=0; i<num;i++){
        Deck=Deck->next;
    }
    Card *wanted;
    if (Deck->next == NULL) {
        wanted=Deck;
    } else {
        wanted = Deck->next;
        Deck->next=Deck->next->next;
    }
    wanted->next = NULL;
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
     int c=1;
     while(Head->next!=NULL){
            cout<<c<<". "<<Head->face<<" "<<Head->rank<<" "<<Head->num<<endl;
            Head = Head->next;
            c++;
        }
        cout<<c<<". "<<Head->face<<" "<<Head->rank<<" "<<Head->num<<endl;

}
int main(){
    
    for (int i=0;i<4;i++){
        for (int j=0;j<13;j++){
            addCard(&fullDeck,(13*i)+(j),faces[j],ranks[i]);
        }
    }
    Player *one= new Player;
    Player *two = new Player;
    one->name  = "Chala";
    one->fillDeck();
    two->fillDeck();
    
    // billboard(one,two);
    Play(one,two);
    // display(two->Top);
    return 0;
} 
