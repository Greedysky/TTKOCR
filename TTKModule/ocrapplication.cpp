#include "ocrapplication.h"
#include "ui_ocrapplication.h"
#include "ocrapplicationobject.h"
#include "ocrfunctionlistuiobject.h"
#include "ocrfileutils.h"
#include "ocrgrabwidget.h"
#include "ocrthread.h"
#include "ocruiobject.h"
#ifdef TTK_BUILD_BY_PDF
#  include "include/mupdf-qt.h"
#endif
#include <QScrollBar>

OCRApplication *OCRApplication::m_instance = nullptr;

OCRApplication::OCRApplication(QWidget *parent)
    : TTKAbstractMoveResizeWidget(false, parent),
      m_ui(new Ui::OCRApplication),
      m_count(0)
{
    m_instance = this;

    m_applicationObject = new OCRApplicationObject(this);

    m_ui->setupUi(this);

    setMinimumSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    setMaximumSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);

    m_ui->iconLabel->setPixmap(QPixmap(":/image/lb_app_logo").scaled(m_ui->iconLabel->size()));
    m_ui->background->setPixmap(QPixmap(":/image/lb_background").scaled(size()));

    m_ui->minButton->setStyleSheet(TTK::UI::FuncMin);
    connect(m_ui->minButton, SIGNAL(clicked()), SLOT(showMinimized()));

    m_ui->closeButton->setStyleSheet(TTK::UI::FuncClose);
    connect(m_ui->closeButton, SIGNAL(clicked()), SLOT(quitWindowClose()));

    m_ui->openButton->setStyleSheet(TTK::UI::PushButtonStyle01);
    m_ui->screenshotButton->setStyleSheet(TTK::UI::PushButtonStyle01);
    m_ui->startButton->setStyleSheet(TTK::UI::PushButtonStyle01);
    m_ui->clearButton->setStyleSheet(TTK::UI::PushButtonStyle01);

    connect(m_ui->openButton, SIGNAL(clicked()), SLOT(openButtonClicked()));
    connect(m_ui->screenshotButton, SIGNAL(clicked()), SLOT(screenshotButtonClicked()));
    connect(m_ui->startButton, SIGNAL(clicked()), SLOT(startButtonClicked()));
    connect(m_ui->clearButton, SIGNAL(clicked()), SLOT(clearButtonClicked()));

    m_ui->pixScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ui->pixScrollArea->setWidgetResizable(true);
    m_ui->pixScrollArea->setFrameShape(QFrame::NoFrame);
    m_ui->pixScrollArea->setFrameShadow(QFrame::Plain);
    m_ui->pixScrollArea->setAlignment(Qt::AlignVCenter);
    m_ui->pixScrollArea->verticalScrollBar()->setStyleSheet(TTK::UI::ScrollBarStyle03);

    m_ui->textScrollArea->setWidgetResizable(true);
    m_ui->textScrollArea->setFrameShape(QFrame::NoFrame);
    m_ui->textScrollArea->setFrameShadow(QFrame::Plain);
    m_ui->textScrollArea->setAlignment(Qt::AlignVCenter);
    m_ui->textScrollArea->verticalScrollBar()->setStyleSheet(TTK::UI::ScrollBarStyle03);
    m_ui->textScrollArea->horizontalScrollBar()->setStyleSheet(TTK::UI::ScrollBarStyle04);

    /////////// Mouse tracking
    setObjectsTracking(QWidgetList() << m_ui->background);
}

