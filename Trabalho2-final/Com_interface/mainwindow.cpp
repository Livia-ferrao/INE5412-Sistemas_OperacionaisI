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
    // Configuração da interface gráfica
    ui->setupUi(this);

    // Inicialização dos objetos de algoritmos de substituição de página
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
    // Obtém o número de quadros a partir da interface gráfica
    int frames = ui->spinBox->value();

    // Limpa os resultados anteriores
    pagingFIFO->clear(frames);
    pagingLRU->clear(frames);
    pagingOPT->clear(frames, references);

    // Divide a entrada do usuário em uma lista de strings
    QStringList stringList = ui->lineEdit->text().split(QRegularExpression("[.,;\\s]+"));

    // Limpa as listas de resultados na interface gráfica
    ui->listWidget_FIFO->clear();
    ui->listWidget_LRU->clear();
    ui->listWidget_OPT->clear();

    for (QString string : stringList) {
        bool isOk = true;
        int page = string.toInt(&isOk);
        if (isOk == false) {
            // Trata erro se a conversão para inteiro falhar
            QMessageBox::critical(this, "Erro", "Erro ao ler a string de referência");
            ui->listWidget_FIFO->clear();
            ui->listWidget_LRU->clear();
            ui->listWidget_OPT->clear();
            return;
        }

        // Atualiza os resultados para cada algoritmo de substituição de página
        QString resultLine = pagingFIFO->update_gui(page);
        ui->listWidget_FIFO->addItem(resultLine);

        resultLine = pagingLRU->update_gui(page);
        ui->listWidget_LRU->addItem(resultLine);

        resultLine = pagingOPT->update_gui(page);
        ui->listWidget_OPT->addItem(resultLine);
    };

    // Atualiza as etiquetas de resultados na interface gráfica
    ui->label_FIFO_result->setText("PF: " + QString::number(pagingFIFO->getPageFaultCount()));
    ui->label_LRU_result->setText("PF: " + QString::number(pagingLRU->getPageFaultCount()));
    ui->label_OPT_result->setText("PF: " + QString::number(pagingOPT->getPageFaultCount()));

    // Imprime informações no terminal
    cout << "\n";
    cout << frames << " quadros" << endl;
    cout << stringList.size() - 1 << " refs" << endl;

    // Imprime a quantidade de faltas de páginas no terminal
    std::cout << "FIFO: " << pagingFIFO->getPageFaultCount() << std::endl;
    std::cout << "LRU: " << pagingLRU->getPageFaultCount() << std::endl;
    std::cout << "OPT: " << pagingOPT->getPageFaultCount() << std::endl;
}

void MainWindow::setFileContent(int numFrames, const std::vector<int> &references)
{
    // Configura o conteúdo do arquivo na interface gráfica
    this->references = references;
    QString text;
    for (int reference : references) {
        text += QString::number(reference) + " ";
    }
    ui->lineEdit->setText(text.trimmed());
    ui->spinBox->setValue(numFrames);
}

void MainWindow::simulateFile()
{
    // Simula o conteúdo do arquivo na interface gráfica
    for (int page : references) {
        QString resultLine = pagingFIFO->update_gui(page);
        ui->listWidget_FIFO->addItem(resultLine);

        resultLine = pagingLRU->update_gui(page);
        ui->listWidget_LRU->addItem(resultLine);

        resultLine = pagingOPT->update_gui(page);
        ui->listWidget_OPT->addItem(resultLine);
    };

    // Atualiza as etiquetas de resultados na interface gráfica
    ui->label_FIFO_result->setText("PF: " + QString::number(pagingFIFO->getPageFaultCount()));
    ui->label_LRU_result->setText("PF: " + QString::number(pagingLRU->getPageFaultCount()));
    ui->label_OPT_result->setText("PF: " + QString::number(pagingOPT->getPageFaultCount()));

    // Imprime informações no terminal
    cout << memory.getNumFrames() << " quadros" << endl;
    cout << references.size() - 1 << " refs" << endl;

    // Imprime a quantidade de faltas de páginas no terminal
    std::cout << "FIFO: " << pagingFIFO->getPageFaultCount() << std::endl;
    std::cout << "LRU: " << pagingLRU->getPageFaultCount() << std::endl;
    std::cout << "OPT: " << pagingOPT->getPageFaultCount() << std::endl;
}

