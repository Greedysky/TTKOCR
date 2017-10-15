#include "ocrapplication.h"
#include "ui_ocrapplication.h"
#include "ocrapplicationobject.h"
#include "ocrfunctionlistuiobject.h"
#include "ocrwidgetutils.h"
#include "ocrcoreutils.h"
#include "ocrthread.h"
#include "ocruiobject.h"
#ifdef OCR_BUILD_BY_PDF
#include "include/mupdf-qt.h"
#endif
#include <QScrollBar>

OCRApplication *OCRApplication::m_instance = nullptr;

OCRApplication::OCRApplication(QWidget *parent)
    : OCRAbstractMoveResizeWidget(parent),
      m_ui(new Ui::OCRApplication)
{
    m_instance = this;
//#ifdef OCR_GREATER_NEW
    setAttribute(Qt::WA_TranslucentBackground, false);
//#endif

    m_count = 0;
    m_applicationObject = new OCRApplicationObject(this);
    ////////////////////////////////////////////////
    m_ui->setupUi(this);

    setMinimumSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    setMaximumSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);

    m_ui->iconLabel->setPixmap(QPixmap(":/image/lb_player_logo").scaled(m_ui->iconLabel->size()));
    m_ui->background->setPixmap(QPixmap(":/image/lb_background").scaled(size()));

    m_ui->minButton->setStyleSheet(OCRUIObject::MFuncMin);
    connect(m_ui->minButton, SIGNAL(clicked()), SLOT(showMinimized()));

    m_ui->closeButton->setStyleSheet(OCRUIObject::MFuncClose);
    connect(m_ui->closeButton, SIGNAL(clicked()), SLOT(quitWindowClose()));

    m_ui->openButton->setStyleSheet(OCRUIObject::MPushButtonStyle04);
    m_ui->startButton->setStyleSheet(OCRUIObject::MPushButtonStyle04);
    m_ui->clearButton->setStyleSheet(OCRUIObject::MPushButtonStyle04);

    connect(m_ui->openButton, SIGNAL(clicked()), SLOT(openButtonClicked()));
    connect(m_ui->startButton, SIGNAL(clicked()), SLOT(startButtonClicked()));
    connect(m_ui->clearButton, SIGNAL(clicked()), SLOT(clearButtonClicked()));

    m_ui->pixScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ui->pixScrollArea->setWidgetResizable(true);
    m_ui->pixScrollArea->setFrameShape(QFrame::NoFrame);
    m_ui->pixScrollArea->setFrameShadow(QFrame::Plain);
    m_ui->pixScrollArea->setAlignment(Qt::AlignVCenter);
    m_ui->pixScrollArea->verticalScrollBar()->setStyleSheet(OCRUIObject::MScrollBarStyle03);

    m_ui->textScrollArea->setWidgetResizable(true);
    m_ui->textScrollArea->setFrameShape(QFrame::NoFrame);
    m_ui->textScrollArea->setFrameShadow(QFrame::Plain);
    m_ui->textScrollArea->setAlignment(Qt::AlignVCenter);
    m_ui->textScrollArea->verticalScrollBar()->setStyleSheet(OCRUIObject::MScrollBarStyle03);
    m_ui->textScrollArea->horizontalScrollBar()->setStyleSheet(OCRUIObject::MScrollBarStyle04);

}

OCRApplication::~OCRApplication()
{
    deleteItems();
    delete m_applicationObject;
    delete m_ui;
}

QString OCRApplication::getClassName()
{
    return staticMetaObject.className();
}

OCRApplication *OCRApplication::instance()
{
    return m_instance;
}

void OCRApplication::quitWindowClose()
{
    m_applicationObject->windowCloseAnimation();
}

void OCRApplication::openButtonClicked()
{
    QStringList lists(OCRUtils::Widget::getOpenFilesDialog(this, "Images (*.png *.bmp *.jpg);;PDF Files(*.pdf)"));
    if(lists.isEmpty())
    {
        return;
    }

    clearButtonClicked();

    QString path = lists.first();
    bool isPdf = QFileInfo(path).suffix().toLower() == "pdf";
    if(isPdf)
    {
#ifdef OCR_BUILD_BY_PDF
        lists.clear();
        MuPDF::Document *document = MuPDF::loadDocument(path);
        for(int i=0; i<document->numPages(); i++)
        {
            OCRThreadItem *item = new OCRThreadItem(this);
            item->m_index = i;
            item->m_path = path;

            QLabel *ll = new QLabel(m_ui->pixScrollAreaWidget);
            ll->setPixmap(QPixmap::fromImage(document->page(i)->renderImage()).scaled(405, 405, Qt::KeepAspectRatio));
            m_ui->pixScrollAreaWidgetLayout->addWidget(ll);
            item->m_obj = ll;

            m_fileList << item;
        }
#endif
        return;
    }

    for(int i=0; i<lists.count(); ++i)
    {
        OCRThreadItem *item = new OCRThreadItem(this);
        item->m_index = i;
        item->m_path = lists[i];

        QLabel *ll = new QLabel(m_ui->pixScrollAreaWidget);
        ll->setPixmap(QPixmap(item->m_path).scaled(405, 405, Qt::KeepAspectRatio));
        m_ui->pixScrollAreaWidgetLayout->addWidget(ll);
        item->m_obj = ll;

        m_fileList << item;
    }
}

void OCRApplication::startButtonClicked()
{
    foreach(OCRThreadItem *item, m_fileList)
    {
        OCRThread *tread = new OCRThread(this);
        connect(tread, SIGNAL(findFinish()), SLOT(findFinish()));
        tread->start(item);
    }
}

void OCRApplication::clearButtonClicked()
{
    m_count = 0;
    deleteItems();
    OCRUtils::Core::dirRemoveRecursively("dir");
    m_ui->textScrollAreaWidget->clear();
}

void OCRApplication::findFinish()
{
    ++m_count;
    if(m_count == m_fileList.count())
    {
        QStringList files(QDir("dir").entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name));
        OCRObject::MIntList data;
        foreach(const QString &path, files)
        {
            QString fileName = QFileInfo(path).baseName();
            data << fileName.trimmed().toInt();
        }
        qSort(data.begin(), data.end(), qLess<int>());

        QString content;
        for(int i=0; i<data.count(); ++i)
        {
            QFile file(QString("%1/%2").arg("dir").arg(i));
            if(file.open(QFile::ReadOnly))
            {
                content.append(file.readAll() + "\r\n");
                content.append("============================================================\r\n");
                file.close();
            }

        }
        m_ui->textScrollAreaWidget->setText(content);
        OCRUtils::Core::dirRemoveRecursively("dir");
    }
}

void OCRApplication::deleteItems()
{
    while(!m_fileList.isEmpty())
    {
        OCRThreadItem *item = m_fileList.takeLast();
        delete item->m_obj;
        delete item;
    }
}