OCRApplication::~OCRApplication()
{
    deleteItems();
    delete m_applicationObject;
    delete m_ui;
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
    const QStringList list(TTK::File::getOpenFileNames(this, "Image Files (*.png *.bmp *.jpg);;PDF Files (*.pdf)"));
    if(list.isEmpty())
    {
        return;
    }

    clearButtonClicked();

    const QString &path = list.front();
    if(QFileInfo(path).suffix().toLower() == "pdf")
    {
#ifdef TTK_BUILD_BY_PDF
        list.clear();
        MuPDF::Document *document = MuPDF::loadDocument(path);
        for(int i = 0; i < document->numPages(); ++i)
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

    for(int i = 0; i < list.count(); ++i)
    {
        OCRThreadItem *item = new OCRThreadItem(this);
        item->m_index = i;
        item->m_path = list[i];

        QLabel *ll = new QLabel(m_ui->pixScrollAreaWidget);
        ll->setPixmap(QPixmap(item->m_path).scaled(405, 405, Qt::KeepAspectRatio));
        m_ui->pixScrollAreaWidgetLayout->addWidget(ll);
        item->m_obj = ll;

        m_fileList << item;
    }
}

void OCRApplication::screenshotButtonClicked()
{
    OCRGrabWidget *w = new OCRGrabWidget(this);
    connect(w, SIGNAL(pixmapChanged(QPixmap)), SLOT(pixmapChanged(QPixmap)));
    w->show();
}

void OCRApplication::startButtonClicked()
{
    if(m_fileList.isEmpty())
    {
        return;
    }

    m_count = 0;
    TTK::File::removeRecursively(DIR_PREFIX);

    for(OCRThreadItem *item : qAsConst(m_fileList))
    {
        OCRThread *tread = new OCRThread(item);
        connect(tread, SIGNAL(findFinish()), SLOT(findFinish()));
        tread->start(item);
    }

    stateChanged(true);
}

void OCRApplication::clearButtonClicked()
{
    if(m_fileList.isEmpty())
    {
        return;
    }

    m_count = 0;
    deleteItems();
    TTK::File::removeRecursively(DIR_PREFIX);
    m_ui->textScrollAreaWidget->clear();
}

void OCRApplication::findFinish()
{
    ++m_count;
    if(m_count == m_fileList.count())
    {
        const QStringList files(QDir(DIR_PREFIX).entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name));
        TTKIntList data;
        for(const QString &path : qAsConst(files))
        {
            const QString &fileName = QFileInfo(path).baseName();
            data << fileName.trimmed().toInt();
        }
        std::sort(data.begin(), data.end());

        QString content;
        for(int i = 0; i < m_fileList.count(); ++i)
        {
            QFile file(QString("%1/%2").arg(DIR_PREFIX).arg(i));
            if(file.open(QIODevice::ReadOnly))
            {
                content.append(file.readAll() + "\r\n");
                file.close();
            }
            else
            {
                content.append("No OCR Data Found \r\n");
            }
            content.append("============================================================\r\n");
        }

        m_ui->textScrollAreaWidget->setText(content);
        TTK::File::removeRecursively(DIR_PREFIX);

        stateChanged(false);
    }
}

void OCRApplication::pixmapChanged(const QPixmap &pix)
{
    if(!QDir().exists(DOWNLOAD_DIR_FULL))
    {
        QDir().mkpath(DOWNLOAD_DIR_FULL);
    }

    const QString &filename = DOWNLOAD_DIR_FULL + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + JPG_FILE;
    pix.save(filename, nullptr, 100);

    OCRThreadItem *item = new OCRThreadItem(this);
    item->m_index = m_fileList.count();
    item->m_path = filename;

    QLabel *ll = new QLabel(m_ui->pixScrollAreaWidget);
    ll->setPixmap(pix.scaled(405, 405, Qt::KeepAspectRatio));
    m_ui->pixScrollAreaWidgetLayout->addWidget(ll);
    item->m_obj = ll;

    m_fileList << item;
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

void OCRApplication::stateChanged(bool state)
{
    if(state)
    {
        m_ui->stateLabel->raise();
        m_ui->stateLabel->show();
        m_ui->stateLabel->start();
    }
    else
    {
        m_ui->stateLabel->stop();
        m_ui->stateLabel->hide();
    }

    m_ui->openButton->setEnabled(!state);
    m_ui->screenshotButton->setEnabled(!state);
    m_ui->startButton->setEnabled(!state);
    m_ui->clearButton->setEnabled(!state);
}
