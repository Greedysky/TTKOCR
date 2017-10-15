#include "mupdf-link.h"
#include "mupdf-link_p.h"
extern "C" {
#include <mupdf/fitz.h>
}
#include <QRectF>
#include <QString>

namespace MuPDF
{

Link::~Link()
{
    delete d;
}

/**
 * @brief Rect area of the link.
 */
QRectF Link::linkArea() const
{
    return QRectF(QPointF(d->link->rect.x0, d->link->rect.y0),
                  QPointF(d->link->rect.x1, d->link->rect.y1));
}

/**
 * @brief Page number(start from 0).
 */
int LinkGoto::page() const
{
    return d->dest.ld.gotor.page;
}

/**
 * @brief Fit horizontally.
 */
bool LinkGoto::fitHorizontally() const
{
    return d->dest.ld.gotor.flags & fz_link_flag_fit_h;
}

/**
 * @brief Fit vertically.
 */
bool LinkGoto::fitVertically() const
{
    return d->dest.ld.gotor.flags & fz_link_flag_fit_v;
}

/**
 * @brief Zoom ratio.
 *
 * @return Do not change zoom ratio when 0.0f is returned.
 */
float LinkGoto::zoom() const
{
    if (d->dest.ld.gotor.flags & fz_link_flag_r_is_zoom) {
        return d->dest.ld.gotor.rb.x;
    }

    return 0.0f;
}

/**
 * @brief A UTF-8 encoded URI to launch.
 */
QString LinkURI::uri() const
{
    return d->dest.ld.uri.uri;
}

/**
 * If true, the x and y coords (as ints, in user
 * space) should be appended to the URI before launch.
 */
bool LinkURI::isMap() const
{
    return d->dest.ld.uri.is_map;
}

/**
 * @brief A UTF-8 file specification to launch.
 */
QString LinkLaunch::file() const
{
    return d->dest.ld.launch.file_spec;
}

/**
 * @brief If true, the destination should be launched in a new window.
 */
bool LinkLaunch::newWindow() const
{
    return d->dest.ld.launch.new_window;
}

/**
 * @brief If true, file() is a URI to launch.
 */
bool LinkLaunch::isURI() const
{
    return d->dest.ld.launch.is_uri;
}

/**
 * @brief The named action to perform.
 */
QString LinkNamed::named() const
{
    return d->dest.ld.named.named;
}

/**
 * @brief Page number(start from 0).
 *
 * @return -1 suggesting that destination is given by destination().
 */
int LinkGotoR::page() const
{
    return d->dest.ld.gotor.page;
}

/**
 * @brief The target destination name to be resolved in the file().
 *
 * @return Maybe empty.
 */
QString LinkGotoR::destination() const
{
    return d->dest.ld.gotor.dest;
}

/**
 * @brief A pointer to a remote file specification (UTF-8).
 * If set, this destination should cause a new file to be opened.
 */
QString LinkGotoR::file() const
{
    return d->dest.ld.gotor.file_spec;
}

/**
 * @brief If true, the destination should open in a new window.
 */
bool LinkGotoR::newWindow() const
{
    return d->dest.ld.gotor.new_window;
}

}
