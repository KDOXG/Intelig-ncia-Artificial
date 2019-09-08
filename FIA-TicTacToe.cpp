#include "lib-minimax.cpp"

int main(int argc, char *argv[])
{
    Minimax TicTacToe;
    TicTacToe.criarNodos(9);
    TicTacToe.gerarArvore(cross);
    TicTacToe.fatorMinMax(cross);
    std::cout << "Fator minimax do jogo da velha: " << TicTacToe.getMinmax();
    return 0;
}