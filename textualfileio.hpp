#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QUrl>

class TextualFileIO : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(TextualFileIO)

    Q_PROPERTY(QUrl filePath READ filePath WRITE setFilePath NOTIFY filePathChanged FINAL)
    Q_PROPERTY(QString fileContent READ fileContent WRITE setFileContent NOTIFY fileContentChanged FINAL)

public:
    explicit TextualFileIO(QObject *parent = nullptr);

    const QUrl& filePath() const;
    const QString& fileContent() const;

public:
    Q_INVOKABLE void readFile(bool async = false);
    Q_INVOKABLE void writeToFile(bool async = false);

public slots:
    void setFilePath(QUrl filepath);
    void setFileContent(QString fileContent);

signals:
    void filePathChanged(QUrl filePath);
    void fileContentChanged(QString fileContent);
    void writeOpResult(bool success, QString errorMessage = "");
    void readingFailed(QString errorMessage);

private:
    QUrl m_filePath;
    QString m_fileContent;
};
