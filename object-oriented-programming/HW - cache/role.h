#ifndef _ROLE_H_
#define _ROLE_H_

#include <iostream>
#include <fstream>
#include <cstring>

enum Role {Actor, Director, Producer};

std::ostream& operator << (std::ostream& out, const Role role);

Role numberToRole(int i);
void writeRoleToFileStream(std::ofstream& fout, const Role role);
Role readRoleFromFileStream(std::ifstream& fin);

#endif 
