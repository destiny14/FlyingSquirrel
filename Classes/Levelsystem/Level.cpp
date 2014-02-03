#include "Level.h"
#include "tinyxml2\tinyxml2.h"
Level* Level::createFromFile(const char* filename)
{
	Level* l = new Level();
	l->dump_to_stdout(filename);
	return nullptr;
}

Level::Level() {}
Level::~Level() {}

void Level::dump_to_stdout(const char* filename)
{
	tinyxml2::XMLDocument doc;
	int e = doc.LoadFile(filename);
	if (e == 0)
	{
		log(doc.FirstChildElement("tag")->GetText());
	}
	else 
	{
		log("XML File Error %i", e);
	}
}