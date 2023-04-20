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
string faces[13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
string ranks[4]={"♣","♠","♥","♦"};
class Player {
    private:
        Card *Top;
        
    public:
        string name;
        Player(string name){
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
            Card* temp = Top;
            remove();
            return temp;
        }
        void displayCards(){
            cout<<Top->face<<" "<<Top->rank<<"\t";
        }
};
void Play(Player *one, Player *two){
    Card *first = one->topCard();
    Card *second = two->topCard();
    one->displayCards();
    cout<<"VS"<<"\t";
    two->displayCards();
    cout<<endl;
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
int compareCards(Card *first, Card*second){
    if (first->num ==second->num){
        return 2;
    } else if (first->num%13>second->num%13 || first->num ==13 && second->num !=13){
        return 0;
    } else return 1;

}
void War(Player *one, Player *two){

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
    // display(fullDeck);
    return 0;
}