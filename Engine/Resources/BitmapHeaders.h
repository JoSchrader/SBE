#include "..\SBE_Internal.h"
#include <basetsd.h>

namespace SBR
{
	enum BitmapCompressionMethods
	{
		BI_COMP_RGB = 0,
		BI_COMP_RLE8 = 1,
		BI_COMP_RLE4 = 2,
		BI_COMP_BITFIELDS = 3,
		BI_COMP_JPEG = 4,
		BI_COMP_PNG = 5,
		BI_COMP_ALPHABITFIELDS = 6,
		BI_COMP_CMYK = 11,
		BI_COMP_CMYKRLE8 = 12,
		BI_COMP_CMYKRLE4 = 13,

		BI_COMP_NONE = BI_COMP_RGB
	};

#pragma pack(push, 1)
	struct BITMAPCOREHEADER_12
	{
		UINT32 headerSize;
		UINT16 width;
		UINT16 height;
		UINT16 colorPlanesNum;
		UINT16 bitsPerPixel;
	};

	struct OS22XBITMAPHEADER_64
	{
		UINT32 headerSize;
		UINT8 data[60];
	};

	struct OS22XBITMAPHEADER_16
	{
		UINT32 headerSize;
		UINT8 data[12];
	};

	struct BITMAPINFOHEADER_40
	{
		UINT32 headerSize;
		UINT32 width;
		UINT32 height;
		UINT16 colorPlanesNum;
		UINT16 bitsPerPixel;
		UINT32 compressionUsed;
		UINT32 imageSize;
		INT32 horizontalResolution;
		INT32 verticalResolution;
		INT32 numOfColorsInPalett;
		INT32 numOfImportantColors;
	};
	struct BITMAPV2INFOHEADER_52
	{
		UINT32 headerSize;
		UINT8 data[48];
	};

	struct BITMAPV3INFOHEADER_56
	{
		UINT32 headerSize;
		UINT8 data[52];
	};
	struct BITMAPV4HEADER_108
	{
		UINT32 headerSize;
		UINT8 data[104];
	};
	struct BITMAPV4HEADER_124
	{
		UINT32 headerSize;
		UINT8 data[120];
	};
#pragma pack(pop)

	union BitmapDIBHeader
	{
		UINT32 headerSize;
		BITMAPCOREHEADER_12 BITMAPCOREHEADER_12;
		OS22XBITMAPHEADER_64 OS22XBITMAPHEADER_64;
		OS22XBITMAPHEADER_16 OS22XBITMAPHEADER_16;
		BITMAPINFOHEADER_40 BITMAPINFOHEADER_40;
		BITMAPV2INFOHEADER_52 BITMAPV2INFOHEADER_52;
		BITMAPV3INFOHEADER_56 BITMAPV3INFOHEADER_56;
		BITMAPV4HEADER_108 BITMAPV4HEADER_108;
		BITMAPV4HEADER_124 BITMAPV4HEADER_124;
	};

#pragma pack(push, 1)
	struct  BitmapHeader
	{
		char type[2];
		unsigned int fileSize;
		UINT16 reserved1;
		UINT16 reserved2;
		int dataOffset;
		BitmapDIBHeader dibHeader;
	};
#pragma pack(pop)
}