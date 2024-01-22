#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "source.h"
#include "worker.h"

#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fillSourcesButton_clicked()
{
    const QString path = QFileDialog::getOpenFileName(this, "Otvori JSON izvora", "../rokSimulacija", "JSON files(*.json)");
    QFile file(path);

    qDeleteAll(m_sources);
    ui->sourcesQListWidget->clear();
    ui->lineEditCurrentVolume->clear();

    if(file.open(QFile::ReadOnly)){
        QTextStream stream(&file);

        QJsonDocument jsonDocument = QJsonDocument::fromJson(stream.readAll().toUtf8());
        QJsonObject jsonObject = jsonDocument.object();

        QJsonArray objectArray = jsonObject["sources"].toArray();

        for(const auto& sourceValue : objectArray){
            Source *source = new Source;
            source->fromQVariant(sourceValue.toVariant());
            m_sources.push_back(source);
        }

        unsigned long long sum = 0;
        for(auto& source : m_sources){
            ui->sourcesQListWidget->addItem(source->toQString());
            sum += source->Volume();
        }
        file.close();

        ui->lineEditCurrentVolume->setText(QString::number(sum));

    }else{
        return;
    }
}


void MainWindow::on_pushButtonBeginTransfer_clicked()
{
    ui->lineEditCurrentTankSize->setText("0");
    ui->lineEditLossSize->setText("0");

    for(auto& source : m_sources){
        auto thread = new Worker(m_sources, &m_mutex);
        connect(thread, &Worker::done, this, &MainWindow::on_workerDone);
        thread->start();
    }
}

void MainWindow::on_workerDone(unsigned int index, unsigned int volume)
{
    QMutexLocker lock(&m_mutex);
    ui->sourcesQListWidget->item(index)->setText(m_sources[index]->toQString());
    auto total = ui->lineEditTankSize->text().toUInt();
    qDebug() << total;
    auto current = ui->lineEditCurrentTankSize->text().toUInt();
    qDebug() << current;
    if(current + volume <= total){
        ui->lineEditCurrentTankSize->setText(QString::number(current+volume));
    }else{
        auto loss = ui->lineEditLossSize->text().toUInt();
        ui->lineEditCurrentTankSize->setText(QString::number(total));
        loss += current + volume - total;
        ui -> lineEditLossSize->setText(QString::number(loss));
    }
}

