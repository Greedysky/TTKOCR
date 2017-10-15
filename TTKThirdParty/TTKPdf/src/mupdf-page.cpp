#include "mupdf-page.h"
#include "mupdf-page_p.h"
#include "mupdf-document.h"
#include "mupdf-document_p.h"
#include "mupdf-textbox.h"
#include "mupdf-textbox_p.h"
extern "C" {
#include <mupdf/fitz.h>
}
#include <QImage>
#include <QSizeF>

static void clear_bgr_samples_with_value(
        unsigned char *samples, int size,
        int b, int g, int r, int a)
{
    int i = 0;

    while (i < size) {
        *(samples + i++) = b;
        *(samples + i++) = g;
        *(samples + i++) = r;
        *(samples + i++) = a;
    }
}

static void clear_rgb_samples_with_value(
        unsigned char *samples, int size,
        int b, int g, int r, int a)
{
    int i = 0;

    while (i < size) {
        *(samples + i++) = r;
        *(samples + i++) = g;
        *(samples + i++) = b;
        *(samples + i++) = a;
    }
}

/**
 * @brief Clean up image data when the last copy of the QImage is destoryed.
 */
static inline void imageCleanupHandler(void *data)
{
    unsigned char *samples = static_cast<unsigned char *>(data);

    if (samples) {
        delete []samples;
    }
}

