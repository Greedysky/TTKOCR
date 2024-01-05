#include "ocrthread.h"
#include "ocralgorithmutils.h"
#include "ocrimageutils.h"
#include "ocrobject.h"

#include "qjson/parser.h"

#include <QDir>
#include <QPixmap>
#include <QHttpMultiPart>
#include <QSslConfiguration>

static constexpr const char *OCR_URL = "RU5EOEI3NnE1aUo0cHVQYlZST2s1eGZUVzY5dmFwemsvSFFJQXFzRjUvc0M1b21VOUFxU25yR1JpQjg9";

OCRThread::OCRThread(QObject *parent)
    : TTKAbstractNetwork(parent)
{

}

void OCRThread::startToRequest(OCRThreadItem *item)
{
    QNetworkRequest request;
    request.setOriginatingObject(item);
    request.setUrl(QUrl(TTK::Algorithm::mdII(OCR_URL, false)));
    TTK::setSslConfiguration(&request);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);
    QHttpPart part;
    part.setRawHeader("Content-Disposition", "form-data; name=\"pic\"; filename=\"pic.jpg\"");
    part.setRawHeader("Content-Type", "image/jpeg");
    part.setBody(TTK::Image::generatePixmapData(QPixmap(item->m_path)));
    multiPart->append(part);
    multiPart->setBoundary("----");

    m_reply = m_manager.post(request, multiPart);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError, TTK_SLOT);
}

void OCRThread::downLoadFinished()
{
    if(!m_reply)
    {
        Q_EMIT findFinish();
        return;
    }

    if(m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok = false;
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
                if(!QDir(DIR_PREFIX).exists())
                {
                    QDir().mkdir(DIR_PREFIX);
                }

                QFile file(QString("%1/%2").arg(DIR_PREFIX).arg(item->m_index));
                if(file.open(QIODevice::WriteOnly))
                {
                    file.write(content.toUtf8());
                    file.close();
                }
            }
        }
    }

    Q_EMIT downLoadDataChanged({});
    deleteAll();
}
