#include "role.h"

const char* RoleEnumStrings[3] = {"Actor", "Director", "Producer"};
const Role RoleEnum[3] = {Actor, Director, Producer};

Role numberToRole(int i)
{
	return RoleEnum[i];
}

std::ostream& operator << (std::ostream& out, const Role role)
{
	out << RoleEnumStrings[role];
	return out;
}

void writeRoleToFileStream(std::ofstream& fout, const Role role)
{
	int i = role;
	fout << i;
}

Role readRoleFromFileStream(std::ifstream& fin)
{
	int i;
	fin >> i;
	return numberToRole(i);
}