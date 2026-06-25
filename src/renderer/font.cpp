#include "magnetar/renderer/font.h"
#include "magnetar/renderer/renderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H

magnetar::Font::Font(File *file)
{
    FT_Error error;

    FT_Library ft;
    error = FT_Init_FreeType(&ft);
    MT_ASSERT(error == FT_Err_Ok, "could not initialize freetype");

    FT_Face face;
    auto bytes = file->read_all();
    error = FT_New_Memory_Face(ft, &bytes[0], bytes.size(), 0, &face);
    MT_ASSERT(error == FT_Err_Ok, "failed to load font {}", file->uri());

    FT_Set_Pixel_Sizes(face, 0, 60);

    glm::ivec2 atlas_size(0, 0);

    for (uint8_t c = 32; c < 127; c++)
    {
        error = FT_Load_Char(face, c, FT_LOAD_RENDER);
        if (error != FT_Err_Ok)
            continue;

        atlas_size.x += face->glyph->bitmap.width;
        atlas_size.y = std::max(
            atlas_size.y,
            (int)face->glyph->bitmap.rows);
    }

    std::vector<uint8_t> atlas(atlas_size.x * atlas_size.y, 0);
    int x_offset = 0;

    for (uint8_t c = 32; c < 127; c++)
    {
        error = FT_Load_Char(face, c, FT_LOAD_RENDER);
        if (error != FT_Err_Ok)
            continue;

        FT_GlyphSlot g = face->glyph;
        for (uint32_t y = 0; y < g->bitmap.rows; y++)
        {
            for (uint32_t x = 0; x < g->bitmap.width; x++)
            {
                atlas[y * atlas_size.x + (x_offset + x)] = g->bitmap.buffer[y * g->bitmap.pitch + x];
            }
        }

        Glyph glyph;
        glyph.uv0.x = (float)x_offset / atlas_size.x;
        glyph.uv0.y = (float)g->bitmap.rows / atlas_size.y;

        glyph.uv1.x = (float)(x_offset + g->bitmap.width) / atlas_size.x;
        glyph.uv1.y = 0.0f;

        glyph.size.x = g->bitmap.width;
        glyph.size.y = g->bitmap.rows;

        glyph.bearing.x = g->bitmap_left;
        glyph.bearing.y = g->bitmap_top;

        glyph.advance = g->advance.x;

        m_glyphs.emplace(c, glyph);

        x_offset += g->bitmap.width;
    }

    Renderer::set_pixel_alignment(PixelStoreMode::UNPACK, 1);
    
    TextureSpecification spec;
    spec.width = atlas_size.x;
    spec.height = atlas_size.y;
    spec.format = TextureFormat::R8;
    spec.mag_filter = TextureFilter::LINEAR;
    spec.min_filter = TextureFilter::LINEAR;
    spec.wrap = TextureWrap::CLAMP_TO_EDGE;
    m_texture = Renderer::create_texture2D(spec, &atlas[0]);

    Renderer::set_pixel_alignment(PixelStoreMode::UNPACK, 4);
}