#include "..\pch.h"
#include "ResourceLoader.h"
#include "DDSInfo.h"

#define NOMINMAX

GLint SBR::ResourceLoader::LoadTexture(std::string path)
{
	boost::filesystem::path bPath(path);
	boost::filesystem::path ext = bPath.extension();

	int textureId = -1;

	if (ext.compare(std::string(".tga"))==0)	
		textureId = SBR::ResourceLoader::LoadTGA(path);
	else if (ext.compare(std::string(".dds")) == 0)
		textureId = SBR::ResourceLoader::LoadDDS(path);
	else if (ext.compare(std::string(".jpg")) == 0 || ext.compare(std::string("jpeg")) == 0)
		textureId = SBR::ResourceLoader::LoadJPG(path);
	else if (ext.compare(std::string(".png")) == 0)
		textureId = SBR::ResourceLoader::LoadPNG(path);

	return textureId;
}

GLint SBR::ResourceLoader::LoadPNG(std::string path)
{
	png_byte header[8];

	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, path.c_str(), "rb");
	if (err != 0)
	{
		return 0;
	}

	// read the header
	fread(header, 1, 8, fp);

	if (png_sig_cmp(header, 0, 8))
	{
		fprintf(stderr, "error: %s is not a PNG.\n", path.c_str());
		fclose(fp);
		return 0;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		fprintf(stderr, "error: png_create_read_struct returned 0.\n");
		fclose(fp);
		return 0;
	}

	// create png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		fprintf(stderr, "error: png_create_info_struct returned 0.\n");
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return 0;
	}

	// create png info struct
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		fprintf(stderr, "error: png_create_info_struct returned 0.\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		fclose(fp);
		return 0;
	}

	// the code in this if statement gets called if libpng encounters an error
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "error from libpng\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return 0;
	}

	// init png reading
	png_init_io(png_ptr, fp);

	// let libpng know you already read the first 8 bytes
	png_set_sig_bytes(png_ptr, 8);

	// read all the info up to the image data
	png_read_info(png_ptr, info_ptr);

	// variables to pass to get info
	int bit_depth, color_type;
	png_uint_32 temp_width, temp_height;

	// get info about png
	png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
		NULL, NULL, NULL);


	// Update the png info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Row size in bytes.
	int rowbytes = (int)png_get_rowbytes(png_ptr, info_ptr);

	// glTexImage2d requires rows to be 4-byte aligned
	rowbytes += 3 - ((rowbytes - 1) % 4);

	// Allocate the image_data as a big block, to be given to opengl
	png_byte * image_data;
	image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte) + 15);
	if (image_data == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG image data\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return 0;
	}

	// row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep * row_pointers = (png_bytep *)malloc(temp_height * sizeof(png_bytep));
	if (row_pointers == NULL)
	{
		fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(image_data);
		fclose(fp);
		return 0;
	}

	// set the individual row_pointers to point at the correct offsets of image_data
	unsigned int i;
	for (i = 0; i < temp_height; i++)
	{
		row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
	}

	// read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);

	// Generate the OpenGL texture object
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, temp_width, temp_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// clean up
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	free(image_data);
	free(row_pointers);
	fclose(fp);
	return texture;
}

struct DXTColBlock
{
	unsigned short col0;
	unsigned short col1;

	unsigned char row[4];
};

struct DXT5AlphaBlock
{
	unsigned char alpha0;
	unsigned char alpha1;

	unsigned char row[6];
};

