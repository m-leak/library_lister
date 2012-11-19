#include "librarylisterconfig.h"

#include <QString>
#include <QDir>
#include <QFile>
#include <QCoreApplication>

const QString LibraryListerConfig::OUTPUT_FILE_SEPARATOR = QString(" | ");
const QString LibraryListerConfig::OUTPUT_FILE_OFFSET = QString("\t");

const QString LibraryListerConfig::CONFIG_FILE_NAME = QString("config.txt");
const QString LibraryListerConfig::OUTPUT_FILE_NAME = QString("output.txt");

QDataStream& operator << (QDataStream& qDataStream, const LibraryListerConfig& libraryListerConfig)
{
    return qDataStream << libraryListerConfig._levelOfSubcategories
                       << libraryListerConfig._includeFolderSize
                       << libraryListerConfig._includeFolderContentQty
                       << libraryListerConfig._includeFileSize
                       << libraryListerConfig._includeFileTime
           ;
}

QDataStream& operator >> (QDataStream& qDataStream, LibraryListerConfig& libraryListerConfig)
{
    return qDataStream >> libraryListerConfig._levelOfSubcategories
                       >> libraryListerConfig._includeFolderSize
                       >> libraryListerConfig._includeFolderContentQty
                       >> libraryListerConfig._includeFileSize
                       >> libraryListerConfig._includeFileTime
           ;
}

LibraryListerConfig::LibraryListerConfig() : _outputFilePath(QCoreApplication::applicationDirPath() + QDir::separator() + OUTPUT_FILE_NAME)
{
    setLevelOfSubcategories(0);
    setIncludeFolderSize(false);
    setIncludeFolderContentQty(false);
    setIncludeFileSize(false);
    setIncludeFileTime(false);
}

void LibraryListerConfig::serializeToFile()
{
    QFile qFile(QCoreApplication::applicationDirPath() + QDir::separator() + CONFIG_FILE_NAME);

    if (!qFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    QDataStream qDataStream(&qFile);
    qDataStream << *this;
}

void LibraryListerConfig::deserializeFromFile()
{
    QFile qFile(QCoreApplication::applicationDirPath() + QDir::separator() + CONFIG_FILE_NAME);

    if (!qFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    QDataStream qDataStream(&qFile);
    qDataStream >> *this;
}

QString LibraryListerConfig::getOutputFilePath() const
{
    return _outputFilePath;
}

void LibraryListerConfig::setOutputFilePath(const QString& qString)
{
    _outputFilePath = qString;
}

int LibraryListerConfig::getLevelOfSubcategories() const
{
    return _levelOfSubcategories;
}

void LibraryListerConfig::setLevelOfSubcategories(const int& value)
{
    _levelOfSubcategories = value;
}

bool LibraryListerConfig::getIncludeFolderSize() const
{
    return _includeFolderSize;
}

void LibraryListerConfig::setIncludeFolderSize(const bool& value)
{
    _includeFolderSize = value;
}

bool LibraryListerConfig::getIncludeFolderContentQty() const
{
    return _includeFolderContentQty;
}

void LibraryListerConfig::setIncludeFolderContentQty(const bool& value)
{
    _includeFolderContentQty = value;
}

bool LibraryListerConfig::getIncludeFileSize() const
{
    return _includeFileSize;
}

void LibraryListerConfig::setIncludeFileSize(const bool& value)
{
    _includeFileSize = value;
}

bool LibraryListerConfig::getIncludeFileTime() const
{
    return _includeFileTime;
}

void LibraryListerConfig::setIncludeFileTime(const bool& value)
{
    _includeFileTime = value;
}
