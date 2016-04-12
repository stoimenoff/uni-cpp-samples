#include "university.h"

/*Helper private methods*/
void University::resize(int newCapacity)
{
	arrayCapacity = newCapacity;
	Student* oldArray = students;
	students = new Student[arrayCapacity];
	for (int i = 0; i < studentsNumber; ++i)
	{
		students[i] = oldArray[i];
	}
	delete[] oldArray;
}

void University::copyStudents(const University& other)
{
	arrayCapacity = other.arrayCapacity;
	studentsNumber = other.studentsNumber;
	students = new Student[arrayCapacity];
	for (int i = 0; i < studentsNumber; ++i)
	{
		students[i] = other.students[i];
	}
}

int University::findStudent(int facultyNumber) const
{
	for (int i = 0; i < studentsNumber; ++i)
	{
		if (students[i].getFacultyNumber() == facultyNumber)
		{
			return i;
		}
	}
	return -1;
}
/*Constructors and assignment operator*/
University::University(unsigned int capacity)
{
	studentsNumber = 0;
	arrayCapacity = capacity;
	students = new Student[arrayCapacity];
}

University::University(const University& other)
{
	copyStudents(other);
}

University& University::operator = (const University& other)
{
	if (this != &other)
	{
		delete[] students;
		copyStudents(other);
	}
	return *this;
}

University::~University()
{
	delete[] students;
}
/*Interface functions*/
bool University::addStudent(const Student& student)
{
	if (studentsNumber == arrayCapacity)
	{
		resize(2 * arrayCapacity);
	}
	int index = findStudent(student.getFacultyNumber());
	if (index != -1) //there is a student with that faculty number
	{
		return false;
	}
	students[studentsNumber] = student;
	studentsNumber += 1;
	return true;
}

bool University::removeStudent(unsigned int facultyNumber)
{
	int index = findStudent(facultyNumber);
	if (index == -1)
	{
		return false;
	}
	Student swaper = students[index];
	students[index] = students[studentsNumber - 1];
	students[studentsNumber - 1] = swaper;
	studentsNumber -= 1;
	return true;
}

Student& University::getStudent(unsigned int facultyNumber)
{
	int index = findStudent(facultyNumber);
	assert(index != -1);
	return students[index];
}

void University::print() const
{	
	std::cout << "---------------University---------------\n";
	for (int i = 0; i < studentsNumber; ++i)
	{
		students[i].print();
	}
}
/*Comparator for sorting*/
bool comparator(const Student& s1, const Student& s2)
{
	return s1.getAverageGrades() < s2.getAverageGrades();
}
/*Sort*/
void University::sortStudents()
{
	std::sort(students, students + studentsNumber, comparator);
}
/*Ostream operator*/
std::ostream& operator << (std::ostream& out, const University& university)
{
	std::cout << "---------------University---------------\n";
	for (int i = 0; i < university.studentsNumber; ++i)
	{
		out << university.students[i];
	}
	return out;
}