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
bool skiptoend=false;
Card* cardAt(int, Card * );
string faces[13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
string ranks[4]={"C","S","H","D"};
int size = 52;
class Player {
    private:
        
        
    public:
        Card *Top=NULL;
        int deck=0;
        string name="COM";
        Player(){
            fillDeck();
        }
        void setName(string name){
            this->name = name;
        }
        void fillDeck(){
            srand(time(0));
            for (int i=0;i<26;i++){
                if (size==1){
                    fullDeck->next = NULL;
                    insert(fullDeck);
                }
                else {
                int n = rand()%(size-1);
                Card* temp = cardAt(n,fullDeck);
                temp->next = NULL;
                insert(temp);
                size--;
                }
            }
        }
        int deckSize(){
            return deck;
        }
        void updDeckSize(){
            Card *temp = Top;
            int c=0;
            while (temp!=NULL) {
                temp=temp->next;
                c++;
            }
            deck = c;
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
            deck++;
        }
        void remove(){
            Top = Top->next;
            deck--;
        }
        Card *topCard(){
            if (Top==NULL) return NULL;
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
int checkWinner(Player *, Player *);
void addCard(Card **,int , string , string );
void addCard(Card *, Card *);
int Play(Player *one, Player *two){
    switch (checkWinner(one,two)) {
        case 1:
            cout<<two->name<<" is out of Cards!"<<endl;
            cout<<one->name<<" Wins the Game!";
            return 1;
            break;
        case 2:
            cout<<one->name<<" is out of Cards!"<<endl;
            cout<<two->name<<" Wins the Game!";
            return 2;
            break;
        default:
            break;
    }
    billboard(one,two);
    Card *first = NULL;
    Card *second = NULL;
    first = one->topCard();
    second = two->topCard();

    int res = compareCards(first,second);
    switch (res)
    {
    case 0:
        first->next = second;
        second->next = NULL;
        one->insert(first);
        cout<<one->name<<" Wins this round!"<<endl;
        break;
    case 1:
        second->next = first;
        first->next = NULL;
        two->insert(second);
        cout<<two->name<<" Wins this round!"<<endl;
        break;
    case 2:
        cout<<"WAR!!!!"<<endl;
        
        switch (War(first,second,one,two))
        {
        case 0:
            one->insert(first);
            one->updDeckSize();
            two->updDeckSize();
            cout<<one->name<<" Wins this War round!"<<endl;
            break;
        case 1:
            two->insert(second);
            one->updDeckSize();
            two->updDeckSize();
            cout<<two->name<<" Wins this War round!"<<endl;
            break;
        case 3:
            cout<<two->name<<" is out of Cards!"<<endl;
            cout<<one->name<<" Wins this War round!"<<endl;
            cout<<one->name<<" Wins the Game!";
            return 1;
            break;
        case 4:
            cout<<one->name<<" is out of Cards!"<<endl;
            cout<<two->name<<" Wins this War round!"<<endl;
            cout<<two->name<<" Wins the Game!";
            return 2;
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
    return -1;
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
    if (first==NULL) return 4;
    else if (second ==NULL) return 3;
    int fir = (first->num)%13;
    int sec = (second->num)%13;
    if (fir ==sec){
        return 2;
    } else if (fir > sec){
        return 0;
    } else return 1;

}
int checkWinner(Player *one, Player *two) {
    if (one->Top == NULL) {
        return 2;
    } else if (two->Top==NULL){
        return 1;
    } 
    return -1;
}
int War(Card *first, Card *second,Player *one, Player *two){
    int n=4;
    
    if (skiptoend==false) {
        one->updDeckSize();
        two->updDeckSize();
        cout<<one->name<<" has "<<one->deck<<" cards left while ";
        cout<<two->name<<" has "<<two->deck<<" cards left\n";
        int bet;    
        do {
        cout<<"Enter the amount of cards you want to bet that is less than ";
        bet = (one->deck<two->deck)?one->deck:two->deck;
        cout<<bet<<": "<<endl;
        cin>>n;
        }while (n<1 || n>=bet);
    }
    Card *tempone = first;
    Card *temptwo = second;
    Card *lastone=NULL;
    Card *lasttwo =NULL;
    for (int i=0;i<n;i++){
        tempone = one->topCard();
        temptwo = two->topCard();
    }
    lastone = tempone;
    lasttwo = temptwo;
    switch (checkWinner(one,two)) {
        case 1:
            return 3;
            break;
        case 2:
            return 4;
            break;
        default:
            break;
    }
    billboard(lastone,lasttwo);
    int res = compareCards(lastone,lasttwo);
    
    switch (res)
    {
    case 0:
        lastone->next = second;
        if(lasttwo==NULL)
            return 3;
        lasttwo->next = NULL;
        break;
    case 1:
        lasttwo->next = first;
        if(lastone==NULL)
            return 4;
        lastone->next = NULL;
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
    string pname;
    cout<<"Enter Player Name: ";
    getline(cin,pname);
    one->setName(pname);
    char inp;
    do {
        cout<<"Do you want to skip to the end? y/n\n";
        cin>>inp;
    }while (inp!='y' && inp!='n');
    switch (inp)
    {
    case 'y':
        skiptoend = true;
        break;
    
    default:
        break;
    }
    // one->fillDeck();
    // two->fillDeck();
    int result;
    while(result!=2 && result!=1)
    {
        result = Play(one,two);
    }
    
    // cout<<one->deckSize();
    return 0;
} 
