#include "lib-minimax.cpp"

int main(int argc, char* argv[])
{
	Minimax TicTacToe = Minimax();
	TicTacToe.criarNodos();
	TicTacToe.gerarArvore(cross);
	TicTacToe.fatorMinMax(cross);
	std::cout << "Fator minimax do jogo da velha: " << TicTacToe.getMinmax();
	return 0;
}
