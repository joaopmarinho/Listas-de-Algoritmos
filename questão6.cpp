#include <bits/stdc++.h>
using namespace std;

void recursive(int price[], int pos, int sum, int numItens, int money, int *total, int min, int *possibilities){
    if(numItens == pos){
        return;
    }
    else if((sum+price[pos])<=money){
        (*total)++;
        if((*total)>= min){
            (*possibilities)++;
        }
        recursive(price, pos+1, sum+price[pos], numItens, money, total, min, possibilities);
        (*total)--;
    }
    recursive(price, pos+1, sum, numItens, money, total, min, possibilities);
}

int main(){
    int cases, trueCase = 0, numItens, smallerQtt, money, possibilities = 0, sum, i, j, totalItens = 0, pos = 0;

    cin >> cases;

    sum = 0;
    while(trueCase < cases){
        cin >> numItens;
        int price[numItens];
        for(i = 0; i< numItens; i++){
            cin >> price[i];
        }
        cin >> smallerQtt >> money;
        if(smallerQtt == 0){
            possibilities = 1;
        }
        recursive(price, pos, sum, numItens, money, &totalItens, smallerQtt, &possibilities);
        cout << "caso " << trueCase << ": " << possibilities << endl;
        totalItens = possibilities = pos = 0;
        trueCase++;
    }
}
