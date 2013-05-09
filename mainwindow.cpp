#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include "quazip/JlCompress.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString question = "<a:p>\r\n"
        "        <a:pPr marL=\"514350\" indent=\"-216000\">\r\n"
        "            <a:buFont typeface=\"+mj-lt\"/>\r\n"
        "            <a:buAutoNum type=\"arabicPeriod\"/>\r\n"
        "        </a:pPr>\r\n"
        "        <a:r>\r\n"
        "            <a:rPr lang=\"ru-RU\" sz=\"1900\" dirty=\"0\" smtClean=\"0\">\r\n"
        "                <a:solidFill>\r\n"
        "                    <a:schemeClr val=\"bg1\"/>\r\n"
        "                </a:solidFill>\r\n"
        "                <a:latin typeface=\"Arial\" pitchFamily=\"34\" charset=\"0\"/>\r\n"
        "                <a:cs typeface=\"Arial\" pitchFamily=\"34\" charset=\"0\"/>\r\n"
        "            </a:rPr>\r\n"
        "            <a:t>%1</a:t>\r\n"
        "        </a:r>\r\n"
        "    </a:p>\r\n";
QString lastQuestion = ""
        "    <a:p>\r\n"
        "        <a:pPr marL=\"514350\" indent=\"-216000\">\r\n"
        "            <a:buFont typeface=\"+mj-lt\"/>\r\n"
        "            <a:buAutoNum type=\"arabicPeriod\"/>\r\n"
        "        </a:pPr>\r\n"
        "        <a:r>\r\n"
        "            <a:rPr lang=\"ru-RU\" sz=\"1900\" dirty=\"0\" smtClean=\"0\">\r\n"
        "                <a:solidFill>\r\n"
        "                    <a:schemeClr val=\"bg1\"/>\r\n"
        "                </a:solidFill>\r\n"
        "                <a:latin typeface=\"Arial\" pitchFamily=\"34\" charset=\"0\"/>\r\n"
        "                <a:cs typeface=\"Arial\" pitchFamily=\"34\" charset=\"0\"/>\r\n"
        "            </a:rPr>\r\n"
        "            <a:t>%1</a:t>\r\n"
        "        </a:r>\r\n"
        "        <a:endParaRPr lang=\"ru-RU\" sz=\"1900\" dirty=\"0\">\r\n"
        "            <a:solidFill>\r\n"
        "                <a:schemeClr val=\"bg1\"/>\r\n"
        "            </a:solidFill>\r\n"
        "            <a:latin typeface=\"Arial\" pitchFamily=\"34\" charset=\"0\"/>\r\n"
        "            <a:cs typeface=\"Arial\" pitchFamily=\"34\" charset=\"0\"/>\r\n"
        "        </a:endParaRPr>\r\n"
        "    </a:p>\r\n";

void MainWindow::on_createTemplate_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Введите имя файла для сохранения"),
                QDir::homePath(),
                "Презентация PowerPoint (*.pptx)");
    if (fileName.isNull()) {
        return;
    }
    QString tempFolder = QDir::tempPath() + QDir::separator() + "presentatio";
    removeFolder(tempFolder);
    copyFolder("blank", tempFolder);
    replaceInFile(tempFolder + QDir::separator()
                  + "ppt" + QDir::separator()
                  + "slides" + QDir::separator()
                  + "slide1.xml",
                  ui->chair->placeholderText(),
                  ui->chair->text());
    replaceInFile(tempFolder + QDir::separator()
                  + "ppt" + QDir::separator()
                  + "slides" + QDir::separator()
                  + "slide2.xml",
                  ui->chair->placeholderText(),
                  ui->chair->text());
    replaceInFile(tempFolder + QDir::separator()
                  + "ppt" + QDir::separator()
                  + "slides" + QDir::separator()
                  + "slide1.xml",
                  ui->subject->placeholderText(),
                  ui->subject->text());
    replaceInFile(tempFolder + QDir::separator()
                  + "ppt" + QDir::separator()
                  + "slides" + QDir::separator()
                  + "slide2.xml",
                  ui->subject->placeholderText(),
                  ui->subject->text());
    replaceInFile(tempFolder + QDir::separator()
                  + "ppt" + QDir::separator()
                  + "slides" + QDir::separator()
                  + "slide1.xml",
                  ui->discipline->placeholderText(),
                  ui->discipline->text());
    replaceInFile(tempFolder + QDir::separator()
                  + "ppt" + QDir::separator()
                  + "slides" + QDir::separator()
                  + "slide2.xml",
                  ui->discipline->placeholderText(),
                  ui->discipline->text());
    replaceInFile(tempFolder + QDir::separator()
                  + "ppt" + QDir::separator()
                  + "slides" + QDir::separator()
                  + "slide1.xml",
                  ui->authors->placeholderText(),
                  ui->authors->text());
    replaceInFile(tempFolder + QDir::separator()
                  + "ppt" + QDir::separator()
                  + "slides" + QDir::separator()
                  + "slide2.xml",
                  ui->authors->placeholderText(),
                  ui->authors->text());
    QStringList questions = ui->questions->toPlainText().split("\n");
    QString questionsToInsert;
    for (int i = 0; i < questions.size(); ++i) {
        if (i != questions.size() - 1) {
            questionsToInsert.append(question.arg(questions.at(i)));
        } else {
            questionsToInsert.append(lastQuestion.arg(questions.at(i)));
        }
    }
    replaceInFile(tempFolder + QDir::separator()
                  + "ppt" + QDir::separator()
                  + "slides" + QDir::separator()
                  + "slide1.xml",
                  "questions",
                  questionsToInsert);
    JlCompress::compressDir(fileName, tempFolder);
    removeFolder(tempFolder);
}

void MainWindow::copyFolder(QString sourceFolder, QString destFolder)
{
    QDir sourceDir(sourceFolder);
    if (!sourceDir.exists()) {
        return;
    }
    QDir destDir(destFolder);
    if (!destDir.exists()) {
        destDir.mkdir(destFolder);
    }
    QStringList files = sourceDir.entryList(QDir::Files | QDir::Hidden);
    for (int i = 0; i < files.count(); i++) {
        QString srcName = sourceFolder + QDir::separator() + files.at(i);
        QString destName = destFolder + QDir::separator() + files.at(i);
        QFile::copy(srcName, destName);
    }
    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < files.count(); i++) {
        QString srcName = sourceFolder + QDir::separator() + files.at(i);
        QString destName = destFolder + QDir::separator() + files.at(i);
        copyFolder(srcName, destName);
    }
}

void MainWindow::removeFolder(QString folder)
{
    QDir dir(folder);
    if (!dir.exists()) {
        return;
    }
    QStringList files = dir.entryList(QDir::Files | QDir::Hidden);
    for (int i = 0; i < files.count(); ++i) {
        QFile::remove(folder + QDir::separator() + files.at(i));
    }
    files.clear();
    files = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < files.count(); ++i) {
        removeFolder(folder + QDir::separator() + files.at(i));
    }
    dir.rmdir(folder);
}

void MainWindow::replaceInFile(QString filePath, QString target, QString data)
{
    QFile file(filePath);
    QTextStream stream;
    stream.setDevice(&file);
    file.open(QIODevice::ReadOnly);
    QString content = stream.readAll();
    file.close();
    content.replace(target, data);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    stream << content;
    file.close();
}
