#include <iostream>
#include <fstream>
#include <vector>

#pragma once

class imageTGA
{
private:
	struct header
	{
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
	};

	struct pixel
	{
		unsigned char blue;
		unsigned char green;
		unsigned char red;
	};

	header headerObj;
	std::vector<pixel> pixelData;

public:

	/*=======constructors=========*/
	imageTGA();
	imageTGA(imageTGA& obj);

	/*===========fileIO==========*/
	void serialize(std::ofstream& file);
	void deserialize(std::ifstream& file);

	/*=========dataAccessors=============*/
	unsigned int getNumPixels() { return pixelData.size(); }
	const std::vector<pixel>& getPixels() { return pixelData; }

	/*================imageEdit===============================================*/

	void multiply(const std::vector<pixel>& top, const std::vector<pixel>& bottom);
	void subtract(const std::vector<pixel>& top, const std::vector<pixel>& bottom);
	void screen(const std::vector<pixel>& top, const std::vector<pixel>& bottom);
	void overlay(const std::vector<pixel>& top, const std::vector<pixel>& bottom);

	/*============operators=============*/
	bool operator==(imageTGA& rhs);
};

