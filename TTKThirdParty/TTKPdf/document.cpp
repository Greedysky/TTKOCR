#include "document.h"

extern "C" {
#include "mupdf/pdf.h"
}

namespace MuPDF
{
class Private
{
public:
    Private(const QString &path)
        : context(nullptr),
          document(nullptr)
    {
        // create context
        context = fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED);
        if(!context)
        {
            return;
        }

        // register the default file types
        fz_register_document_handlers(context);

        // open document
        fz_try(context)
        {
            document = fz_open_document(context, qPrintable(path));
        }
        fz_catch(context)
        {
            deinit();
        }
    }

    Private(const char *bytes, int length)
        : context(nullptr),
          document(nullptr)
    {
        // create context
        context = fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED);
        if(!context)
        {
            return;
        }

        // register the default file types
        fz_register_document_handlers(context);

        // open document
        fz_try(context)
        {
            // access to the bytes stream
            fz_stream* stream = fz_open_memory(context, (const unsigned char *)bytes, length);
            document = fz_open_document_with_stream(context, ".pdf", stream);
        }
        fz_catch(context)
        {
            deinit();
        }
    }

    ~Private()
    {
        deinit();
    }

    void deinit()
    {
        if(document)
        {
            fz_drop_document(context, document);
            document = nullptr;
        }

        if(context)
        {
            fz_drop_context(context);
            context = nullptr;
        }
    }

    QString info(const char *key)
    {
        pdf_document *xref = (pdf_document *)document;
        pdf_obj *info = pdf_dict_gets(context, pdf_trailer(context, xref), (char *)"Info");
        if(!info)
        {
            return {};
        }

        pdf_obj *obj = pdf_dict_gets(context, info, (char *)key);
        if(!obj)
        {
            return {};
        }

        char *str = pdf_new_utf8_from_pdf_string_obj(context, obj);
        const QString &value = QString::fromUtf8(str);
        free(str);
        return value;
    }

    int page;
    fz_context *context;
    fz_document *document;
};


Page::Page(Private *ptr)
    : d(ptr)
{

}

QImage Page::renderImage(float x, float y, float r) const
{
    fz_matrix ctm = fz_scale(x, y);
    ctm = fz_pre_rotate(ctm, r);

    fz_pixmap *pix = nullptr;
    fz_try(d->context)
    {
        pix = fz_new_pixmap_from_page_number(d->context, d->document, d->page, ctm, fz_device_rgb(d->context), 0);
    }
    fz_catch(d->context)
    {
        fz_drop_document(d->context, d->document);
        fz_drop_context(d->context);
        return {};
    }

    if(!pix)
    {
        return {};
    }

    const int width = fz_pixmap_width(d->context, pix);
    const int height = fz_pixmap_height(d->context, pix);
    QImage image(pix->samples, width, height, pix->stride, QImage::Format_RGB888);
    return image;
}


Document::Document(const QString &path)
    : d(new Private(path))
{

}

Document::Document(const QByteArray &bytes)
    : d(new Private(bytes.constData(), bytes.length()))
{

}

Document::~Document()
{
    delete d;
    d = nullptr;
}

bool Document::valid() const
{
    return d->context && d->document;
}

bool Document::needsPassword() const
{
    return fz_needs_password(d->context, d->document);
}

bool Document::authPassword(const QString &password)
{
    return fz_authenticate_password(d->context, d->document, qPrintable(password));
}

int Document::numPages() const
{
    int v = -1;
    fz_try(d->context)
    {
        v = fz_count_pages(d->context, d->document);
    }
    while (0);
    return v;
}

Page *Document::page(int index)
{
    d->page = index;
    return new Page(d);
}

QString Document::pdfVersion() const
{
    const pdf_document *xref = (pdf_document *)d->document;
    return QString::number(xref->version / 10.0f);
}

QString Document::title() const
{
    return d->info("Title");
}

QString Document::author() const
{
    return d->info("Author");
}

QString Document::subject() const
{
    return d->info("Subject");
}

QString Document::keywords() const
{
    return d->info("Keywords");
}

QString Document::creator() const
{
    return d->info("Creator");
}

QString Document::producer() const
{
    return d->info("Producer");
}

QDateTime Document::modDate() const
{
    const QString &v = d->info("ModDate");
    if(v.isEmpty())
    {
        return QDateTime();
    }

    // see pdf_reference_1.7.pdf 2.8.3 Dates
    return QDateTime::fromString(v.left(16), "'D:'yyyyMMddHHmmss");
}

QDateTime Document::creationDate() const
{
    const QString &v = d->info("CreationDate");
    if(v.isEmpty())
    {
        return QDateTime();
    }

    // see pdf_reference_1.7.pdf 2.8.3 Dates
    return QDateTime::fromString(v.left(16), "'D:'yyyyMMddHHmmss");
}
}
