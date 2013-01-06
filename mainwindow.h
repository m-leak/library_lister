#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "librarylisterconfig.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void list_folders_to_file_wraper () const;
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:

    void list_folders_header_to_stream (QDir&, QTextStream&) const;
    void list_folders_to_stream (QDir&, QTextStream&, int&) const;
    void folder_to_stream (const QFileInfo&, QTextStream&) const;
    void file_to_stream (const QFileInfo&, QTextStream&) const;

    bool isLevelOfSubcategoryOutputable(const int &) const;

    Ui::MainWindow *ui;
    LibraryListerConfig* _libraryListerConfig;

};

#endif // MAINWINDOW_H
