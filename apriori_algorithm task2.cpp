#include<bits/stdc++.h>

#include<fstream>
#include<string>
#define minimumT 85
#define confiminimumT 99

using namespace std;

struct pattern
{
    vector<string> item;
    double support;
};

int numOftran ;
vector<string> transaction[3200];
vector<string> itemList;
vector<int> bin;
vector<pattern> C[100],L[100] ;

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


double calculateSupport_multiLen(vector<string> str)
{
    double sup = 0.0 ;
    for(int i = 0 ; i < numOftran ; i++){
        int c = 0 ;
        for(int j = 0 ; j < str.size() ; j++){
            for(int k = 0 ; k < transaction[i].size() ; k++){
                if(str[j] == transaction[i][k]){
                    c++ ;

                    break ;
                }
            }
        }
    if(c == str.size())
        sup++ ;
    }
    return sup ;
}



bool isJoinable(vector<string>L_one,vector<string>L_two,int currL)
{
    if(currL==1)return true;


    else
    {
        int c=0;
        for(int i=0; i<currL-1; i++)
        {
            if(L_one[i]==L_two[i])
                c++;
        }
        if(c == currL-1)
        {
            return true;
        }

        else {
            return false;
        }
    }

}

bool isFrequent(vector<string> now, int currL)
{
    for(int i = 0 ; i < L[currL].size() ; i++){
        int c = 0 ;
        for(int j = 0 ; j < L[currL][i].item.size() ; j++){
           if(now[j] == L[currL][i].item[j])
            c++ ;
        }
        if(c == now.size()){
            return true ;
        }
    }
    return false ;
}


bool checkDownwardClosure(vector<string> str , int currL)
{

    for(int i = 0 ; i < str.size() ; i++){
        vector<string> now ;
        for(int j = 0 ; j < str.size() ; j++){
            if(j != i){
                now.push_back(str[j]) ;
            }
        }
        if(!isFrequent(now, currL)){
                return false ;
        }

    }
    return true ;
}


void printFrequent(int l)
{

    for(int i=1; i<=l; i++)
    {
        cout<<endl;
        cout<< i  << "Lenghth Frequent list: "<<endl;
        for(int j=0; j<L[i].size(); j++)
        {
            cout<<"{ ";
            for(int k =0; k<L[i][j].item.size(); k++)
            {

                cout<<L[i][j].item[k]<<" ";
            }
            cout<<"} ";
            cout<<"  the support: ";
            cout<<L[i][j].support<<"  ";
            cout<<endl;

        }
    }

    cout<<endl;
}


int apriori(int currL){
  while(true)
    {
        //last L[] wont be compared to anyone so L[]-1
        for(int i=0; i<L[currL].size()-1; i++)
        {
            for(int j=i+1; j<L[currL].size(); j++)
            {
                if(isJoinable(L[currL][i].item,L[currL][j].item,currL))
                {
                    vector<string>str;
                    for(int k=0; k<L[currL][i].item.size(); k++)
                    {
                        str.push_back(L[currL][i].item[k]);
                    }

                    str.push_back(L[currL][j].item[currL-1]);
                    if(checkDownwardClosure(str,currL))
                    {
                        double sup = calculateSupport_multiLen(str);
                        struct pattern temp;
                        for(int i=0; i<str.size(); i++)
                            temp.item.push_back(str[i]);
                        temp.support = (sup/numOftran)*100;
                        C[currL+1].push_back(temp); //generating next candidate pattern
                    }
                }
            }
        }
        if(C[currL+1].size( ) == 0)
            return currL;
        for(int i=0; i<C[currL+1].size(); i++)
        {
            if(C[currL+1][i].support>=minimumT)
            {
                L[currL+1].push_back(C[currL+1][i]); //Generating next Frequent pattern
            }
        }

        if(L[currL].size( ) == 0)
            return currL;


        currL++;

    }


}

int dectobin(int decimalNumber)
{
    int binaryNumber = 0, base = 1, remainder;


    while (decimalNumber > 0) {
        remainder = decimalNumber % 2;
        binaryNumber = binaryNumber + remainder * base;
        base = base * 10;
        decimalNumber = decimalNumber / 2;
    }

return binaryNumber;
}


double confidencecal(vector<string>s, struct pattern temp, vector<string>re)
{
     double s_support = (calculateSupport_multiLen(s)/numOftran)*100;
     //cout<<"s__supp"<<s_support<<endl;
     double l_support = temp.support;
     //cout<<"supp"<<l_support<<endl;
     double confidence = (l_support/s_support)*100;

     if(confidence > confiminimumT)
     {
         cout<<endl;
     cout<<"{";
     for(int i =0; i< s.size(); i++){
        cout<<s[i]<<" ";
     }
     cout<<"} ";
     cout<<" -->";
     cout<<" {";
      for(int i =0; i< re.size(); i++){
        cout<<re[i]<<" ";
     }
     cout<<"}"<<endl;

     cout<<"confidence ="<<confidence<<"%"<<endl;
     cout<<endl;
     }


}



void subpattern(struct pattern temp)
{
   for( int i=0; i<temp.item.size(); i++){
    cout<<temp.item[i]<<" ";
   }
   cout<<endl;

    int sz=temp.item.size();
    //cout<<"the sz is " <<sz<<endl;
    int subsets=pow(2,sz);

  for(int i =1; i<subsets-1; i++){
    int binary = dectobin(i);
    int div = pow(10,sz-1);

    vector<string>s,re;
    for(int j =0; j<sz; j++){
        int ans= binary/div;
        int rem=binary%div;

        if(ans!=0)
        {
             //cout<<temp.item[j]<<" ";
             s.push_back(temp.item[j]);

        }
        else  re.push_back(temp.item[j]);

        binary = rem;
        div= div/10;
    }
    //cout<<endl;
    confidencecal(s,temp,re);
  }

//cout<<"\n"<<endl;

}




//main function
int main()
{
fstream newfile;
newfile.open("chess_data.dat.txt",ios::in);
string tp;

while(getline(newfile, tp)){
    //cout<<tp<<endl;

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

//sort transaction in dictionary order
for(int i=0; i<numOftran; i++){
    sort(transaction[i].begin(), transaction[i].end());
}

//relative suppport
for(int i =0; i<itemList.size(); i++){

    double sup = calculateSupport(itemList[i]);
    struct pattern temp;
    double relativeSupport;
    temp.item.push_back(itemList[i]);
    temp.support = (sup/numOftran) * 100;
   C[1].push_back(temp);
   // cout<<"For the item "<<itemList[i]<<":-  the relative support is:- "<< relativeSupport <<"%"<<endl;
}

for(int i=0; i<C[1].size(); i++){
    if(C[1][i].support>= minimumT){
        L[1].push_back(C[1][i]);
    }

}
 int currL=1;

 int len = apriori(currL);


 for(int i=2; i<=len; i++){
        for(int j=0; j<L[i].size(); j++){
            subpattern(L[i][j]);
        }
    }

 //printFrequent(len);
//printtransaction();
//printitemList();
//frequent pattern print hw
//doneCheck3
}
