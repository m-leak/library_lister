#ifndef LIBRARYLISTERCONFIG_H
#define LIBRARYLISTERCONFIG_H

#include <QDataStream>
#include <QString>

class LibraryListerConfig
{
friend QDataStream& operator << (QDataStream&, const LibraryListerConfig&);
friend QDataStream& operator >> (QDataStream&, LibraryListerConfig&);

public:
    LibraryListerConfig();

    void serializeToFile();
    void deserializeFromFile();

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

    static const QString OUTPUT_FILE_SEPARATOR;
    static const QString OUTPUT_FILE_OFFSET;

protected:
private:
    QString _outputFilePath;
    int _levelOfSubcategories;
    bool _includeFolderSize;
    bool _includeFolderContentQty;
    bool _includeFileSize;
    bool _includeFileTime;

    static const QString CONFIG_FILE_NAME;
    static const QString OUTPUT_FILE_NAME;
};

#endif // LIBRARYLISTERCONFIG_H