void flip_dxt5_alpha(DXT5AlphaBlock *block)
{
	unsigned char gBits[4][4];

	const unsigned long mask = 0x00000007;          // bits = 00 00 01 11
	unsigned long bits = 0;
	memcpy(&bits, &block->row[0], sizeof(unsigned char) * 3);

	gBits[0][0] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[0][1] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[0][2] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[0][3] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[1][0] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[1][1] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[1][2] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[1][3] = (unsigned char)(bits & mask);

	bits = 0;
	memcpy(&bits, &block->row[3], sizeof(unsigned char) * 3);

	gBits[2][0] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[2][1] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[2][2] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[2][3] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[3][0] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[3][1] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[3][2] = (unsigned char)(bits & mask);
	bits >>= 3;
	gBits[3][3] = (unsigned char)(bits & mask);

	unsigned long *pBits = ((unsigned long*)&(block->row[0]));

	*pBits = *pBits | (gBits[3][0] << 0);
	*pBits = *pBits | (gBits[3][1] << 3);
	*pBits = *pBits | (gBits[3][2] << 6);
	*pBits = *pBits | (gBits[3][3] << 9);

	*pBits = *pBits | (gBits[2][0] << 12);
	*pBits = *pBits | (gBits[2][1] << 15);
	*pBits = *pBits | (gBits[2][2] << 18);
	*pBits = *pBits | (gBits[2][3] << 21);

	pBits = ((unsigned long*)&(block->row[3]));

#ifdef MACOS
	*pBits &= 0x000000ff;
#else
	*pBits &= 0xff000000;
#endif

	*pBits = *pBits | (gBits[1][0] << 0);
	*pBits = *pBits | (gBits[1][1] << 3);
	*pBits = *pBits | (gBits[1][2] << 6);
	*pBits = *pBits | (gBits[1][3] << 9);

	*pBits = *pBits | (gBits[0][0] << 12);
	*pBits = *pBits | (gBits[0][1] << 15);
	*pBits = *pBits | (gBits[0][2] << 18);
	*pBits = *pBits | (gBits[0][3] << 21);
}

void _inline swap(void *byte1, void *byte2, unsigned int size)
{
	unsigned char *tmp = new unsigned char[size];

	memcpy(tmp, byte1, size);
	memcpy(byte1, byte2, size);
	memcpy(byte2, tmp, size);

	delete[] tmp;
}

void FlipDDS(unsigned char * data, int numBlocks)
{
	DXTColBlock *curblock = (DXTColBlock *)data;
	DXT5AlphaBlock *alphablock;

	for (int i = 0; i < numBlocks; i++)
	{
		alphablock = (DXT5AlphaBlock*)curblock;

		//flip_dxt5_alpha(alphablock);

		curblock++;

		std::swap(curblock->row[0], curblock->row[3]);
		std::swap(curblock->row[1], curblock->row[2]);

		curblock++;
	}
}

