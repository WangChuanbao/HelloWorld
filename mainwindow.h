#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QCloseEvent>

class QLineEdit;
class QDialog;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newFile();
    bool isSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);

private slots:
    void on_pushButton_clicked();

    void on_actionNew_file_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAS_triggered();

    void on_actionOpen_triggered();

    void on_actionClose_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void showFindText();

    void on_actionFind_triggered();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    bool _isUntitled;   //记录文件是否保存，true 未保存
    QString _curFile;   //当前文件路径
    QLineEdit *_findLineEdit;
    QDialog *_findDlg;
    QLabel *_statusLabel;
};

#endif // MAINWINDOW_H
