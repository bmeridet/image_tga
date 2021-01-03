#include "imageTGA.h"

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();

int main()
{
	// multiply function - done
	//task1();

	// subtract function - done
	//task2();

	// multiply followed by screen - done
	//task3();

	// multiply followed by subtract
	//task4();
	
	// overlay function - done
	//task5();

	// add 200 to the green channel
	//task6();

	// scale red channel by 4 and blue channel by 0
	//task7();

	// write each color channel to a seperate file
	//task8();

	// load data from 3 color files into the 3 color channels of the image
	//task9();

	// rotate image 180 degrees -- reverse the pixel data
	//task10();

	return 0;
}

void task1()
{
	std::cout << "Running task 1..." << std::endl;

	std::string file1 = "layer1.tga";
	std::string file2 = "pattern1.tga";
	std::string file3 = "EXAMPLE_part1.tga";

	std::ifstream imageFile1(file1, std::ios_base::binary);
	std::ifstream imageFile2(file2, std::ios_base::binary);
	std::ifstream imageFile3(file3, std::ios_base::binary);

	imageTGA top;
	top.deserialize(imageFile1);

	imageTGA bottom;
	bottom.deserialize(imageFile2);

	imageTGA product(top);
	product.multiply(top.getPixels(), bottom.getPixels());

	std::ofstream outFile("part1.tga", std::ios_base::binary);
	product.serialize(outFile);

	imageTGA answer;
	answer.deserialize(imageFile3);

	std::cout << "Finished task 1." << std::endl;

	if (product == answer)
		std::cout << "The images are equal." << std::endl;
	else
		std::cout << "The images are not equal." << std::endl;
}

void task2()
{
	std::cout << "Running task 2..." << std::endl;

	std::string file1 = "car.tga";
	std::string file2 = "layer2.tga";
	std::string file3 = "EXAMPLE_part2.tga";

	std::ifstream imageFile1(file1, std::ios_base::binary);
	std::ifstream imageFile2(file2, std::ios_base::binary);
	std::ifstream imageFile3(file3, std::ios_base::binary);

	imageTGA bottom;
	bottom.deserialize(imageFile1);

	imageTGA top;
	top.deserialize(imageFile2);

	imageTGA product(bottom);
	product.subtract(top.getPixels(), bottom.getPixels());

	std::ofstream outFile("part2.tga", std::ios_base::binary);
	product.serialize(outFile);

	imageTGA answer;
	answer.deserialize(imageFile3);

	std::cout << "Finished task 2." << std::endl;

	if (product == answer)
		std::cout << "The images are equal." << std::endl;
	else
		std::cout << "The images are not equal." << std::endl;
}

void task3()
{
	std::cout << "Running task 3..." << std::endl;

	std::string file1 = "layer1.tga";
	std::string file2 = "pattern2.tga";
	std::string file3 = "text.tga";
	std::string file4 = "EXAMPLE_part3.tga";

	std::ifstream imageFile1(file1, std::ios_base::binary);
	std::ifstream imageFile2(file2, std::ios_base::binary);
	std::ifstream imageFile3(file3, std::ios_base::binary);
	std::ifstream imageFile4(file4, std::ios_base::binary);

	// multiply layer1.tga and pattern2.tga
	imageTGA bottom;
	bottom.deserialize(imageFile1);

	imageTGA top;
	top.deserialize(imageFile2);

	imageTGA product1(bottom);
	product1.multiply(top.getPixels(), bottom.getPixels());

	// screen product1 with text.tga as the top layer
	imageTGA newTop;
	newTop.deserialize(imageFile3);

	imageTGA product2(product1);
	product2.screen(newTop.getPixels(), product1.getPixels());

	std::ofstream outFile("part3.tga", std::ios_base::binary);
	product2.serialize(outFile);

	// compare to example file
	imageTGA answer;
	answer.deserialize(imageFile4);

	std::cout << "Finished task 3." << std::endl;

	if (product2 == answer)
		std::cout << "The images are equal." << std::endl;
	else
		std::cout << "The images are not equal." << std::endl;
}

void task4()
{

}

void task5()
{
	std::cout << "Running task 5..." << std::endl;

	std::string file1 = "layer1.tga";
	std::string file2 = "pattern1.tga";
	std::string file3 = "EXAMPLE_part5.tga";

	std::ifstream imageFile1(file1, std::ios_base::binary);
	std::ifstream imageFile2(file2, std::ios_base::binary);
	std::ifstream imageFile3(file3, std::ios_base::binary);

	imageTGA top;
	top.deserialize(imageFile1);

	imageTGA bottom;
	bottom.deserialize(imageFile2);

	imageTGA product(top);
	product.overlay(top.getPixels(), bottom.getPixels());

	std::ofstream outFile("part5.tga", std::ios_base::binary);
	product.serialize(outFile);

	imageTGA answer;
	answer.deserialize(imageFile3);

	std::cout << "Finished task 5." << std::endl;

	if (product == answer)
		std::cout << "The images are equal." << std::endl;
	else
		std::cout << "The images are not equal." << std::endl;
}

void task6()
{

}

void task7()
{

}

void task8()
{

}

void task9()
{

}

void task10()
{

}