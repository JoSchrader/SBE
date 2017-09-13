#pragma once
#include "..\SBE_Internal.h"
#include "Loaders\FileOperations.h"
#include "BitmapHeaders.h"

#include <memory>

namespace SBR
{
	class BitmapPixelColor
	{
	public:
		UINT8 r;
		UINT8 g;
		UINT8 b;

		BitmapPixelColor()
		{
			this->r = 0;
			this->g = 0;
			this->b = 0;
		}

		BitmapPixelColor(UINT8 r, UINT8 g, UINT8 b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}
	};

	class Bitmap
	{
	private:
		int width;
		int height;
		BitmapPixelColor* data;

	public:
		Bitmap(int width, int height)
		{
			this->width = width;
			this->height = height;
			this->data = (BitmapPixelColor*)malloc(sizeof(BitmapPixelColor)*width*height);
			memset(this->data, 0, sizeof(BitmapPixelColor)*width*height);
		}

		Bitmap(int width, int height, BitmapPixelColor* buffer)
		{
			this->width = width;
			this->height = height;
			BitmapPixelColor* tmp = (BitmapPixelColor*)malloc(sizeof(BitmapPixelColor)*width*height);
			memcpy(tmp, buffer, sizeof(BitmapPixelColor)*width*height);
		}

		~Bitmap()
		{
			delete data;
		}

		void SetPixel(int x, int y, BitmapPixelColor color)
		{
			if (x < 0 || y < 0 || x >= width || y >= height)
				return;

			this->data[y * width + x] = color;
		}
		
		void MultPixel(int x, int y, BitmapPixelColor color)
		{
			if (x < 0 || y < 0 || x >= width || y >= height)
				return;

			float newColorFactor = (color.r + color.g + color.b) / (3*255.0) ;
			float oldColorFactor = 1- newColorFactor;

			int r = newColorFactor * color.r + oldColorFactor * this->data[y*width + x].r;
			int g = newColorFactor * color.b + oldColorFactor * this->data[y*width + x].g;
			int b = newColorFactor * color.r + oldColorFactor * this->data[y*width + x].b;

			this->data[y*width + x].r = r;
			this->data[y*width + x].g = g;
			this->data[y*width + x].b = b;
		}

		BitmapPixelColor GetPixel(int x, int y, BitmapPixelColor color)
		{
			if (x < 0 || y < 0 || x >= width || y >= height)
				return BitmapPixelColor(-1, -1, -1);

			return this->data[y*width + x];
		}

		void SaveToFile(char* path)
		{
			int rowsize = (int) floor((sizeof(BitmapPixelColor) * 8 * this->width + 31) / 32.0) * 4;

			int size = 14; //common header
			size += sizeof(BITMAPINFOHEADER_40);
			size += sizeof(BitmapPixelColor) * rowsize * height;

			char* buffer = (char*)malloc(size);
			BitmapHeader* header = (BitmapHeader*)buffer;
			BITMAPCOREHEADER_12* dbiHeader = &(header->dibHeader.BITMAPCOREHEADER_12);

			header->type[0] = 'B';
			header->type[1] = 'M';
			header->fileSize = size;
			header->reserved1 = 0;
			header->reserved2 = 0;
			header->dataOffset = 26; //size of common header + dbiheader

			dbiHeader->headerSize = 12;
			dbiHeader->width = this->width;
			dbiHeader->height = this->height;
			dbiHeader->colorPlanesNum = 1;
			dbiHeader->bitsPerPixel = sizeof(BitmapPixelColor) * 8;

			char* dataToPointer = buffer + header->dataOffset;
			BitmapPixelColor* dataFromPointer = this->GetData();
			for (int i = 0; i < this->height; i++)
			{
				memcpy(dataToPointer, dataFromPointer, sizeof(BitmapPixelColor)*width);
				dataToPointer += rowsize;
				dataFromPointer += width;
			}

			SBR::File::Write(path, buffer, size);

			delete buffer;
		}

		int GetWidth() { return this->width; }
		int GetHeight() { return this->height; }
		BitmapPixelColor* GetData() { return data; }
	};

	class BitmapLoader
	{
	private:
		static Bitmap* ProcessHeader_12(char* buffer)
		{
			BitmapHeader* header = (BitmapHeader*)buffer;
			BITMAPCOREHEADER_12* dibHeader = &(header->dibHeader.BITMAPCOREHEADER_12);

			return nullptr;
		}

		static Bitmap* ProcessHeader_40(char* buffer)
		{
			BitmapHeader* header = (BitmapHeader*)buffer;
			BITMAPINFOHEADER_40* dibHeader = &(header->dibHeader.BITMAPINFOHEADER_40);

			if (dibHeader->compressionUsed != SBR::BitmapCompressionMethods::BI_COMP_NONE)
				return nullptr;

			int size = dibHeader->width * dibHeader->height * dibHeader->bitsPerPixel;

		}


	public:
		static std::unique_ptr<Bitmap> LoadBitmap(char* path)
		{
			Bitmap* bmp = nullptr;
			int size = 0;
			char* buffer = nullptr;

			if (!SBR::File::Exist(path))
				goto Exit;

			buffer = SBR::File::Read(path, &size);

			BitmapHeader* header = (BitmapHeader*)buffer;

			if (!((header->type[0] == 'B' && header->type[1] == 'M') ||
				(header->type[0] == 'B' && header->type[1] == 'A') ||
				(header->type[0] == 'C' && header->type[1] == 'I') ||
				(header->type[0] == 'C' && header->type[1] == 'P') ||
				(header->type[0] == 'I' && header->type[1] == 'C') ||
				(header->type[0] == 'P' && header->type[1] == 'T')))
			{
				goto Exit;
			}

			switch (header->dibHeader.headerSize)
			{
			case 12: bmp = ProcessHeader_12(buffer); break;
			case 40: bmp = ProcessHeader_40(buffer); break;
			default: bmp = nullptr; break;
			}

		Exit:
			delete buffer;
			return std::unique_ptr<SBR::Bitmap>(bmp);
		}
	};
}