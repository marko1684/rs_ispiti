#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "source.h"
#include <QWidget>
#include <QVector>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fillSourcesButton_clicked();
    void on_pushButtonBeginTransfer_clicked();
    void on_workerDone(unsigned index, unsigned volume);

private:
    Ui::MainWindow *ui;
    QVector<Source*> m_sources;
    QMutex m_mutex;
};
#endif // MAINWINDOW_H
