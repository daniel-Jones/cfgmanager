#include "cfgmanager.h"
#include "ui_cfgmanager.h"

cfgmanager::cfgmanager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cfgmanager)
{
    ui->setupUi(this);
    load_location();
}

cfgmanager::~cfgmanager()
{
    delete ui;
}

int cfgmanager::show_question_box(QString message, QString omessage)
{
    QMessageBox qbox;
    qbox.setText(message);
    qbox.setInformativeText(omessage);
    qbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    qbox.setDefaultButton(QMessageBox::Cancel);
    return qbox.exec();
}

void cfgmanager::loop_cfg()
{
    QStringList lines = this->ui->text_area->toPlainText().split("\n");
    ui->text_area->clear();
    ui->text_area->append("alias nl \"l0\"\nbind o \"nl\"");
    for (int x = 0; x < lines.length() - 1; x++)
    {
        if (lines[x] != " ")
            ui->text_area->append("alias l" + QString::number(x) + " \"say " + lines[x] + ";alias nl l" + QString::number(x + 1) + "\"");
    }
    ui->text_area->append("alias l" + QString::number(lines.length() - 1) + " \"say " + lines[lines.length() - 1] + ";alias nl l" + QString::number(0) + "\"");
}

void cfgmanager::save_location(QString loc)
{
    QString fileloc = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/locations";
    QFile file(fileloc);
    qDebug() << fileloc;
    if (!QDir("Folder").exists())
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    QDir().remove(fileloc);
    if ( file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << loc << endl;
        file.close();
    }
    else
    {
        qDebug () << "error";
    }
}

void cfgmanager::load_location()
{
    QString fileloc = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/locations";
    QFile file(fileloc);
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
        }
        ui->location_name->setText(line);
    }
    file.close();
}

void cfgmanager::on_quit_button_clicked()
{
    int ret = show_question_box("Do you want to quit?",
                                "All unsaved edits will be lost.");
    switch (ret)
    {
        case QMessageBox::Yes:
            {
                qDebug() << "Quitting.";
                this->close();
                break;
            }
        case QMessageBox::No:
            {
            qDebug() << "Not quitting.";
            break;
            }
    default:
       {
            qDebug() << "No selection.";
            break;
       }
    }
}

void cfgmanager::on_loop_button_clicked()
{
    int ret = show_question_box("Do you want to loop your cfg?",
                                "This will create a looping cfg 'say' file out of any text currently in the text area. This is great for looping song lyrics. No commands will remain, only things to be spammed in chat.");
    switch (ret)
    {
        case QMessageBox::Yes:
            {
                qDebug() << "Looping config.";
                loop_cfg();
                break;
            }
        case QMessageBox::No:
            {
            qDebug() << "Not looping config";
            break;
            }
    default:
       {
            qDebug() << "No selection.";
            break;
       }
    }
}

void cfgmanager::on_save_button_clicked()
{
    if (!ui->cfg_name->text().isEmpty())
    {
        qDebug() << "doing";
        QString fileloc = ui->location_name->text() + "/" + ui->cfg_name->text();
        QDir().remove(fileloc);
        QFile file(fileloc);
        if ( file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            QStringList lines = ui->text_area->toPlainText().split("\n");
            for (int x = 0; x < lines.length(); x++)
            {
                if (lines[x] != " ")
                    stream << lines[x] << endl;
            }
            file.close();
        }
        else
        {
            qDebug () << "error";
        }
    }
}

void cfgmanager::on_location_button_clicked()
{
    csgodir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
            "/",
            QFileDialog::ShowDirsOnly
            | QFileDialog::DontResolveSymlinks);
    if (csgodir != "")
    {
        ui->location_name->setText(csgodir);
        save_location(csgodir);
    }
}

void cfgmanager::on_load_button_clicked()
{

}
