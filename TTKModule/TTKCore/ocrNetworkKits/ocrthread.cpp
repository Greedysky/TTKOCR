#include "ocrthread.h"
#include "ocralgorithmutils.h"
#include "ocrwidgetutils.h"

#include "qjson/parser.h"

#include <QDir>
#include <QPixmap>
#include <QHttpMultiPart>
#include <QNetworkRequest>
#include <QSslConfiguration>
#include <QNetworkAccessManager>

#define OCR_URL     "RU5EOEI3NnE1aUo0cHVQYlZST2s1eGZUVzY5dmFwemsvSFFJQXFzRjUvc0M1b21VOUFxU25yR1JpQjg9"

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

void OCRThread::start(OCRThreadItem *item)
{
    QNetworkRequest request;
    request.setOriginatingObject(item);
    request.setUrl(QUrl(OCRUtils::Algorithm::mdII(OCR_URL, false)));
#ifndef QT_NO_SSL
    QSslConfiguration sslConfig = request.sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);
#endif
    QPixmap pix(item->m_path);

    QString content = QString("form-data; name=\"pic\"; filename=\"pic.jpg\"");
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);
    QHttpPart part;
    part.setRawHeader("Content-Disposition", content.toUtf8());
    part.setRawHeader("Content-Type", "image/jpeg");
    part.setBody(OCRUtils::Widget::GeneratePixmapData(pix));
    multiPart->append(part);
    multiPart->setBoundary("----");

    m_reply = m_manager->post(request, multiPart);
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(m_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), SLOT(errorSlot(QNetworkReply::NetworkError)));
#else
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(errorSlot(QNetworkReply::NetworkError)));
#endif
    connect(m_reply, SIGNAL(finished()), SLOT(finishedSlot()));
}

void OCRThread::finishedSlot()
{
    if(!m_reply)
    {
        emit findFinish();
        return;
    }

    if(m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        QVariant data = json.parse(m_reply->readAll(), &ok);

        if(ok)
        {
            QString content;
            QVariantMap value = data.toMap();
            if(value["success"].toInt() == 1)
            {
                QVariantList datas = value["result"].toList();
                for(const QVariant &var : qAsConst(datas))
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
            }
        }
    }
    emit findFinish();
}

void OCRThread::errorSlot(QNetworkReply::NetworkError code)
{
    if(!m_reply)
    {
        return;
    }

    TTK_LOGGER_ERROR("QNetworkReply::NetworkError : " + QString::number((int)code) + " \n" + m_reply->errorString());
}
