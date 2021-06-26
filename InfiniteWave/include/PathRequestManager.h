#pragma once
#ifndef PATH_REQUEST_MANAGER_H
#define PATH_REQUEST_MANAGER_H
#include <queue>
#include <SFML/System/Thread.hpp>

#include "PathFinding.h"

class Zombie;

class PathFindingRequest
{
public:
	Zombie* zombie;
	sf::Vector2f start_position;

	PathFindingRequest(Zombie& zombie, const sf::Vector2f& start_position):zombie(&zombie), start_position(start_position){}
};

class PathRequestManager
{
public:
	PathRequestManager(PathFinding& path_finding);
	~PathRequestManager();
	
	void AddRequest(Zombie& zombie_obj, const sf::Vector2f& start_position);
	void TryNext();
	void StartProcess();
	Grid* getGrid();
private:
	bool isBusy = false;
	
	PathFinding& mPathfinding;
	std::queue<PathFindingRequest> requestQueue;
	PathFindingRequest* currentRequest;
	sf::Thread pfThread;
};

#endif


