#include <stdio.h>
#include "bitstream.h"
#include "swf_shape_with_style.h"

int
swf_shape_with_style_parse(bitstream_t *bs,
                           swf_shape_with_style_t *shape_with_style,
                           swf_tag_t *tag) {
    int result;
    result = swf_styles_parse(bs, &(shape_with_style->styles), tag);
    if (result) {
        return result;
    }
    result = swf_shape_record_parse(bs, &(shape_with_style->shape_records),
                                    tag,
                                    &(shape_with_style->styles.styles_count));
    return result;
}

int
swf_shape_with_style_build(bitstream_t *bs, swf_shape_with_style_t *shape_with_style, swf_tag_t *tag) {
    swf_styles_build(bs, &(shape_with_style->styles), tag);
    swf_shape_record_build(bs, &(shape_with_style->shape_records), tag,
                           &(shape_with_style->styles.styles_count));
    return 0;
}

int
swf_shape_with_style_print(swf_shape_with_style_t *shape_with_style, int indent_depth, swf_tag_t *tag) {
    swf_styles_print(&(shape_with_style->styles), indent_depth, tag);
    swf_shape_record_print(&(shape_with_style->shape_records), indent_depth,
                           tag, &(shape_with_style->styles.styles_count));
    return 0;
}