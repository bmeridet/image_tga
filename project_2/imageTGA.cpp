#include "imageTGA.h"

const int MIN_PIXEL_VAL = 0;
const int MAX_PIXEL_VAL = 255;

/*==============================constructosrs=======================================*/

imageTGA::imageTGA()
{
	headerObj.idLength = '0';
	headerObj.colorMapType = '0';
	headerObj.dataTypeCode = '0';
	headerObj.colorMapOrigin = 0;
	headerObj.colorMapLength = 0;
	headerObj.colorMapDepth = '0';
	headerObj.xOrigin = 0;
	headerObj.yOrigin = 0;
	headerObj.width = 0;
	headerObj.height = 0;
	headerObj.bitsPerPixel = '0';
	headerObj.imageDescriptor = '0';
}

imageTGA::imageTGA(imageTGA& obj)
{
	headerObj.idLength = obj.headerObj.idLength;
	headerObj.colorMapType = obj.headerObj.colorMapType;
	headerObj.dataTypeCode = obj.headerObj.dataTypeCode;
	headerObj.colorMapOrigin = obj.headerObj.colorMapOrigin;
	headerObj.colorMapLength = obj.headerObj.colorMapLength;
	headerObj.colorMapDepth = obj.headerObj.colorMapDepth;
	headerObj.xOrigin = obj.headerObj.xOrigin;
	headerObj.yOrigin = obj.headerObj.yOrigin;
	headerObj.width = obj.headerObj.width;
	headerObj.height = obj.headerObj.height;
	headerObj.bitsPerPixel = obj.headerObj.bitsPerPixel;
	headerObj.imageDescriptor = obj.headerObj.imageDescriptor;
}

/*=====================================fileIO===================================================*/

void imageTGA::serialize(std::ofstream& file)
{
	/*===========Write_Header=============*/

	file.write(&headerObj.idLength, sizeof(headerObj.idLength));
	file.write(&headerObj.colorMapType, sizeof(headerObj.colorMapType));
	file.write(&headerObj.dataTypeCode, sizeof(headerObj.dataTypeCode));
	file.write((char*)&headerObj.colorMapOrigin, sizeof(headerObj.colorMapOrigin));
	file.write((char*)&headerObj.colorMapLength, sizeof(headerObj.colorMapLength));
	file.write(&headerObj.colorMapDepth, sizeof(headerObj.colorMapDepth));
	file.write((char*)&headerObj.xOrigin, sizeof(headerObj.xOrigin));
	file.write((char*)&headerObj.yOrigin, sizeof(headerObj.yOrigin));
	file.write((char*)&headerObj.width, sizeof(headerObj.width));
	file.write((char*)&headerObj.height, sizeof(headerObj.height));
	file.write(&headerObj.bitsPerPixel, sizeof(headerObj.bitsPerPixel));
	file.write(&headerObj.imageDescriptor, sizeof(headerObj.imageDescriptor));

	/*=============Write_pixels==============*/

	for (int i = 0; i < pixelData.size(); ++i)
	{
		file.write((char*)&pixelData.at(i).blue, sizeof(pixelData.at(i).blue));
		file.write((char*)&pixelData.at(i).green, sizeof(pixelData.at(i).green));
		file.write((char*)&pixelData.at(i).red, sizeof(pixelData.at(i).red));
	}
}

void imageTGA::deserialize(std::ifstream& file)
{
	/*===========Write_Header=============*/

	file.read(&headerObj.idLength, sizeof(headerObj.idLength));
	file.read(&headerObj.colorMapType, sizeof(headerObj.colorMapType));
	file.read(&headerObj.dataTypeCode, sizeof(headerObj.dataTypeCode));
	file.read((char*)&headerObj.colorMapOrigin, sizeof(headerObj.colorMapOrigin));
	file.read((char*)&headerObj.colorMapLength, sizeof(headerObj.colorMapLength));
	file.read(&headerObj.colorMapDepth, sizeof(headerObj.colorMapDepth));
	file.read((char*)&headerObj.xOrigin, sizeof(headerObj.xOrigin));
	file.read((char*)&headerObj.yOrigin, sizeof(headerObj.yOrigin));
	file.read((char*)&headerObj.width, sizeof(headerObj.width));
	file.read((char*)&headerObj.height, sizeof(headerObj.height));
	file.read(&headerObj.bitsPerPixel, sizeof(headerObj.bitsPerPixel));
	file.read(&headerObj.imageDescriptor, sizeof(headerObj.imageDescriptor));

	/*=============Write_pixels==============*/

	int dataSize = headerObj.width * headerObj.height;

	for (int i = 0; i < dataSize; ++i)
	{
		pixel pixel;

		file.read((char*)&pixel.blue, sizeof(pixel.blue));
		file.read((char*)&pixel.green, sizeof(pixel.green));
		file.read((char*)&pixel.red, sizeof(pixel.red));

		pixelData.push_back(pixel);
	}
}

/*=========================================imageEdit========================================*/