namespace MuPDF
{

QPointF mapToOrigin(const QPointF &pos, float scaleX, float scaleY, float rotation)
{
    fz_matrix transform = fz_identity;
    fz_matrix inverse;
    fz_point point;

    // build matrix
    fz_rotate(&transform, rotation);
    fz_pre_scale(&transform, scaleX, scaleY);

    // invert matrix
    fz_invert_matrix(&inverse, &transform);

    // map
    point.x = pos.x();
    point.y = pos.y();
    fz_transform_point(&point, &inverse);

    return QPointF(point.x, point.y);
}

QSizeF mapToOrigin(const QSizeF &size, float scaleX, float scaleY, float rotation)
{
    fz_matrix transform = fz_identity;
    fz_matrix inverse;
    fz_point vector;

    // build matrix
    fz_rotate(&transform, rotation);
    fz_pre_scale(&transform, scaleX, scaleY);

    // invert matrix
    fz_invert_matrix(&inverse, &transform);

    // map
    vector.x = size.width();
    vector.y = size.height();
    fz_transform_vector(&vector, &inverse);

    return QSizeF(vector.x, vector.y);
}

QRectF mapToOrigin(const QRectF &rect, float scaleX, float scaleY, float rotation)
{
    fz_matrix transform = fz_identity;
    fz_matrix inverse;
    fz_rect r;

    // build matrix
    fz_rotate(&transform, rotation);
    fz_pre_scale(&transform, scaleX, scaleY);

    // invert matrix
    fz_invert_matrix(&inverse, &transform);

    // map
    r.x0 = rect.left();
    r.y0 = rect.top();
    r.x1 = rect.right();
    r.y1 = rect.bottom();
    fz_transform_rect(&r, &inverse);

    return QRectF(r.x0, r.y0, r.x1 - r.x0, r.y1 - r.y0);
}

QPointF mapFromOrigin(const QPointF &pos, float scaleX, float scaleY, float rotation)
{
    fz_matrix transform = fz_identity;
    fz_point point;

    // build matrix
    fz_rotate(&transform, rotation);
    fz_pre_scale(&transform, scaleX, scaleY);

    // map
    point.x = pos.x();
    point.y = pos.y();
    fz_transform_point(&point, &transform);

    return QPointF(point.x, point.y);
}

QSizeF mapFromOrigin(const QSizeF &size, float scaleX, float scaleY, float rotation)
{
    fz_matrix transform = fz_identity;
    fz_point vector;

    // build matrix
    fz_rotate(&transform, rotation);
    fz_pre_scale(&transform, scaleX, scaleY);

    // map
    vector.x = size.width();
    vector.y = size.height();
    fz_transform_vector(&vector, &transform);

    return QSizeF(vector.x, vector.y);
}

QRectF mapFromOrigin(const QRectF &rect, float scaleX, float scaleY, float rotation)
{
    fz_matrix transform = fz_identity;
    fz_rect r;

    // build matrix
    fz_rotate(&transform, rotation);
    fz_pre_scale(&transform, scaleX, scaleY);

    // map
    r.x0 = rect.left();
    r.y0 = rect.top();
    r.x1 = rect.right();
    r.y1 = rect.bottom();
    fz_transform_rect(&r, &transform);

    return QRectF(r.x0, r.y0, r.x1 - r.x0, r.y1 - r.y0);
}

Page::~Page()
{
    delete d;
    d = NULL;
}

PagePrivate::PagePrivate(DocumentPrivate *dp, int index)
    : documentp(dp)
    , context(documentp->context)
    , document(documentp->document)
    , page(NULL)
    , display_list(NULL)
    , text_sheet(NULL)
    , text_page(NULL)
    , transparent(documentp->transparent)
    , b(documentp->b), g(documentp->g), r(documentp->r), a(documentp->a)
{
    fz_try(context)
    {
        fz_rect bounds;
        fz_device *list_device;
        fz_device *text_device;

        // load page
        page = fz_load_page(context, document, index);
        
        // display list
        display_list = fz_new_display_list(context);
        list_device = fz_new_list_device(context, display_list);
        fz_run_page(context, page, list_device, &fz_identity, NULL);
        fz_drop_device(context, list_device);

        // create text sheet and text page
        text_sheet = fz_new_text_sheet(context);
        text_page = fz_new_text_page(context);
        text_device = fz_new_text_device(context, text_sheet, text_page);
        fz_bound_page(context, page, &bounds);
        fz_run_display_list(context, display_list, text_device, &fz_identity, &bounds, NULL);
        fz_drop_device(context, text_device);
    }
    fz_catch(context)
    {
        deleteData();
    }
}

/**
 * @brief Check whether this page object is valid.
 */
bool Page::isValid() const
{
    return (d && d->page) ? true : false;
}

/**
 * @brief Render page to QImage
 *
 * @param scaleX scale for X direction
 *               (Default value: 1.0f; >1.0f: zoom in; <1.0f: zoom out)
 * @param scaleY scale for Y direction
 *               (Default value: 1.0f; >1.0f: zoom in; <1.0f: zoom out)
 * @param rotation degree of clockwise rotation (Range: [0.0f, 360.0f))
 *
 * @return This function will return a empty QImage if failed.
 */
QImage Page::renderImage(float scaleX, float scaleY, float rotation) const
{
    fz_pixmap *pixmap = NULL;
    unsigned char *samples = NULL;
    unsigned char *copyed_samples = NULL;
    int width = 0;
    int height = 0;
    int size = 0;

    // build transform matrix
    fz_matrix transform = fz_identity;
    fz_rotate(&transform, rotation);
    fz_pre_scale(&transform, scaleX, scaleY);

    // get transformed page size
    fz_rect bounds;
    fz_irect bbox;
    fz_bound_page(d->context, d->page, &bounds);
    fz_transform_rect(&bounds, &transform);
    fz_round_rect(&bbox, &bounds);

    // render to pixmap
    fz_device *dev = NULL;
    fz_try(d->context)
    {
        // fz_pixmap will always include a separate alpha channel
#if QT_VERSION < 0x050200
        pixmap = fz_new_pixmap_with_bbox(d->context, fz_device_bgr(d->context), &bbox);
#else
        // use rgba for Qt5.2
        pixmap = fz_new_pixmap_with_bbox(d->context, fz_device_rgb(d->context), &bbox);
#endif
        samples = fz_pixmap_samples(d->context, pixmap);
        width = fz_pixmap_width(d->context, pixmap);
        height = fz_pixmap_height(d->context, pixmap);
        size = width * height * 4;
        if (!d->transparent) {
            if (d->b >= 0 && d->g >= 0 && d->r >= 0 && d->a >= 0) {
                // with user defined background color
#if QT_VERSION < 0x050200
                clear_bgr_samples_with_value(samples, size, d->b, d->g, d->r, d->a);
#else
                // use rgba for Qt5.2
                clear_rgb_samples_with_value(samples, size, d->b, d->g, d->r, d->a);
#endif
            } else {
                // with white background
                fz_clear_pixmap_with_value(d->context, pixmap, 0xff);
            }
        }
        dev = fz_new_draw_device(d->context, pixmap);
        fz_run_display_list(d->context, d->display_list, dev, &transform, &bounds, NULL);
    }
    fz_always(d->context)
    {
        if (dev) {
            fz_drop_device(d->context, dev);
        }
        dev = NULL;
    }
    fz_catch(d->context)
    {
        if (pixmap) {
            fz_drop_pixmap(d->context, pixmap);
        }
        pixmap = NULL;
    }

    // render to QImage
    QImage image;
    if (NULL == pixmap) {
        return image;
    }
    copyed_samples = new unsigned char[size];
    memcpy(copyed_samples, samples, size);
    fz_drop_pixmap(d->context, pixmap);
#if QT_VERSION < 0x050200
    #if QT_VERSION >= 0x050000
    // most computers use little endian, so Format_ARGB32 means bgra order
    // note: this is not correct for computers with big endian architecture
    image = QImage(copyed_samples,
            width, height, QImage::Format_ARGB32, imageCleanupHandler, copyed_samples);
    #else
    image = QImage(copyed_samples,
            width, height, QImage::Format_ARGB32);
//    if(copyed_samples)
//    {
//        delete []copyed_samples;
//    }
    #endif
#else
    // with Qt 5.2, Format_RGBA8888 is correct for any architecture
    image = QImage(copyed_samples,
            width, height, QImage::Format_RGBA8888, imageCleanupHandler, copyed_samples);
#endif
    return image;
}

/**
 * @brief %Page size at 72 dpi
 */
QSizeF Page::size() const
{
    fz_rect rect;

    fz_bound_page(d->context, d->page, &rect);
    return QSizeF(rect.x1 - rect.x0, rect.y1 - rect.y0);
}

/**
 * @brief Whether to do transparent page rendering.
 * This function modify setting of current page only.
 * For global setting, use Document::setTransparentRendering() instead.
 *
 * @param enable True: transparent; False: not transparent(default).
 */
void Page::setTransparentRendering(bool enable)
{
    d->transparent = enable;
}

/**
 * @brief Set background color.
 * This function modify setting of current page only.
 * For global setting, use Document::setBackgroundColor() instead.
 *
 * @note This function will only work when page is not transparent.
 * This function won't change content of your file, it only change
 * the way you render the page.
 *
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 * @param a alpha channel(default with non transparent)
 */
void Page::setBackgroundColor(int r, int g, int b, int a)
{
    d->r = r;
    d->g = g;
    d->b = b;
    d->a = a;
}

/**
 * @brief Return the text in a rect.
 *
 * @param rect original rect (72 dpi), not transformed rect
 */
QString Page::text(const QRectF &rect) const
{
    QString ret;
    fz_rect r;
    char *str;

    // build fz_rect
    r.x0 = rect.left();
    r.y0 = rect.top();
    r.x1 = rect.right();
    r.y1 = rect.bottom();
    
    // get text
    if (!fz_is_infinite_rect(&r)) {
        str = fz_copy_selection(d->context, d->text_page, r);
        ret = QString::fromUtf8(str);
        free(str);
    }

    return ret;
}

/**
 * @brief Return all text boxes of the page.
 *
 * @note The returned text boxes should be deleted when they are no longer used.
 * @note Sizes of the returned text boxes are at 72 dpi.
 */
QList<TextBox *> Page::textList() const
{
    QList<TextBox *> ret;
    TextBox *box;
    TextBoxPrivate *boxp;
    fz_text_block *block;
    fz_text_line *line;
    fz_text_span *span;

    for (int block_num = 0; block_num < d->text_page->len; ++block_num) {
        // get block
        if (d->text_page->blocks[block_num].type != FZ_PAGE_BLOCK_TEXT) {
            continue;
        }
        block = d->text_page->blocks[block_num].u.text;

        for (line = block->lines; line < block->lines + block->len; ++line) { // lines
            for (span = line->first_span; span; span = span->next) { // spans
                boxp = new TextBoxPrivate(d->context, span);
                box = new TextBox(boxp);
                ret << box;
            }
        }
    }

    return ret;
}

PagePrivate::~PagePrivate()
{
    if (page) {
        deleteData();
        documentp->pages.removeAt(documentp->pages.indexOf(this));
    }
}

} // end namespace MuPDF
