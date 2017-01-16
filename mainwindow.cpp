#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QFormLayout>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QAction *open = new  QAction(QString::fromLocal8Bit("&Open"),this);
//    QIcon icon(":/myImages/1.jpg");
//    open->setIcon(icon);
//    open->setShortcut(QKeySequence(QString::fromLocal8Bit("Ctrl+O")));
//    ui->menu_f->addAction(open);

    //ui->menu_f->actionAt(QPoint(0,5))->setShortcut(QKeySequence(QString::fromLocal8Bit("ctrl+Q")));
    ui->textEdit->setVisible(false);
    _isUntitled = true;
    _curFile = QString::fromLocal8Bit("未命名.txt");
    setWindowTitle(_curFile);

    _findDlg = new QDialog(this);
    _findDlg->setWindowTitle(QString::fromLocal8Bit("查找"));
    _findLineEdit = new QLineEdit(_findDlg);
    QPushButton *btn = new QPushButton(QString::fromLocal8Bit("查找下一个"),_findDlg);
    QVBoxLayout *layout = new QVBoxLayout(_findDlg);
    layout->addWidget(_findLineEdit);
    layout->addWidget(btn);
    connect(btn,SIGNAL(clicked()),this,SLOT(showFindText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    if (isSave())
    {
        _isUntitled = true;
        _curFile = QString::fromLocal8Bit("未命名.txt");
        setWindowTitle(_curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::isSave()
{
    if (ui->textEdit->document()->isModified())
    {
        //QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("文件尚未保存，是否保存？"),QMessageBox::Ok);
        QMessageBox box;
        box.setWindowTitle(QString::fromLocal8Bit("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(_curFile+QString::fromLocal8Bit("尚未保存，是否保存？"));
        QPushButton *yesBtn = box.addButton(QString::fromLocal8Bit("是"),QMessageBox::YesRole);
        box.addButton(QString::fromLocal8Bit("否"),QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton(QString::fromLocal8Bit("取消"),QMessageBox::RejectRole);
        box.exec();
        if (box.clickedButton() == yesBtn)
            return save();
        else if (box.clickedButton() == cancelBtn)
            return false;
        else return true;
    }
    return true;
}

bool MainWindow::save()
{
    if (_isUntitled)
    {
        return saveAs();
    }
    else {
        return saveFile(_curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("另存为"),_curFile);
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("错误"),
                             QString::fromLocal8Bit("无法写入文件%1：\n%2").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    _isUntitled = false;
    _curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(_curFile);
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("错误"),
                             QString::fromLocal8Bit("无法读取文件%1： \n%2").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setText(in.readAll());
    QApplication::restoreOverrideCursor();
    _curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(_curFile);
    return true;
}

void MainWindow::showFindText()
{
    QString str = _findLineEdit->text();
    if (!ui->textEdit->find(str,QTextDocument::FindCaseSensitively|QTextDocument::FindBackward))
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("查找"),QString::fromLocal8Bit("未找到%1").arg(str));
    }
}

void MainWindow::on_pushButton_clicked()
{
    QDialog *dlg = new QDialog(this);
    dlg->show();
}

void MainWindow::on_actionNew_file_triggered()
{
    newFile();
}

void MainWindow::on_actionSave_triggered()
{
    save();
}

void MainWindow::on_actionSaveAS_triggered()
{
    saveAs();
}

void MainWindow::on_actionOpen_triggered()
{
    if (isSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
        {
            loadFile(fileName);
            _isUntitled = false;
            ui->textEdit->setVisible(true);
        }
    }
}

void MainWindow::on_actionClose_triggered()
{
    if (isSave())
    {
        ui->textEdit->setVisible(false);
    }
}

void MainWindow::on_actionExit_triggered()
{
    on_actionClose_triggered();
    //qApp是指向应用程序的全局指针
    qApp->quit();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isSave())
        event->accept();
    else
        event->ignore();
}

void MainWindow::on_actionFind_triggered()
{
    _findDlg->show();
}
