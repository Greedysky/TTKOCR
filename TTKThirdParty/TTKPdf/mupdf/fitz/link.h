// Copyright (C) 2004-2022 Artifex Software, Inc.
//
// This file is part of MuPDF.
//
// MuPDF is free software: you can redistribute it and/or modify it under the
// terms of the GNU Affero General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// MuPDF is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more
// details.
//
// You should have received a copy of the GNU Affero General Public License
// along with MuPDF. If not, see <https://www.gnu.org/licenses/agpl-3.0.en.html>
//
// Alternative licensing terms are available from the licensor.
// For commercial licensing, see <https://www.artifex.com/> or contact
// Artifex Software, Inc., 39 Mesa Street, Suite 108A, San Francisco,
// CA 94129, USA, for further information.

#ifndef MUPDF_FITZ_LINK_H
#define MUPDF_FITZ_LINK_H

#include "mupdf/fitz/system.h"
#include "mupdf/fitz/context.h"
#include "mupdf/fitz/geometry.h"
#include "mupdf/fitz/types.h"

typedef struct fz_link fz_link;
typedef void (fz_link_set_rect_fn)(fz_context *ctx, fz_link *link, fz_rect rect);
typedef void (fz_link_set_uri_fn)(fz_context *ctx, fz_link *link, const char *uri);
typedef void (fz_link_drop_link_fn)(fz_context *ctx, fz_link *link);

/**
	fz_link is a list of interactive links on a page.

	There is no relation between the order of the links in the
	list and the order they appear on the page. The list of links
	for a given page can be obtained from fz_load_links.

	A link is reference counted. Dropping a reference to a link is
	done by calling fz_drop_link.

	rect: The hot zone. The area that can be clicked in
	untransformed coordinates.

	uri: Link destinations come in two forms: internal and external.
	Internal links refer to other pages in the same document.
	External links are URLs to other documents.

	next: A pointer to the next link on the same page.
*/
typedef struct fz_link
{
	int refs;
	struct fz_link *next;
	fz_rect rect;
	char *uri;
	fz_link_set_rect_fn *set_rect_fn;
	fz_link_set_uri_fn *set_uri_fn;
	fz_link_drop_link_fn *drop;
} fz_link;

typedef enum
{
	FZ_LINK_DEST_FIT,
	FZ_LINK_DEST_FIT_B,
	FZ_LINK_DEST_FIT_H,
	FZ_LINK_DEST_FIT_BH,
	FZ_LINK_DEST_FIT_V,
	FZ_LINK_DEST_FIT_BV,
	FZ_LINK_DEST_FIT_R,
	FZ_LINK_DEST_XYZ
} fz_link_dest_type;

typedef struct
{
	fz_location loc;
	fz_link_dest_type type;
	float x, y, w, h, zoom;
} fz_link_dest;

fz_link_dest fz_make_link_dest_none(void);
fz_link_dest fz_make_link_dest_xyz(int chapter, int page, float x, float y, float z);

/**
	Create a new link record.

	next is set to NULL with the expectation that the caller will
	handle the linked list setup. Internal function.

	Different document types will be implemented by deriving from
	fz_link. This macro allocates such derived structures, and
	initialises the base sections.
*/
fz_link *fz_new_link_of_size(fz_context *ctx, int size, fz_rect rect, const char *uri);
#define fz_new_derived_link(CTX,TYPE,RECT,URI) \
	   ((TYPE *)Memento_label(fz_new_link_of_size(CTX,sizeof(TYPE),RECT,URI),#TYPE))

/**
	Increment the reference count for a link. The same pointer is
	returned.

	Never throws exceptions.
*/
fz_link *fz_keep_link(fz_context *ctx, fz_link *link);

/**
	Decrement the reference count for a link. When the reference
	count reaches zero, the link is destroyed.

	When a link is freed, the reference for any linked link (next)
	is dropped too, thus an entire linked list of fz_link's can be
	freed by just dropping the head.
*/
void fz_drop_link(fz_context *ctx, fz_link *link);

/**
	Query whether a link is external to a document (determined by
	uri containing a ':', intended to match with '://' which
	separates the scheme from the scheme specific parts in URIs).
*/
int fz_is_external_link(fz_context *ctx, const char *uri);

void fz_set_link_rect(fz_context *ctx, fz_link *link, fz_rect rect);
void fz_set_link_uri(fz_context *ctx, fz_link *link, const char *uri);

#endif
