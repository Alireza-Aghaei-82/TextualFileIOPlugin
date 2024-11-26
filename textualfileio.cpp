#include "textualfileio.hpp"

#include <QDebug>
#include <QFile>

#include <thread>


extern void qml_register_types_MyModules_IO_TextualFileIO();


TextualFileIO::TextualFileIO(QObject *parent)
    : QObject(parent)
{
    volatile auto registration = &qml_register_types_MyModules_IO_TextualFileIO;
    Q_UNUSED(registration);

}

const QUrl &TextualFileIO::filePath() const
{
    volatile auto registration = &qml_register_types_MyModules_IO_TextualFileIO;
    Q_UNUSED(registration);

    return m_filePath;
}

const QString &TextualFileIO::fileContent() const
{
    volatile auto registration = &qml_register_types_MyModules_IO_TextualFileIO;
    Q_UNUSED(registration);

    return m_fileContent;
}

void TextualFileIO::setFilePath(QUrl filepath)
{
    volatile auto registration = &qml_register_types_MyModules_IO_TextualFileIO;
    Q_UNUSED(registration);

    if(filepath != m_filePath)
    {
        m_filePath= filepath;
        emit filePathChanged(filepath);
    }
}

void TextualFileIO::setFileContent(QString fileContent)
{
    volatile auto registration = &qml_register_types_MyModules_IO_TextualFileIO;
    Q_UNUSED(registration);

    if(fileContent != m_fileContent)
    {
        m_fileContent = fileContent;
        emit fileContentChanged(fileContent);
    }
}

void TextualFileIO::readFile(bool async)
{
    volatile auto registration = &qml_register_types_MyModules_IO_TextualFileIO;
    Q_UNUSED(registration);

    if(m_filePath.isEmpty())
    {
        qDebug() << tr("[FileIO][readFile]: Trying to read the file but no file path is specified!");
        emit readingFailed(tr("Trying to read the file but no file path is specified!"));
        return;
    }

    m_filePath = m_filePath.toLocalFile();

    auto readTask {[this]()
    {
        const auto pathStr {m_filePath.toString()};
        QFile file{pathStr};

        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << tr("[FileIO][readFile]: Could not open the following file for reading:\n%1").arg(pathStr);
            emit readingFailed(tr("Could not open the following file for reading:\n%1").arg(pathStr));
            return;
        }

        bool success {true};

        {
            QTextStream stream{&file};
            m_fileContent = stream.readAll();

            if(stream.status() != QTextStream::Ok)
            {
                qDebug() << tr("[FileIO][readFile]: Something went wrong, while trying to read from the following file:\n%1").arg(pathStr);
                emit readingFailed(tr("Something went wrong, while trying to read from the following file:\n%1").arg(pathStr));
                success = false;
            }
        }

        if(success)
            emit fileContentChanged(m_fileContent);
    }};

    if(async)
        std::thread{readTask}.detach();

    else
        readTask();
}

void TextualFileIO::writeToFile(bool async)
{
    volatile auto registration = &qml_register_types_MyModules_IO_TextualFileIO;
    Q_UNUSED(registration);

    if(m_filePath.isEmpty())
    {
        qDebug() << tr("[FileIO][readFile]: Trying to write to a file, but no file path is specified!");
        emit writeOpResult(false, tr("Trying to write to a file, but no file path is specified!"));
        return;
    }

    m_filePath = m_filePath.toLocalFile();

    auto writeTask {[this]()
        {
            const auto pathStr {m_filePath.toString()};
            QFile file{pathStr};

            if(!file.open(QIODevice::WriteOnly))
            {
                qDebug() << tr("[FileIO][readFile]: Could not open the following file for writing:\n%1").arg(pathStr);
                emit writeOpResult(false, tr("Could not open the following file for writing:\n%1").arg(pathStr));
                return;
            }

            {
                QTextStream stream{&file};
                stream << m_fileContent;

                if(stream.status() != QTextStream::Ok)
                {
                    qDebug() << tr("[FileIO][readFile]: Something went wrong, while trying to write into the following file:\n%1").arg(pathStr);
                    emit writeOpResult(false, tr("Something went wrong, while trying to write into the following file:\n%1").arg(pathStr));
                    return;
                }
            }

            emit writeOpResult(true);
        }
    };

    if(async)
        std::thread{writeTask}.detach();

    else
        writeTask();
}


