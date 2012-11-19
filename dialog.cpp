#include<QFileDialog>

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setupDialog(const LibraryListerConfig *libraryListerConfig)
{
    setOutputFilePath(libraryListerConfig->getOutputFilePath());
    setLevelOfSubcategories(libraryListerConfig->getLevelOfSubcategories());
    setIncludeFolderSize(libraryListerConfig->getIncludeFolderSize());
    setIncludeFolderContentQty(libraryListerConfig->getIncludeFolderContentQty());
    setIncludeFileSize(libraryListerConfig->getIncludeFileSize());
    setIncludeFileTime(libraryListerConfig->getIncludeFileTime());
}

void Dialog::on_pushButton_clicked()
{
    QString qString = QFileDialog::getSaveFileName(this, tr("Save File"),getOutputFilePath());

    ui->lineEdit->setText(qString);
}

QString Dialog::getOutputFilePath() const
{
    return ui->lineEdit->text();
}

void Dialog::setOutputFilePath(const QString& qString)
{
    ui->lineEdit->setText(qString);
}

int Dialog::getLevelOfSubcategories() const
{
    return ui->comboBox->currentIndex();
}

void Dialog::setLevelOfSubcategories(const int& value)
{
    ui->comboBox->setCurrentIndex(value);
}

bool Dialog::getIncludeFolderSize() const
{
    return ui->checkBox->isChecked();
}

void Dialog::setIncludeFolderSize(const bool& value)
{
    ui->checkBox->setChecked(value);
}

bool Dialog::getIncludeFolderContentQty() const
{
    return ui->checkBox_2->isChecked();
}

void Dialog::setIncludeFolderContentQty(const bool& value)
{
    ui->checkBox_2->setChecked(value);
}

bool Dialog::getIncludeFileSize() const
{
    return ui->checkBox_3->isChecked();
}

void Dialog::setIncludeFileSize(const bool& value)
{
    ui->checkBox_3->setChecked(value);
}

bool Dialog::getIncludeFileTime() const
{
    return ui->checkBox_4->isChecked();
}

void Dialog::setIncludeFileTime(const bool& value)
{
    ui->checkBox_4->setChecked(value);
}