void imageTGA::multiply(const std::vector<pixel>& top, const std::vector<pixel>& bottom)
{
	pixelData.clear();

	for (int i = 0; i < top.size(); ++i)
	{
		pixel c;

		c.blue = (((float)top.at(i).blue * (float)bottom.at(i).blue) / MAX_PIXEL_VAL) + 0.5f;
		c.green = (((float)top.at(i).green * (float)bottom.at(i).green) / MAX_PIXEL_VAL) + 0.5f;
		c.red = (((float)top.at(i).red * (float)bottom.at(i).red) / MAX_PIXEL_VAL) + 0.5f;

		pixelData.push_back(c);
	}
}

void imageTGA::subtract(const std::vector<pixel>& top, const std::vector<pixel>& bottom)
{
	pixelData.clear();

	for (int i = 0; i < bottom.size(); ++i)
	{
		pixel c;

		int b = (int)bottom.at(i).blue - (int)top.at(i).blue;
		int g = (int)bottom.at(i).green - (int)top.at(i).green;
		int r = (int)bottom.at(i).red - (int)top.at(i).red;

		if (b < 0)
			b = 0;
		if (g < 0)
			g = 0;
		if (r < 0)
			r = 0;

		c.blue = b;
		c.green = g;
		c.red = r;

		pixelData.push_back(c);
	}
}

void imageTGA::screen(const std::vector<pixel>& top, const std::vector<pixel>& bottom)
{
	pixelData.clear();

	for (int i = 0; i < top.size(); ++i)
	{
		pixel c;

		float top_b = (float)top.at(i).blue / MAX_PIXEL_VAL;
		float top_g = (float)top.at(i).green / MAX_PIXEL_VAL;
		float top_r = (float)top.at(i).red / MAX_PIXEL_VAL;

		float bottom_b = (float)bottom.at(i).blue / MAX_PIXEL_VAL;
		float bottom_g = (float)bottom.at(i).green / MAX_PIXEL_VAL;
		float bottom_r = (float)bottom.at(i).red / MAX_PIXEL_VAL;

		float b = ((1 - (1 - top_b) * (1 - bottom_b)) * MAX_PIXEL_VAL) + 0.5f;
		float g = ((1 - (1 - top_g) * (1 - bottom_g)) * MAX_PIXEL_VAL) + 0.5f;
		float r = ((1 - (1 - top_r) * (1 - bottom_r)) * MAX_PIXEL_VAL) + 0.5f;

		c.blue = b;
		c.green = g;
		c.red = r;

		pixelData.push_back(c);
	}
}

void imageTGA::overlay(const std::vector<pixel>& top, const std::vector<pixel>& bottom)
{
	pixelData.clear();

	for (int i = 0; i < top.size(); ++i)
	{
		pixel c;

		float top_b = (float)top.at(i).blue / MAX_PIXEL_VAL;
		float top_g = (float)top.at(i).green / MAX_PIXEL_VAL;
		float top_r = (float)top.at(i).red / MAX_PIXEL_VAL;

		float bottom_b = (float)bottom.at(i).blue / MAX_PIXEL_VAL;
		float bottom_g = (float)bottom.at(i).green / MAX_PIXEL_VAL;
		float bottom_r = (float)bottom.at(i).red / MAX_PIXEL_VAL;

		float bottom_ave = (bottom_b + bottom_g + bottom_r) / 3;

		float b, g, r;

		if (bottom_ave <= 0.5)
		{
			b = ((2 * top_b * bottom_b) * MAX_PIXEL_VAL) + 0.5f;
			g = ((2 * top_g * bottom_g) * MAX_PIXEL_VAL) + 0.5f;
			r = ((2 * top_r * bottom_r) * MAX_PIXEL_VAL) + 0.5f;
		}
		else
		{
			b = ((1 - 2 * (1 - top_b) * (1 - bottom_b)) * MAX_PIXEL_VAL) + 0.5f;
			g = ((1 - 2 * (1 - top_g) * (1 - bottom_g)) * MAX_PIXEL_VAL) + 0.5f;
			r = ((1 - 2 * (1 - top_r) * (1 - bottom_r)) * MAX_PIXEL_VAL) + 0.5f;
		}

		if (b > 255)
			b = 255;
		if (g > 255)
			g = 255;
		if (r > 255)
			r = 255;

		if (b < 0)
			b = 0;
		if (g < 0)
			g = 0;
		if (r < 0)
			r = 0;

		c.blue = b;
		c.green = g;
		c.red = r;

		pixelData.push_back(c);
	}
}

/*=======================operators================================*/
bool imageTGA::operator==(imageTGA& rhs)
{
	if (headerObj.width != rhs.headerObj.width || headerObj.height != rhs.headerObj.height)
		return false;

	if (pixelData.size() != rhs.pixelData.size())
		return false;

	for (int i = 0; i < pixelData.size(); ++i)
	{
		if (pixelData.at(i).blue != rhs.pixelData.at(i).blue || pixelData.at(i).green != rhs.pixelData.at(i).green || pixelData.at(i).red != rhs.pixelData.at(i).red)
			return false;
	}

	return true;
}