#pragma once
#ifndef PATH_REQUEST_MANAGER_H_
#define PATH_REQUEST_MANAGER_H_

#include <queue>
#include <SFML/System/Thread.hpp>

#include "PathFinding.h"

class Zombie;


class PathFindingRequest
{
public:
	Zombie* zombie;
	sf::Vector2f startPosition;

	PathFindingRequest(Zombie& zombie, const sf::Vector2f& start_position):zombie(&zombie), startPosition(start_position){}
};

class PathRequestManager
{
public:
	PathRequestManager(PathFinding& path_finding);
	~PathRequestManager();
	
	void AddRequest(Zombie& zombie_obj, const sf::Vector2f& start_position);
	void TryNext();
	void StartProcess();
	
	Grid* GetGrid();

private:
	bool mIsBusy = false;
	
	PathFinding& mPathfinding;
	PathFindingRequest* mCurrentRequest;
	sf::Thread mPFThread;

	std::queue<PathFindingRequest> mRequestQueue;
};

#endif


