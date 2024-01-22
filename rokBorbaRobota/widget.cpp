#include "widget.h"
#include "./ui_widget.h"
#include "worker.h"

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QTextStream>
#include <QJsonArray>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_button_loadRobots_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open json with robots", "home/Marko/Desktop", "JSON files (*.json)");
    QFile file(path);
    if(!file.open(QFile::ReadOnly)){
        return;
    }
    qDeleteAll(m_robots);
    m_robots.clear();
    QTextStream stream(file.readAll());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(stream.readAll().toUtf8());
    file.close();

    auto robotsVariant = jsonDoc.toVariant().toList();
    for(const auto& robotVariant : robotsVariant){
        Robot* robot = new Robot();
        robot->fromQVariant(robotVariant);
        m_robots.push_back(robot);
    }
    int i = 1;
    for(auto& robot : m_robots){
        ui->listWidget->addItem(QString::number(i) + ": " + robot->toQString());
        i++;
    }
    ui->lineEditNumOfRobots->setText(QString::number(i));

}


void Widget::on_button_beginBattle_clicked()
{
    if(ui->listWidget->count() == 0){
        return;
    }
    ui->button_loadRobots->setEnabled(false);
    ui->button_beginBattle->setEnabled(false);
    ui->lineEditRobotWithMostWins->setText("");


    ui->tableWidget->setColumnCount(m_robots.size());
    ui->tableWidget->setRowCount(m_robots.size());
    for(int i = 0; i < m_robots.size(); i++){
        for(int j = 0; j < m_robots.size(); j++){
            auto *tableItem = new QTableWidgetItem;
            if(i == j){
                tableItem->setText("\\");
            }
            ui->tableWidget->setItem(i, j, tableItem);
        }
    }

    for(int i = 0; i < m_robots.size();i++){
        for(int j = 0; j < i; j++){
            auto* thread = new Worker(m_robots, &m_mutex, i, j);
            connect(thread, &QThread::finished, thread, &QObject::deleteLater);
            connect(thread, &Worker::battleFinished, this, &Widget::on_battleFinished);
            m_numOfActiveThreads++;
            thread -> start();
            qDebug() << m_numOfActiveThreads;
        }
    }
}

void Widget::on_battleFinished(unsigned int i, unsigned int j, bool won)
{
    qDebug() << "zavrsena borba" + QString::number(i) + " " + QString::number(j);
    if(won){
        ui->tableWidget->item(i, j)->setText("Pobedio");
        ui->tableWidget->item(j, i)->setText("Izgubio");
    }else{
        ui->tableWidget->item(i, j)->setText("Izgubio");
        ui->tableWidget->item(j, i)->setText("Pobedio");
    }
    m_numOfActiveThreads--;
    if(m_numOfActiveThreads == 0){
        ui->button_beginBattle->setEnabled(true);
        ui->button_loadRobots->setEnabled(true);
        unsigned max = 0;
        unsigned maxIndex = 0;
        for(int i = 0; i < m_robots.size(); i++){
            unsigned count = 0;
            for(int j = 0; j < m_robots.size(); j++){
                if(ui->tableWidget->item(i, j)->text() == "Pobedio"){
                    count++;
                }
            }
            if(count > max){
                max = count;
                maxIndex = i;
            }
        }
        ui->lineEditRobotWithMostWins->setText(m_robots[i]->Name());
    }
}

