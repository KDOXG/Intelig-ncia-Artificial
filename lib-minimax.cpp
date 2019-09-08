#include <iostream>
#include <vector>
#define cross 1
#define circle 2
#define byte unsigned char

byte invertMinmax(byte m);
byte JogoDaVelha(std::vector<byte> map);

struct node
{
	std::vector<byte> map;
	byte minmax;
	std::vector<node*> nodes;
};

class Minimax
{
private:
	void alocarNodos(node* no, byte altura);
	void criarArvore(node* no, std::vector<byte> estadoAtual, byte n, byte minmax);
	void valorMinMax(node* no, byte altura, byte minmax);
	node head;

public:
	Minimax()
	{
		head.map = std::vector<byte>(9, 0);
		head.minmax = 3;
		head.nodes = std::vector<node*>(9, NULL);
	}
	std::string getMinmax()
	{
		switch (head.minmax)
		{
		case 0:
			return "Empate";
		case 1:
			return "Cruz";
		case 2:
			return "Circulo";
		default:
			return "UNKNOWN";
		}
	}
	void criarNodos();
	void gerarArvore(byte inicio);
	void fatorMinMax(byte m);
};

byte invertMinmax(byte m)
{
	if (m == cross)
		return circle;
	else
		return cross;
}

byte JogoDaVelha(std::vector<byte> map)
{
	if (map[0] == map[1] && map[0] == map[2] && map[0] != 0)
		return map[0];
	if (map[3] == map[4] && map[3] == map[5] && map[3] != 0)
		return map[3];
	if (map[6] == map[7] && map[6] == map[8] && map[6] != 0)
		return map[6];
	if (map[0] == map[3] && map[0] == map[6] && map[0] != 0)
		return map[0];
	if (map[1] == map[4] && map[1] == map[7] && map[1] != 0)
		return map[1];
	if (map[2] == map[5] && map[2] == map[8] && map[2] != 0)
		return map[2];
	if (map[0] == map[4] && map[0] == map[8] && map[0] != 0)
		return map[0];
	if (map[3] == map[5] && map[3] == map[7] && map[3] != 0)
		return map[3];
	return 0;
}

void Minimax::alocarNodos(node* no, byte altura)
{
	no->map = std::vector<byte>(9, 0);
	no->minmax = 3;
	no->nodes = std::vector<node*>(9, NULL);
	for (byte i = 0; i < altura; i++)
	{
		no->nodes[i] = new node;
		alocarNodos(no->nodes[i], altura - 1);
	}
}

void Minimax::criarNodos()
{
	for (byte i = 0; i < head.nodes.size(); i++)
	{
		head.nodes[i] = new node;
		alocarNodos(head.nodes[i], head.nodes.size() - 1);
	}
}

void Minimax::criarArvore(node* no, std::vector<byte> estadoAtual, byte n, byte minmax)
{
	if (n != 0)
	{
		byte j;
		std::vector<byte> estadoProx(estadoAtual);
		std::vector<byte> estadoAux(estadoAtual);
		for (byte i = 0; i < n; i++)
		{
			for (j = 0; j < estadoAux.size(); j++)
				if (estadoAux[j] == 0)
					break;
			if (j == estadoAux.size())
				break;
			estadoAux[j] = minmax;
			estadoProx[j] = minmax;
			criarArvore(no->nodes[i], estadoProx, n - 1, invertMinmax(minmax));
			estadoProx = estadoAtual;
		}
	}
	no->map = estadoAtual;
	no->minmax = 3;
}

void Minimax::gerarArvore(byte inicio)
{
	for (byte i = 0; i < head.nodes.size(); i++)
		criarArvore(head.nodes[i], head.map, head.nodes.size() - 1, invertMinmax(inicio));
}

void Minimax::valorMinMax(node* no, byte altura, byte minmax)
{
	if (altura == 0)
	{
		no->minmax = JogoDaVelha(no->map);
		return;
	}
	else
	{
		no->minmax = JogoDaVelha(no->map);
		if (no->minmax != 0)
			return;
		for (byte i = 0; i < altura; i++)
		{
			valorMinMax(no->nodes[i], altura - 1, invertMinmax(minmax));
			if (no->nodes[i]->minmax == minmax || no->nodes[i]->minmax == 0)
			{
				no->minmax = no->nodes[i]->minmax;
				return;
			}
			if (i == altura - 1)
			{
				no->minmax = no->nodes[0]->minmax;
				return;
			}
		}
	}

}

void Minimax::fatorMinMax(byte m)
{
	for (byte i = 0; i < head.nodes.size(); i++)
	{
		valorMinMax(head.nodes[i], 9 - 1, invertMinmax(m));
		if (head.nodes[i]->minmax == 0)
			head.minmax = 0;
		if (head.nodes[i]->minmax == m)
		{
			head.minmax = m;
			return;
		}
	}

}
