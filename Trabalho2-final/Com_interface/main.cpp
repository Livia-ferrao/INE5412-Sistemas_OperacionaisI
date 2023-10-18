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
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <num_frames>" << endl;
        return 1;
    }
    int num_frames = stoi(argv[1]);
    vector<int> references;

    int page;
    while (!feof(stdin))
    {
        if (scanf("%d", &page) != 1) {
            printf("Error: Please enter a valid integer.\n");
        }
        references.push_back(page);
    }

    QApplication a(argc, argv);
    MainWindow w(nullptr, num_frames, references);
    w.show();
    w.setFileContent(num_frames, references);
    w.simulateFile();
    return a.exec();
}
