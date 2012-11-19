#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "librarylisterconfig.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void setupDialog(const LibraryListerConfig*);

    QString getOutputFilePath() const;
    void setOutputFilePath(const QString&);

    int getLevelOfSubcategories() const;
    void setLevelOfSubcategories(const int&);

    bool getIncludeFolderSize() const;
    void setIncludeFolderSize(const bool&);

    bool getIncludeFolderContentQty() const;
    void setIncludeFolderContentQty(const bool&);

    bool getIncludeFileSize() const;
    void setIncludeFileSize(const bool&);

    bool getIncludeFileTime() const;
    void setIncludeFileTime(const bool&);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
