/*
  +----------------------------------------------------------------------+
  | Author: yoya@awm.jp                                                  |
  +----------------------------------------------------------------------+
*/

#ifndef __SWF_SHAPE_RECORD_H__
#define __SWF_SHAPE_RECORD_H__

#include "swf_tag.h"
#include "swf_styles_count.h"
#include "swf_shape_record_end.h"
#include "swf_shape_record_setup.h"
#include "swf_shape_record_edge.h"

typedef struct swf_shape_record_ {
    union {
        unsigned char first_6bits : 6;
        swf_shape_record_end_t   shape_end;
        swf_shape_record_setup_t shape_setup;
        swf_shape_record_edge_t  shape_edge;
    } shape;
    struct swf_shape_record_ *next;
} swf_shape_record_t;

extern int swf_shape_record_parse(bitstream_t *bs,
                                  swf_shape_record_t *shape_record,
                                  swf_tag_t *tag, swf_styles_count_t *count);
extern int swf_shape_record_build(bitstream_t *bs,
                                  swf_shape_record_t *shape_record,
                                  swf_tag_t *tag, swf_styles_count_t *count);
extern int swf_shape_record_print(swf_shape_record_t *shape_record,
                                  int indent_depth, swf_tag_t *tag,
                                  swf_styles_count_t *count);
extern int swf_shape_record_delete(swf_shape_record_t *shape_record);

#endif /* __SWF_SHAPE_RECORD_H__ */