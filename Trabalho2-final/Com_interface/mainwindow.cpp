#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <memory>
#include <vector>
#include "abstract_paging.h"
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent, int num_frames, std::vector<int> references)
    : QMainWindow(parent), ui(new Ui::MainWindow), memory(num_frames), references(references)
{
    ui->setupUi(this);
    pagingFIFO = std::make_unique<FifoPaging>(memory);
    pagingLRU = std::make_unique<LruPaging>(memory);
    pagingOPT = std::make_unique<OptPaging>(memory, references);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    int frames = ui->spinBox->value();

    pagingFIFO->clear(frames);
    pagingLRU->clear(frames);
    pagingOPT->clear(frames, references);

    QStringList stringList = ui->lineEdit->text().split(QRegularExpression("[.,;\\s]+"));

    ui->listWidget_FIFO->clear();
    ui->listWidget_LRU->clear();
    ui->listWidget_OPT->clear();

    for (QString string : stringList) {
        bool isOk = true;
        int page = string.toInt(&isOk);
        if (isOk == false) {
            QMessageBox::critical(this, "Erro", "Erro ao ler a string de referência");
            ui->listWidget_FIFO->clear();
            ui->listWidget_LRU->clear();
            ui->listWidget_OPT->clear();
            return;
        }

        //FIFO
        QString resultLine = pagingFIFO->update_gui(page);
        ui->listWidget_FIFO->addItem(resultLine);

        // LRU
        resultLine = pagingLRU->update_gui(page);
        ui->listWidget_LRU->addItem(resultLine);

        // OPT (só está lendo 7341 números)
        resultLine = pagingOPT->update_gui(page);
        ui->listWidget_OPT->addItem(resultLine);
    };

    ui->label_FIFO_result->setText("PF: " + QString::number(pagingFIFO->getPageFaultCount()));
    ui->label_LRU_result->setText("PF: " + QString::number(pagingLRU->getPageFaultCount()));
    ui->label_OPT_result->setText("PF: " + QString::number(pagingOPT->getPageFaultCount()));

    // Imprime no terminal
    cout << "\n";
    cout << frames << " quadros" << endl;
    cout << stringList.size() - 1<< " refs" << endl;

    // Quantidade de faltas de páginas
    std::cout << "FIFO: " << pagingFIFO->getPageFaultCount() << std::endl;
    std::cout << "LRU: " << pagingLRU->getPageFaultCount() << std::endl;
    std::cout << "OPT: " << pagingOPT->getPageFaultCount() << std::endl;
}

void MainWindow::setFileContent(int numFrames, const std::vector<int> &references)
{
    this->references = references;
    QString text;
    for (int reference : references) {
        text += QString::number(reference) + " ";
    }
    ui->lineEdit->setText(text.trimmed());
    ui->spinBox->setValue(numFrames);
}

void MainWindow::simulateFile(){
    for (int page: references){
        // FIFO
        QString resultLine = pagingFIFO->update_gui(page);
        ui->listWidget_FIFO->addItem(resultLine);

        // LRU
        resultLine = pagingLRU->update_gui(page);
        ui->listWidget_LRU->addItem(resultLine);

        // OPT
        resultLine = pagingOPT->update_gui(page);
        ui->listWidget_OPT->addItem(resultLine);
    };

    ui->label_FIFO_result->setText("PF: " + QString::number(pagingFIFO->getPageFaultCount()));
    ui->label_LRU_result->setText("PF: " + QString::number(pagingLRU->getPageFaultCount()));
    ui->label_OPT_result->setText("PF: " + QString::number(pagingOPT->getPageFaultCount()));

    // Imprime no terminal
    cout << memory.getNumFrames() << " quadros" << endl;
    cout << references.size() -1 << " refs" << endl;

    // Quantidade de faltas de páginas
    std::cout << "FIFO: " << pagingFIFO->getPageFaultCount() << std::endl;
    std::cout << "LRU: " << pagingLRU->getPageFaultCount() << std::endl;
    std::cout << "OPT: " << pagingOPT->getPageFaultCount() << std::endl;
}
