#include <iostream>
#include <vector>
#include <list>
//#include <lib.h>  Colocar todas as funcoes e definicoes neste header
#define cross 1
#define circle 2

using namespace std;

struct node
{
    vector<short> map;
    short minmax;
    list<node> nodes;
};

short invertMinmax(short m);
short JogoDaVelha(vector<short> map);
void insertNode(node *no, vector<short> m, short n, short mm);

short invertMinmax(short m)
{
    if (m == cross)
        return circle;
    else
        return cross;
}

short JogoDaVelha(vector<short> map, short m)
{
    if (map[0] == map[1] == map[2])
        return map[0];
    if (map[3] == map[4] == map[5])
        return map[3];
    if (map[6] == map[7] == map[8])
        return map[6];
    if (map[0] == map[3] == map[6])
        return map[0];
    if (map[1] == map[4] == map[7])
        return map[1];
    if (map[2] == map[5] == map[8])
        return map[2];
    if (map[0] == map[4] == map[8])
        return map[0];
    if (map[3] == map[5] == map[7])
        return map[3];
    return 0;
}

class Minimax
{
    private:
        void insertNode(node *no, vector<short> m, short n, short mm);
        node head;

    public:
        Minimax()
        {
            head.map = vector<short>(9);
            head.minmax = 0;
            head.nodes = list<node>();
        }
        short getMinmax()
        {
            return head.minmax;
        }
        void criarArvore();
        void fatorMinMax();
};

void Minimax::criarArvore()
{
    insertNode(&head,head.map,9,cross);
    //O que fazer aqui...?
}

void insertNode(node *no, vector<short> m, short n, short mm)
{//Preciso arrumar alguns erros de sintaxe; percorrer a arvore em pos ordem?
//Ignorar o comentario acima. Parece que a logica funciona.
    if (n == 0)
    {
        no->minmax = JogoDaVelha(m);
    }
    else
    {
        short k;
        vector<short> o(m);
        vector<short> p(m);
        list<node>::iterator i = no->nodes.begin();
        for (short j = 0; j < n; i++, j++)
        {
            for (k = 0; k < p.size(); k++)
                if (p[k] == 0)
                    break;
            if (k == p.size())
                break;
            p[k] = mm;
            o[k] = mm;
            insertNode(*i,o,n-1,invertMinmax(mm));
            o = m;
        }
        no->minmax = mm;
    }
}

void Minimax::fatorMinMax()
{
    //E aqui que o negocio fica divertido~
    //Lembrete: o que define um no folha e no.nodes.size() ser 0
}

int main(int argc, char *argv[])
{
    Minimax TicTacToe();
    TicTacToe.criarArvore();
    TicTacToe.fatorMinmax();
    cout << "Fator minimax do jogo da velha: " << TicTacToe.getMinmax();
    return 0;
}
