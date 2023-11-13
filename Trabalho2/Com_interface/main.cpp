#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
      // Verifica se o número correto de argumentos foi fornecido
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <num_frames>" << endl;
        return 1;
    }
    // Converte o argumento de linha de comando para o número de quadros de página
    int num_frames = stoi(argv[1]);
    // Cria um vetor para armazenar as referências às páginas de memória
    vector<int> references;
    // Página
    int page;
    // Lê sequências de números da entrada padrão até atingir o final do arquivo
    while (!feof(stdin))
    {
        // Tenta ler um número inteiro da entrada padrão
        if (scanf("%d", &page) != 1) {
            printf("Erro: Por favor, insira um número inteiro válido.\n");
        }
        // Adiciona a página lida ao vetor de referências
        references.push_back(page);
    }

    // Inicializa o aplicativo Qt
    QApplication a(argc, argv);
    // Cria uma instância da janela principal passando o número de quadros e as referências
    MainWindow w(nullptr, num_frames, references);
    // Exibe a janela principal
    w.show();
    // Configura o conteúdo do arquivo na janela principal
    w.setFileContent(num_frames, references);
    // Simula o conteúdo do arquivo na janela principal
    w.simulateFile();
    // Executa o loop de eventos do aplicativo Qt
    return a.exec();
}
