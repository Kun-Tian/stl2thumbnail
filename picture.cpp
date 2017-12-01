#include "picture.h"

#include <png.h>

Picture::Picture(unsigned size)
    : m_size(size)
    , m_stride(size * m_depth)
{
    m_buffer.resize(size * m_stride); // rgb 8bit
}

Byte* Picture::data()
{
    return m_buffer.data();
}

void Picture::save(const std::string& filename)
{
    auto fd = fopen(filename.c_str(), "wb");

    auto png_ptr  = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    auto info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fd);
    png_set_IHDR(png_ptr, info_ptr, m_size, m_size,
        8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);

    for (size_t row = 0; row < m_size; ++row)
    {
        png_write_row(png_ptr, m_buffer.data() + row * m_stride);
    }

    png_write_end(png_ptr, nullptr);

    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&png_ptr, nullptr);

    fclose(fd);
}

void Picture::setRGB(unsigned x, unsigned y, Byte r, Byte g, Byte b)
{
    if (x >= m_size || y >= m_size)
        return;

    m_buffer[y * m_stride + x * m_depth + 0] = r;
    m_buffer[y * m_stride + x * m_depth + 1] = g;
    m_buffer[y * m_stride + x * m_depth + 2] = b;
}