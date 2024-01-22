#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "city.h"
#include "worker.h"

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QFile>
#include <QFileDialog>

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
    QString path = QFileDialog::getOpenFileName(this, "Open file with cities", "", "only JSON files (*.json)");
    QFile file(path);

    if(!file.open(QFile::ReadOnly)){
        return;
    }

    qDeleteAll(m_cities);
    m_cities.clear();
    ui->listWidgetCities->clear();

    QTextStream stream(file.readAll());

    QJsonDocument jsonDoc = QJsonDocument::fromJson(stream.readAll().toUtf8());
    file.close();
    auto jsonVariant = jsonDoc.toVariant().toList();
    for(const auto& variant : jsonVariant){
        City *city = new City();
        city->fromQVariant(variant);
        m_cities.push_back(city);
        ui->listWidgetCities->addItem(city->toQString());
    }
}


void MainWindow::on_buttonBuildRoads_clicked()
{
    for(unsigned i = 0; i < m_cities.size(); i++){
        auto thread = new Worker(m_cities, i);
        connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        connect(thread, &Worker::roadBuilt, this, &MainWindow::on_roadBuilt);
        m_cities[i]->setVisited(true);
        m_numberOfActiveThreads++;
        thread->start();
    }
}

void MainWindow::on_roadBuilt(unsigned int i, unsigned int j)
{
    m_numberOfActiveThreads--;
    ui->textEditRoads->append("\nAdded a new road from " + m_cities[i]->Name() + " to " + m_cities[j]->Name());

    if(m_numberOfActiveThreads == 0){
        unsigned numOfLeft = 0;
        for(auto it = m_cities.begin(); it != m_cities.end(); it++){
            if((*it)->Visited() == false){
                numOfLeft++;
            }
        }
        if(numOfLeft > 0){
            for(unsigned i = 0; i < m_cities.size(); i++){
                if(!m_cities[i]->Visited()){
                    auto thread = new Worker(m_cities, i);
                    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
                    connect(thread, &Worker::roadBuilt, this, &MainWindow::on_roadBuilt);
                    m_cities[i]->setVisited(true);
                    m_numberOfActiveThreads++;
                    thread->start();
                }
            }
        }
        else{
            ui->textEditRoads->append("\n\n#########################\n All roads are built");
        }
    }
}

