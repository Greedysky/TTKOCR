#include "ocrthread.h"
#include "ocralgorithmutils.h"
#include "ocrimageutils.h"
#include "ocrobject.h"

#include "qjson/json.h"

#include <QDir>
#include <QPixmap>
#include <QHttpMultiPart>

static constexpr const char *BASE_URL = "RU5EOEI3NnE1aUo0cHVQYlZST2s1eGZUVzY5dmFwemsvSFFJQXFzRjUvc0M1b21VOUFxU25yR1JpQjg9";

OCRNetworkRequest::OCRNetworkRequest(QObject *parent)
    : TTKAbstractNetwork(parent)
{

}

void OCRNetworkRequest::startToRequest(OCRRequestItem *item)
{
    QNetworkRequest request;
    request.setOriginatingObject(item);
    request.setUrl(TTK::Algorithm::mdII(BASE_URL, false));
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

void OCRNetworkRequest::downLoadFinished()
{
    if(!m_reply)
    {
        Q_EMIT findFinish();
        return;
    }

    if(m_reply->error() == QNetworkReply::NoError)
    {
        QJsonParseError ok;
        const QJsonDocument &json = QJsonDocument::fromJson(m_reply->readAll(), &ok);
        if(QJsonParseError::NoError == ok.error)
        {
            QString content;
            QVariantMap value = json.toVariant().toMap();
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
                    content.append(value["content"].toString() + TTK_WLINEFEED);
                }
            }

            if(!content.isEmpty())
            {
                OCRRequestItem *item = qobject_cast<OCRRequestItem*>(m_reply->request().originatingObject());
                if(!QDir(DIR_PREFIX_FULL).exists())
                {
                    QDir().mkdir(DIR_PREFIX_FULL);
                }

                QFile file(QString("%1/%2").arg(DIR_PREFIX_FULL).arg(item->m_index));
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