GLint SBR::ResourceLoader::LoadDDS(std::string path)
{
	FILE* f;
	errno_t err = fopen_s(&f, path.c_str(), "rb");
	if (err != 0)
	{
		return 0;
	}

	DDS_header hdr;
	size_t s = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int mipMapCount = 0;
	//  DDS is so simple to read, too
	fread(&hdr, sizeof(hdr), 1, f);
	assert(hdr.dwMagic == DDS_MAGIC);
	assert(hdr.dwSize == 124);

	if (hdr.dwMagic != DDS_MAGIC || hdr.dwSize != 124 ||
		!(hdr.dwFlags & DDSD_PIXELFORMAT) || !(hdr.dwFlags & DDSD_CAPS))
	{
		return 0;
	}

	int xSize = hdr.dwWidth;
	int ySize = hdr.dwHeight;
	//assert(!(xSize & (xSize - 1)));
	//	assert(!(ySize & (ySize - 1)));

	DdsLoadInfo * li;

	if (PF_IS_DXT1(hdr.sPixelFormat)) {
		li = &loadInfoDXT1;
	}
	else if (PF_IS_DXT3(hdr.sPixelFormat)) {
		li = &loadInfoDXT3;
	}
	else if (PF_IS_DXT5(hdr.sPixelFormat)) {
		li = &loadInfoDXT5;
	}
	else {
		return 0;
	}

	GLuint glid;
	glGenTextures(1, &glid);
	glBindTexture(GL_TEXTURE_2D, glid);

	//fixme: do cube maps later
	//fixme: do 3d later
	x = xSize;
	y = ySize;
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
	mipMapCount = (hdr.dwFlags & DDSD_MIPMAPCOUNT) ? hdr.dwMipMapCount : 1;
	//if( mipMapCount > 1 ) {
	//  hasMipmaps_ = true;
	//}
	if (li->compressed) {
		size_t size = std::max(li->divSize, x) / li->divSize * std::max(li->divSize, y) / li->divSize * li->blockBytes;
		assert(size == hdr.dwPitchOrLinearSize);
		assert(hdr.dwFlags & DDSD_LINEARSIZE);
		unsigned char * data = (unsigned char *)malloc(size);
		if (!data) {
			return 0;
		}
		for (unsigned int ix = 0; ix < mipMapCount; ++ix) {
			fread(data, 1, size, f);

			int blocksize = 16;
			unsigned int xblocks = x / 4;
			unsigned int yblocks = y / 4;
			unsigned int linesize = xblocks * blocksize;

			unsigned char *top;
			unsigned char *bottom;

			for (unsigned int j = 0; j < (yblocks >> 1); j++)
			{

				top = data + j * linesize;
				bottom = data + (((yblocks - j) - 1) * linesize);
				FlipDDS(top, xblocks);
				FlipDDS(bottom, xblocks);

				std::swap_ranges(top, top + linesize, bottom);
			}

			glCompressedTexImage2D(GL_TEXTURE_2D, ix, li->internalFormat, x, y, 0, (GLsizei)size, data);

			x = (x + 1) >> 1;
			y = (y + 1) >> 1;

			size = std::max(li->divSize, x) / li->divSize * std::max(li->divSize, y) / li->divSize * li->blockBytes;

		}
		free(data);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount - 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	fclose(f);
	return glid;
}

GLint SBR::ResourceLoader::LoadJPG(std::string path)
{
	int width, height;
	int channels;
	GLint internalFormat;
	GLuint type;

	FILE* file = fopen(path.c_str(), "rb");
	struct jpeg_decompress_struct info;
	struct jpeg_error_mgr err;

	info.err = jpeg_std_error(&err);
	jpeg_create_decompress(&info);

	if (!file)
	{
		return 0;
	}

	jpeg_stdio_src(&info, file);
	jpeg_read_header(&info, TRUE);

	width = info.image_width;
	height = info.image_height;
	channels = info.num_components;
	internalFormat = info.num_components;

	if (channels == 3)
		type = GL_RGB;
	else if (channels == 1)
		type = GL_LUMINANCE;
	else
		return 0;

	jpeg_start_decompress(&info);

	GLubyte *texels = (GLubyte *)malloc(sizeof(GLubyte)* width * height * channels);
	JSAMPROW j;

	for (int i = 0; i < height; ++i)
	{
		j = (texels + width * channels * (height - i - 1));
		jpeg_read_scanlines(&info, &j, 1);
	}

	jpeg_finish_decompress(&info);   //finish decompressing this file

	fclose(file);                    //close the file

	GLuint glid;
	glGenTextures(1, &glid);
	glBindTexture(GL_TEXTURE_2D, glid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLint alignment;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, type, GL_UNSIGNED_BYTE, texels);

	glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);

	return glid;

}

typedef struct
{
	GLubyte* imageData;         // Hold All The Color Values For The Image.
	GLuint  bpp;                // Hold The Number Of Bits Per Pixel.          
	GLuint width;               // The Width Of The Entire Image.  
	GLuint height;              // The Height Of The Entire Image. 
	GLuint texID;               // Texture ID For Use With glBindTexture.  
	GLuint type;                // Data Stored In * ImageData (GL_RGB Or GL_RGBA)
} TgaTexture;


typedef struct
{
	GLubyte header[6];          // Holds The First 6 Useful Bytes Of The File
	GLuint bytesPerPixel;           // Number Of BYTES Per Pixel (3 Or 4)
	GLuint imageSize;           // Amount Of Memory Needed To Hold The Image
	GLuint type;                // The Type Of Image, GL_RGB Or GL_RGBA
	GLuint Height;              // Height Of Image                 
	GLuint Width;               // Width Of Image              
	GLuint Bpp;             // Number Of BITS Per Pixel (24 Or 32)
	bool compressed;
} TGA;


bool LoadUncompressedTGA(GLubyte* f, TgaTexture* texture);
bool LoadCompressedTGA(GLubyte* f);

