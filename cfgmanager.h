#ifndef CFGMANAGER_H
#define CFGMANAGER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include <QDir>

namespace Ui {
class cfgmanager;
}

class cfgmanager : public QMainWindow
{
    Q_OBJECT

public:
    explicit cfgmanager(QWidget *parent = 0);
    ~cfgmanager();
    QString csgodir;

private slots:
    void on_quit_button_clicked();

    void on_loop_button_clicked();

    void on_save_button_clicked();

    void on_location_button_clicked();

private:
    Ui::cfgmanager *ui;
    int show_question_box(QString message, QString omessage);
    void loop_cfg();
    void save_location(QString loc);
    void load_location();
};

#endif // CFGMANAGER_H
