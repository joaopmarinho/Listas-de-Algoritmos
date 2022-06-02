#include <bits/stdc++.h>
using namespace std;
//p0 = x0, x0 -> pf = xf, xf
//E(Pi,Pj) = (Xj-Xi)^2 + (Yj-Yi)^2.

struct location{
    int x = 0;
    int y = 0;
    int moeda = 0;
};

struct plataforma{
    int aresta;
    double peso;
};

void bellmanFord(vector <plataforma> g[], int pos, int numLinhas){ // pos = 0 na main
    int percursor[numLinhas], caminho[numLinhas], saver = 0;
    double k[numLinhas], k1[numLinhas]; // k e k-1
    for(int j=0; j< numLinhas; j++){
        percursor[j] = -1;
        k1[j] = INT_MAX;
    }
    k1[pos] = 0;
    for(int j=1;j<numLinhas; j++){
        for(int l=0; l< numLinhas; l++){
        k[l] = k1[l];
        }
        for(int l=0; l< numLinhas; l++){
            for(int e=0; e< g[l].size(); e++){
                int aresta = g[l][e].aresta;
                double peso = g[l][e].peso;
                if((k[l]+peso) < k1[aresta]){
                    k1[aresta] =k[l]+peso;
                    percursor[aresta] = l;
                }
            }
        }
    }

    for(int l=0; l< numLinhas; l++){
        for(int e=0; e< g[l].size(); e++){
            int aresta = g[l][e].aresta;
            double peso = g[l][e].peso;
            if((k1[l]+peso) < k[aresta]){
               cout << "LOOP";
               return;
            }
        }
    }

    cout << k1[numLinhas-1] << " ";
    for(int j=numLinhas-1; j<numLinhas ;){
        caminho[saver] = j;
        j = percursor[j];
        saver++;
        if(j==0){
            saver--;
            break;
        }
    }
    cout << "0" << " ";
    while(saver > -1){
        if(saver == 0){
            cout << caminho[saver];   
            saver--; 
        }
        else{
        cout << caminho[saver] << " " ;
            saver--; 
        }
    }
}

double energia(location ptr[], int indice1, int indice2){
    double energizado = pow((ptr[indice2].x - ptr[indice1].x), 2) + pow((ptr[indice2].y - ptr[indice1].y), 2); 
    if(ptr[indice2].moeda == 1){
        energizado = energizado * -1;
    }
    return energizado;
}

int main(){
    int casosTeste, numLinhas, qtdMoedas, moeda, vizinhos, valor = 0, teste1;

    cin >> casosTeste;
    
    while(casosTeste){
        cin >> numLinhas; 
        location ptr[numLinhas];
        vector <plataforma> g[numLinhas];
        for(int i=0; i<numLinhas; i++){
        cin >> ptr[i].x >> ptr[i].y;
        }
        cin >> qtdMoedas;
        int m =0;
        while(m< qtdMoedas){
            cin >> moeda;
            ptr[moeda].moeda = 1;
            m++;
        }
        for(int i=0; i<numLinhas; i++){
            cin >> teste1;
            for(int cont = 0; cont < teste1; cont++){
                cin >> vizinhos;
                plataforma temp;
                temp.aresta = vizinhos;
                temp.peso = energia(ptr, i, vizinhos);
                g[i].push_back(temp);
            }
        }
        bellmanFord(g, 0, numLinhas);
        casosTeste--;
        cout << "\n";    
    }
}