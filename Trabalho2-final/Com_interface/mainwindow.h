#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <iostream>
#include <memory>
#include "abstract_paging.h"
#include "memory.h"
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int num_frames = 0, std::vector<int> references = {});
    ~MainWindow();
    void setFileContent(int numFrames, const std::vector<int> &references);
    void simulateFile();
    void print_terminal(int frames);

private slots:
    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<int> references;

    // Memória
    Memory memory;
    // Ponteiro para algoritmo FIFO
    std::unique_ptr<AbstractPaging> pagingFIFO;
    // Ponteiro para algoritmo LRU
    std::unique_ptr<AbstractPaging> pagingLRU;
    // Ponteiro para algoritmo OPT
    std::unique_ptr<AbstractPaging> pagingOPT;
};
#endif // MAINWINDOW_H
