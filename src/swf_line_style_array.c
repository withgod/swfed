#include <stdio.h>
#include <stdlib.h> // calloc
#include "bitstream.h"
#include "swf_line_style_array.h"

int
swf_line_style_array_parse(bitstream_t *bs,
                           swf_line_style_array_t *shape_with_style,
                           swf_tag_t *tag) {
    int i;
    int result;
    result = bitstream_getbyte(bs);
    if (result == -1) {
        fprintf(stderr, "swf_line_style_array_parse: bitstream_getbyte failed at (L%d)\n", __LINE__);
        return 1;
    }
    shape_with_style->count = result;
    if ((tag->tag != 2) && // ! DefineShape
         (shape_with_style->count == 255)) {
        result = bitstream_getbytesLE(bs, 2);
        if (result == -1) {
            fprintf(stderr, "swf_line_style_array_parse: bitstream_getbyte failed at (L%d)\n", __LINE__);
            return 1;
        }
        shape_with_style->count = result;
    }
    if (1000 < shape_with_style->count) { // XXX
        fprintf(stderr, "swf_line_style_array_parse: too many count(%d)\n",
                shape_with_style->count);
        return 1;
    }
    shape_with_style->line_style = calloc(shape_with_style->count, sizeof(swf_line_style_t));
    for (i = 0 ; i < shape_with_style->count ; i++) {
        result = swf_line_style_parse(bs, &(shape_with_style->line_style[i]), tag);
        if (result) {
            shape_with_style->count = i; // XXX
            return result;
        }
    }
    return 0;
}

int
swf_line_style_array_build(bitstream_t *bs, swf_line_style_array_t *shape_with_style, swf_tag_t *tag) {
    int i;
    if ((tag->tag != 2) || // ! DefineShape
        (255 <= shape_with_style->count)) {
        bitstream_putbyte(bs, 255);
        bitstream_putbytesLE(bs, shape_with_style->count, 2);
    } else {
        bitstream_putbyte(bs, shape_with_style->count);
    }
    for (i = 0 ; i < shape_with_style->count ; i++) {
        swf_line_style_build(bs, &(shape_with_style->line_style[i]), tag);
    }
    return 0;
}

int
swf_line_style_array_print(swf_line_style_array_t *shape_with_style, int indent_depth, swf_tag_t *tag) {
    int i;
    print_indent(indent_depth);
    printf("shape_with_style->count=%u\n", shape_with_style->count);
    for (i = 0 ; i < shape_with_style->count ; i++) {
        swf_line_style_print(&(shape_with_style->line_style[i]),
                             indent_depth + 1, tag);
    }
    return 0;
}

int
swf_line_style_array_delete(swf_line_style_array_t *line_style_array) {
    free(line_style_array->line_style);
    return 0;
}