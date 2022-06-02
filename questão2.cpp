#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class musica
{
public:
    int time;
    string name;
    int total;
    int key;
    musica(){
        time = 0;
        total = 0;
        key = 0;
        name = "";
    }
};

int main()
{
    musica *music, search, *aux;
    int tam, i, qtdItens = 0, mark, pos = 0, max;
    cin >> tam;
    string config = "", teste;
    music = (musica*) calloc (tam, sizeof(musica));

    while (config != "END")
    {
        cin >> config;
        if (config == "ADD")
        {
            search.name = "";
            search.key = 0;
            search.total = 0;
            mark = 1;

            if (qtdItens - 1 >= tam / 2)
            {
                aux = (musica*) calloc (tam, sizeof(musica));
                max = 0;
                for (i = 0; i < tam; i++) 
                {
                    if (music[i].time > 0) 
                    {
                        aux[max] = music[i];
                        max++;
                        if(max >= qtdItens){
                            i = tam;
                        }
                    }
                }
                tam = (tam * 2) + 1;
                free(music);
                music = (musica*) calloc (tam, sizeof(musica));
                for (i = 0; i < tam/2; i++)
                {
                    mark = 1;
                    if (aux[i].time != 0) {
                        pos = aux[i].key % tam;
                        while (mark)
                        {
                            if (music[pos].time != 0)
                            {
                                pos = (pos + 1) % tam;
                            }
                            else
                            {
                                music[pos] = aux[i];
                                mark = 0;
                            }
                        }
                    }
                }
                free(aux);
            }

            cin >> search.name >> search.time;
            
            for (i = 0; i < search.name.length(); i++)
            {
                search.key += search.name[i] * i;
            }

            pos = search.key % tam;
            while (mark)
            {
                if (music[pos].time != 0)
                {
                    pos = (pos + 1) % tam;
                }
                else
                {
                    music[pos] = search;
                    cout << music[pos].name << " " << pos << endl;
                    mark = 0;
                }
            }
            qtdItens++;
        }
        if (config == "PLAY")
        {
            cin >> teste;
            pos = 0;
            for (i = 0; i < teste.length(); i++)
            {
                pos += teste[i] * i;
            }
            pos = pos % tam;
            mark = 1;
            while (mark)
            {   
                if (music[pos].name != teste)
                {
                    pos = (pos + 1) % tam;
                }
                else
                {
                    music[pos].total += music[pos].time;
                    cout << music[pos].name << " " << music[pos].total << endl;
                    mark = 0;
                }
            }
        }
        if (config == "TIME")
        {
            cin >> teste;
            pos = 0;
            for (i = 0; i < teste.length(); i++)
            {
                pos += teste[i] * i;
            }
            pos = pos % tam;
            mark = 1;
            while (mark)
            {
                if (music[pos].name != teste)
                {
                    pos = (pos + 1) % tam;
                }
                else
                {
                    cout << music[pos].name << " " << music[pos].total << endl;
                    mark = 0;
                }
            }
        }
    }
    free (music);
    return 0;
}