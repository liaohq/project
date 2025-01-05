#ifndef SPACE_H
#define SPACE_H


class Space {
public:
	Space(int mapID): m_mapID(mapID){}
	~Space();
	int	GetMapID();
private:
	int m_mapID;
};

#endif



