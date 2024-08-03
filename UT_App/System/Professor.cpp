#include "Professor.hpp"

Professor::Professor(string Id, string name, int majorId, string position)
    : Account(Id, name, majorId), position(position) {}
Professor::~Professor() {}

void Professor::setProfessorPosition(const string &rank)
{
    position = rank;
}