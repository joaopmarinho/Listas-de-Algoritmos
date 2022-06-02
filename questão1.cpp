#include <iostream>

using namespace std;

struct node
{

    int pos;
    int val;
    node *next = nullptr;
};

struct queue
{ // tipo fila(nota que a head é um nó sentinela)

    int tam = 0;
    node *head = new node[1];
    node *tail = head;
};

struct resto
{ // esse tipo é pra usar na função pop só pra salvar o valor excluido e a nova fila depois de excluir

    int pos;
    int val;
    queue fila;
};

struct stack
{ // tipo pilha criado com no sentinela

    node *top = new node[1];
    int tam = 0;
};

struct resto_stk
{ // esse tipo é pra usar na função desempilhar só pra salvar o valor excluido e a nova pilha depois de excluir

    int pos;
    int val;
    stack pilha;
};

queue enqueue(int pos, int val, queue A)
{ // enfilera um valor

    queue fila;
    fila = A;
    node *novo = new node[1];
    novo->pos = pos;
    novo->val = val;
    fila.tail->next = novo;
    fila.tail = novo;
    fila.tam += 1;
    return fila;
}
resto pop(queue A)
{ // exclue um valor

    int val;
    node *point;
    resto excl;

    if (A.tam == 1)
    {

        point = A.head->next;
        A.head->next = point->next;
        point->next = nullptr;
        excl.val = point->val;
        excl.pos = point->pos;
        delete[] point;
        A.tail = A.head;
        A.tam -= 1;
    }
    else
    {
        point = A.head->next;
        A.head->next = point->next;
        point->next = nullptr;
        excl.val = point->val;
        excl.pos = point->pos;
        delete[] point;
        A.tam -= 1;
    }
    excl.fila = A;

    return excl;
}
stack empilhar(int pos, int val, stack A)
{

    node *novo = new node[1];
    novo->val = val;
    novo->pos = pos;
    novo->next = A.top->next;
    A.top->next = novo;
    A.tam--;
    return A;
}
resto_stk desempilhar(stack A)
{

    resto_stk excl;
    node *point;
    point = A.top->next;
    A.top->next = point->next;
    point->next = nullptr;
    excl.val = point->val;
    excl.pos = point->pos;
    delete[] point;
    A.tam--;
    excl.pilha = A;

    return excl;
}
node *buscar(queue A, int pos_fila)
{ // busca um elemento na fila

    int i = 0;
    node *point = A.head;

    for (i = 0; i < pos_fila; i++)
    {

        point = point->next;
    }

    return point;
}
queue circularizar(int pos, int val, queue A)
{

    node *novo = new node[1];
    novo->val = val;
    novo->pos = pos;
    if (A.tam == 0)
    {

        novo->next = novo;
        A.head->next = novo;
        A.tail = novo;
        A.tam++;
    }
    else
    {
        novo->next = A.head->next;
        A.tail->next = novo;
        A.tam++;
    }
    A.head->next = novo;
    A.tail = A.tail;
    return A;
}
resto excluir_cir(queue A)
{

    node *point = new node[1];
    resto excl;

    if (A.tam != 1)
    {

        point = A.head->next;
        A.head->next = point->next;
        A.tail->next = point->next;
        excl.pos = point->pos;
        excl.val = point->val;
        A.tam--;
        excl.fila = A;
        point->next = nullptr;
        delete[] point;
    }
    else
    {
        point = A.head->next;
        point->next = nullptr;
        A.head->next = nullptr;
        A.tail = A.head;
        A.tam--;
        excl.pos = point->pos;
        excl.val = point->val;
        excl.fila = A;
        delete[] point;
    }

    return excl;
}
queue girar(queue A)
{

    node *point;
    if (A.tam > 1)
    {

        point = A.tail;
        A.tail = buscar(A, A.tam - 1);
        A.head->next = point;
    }

    return A;
}

int main()
{

    int ciclo = 0, X, T;
    string input = "";
    stack pilha;
    queue fila, circular;

    cin >> ciclo;

    while (input != "END")
    {

        cin >> input;

        if (input == "LOAD")
        {

            cin >> X >> T;
            fila = enqueue(X, T, fila);
        }

        if (input == "UNLD")
        {

            resto_stk pronto = desempilhar(pilha);
            pilha = pronto.pilha;
            cout << "UNLD " << pronto.pos << endl;
        }

        if (input == "PROC")
        {

            if (circular.tam > 0)
            {

                if (circular.head->next->val == 0)
                {

                    resto pronto = excluir_cir(circular);
                    circular = pronto.fila;
                    pilha = empilhar(pronto.pos, pronto.val, pilha);
                }
            }
            if (fila.tam > 0)
            {

                resto pronto_fila = pop(fila);

                fila = pronto_fila.fila;
                circular = circularizar(pronto_fila.pos, pronto_fila.val, circular);
            }
            if (circular.tam > 0)
            {

                circular.tail->val -= ciclo;

                if (circular.tail->val < 0)
                {

                    circular.tail->val = 0;
                }

                cout << "PROC " << circular.tail->pos << " " << circular.tail->val << endl;
                circular = girar(circular);
            }
            else
            {

                cout << "PROC -1 -1" << endl;
            }
        }
    }
    return 0;
}