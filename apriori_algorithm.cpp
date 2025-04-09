#include<bits/stdc++.h>

#include<fstream>
#include<string>
#define minimumT 85

using namespace std;

struct pattern
{
    vector<string> item;
    double support;
};

int numOftran ;
vector<string> transaction[3200];
vector<string> itemList;
vector<pattern> C[100],L[100];

//Transaction Print;
void printtransaction(){
for(int i =0; i<numOftran; i++){
    for(int j=0; j<transaction[i].size();j++){
        cout<<transaction[i][j]<<" ";
    }
    cout<<endl;
}
}

//itemList print
void printitemList(){
 for(int i=0; i<itemList.size(); i++){
    cout<<itemList[i]<<" ";
 }
 cout<<endl;
 cout<<"the itemList size is "<<itemList.size();
}

double calculateSupport(string item){
    double sup = 0.0;
 for(int i = 0; i<numOftran; i++){
    for(int j= 0; j< transaction[i].size(); j++){
        if(item == transaction[i][j]){
            sup++;
            break;
        }
    }
 }
 return sup;
}

//main function
int main()
{
fstream newfile;
newfile.open("chess.dat",ios::in);
string tp;

while(getline(newfile, tp)){
    cout<<tp<<endl;

    stringstream check1(tp);
    string intermediate;

    while(getline(check1, intermediate, ' '))
    {

        transaction[numOftran].push_back(intermediate);

        bool flag = false;
        for(int i =0; i <itemList.size(); i++){
            if(itemList[i] == intermediate){
                flag = true;
                break;
            }
        }

        if(!flag)
        {
            itemList.push_back(intermediate);
        }
    }
    numOftran ++;
}

newfile.close();

//sort
sort(itemList.begin(), itemList.end());

//sort transaction
for(int i=0; i<numOftran; i++){
    sort(transaction[i].begin(), transaction[i].end());
}

for(int i =0; i<itemList.size(); i++){

    double sup = calculateSupport(itemList[i]);
    double relativeSupport;
    relativeSupport = (sup/numOftran) * 100;
    cout<<relativeSupport<<endl;
}

printtransaction();
printitemList();

}
