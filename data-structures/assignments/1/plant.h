#ifndef _PLANT_H_
#define _PLANT_H_

#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::ofstream;
using std::ifstream;
using std::ostream;
using std::endl;

struct Plant
{
	string species;
	double minTemperature;
	double maxTemperature;
	Plant(const string& species = "UNSPECIFIED", double minTemperature = 0,  double maxTemperature = 50)
		: species(species), minTemperature(minTemperature), maxTemperature(maxTemperature) {}
	double averageTemperature() const
	{
		return (minTemperature + maxTemperature) / 2;
	}
};

ifstream& operator >> (ifstream& in, Plant& plant)
{
	in >> plant.species;
	in >> plant.minTemperature;
	in >> plant.maxTemperature;
	return in;
}

ostream& operator << (ostream& out, Plant& plant)
{
	out << "Species: " << plant.species << endl;
	out << "Temperature: [" << plant.minTemperature;
	out << ", " << plant.maxTemperature << "]";
	return out;
}

void writeToBinary(ofstream& out, const Plant& plant)
{
	size_t size = plant.species.size();
	out.write((const char*) &size, sizeof(size));
	out.write(plant.species.c_str(), size);
	out.write((const char*) &plant.minTemperature, sizeof(plant.minTemperature));
	out.write((const char*) &plant.maxTemperature, sizeof(plant.maxTemperature));
}

ifstream& readFromBinary(ifstream& in, Plant& plant)
{
	size_t size = 0;
	in.read((char*) &size, sizeof(size));
	char* tmp = new char[size + 1];
	in.read(tmp, size);
	tmp[size] = '\0';
	plant.species = tmp;
	delete tmp;

	in.read((char*) &plant.minTemperature, sizeof(plant.minTemperature));
	in.read((char*) &plant.maxTemperature, sizeof(plant.maxTemperature));
	return in;
}

#endif
