#ifndef MUPDF_LINK_P_H
#define MUPDF_LINK_P_H

extern "C" {
#include <mupdf/fitz.h>
}

namespace MuPDF
{

class LinkPrivate
{
public:
    LinkPrivate(fz_link *l) : link(l), dest(l->dest) {}
    LinkPrivate(fz_link_dest d) : link(nullptr), dest(d) {}

    fz_link *link;
    fz_link_dest dest;
};

}

#endif // end MUPDF_LINK_P_H
