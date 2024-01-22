#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "worker.h"

#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

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

void MainWindow::on_buttonLoadCities_clicked()
{
    qDeleteAll(m_cities);
    m_cities.clear();
    ui->listWidgetCities->clear();
    QVector<QString> paths = QFileDialog::getOpenFileNames(this, "Select one or more cities.", "/home/Desktop", "JSON files (*.json)");

    for(auto& path : paths){
        QFile file(path);
        if(file.open(QFile::ReadOnly | QFile::Text)){
            QTextStream stream(file.readAll());
            QJsonDocument jsonDoc = QJsonDocument::fromJson(stream.readAll().toUtf8());
            // QJsonObject jsonObj = jsonDoc.object();
            City* city = new City();
            QVariant variant = jsonDoc.toVariant();
            city->fromQVariant(variant);
            m_cities.push_back(city);
        }
    }

    for(auto& city : m_cities){
        ui->listWidgetCities->addItem(city->toQString());
    }
}


void MainWindow::on_buttonBeginVisit_clicked()
{
    int numOfVisitors;
    try{
        numOfVisitors = ui->lineEditNumOfVisitors->text().toUInt();
    }catch(const std::exception& e){
        return;
    }
    if(numOfVisitors > 0){
        ui->buttonBeginVisit->setEnabled(false);
        ui->buttonLoadCities->setEnabled(false);
        ui->lineEditDistanceSum->setText("");
        ui->listWidgetMoreExpensive->clear();
        for(numOfVisitors; numOfVisitors > 0; numOfVisitors--){
            auto thread = new Worker(m_cities,&m_mutex);
            m_activeThreads++;

            connect(thread, &QThread::finished, thread, &QObject::deleteLater);
            connect(thread, &Worker::takenArticle, this, &MainWindow::on_takenArticle);
            connect(thread, &Worker::done, this, &MainWindow::on_threadFinished);

            thread->start();
        }
    }

}

void MainWindow::on_takenArticle(unsigned i, QString article)
{
    ui->listWidgetCities->item(i)->setText(m_cities[i]->toQString());
    m_collectedArticles[article]++;
    ui->listWidgetMoreExpensive->clear();
    for(auto& item : m_collectedArticles.toStdMap()){
        const auto text = item.first + ": " + QString::number(item.second);
        ui->listWidgetMoreExpensive->addItem(text);
    }
}

void MainWindow::on_threadFinished(unsigned distance)
{
    m_activeThreads--;

    m_totalDistancePassed += distance;
    ui->lineEditDistanceSum->setText(QString::number(m_totalDistancePassed));

    if(m_activeThreads == 0){
        ui->buttonBeginVisit->setEnabled(true);
        ui->buttonLoadCities->setEnabled(true);
    }
}

