#include<QFileDialog>
#include<QDir>
#include<QDialog>
#include <QMessageBox>
#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _libraryListerConfig(new LibraryListerConfig())
{
    ui->setupUi(this);
    _libraryListerConfig->deserializeFromFile();
}

MainWindow::~MainWindow()
{
    delete _libraryListerConfig;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString qString = QFileDialog::getExistingDirectory(this, tr("Browse for a directory"),                                                    QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (qString.length())
    {
        this->ui->label_3->setText(qString);
        ui->pushButton_3->setEnabled(true);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    Dialog dialog(this);
    dialog.setupDialog(_libraryListerConfig);

    if (dialog.exec() ==  QDialog::Accepted)
    {
        _libraryListerConfig->setOutputFilePath(dialog.getOutputFilePath());
        _libraryListerConfig->setLevelOfSubcategories(dialog.getLevelOfSubcategories());
        _libraryListerConfig->setIncludeFolderSize(dialog.getIncludeFolderSize());
        _libraryListerConfig->setIncludeFolderContentQty(dialog.getIncludeFolderContentQty());
        _libraryListerConfig->setIncludeFileSize(dialog.getIncludeFileSize());
        _libraryListerConfig->setIncludeFileTime(dialog.getIncludeFileTime());

        _libraryListerConfig->serializeToFile();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    list_folders_to_file_wraper();
}

void MainWindow::list_folders_to_file_wraper() const
{
    QFile qFile(_libraryListerConfig->getOutputFilePath());
    QDir qDir(this->ui->label_3->text());

    if (!qFile.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        return;
    }
    QTextStream qTextStream(&qFile);

    int levelOfSubcategory = 0;
    list_folders_to_stream(qDir, qTextStream, levelOfSubcategory);
}

void MainWindow::list_folders_to_stream(QDir& qDir, QTextStream& qTextStream, int& levelOfSubcategory) const
{
    ++levelOfSubcategory;

    if (isLevelOfSubcategoryOutputable(levelOfSubcategory))
    {
        --levelOfSubcategory;
        return;
    }

    QFileInfoList qFileInfoList = qDir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Size | QDir::DirsFirst);

    for (int i = 0; i < qFileInfoList.size(); ++i)
    {
        QFileInfo qFileInfo = qFileInfoList.at(i);

        // qTextStream << LibraryListerConfig::OUTPUT_FILE_OFFSET.repeated(levelOfSubcategory - 1);
        if (qFileInfo.isDir())
        {
            folder_to_stream(qFileInfo, qTextStream);
            QDir foo(qFileInfo.absoluteFilePath());
            list_folders_to_stream(foo, qTextStream, levelOfSubcategory);
        }
        else
        {
            file_to_stream(qFileInfo, qTextStream);
        }
    }
    // qTextStream << endl;

    --levelOfSubcategory;
}

void MainWindow::folder_to_stream (const QFileInfo& qFileInfo, QTextStream& qTextStream) const
{
    qTextStream << qFileInfo.fileName();
    if (_libraryListerConfig->getIncludeFolderSize())
    {
         qTextStream << LibraryListerConfig::OUTPUT_FILE_SEPARATOR
                     << qFileInfo.size();
    }
    qTextStream << endl;
}

void MainWindow::file_to_stream (const QFileInfo& qFileInfo, QTextStream& qTextStream) const
{
    // qTextStream << QString("%1 %2").arg(qFileInfo.size()).arg(qFileInfo.fileName()) << endl;
    qTextStream << qFileInfo.fileName();
    if (_libraryListerConfig->getIncludeFileSize())
    {
         qTextStream << LibraryListerConfig::OUTPUT_FILE_SEPARATOR
                     << qFileInfo.size();
    }
    if (_libraryListerConfig->getIncludeFileTime())
    {
        qTextStream << LibraryListerConfig::OUTPUT_FILE_SEPARATOR
                    << qFileInfo.created().toString("ddd MMMM d yy");
    }
    qTextStream << endl;
}

bool MainWindow::isLevelOfSubcategoryOutputable(const int& value) const
{
    bool isLevelOfSubcategoryOutputable = (_libraryListerConfig->getLevelOfSubcategories() != 0) && (value > _libraryListerConfig->getLevelOfSubcategories());
    return isLevelOfSubcategoryOutputable;
}
