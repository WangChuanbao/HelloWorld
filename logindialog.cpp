#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText(QString::fromLocal8Bit("用户名"));
    ui->lineEdit_2->setPlaceholderText(QString::fromLocal8Bit("密码"));
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString passwd = ui->lineEdit_2->text();

    qDebug() << name << "\t" << passwd << endl;
    qDebug() << name.compare("work") << "\t" << passwd.compare("88521") << endl;

    if (name.compare("work")==0 && passwd.compare("88521")==0 )
    {
        accept();
    }
    else {
        QMessageBox::warning(this,QString::fromLocal8Bit("错误提示"),QString::fromLocal8Bit("用户名或密码错误"),QMessageBox::Ok);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit->setFocus();
    }
}

void LoginDialog::on_pushButton_2_clicked()
{
    close();
}
