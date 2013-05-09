#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_createTemplate_clicked();

private:
    Ui::MainWindow *ui;
    void copyFolder(QString sourceFolder, QString destinationFolder);
    void removeFolder(QString folder);
    void replaceInFile(QString filePath, QString target, QString data);
};

#endif // MAINWINDOW_H
