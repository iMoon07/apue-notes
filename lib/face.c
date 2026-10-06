#include "moon.h"

#define STBI_NO_HDR
#define STBI_NO_LINEAR
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define FACE_COLUMNS 2
#define FACE_ROWS 1
#define KITTY_CHUNK_SIZE 4096

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

static const char base64_table[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char *
base64_encode(const unsigned char *data, size_t length)
{
    char *output;
    size_t output_length;
    size_t input_index;
    size_t output_index;

    output_length = ((length + 2) / 3) * 4;

    output = malloc(output_length + 1);
    if (output == NULL)
        return NULL;

    input_index = 0;
    output_index = 0;

    while (input_index < length) {
        unsigned int a;
        unsigned int b;
        unsigned int c;
        unsigned int value;

        a = input_index < length ? data[input_index++] : 0;
        b = input_index < length ? data[input_index++] : 0;
        c = input_index < length ? data[input_index++] : 0;

        value = (a << 16) | (b << 8) | c;

        output[output_index++] = base64_table[(value >> 18) & 0x3f];
        output[output_index++] = base64_table[(value >> 12) & 0x3f];
        output[output_index++] = base64_table[(value >> 6) & 0x3f];
        output[output_index++] = base64_table[value & 0x3f];
    }

    if (length % 3 == 1) {
        output[output_length - 2] = '=';
        output[output_length - 1] = '=';
    } else if (length % 3 == 2) {
        output[output_length - 1] = '=';
    }

    output[output_length] = '\0';

    return output;
}

static int
get_face_path(char *path, size_t path_size)
{
    char executable_path[PATH_MAX];
    char *last_slash;
    ssize_t length;
    int result;

    length = readlink("/proc/self/exe",
                      executable_path,
                      sizeof(executable_path) - 1);
    if (length < 0)
        return -1;

    executable_path[length] = '\0';

    last_slash = strrchr(executable_path, '/');
    if (last_slash == NULL)
        return -1;

    *last_slash = '\0';

    result = snprintf(path,
                      path_size,
                      "%s/../assets/foto-raja.jpg",
                      executable_path);

    if (result < 0 || (size_t)result >= path_size)
        return -1;

    return 0;
}

static void
kitty_display_rgb(const unsigned char *pixels, int width, int height)
{
    char *encoded;
    size_t raw_size;
    size_t encoded_length;
    size_t offset;

    raw_size = (size_t)width * (size_t)height * 3;

    encoded = base64_encode(pixels, raw_size);
    if (encoded == NULL)
        return;

    encoded_length = strlen(encoded);
    offset = 0;

    while (offset < encoded_length) {
        size_t chunk_length;
        int more_data;

        chunk_length = encoded_length - offset;
        if (chunk_length > KITTY_CHUNK_SIZE)
            chunk_length = KITTY_CHUNK_SIZE;

        more_data = offset + chunk_length < encoded_length;

        if (offset == 0) {
            printf("\033_Ga=T,f=24,s=%d,v=%d,c=%d,r=%d,m=%d;",
                   width,
                   height,
                   FACE_COLUMNS,
                   FACE_ROWS,
                   more_data);
        } else {
            printf("\033_Gm=%d;", more_data);
        }

        fwrite(encoded + offset, 1, chunk_length, stdout);
        printf("\033\\");

        offset += chunk_length;
    }

    free(encoded);
}

void
moon_face(void)
{
    char face_path[PATH_MAX];
    unsigned char *pixels;
    int width;
    int height;
    int channels;

    if (get_face_path(face_path, sizeof(face_path)) < 0) {
        printf("> ");
        fflush(stdout);
        return;
    }

    pixels = stbi_load(face_path, &width, &height, &channels, 3);
    if (pixels == NULL) {
        printf("> ");
        fflush(stdout);
        return;
    }

    kitty_display_rgb(pixels, width, height);

    stbi_image_free(pixels);

    printf("\033[%dC", FACE_COLUMNS);
    fflush(stdout);
}