GLint SBR::ResourceLoader::LoadTGA(std::string path)
{
	boost::iostreams::mapped_file mmap(path, boost::iostreams::mapped_file::readonly);
	GLubyte* f = (GLubyte*)mmap.const_data();
	auto l = f + mmap.size();

	GLubyte uTGAcompare[12] = { 0,0, 2,0,0,0,0,0,0,0,0,0 };
	GLubyte cTGAcompare[12] = { 0,0,10,0,0,0,0,0,0,0,0,0 };

	TgaTexture texture;
	TGA tga;

	if (std::memcmp(f, uTGAcompare, 12) == 0)
		tga.compressed = false;
	else if (std::memcmp(f, cTGAcompare, 12) == 0)
		tga.compressed = true;
	else
		return -1; // no valid header found

	f += 12;

	memcpy(tga.header, f, 6);
	f += 6;
	texture.width = tga.header[1] * 256 + tga.header[0];   // Calculate Height
	texture.height = tga.header[3] * 256 + tga.header[2];   // Calculate The Width
	texture.bpp = tga.header[4];                // Calculate Bits Per Pixel
	tga.Width = texture.width;              // Copy Width Into Local Structure
	tga.Height = texture.height;                // Copy Height Into Local Structure
	tga.Bpp = texture.bpp;

	if ((texture.width <= 0) || (texture.height <= 0) || ((texture.bpp != 24) && (texture.bpp != 32)))
	{
		return false;               // Return False
	}

	if (texture.bpp == 24)               // Is It A 24bpp Image?
		texture.type = GL_RGB;       // If So, Set Type To GL_RGB
	else                        // If It's Not 24, It Must Be 32
		texture.type = GL_RGBA;      // So Set The Type To GL_RGBA


	tga.bytesPerPixel = (tga.Bpp / 8);    // Calculate The BYTES Per Pixel												
	tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height); // Calculate Memory Needed To Store Image

	texture.imageData = (GLubyte *)malloc(tga.imageSize);

	if (tga.compressed == false)
	{
		memcpy(texture.imageData, f, tga.imageSize);
		for (GLuint cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
		{
			// 1st Byte XOR 3rd Byte XOR 1st Byte XOR 3rd Byte
			texture.imageData[cswap] ^= texture.imageData[cswap + 2] ^=
				texture.imageData[cswap] ^= texture.imageData[cswap + 2];
		}
	}

	else if (tga.compressed == true)
	{
		GLuint pixelcount = tga.Height * tga.Width; // Number Of Pixels In The Image
		GLuint currentpixel = 0;            // Current Pixel We Are Reading From Data
		GLuint currentbyte = 0;            // Current Byte We Are Writing Into Imagedata										  
		GLubyte * colorbuffer = (GLubyte *)malloc(tga.bytesPerPixel);  // Storage For 1 Pixel

		do
		{

			GLubyte chunkheader = f[0];
			f++;

			if (chunkheader < 128)
			{
				chunkheader++;
				for (short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
				{
					memcpy(colorbuffer, f, tga.bytesPerPixel);
					f += tga.bytesPerPixel;
					// write to memory
					texture.imageData[currentbyte] = colorbuffer[2];				    // Flip R and B vcolor values around in the process 
					texture.imageData[currentbyte + 1] = colorbuffer[1];
					texture.imageData[currentbyte + 2] = colorbuffer[0];

					if (tga.bytesPerPixel == 4)												// if its a 32 bpp image
					{
						texture.imageData[currentbyte + 3] = colorbuffer[3];				// copy the 4th byte
					}

					currentbyte += tga.bytesPerPixel;										// Increase thecurrent byte by the number of bytes per pixel
					currentpixel++;															// Increase current pixel by 1

					if (currentpixel > pixelcount)											// Make sure we havent read too many pixels
					{
						return -1;														// Return failed
					}
				}
			}
			else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
			{
				chunkheader -= 127;															// Subteact 127 to get rid of the ID bit
				memcpy(colorbuffer, f, tga.bytesPerPixel);
				f += tga.bytesPerPixel;

				for (short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
				{																			// by the header
					texture.imageData[currentbyte] = colorbuffer[2];					// switch R and B bytes areound while copying
					texture.imageData[currentbyte + 1] = colorbuffer[1];
					texture.imageData[currentbyte + 2] = colorbuffer[0];

					if (tga.bytesPerPixel == 4)												// If TGA images is 32 bpp
					{
						texture.imageData[currentbyte + 3] = colorbuffer[3];				// Copy 4th byte
					}

					currentbyte += tga.bytesPerPixel;										// Increase current byte by the number of bytes per pixel
					currentpixel++;															// Increase pixel count by 1

					if (currentpixel > pixelcount)											// Make sure we havent written too many pixels
					{
						return -1;														// Return failed
					}
				}
			}
		} while (currentpixel < pixelcount);
	}

	GLuint glid;
	glGenTextures(1, &glid);
	glBindTexture(GL_TEXTURE_2D, glid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, texture.type, texture.width, texture.width, 0, texture.type, GL_UNSIGNED_BYTE, texture.imageData);

	return glid;
}