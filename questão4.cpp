#include <iostream>
#include <math.h>
using namespace std;

struct Hospital
{
    int id = 0;
    int initCases = 0;
};

struct Heap
{
    Hospital *n = NULL;
    int size = 0;
    int tam = 0;
    int tamPos = 0;
};

bool bigbig(Hospital first, Hospital second){
    
    if(first.initCases < second.initCases){
        return false;
    }
    else{
        if(first.initCases != second.initCases){
            return true;
        }
        else{
            if(first.id<=second.id)
                return false;
            else
                return true;
        }
    }
}

Heap bubbleDown(int p, Heap H, int *index){
    int left, right, mid;
    Hospital help;
    left = 2*p + 1;
    right = 2*p +2;
    mid = p;
    if(left < H.tam && bigbig(H.n[left], H.n[mid])){
        mid = left;
    }
    if(right < H.tam && bigbig(H.n[right], H.n[mid])){
        mid = right;
    }
    if(mid != p){
        help = H.n[mid];
        H.n[mid] = H.n[p];
        H.n[p] = help;
        index[H.n[mid].id] = mid;
        index[H.n[p].id] = p;
        return bubbleDown(mid, H, index);
    }
    return H;
}

Heap buildHeap(int tam, Heap heap, int *index){
    int cont;
    for(cont= floor(tam/2)-1; cont>=0; cont--){
        bubbleDown(cont, heap, index);
    }
    return heap;
}

Heap bubbleUp(int p, Heap H, int *index){
    int i = p;
    Hospital help;
    while(i>0 && bigbig(H.n[i], H.n[(i-1)/2])){
        help = H.n[i];
        index[H.n[i].id] = (i-1)/2;
        index[H.n[(i-1)/2].id] = i;
        H.n[i] = H.n[(i-1)/2];
        H.n[(i-1)/2] = help;
        i = (i-1)/2;
    }
    return H;
}

int main()
{
    Heap heap;
    int tam, i, soma = 0, cases, id, payment, *index = NULL, useful, casesTest;
    string input = "";
    cin >> tam;

    heap.n = (Hospital *)calloc(tam, sizeof(Hospital));
    index = (int *)calloc(tam, sizeof(int));

    for (i = 0; i < tam; i++)
    {
        cin >> cases;
        soma += cases;
        heap.size++;
        heap.tam++;
        heap.tamPos++;
        index[i] = i;
        heap.n[i].id = i;
        heap.n[i].initCases = cases;
    }
    heap = buildHeap(tam, heap, index);
    // i = 0;
    //             while(i!=heap.size){
    //                 cout << heap.n[i].id << " " << heap.n[i].initCases << endl;
    //                 i++;
    //             }

    while (input != "END")
    {
        cin >> input;
        if (input == "NEW")
        {
            cin >> id >> cases;
            heap.tamPos++;
            index = (int*) realloc(index, heap.tamPos*sizeof(int));
            index[heap.tamPos-1] = id;
            soma += cases;

            if(heap.tam != heap.size){
                heap.n[heap.tam].id = id;
                heap.n[heap.tam].initCases = cases;
                heap.tam++;
                bubbleUp(heap.tam-1, heap, index);            
            }
            else{
                heap.size = heap.size *2;
                heap.n = (Hospital*) realloc(heap.n , sizeof(Hospital) * heap.size);
                heap.n[heap.tam].id = id;
                heap.n[heap.tam].initCases = cases;
                heap.tam++;
                bubbleUp(heap.tam-1, heap, index);
            }
            cout << heap.n[0].id << " " << heap.n[0].initCases << endl;
            // i = 0;
            //     while(i!=heap.tamPos){
            //         cout << heap.n[i].id << " " << heap.n[i].initCases << endl;
            //         i++;
            //     }
        }
        else if (input == "DEL")
        {
            cin >> id;
            soma -= heap.n[index[id]].initCases;
            heap.n[index[id]].initCases = 0;
            bubbleDown(index[id], heap, index);
            if(soma == 0){
                cout << "-1 -1" << endl;
            }
            else
                cout << heap.n[0].id << " " << heap.n[0].initCases << endl;
        }
        else if (input == "IN")
        {
            cin >> id >> cases;
            heap.n[index[id]].initCases += cases;
            soma += cases;
            cout << heap.n[index[id]].initCases << endl;
            bubbleUp(index[id], heap, index);
        }
        else if (input == "OUT")
        {
            cin >> id >> cases;
            heap.n[index[id]].initCases -= cases;
            soma -= cases;
            cout << heap.n[index[id]].initCases << endl;
            bubbleDown(index[id], heap, index);
        }
        else if (input == "PAY")
        {
            cin >> payment;
            int test = payment;      
            while(payment > 0 && heap.n[0].initCases > 0){
                heap.n[0].initCases -= 1;
                bubbleDown(0, heap, index);
                soma -= 1;
                payment--;
            }
            cout << test - payment << endl;
        }
        else{
            if(input == "END"){
                cout << soma << endl;
            }
        }
    }
}