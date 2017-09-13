#include <Engine\SBE.h>

#include <FreeType2\include\ft2build.h>
#include FT_FREETYPE_H

void main()
{
	FT_Library library;
	FT_Error error = FT_Init_FreeType(&library);

	FT_Face face;
	error = FT_New_Face(library, "Content/Fonts/verdana.ttf", 0, &face);

	error = FT_Set_Pixel_Sizes(face, 0, 200);

	FT_UInt glyph_index = FT_Get_Char_Index(face, 0x0041);
	error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

	auto bitmap = SBR::BitmapLoader::LoadBitmap("Content/Textures/CreatedBMP.bmp");

	char* text = "WUHU - :)";
	int textLength = strlen(text);

	int width = 2000, height = 500;
	SBR::Bitmap bmp(width, height);

	int penX = 5, penY = 200;

	for (int i = 0; i < textLength; i++)
	{
		FT_UInt glyph_index = FT_Get_Char_Index(face, text[i]);
		error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);



		for (int x = 0; x < face->glyph->bitmap.width; x++)
		{
			for (int y = 0; y < face->glyph->bitmap.rows; y++)
			{
				unsigned char value = face->glyph->bitmap.buffer[face->glyph->bitmap.pitch*y+x];
				bmp.SetPixel(penX + x + face->glyph->bitmap_left, penY - y + face->glyph->bitmap_top, SBR::BitmapPixelColor(value, value, value));
			}
		}

		penX += face->glyph->bitmap.width+10;
	}


	bmp.SaveToFile("Content/Textures/CreatedBMP.bmp");


	auto vec3 = new SBM::Vector3();

	char* gb = (char*)malloc(1024);

	delete vec3;
	delete gb;
}