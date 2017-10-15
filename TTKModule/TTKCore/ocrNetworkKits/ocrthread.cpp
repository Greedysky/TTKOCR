#include "ocrthread.h"
#include "qjson/json_parser.hh"

#include <QDir>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QNetworkRequest>
#include <QSslConfiguration>
#include <QNetworkAccessManager>

OCRThread::OCRThread(QObject *parent)
    : QObject(parent)
{
    m_reply = nullptr;
    m_manager = new QNetworkAccessManager(this);
}

OCRThread::~OCRThread()
{
    delete m_manager;
}

QString OCRThread::getClassName()
{
    return staticMetaObject.className();
}

void OCRThread::start(OCRThreadItem *item)
{
    QNetworkRequest request;
    request.setOriginatingObject(item);
    request.setUrl(QUrl("http://ocr.shouji.sogou.com/v2/ocr/json"));

    QFile file(item->m_path);
    if(!file.open(QFile::ReadOnly))
    {
        return;
    }

    QFileInfo fInfo(file.fileName());
    QString content = QString("form-data; name=\"pic\"; filename=\"%1\"").arg(fInfo.fileName());
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart part;
    part.setRawHeader("Content-Disposition", content.toUtf8());
    part.setRawHeader("Content-Type", getContentType(fInfo.suffix().toLower()).toUtf8());
    part.setBody(file.readAll());
    multiPart->append(part);
    multiPart->setBoundary("----");

    m_reply = m_manager->post(request, multiPart);
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(errorSlot(QNetworkReply::NetworkError)));
    connect(m_reply, SIGNAL(finished()), SLOT(finishedSlot()));
}

void OCRThread::finishedSlot()
{
    if(!m_reply)
    {
        return;
    }

    if(m_reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = m_reply->readAll();

        QJson::Parser parser;
        bool ok;
        QVariant data = parser.parse(bytes, &ok);
        if(ok)
        {
            QString content;
            QVariantMap value = data.toMap();
            if(value["success"].toInt() == 1)
            {
                QVariantList datas = value["result"].toList();
                foreach(const QVariant &var, datas)
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    content.append(value["content"].toString() + "\r\n");
                }
            }

            if(!content.isEmpty())
            {
                OCRThreadItem *item = qobject_cast<OCRThreadItem*>(m_reply->request().originatingObject());
                if(!QDir("dir").exists())
                {
                    QDir().mkdir("dir");
                }
                QFile file(QString("%1/%2").arg("dir").arg(item->m_index));
                if(file.open(QFile::WriteOnly))
                {
                    file.write(content.toUtf8());
                    file.close();
                }

                emit findFinish();
            }
        }
    }

}

void OCRThread::errorSlot(QNetworkReply::NetworkError code)
{
    if(!m_reply)
    {
        return;
    }

    qDebug() <<  "QNetworkReply::NetworkError : " + QString::number((int)code) + " \n" + m_reply->errorString();
}

QString OCRThread::getContentType(const QString &suffix)
{
    if(suffix== "jpg")
        return "image/jpeg";
    else if(suffix== "png")
        return "image/png";
    else if(suffix== "bmp")
        return "application/x-bmp";
    return QString();
}
