#include "PathRequestManager.h"
#include "Zombie.h"

PathRequestManager::PathRequestManager(PathFinding& path_finding): mPathfinding(path_finding), currentRequest(nullptr), pfThread(&PathRequestManager::StartProcess, this)
{
	pfThread.launch();

}

PathRequestManager::~PathRequestManager()
{
	pfThread.terminate();
}

void PathRequestManager::StartProcess()
{
	while (true) {
		if (!requestQueue.empty()) {
			currentRequest = &requestQueue.front();
			//Skip if zombie deleted
			if (currentRequest->zombie == nullptr)
			{
				requestQueue.pop();
				continue;
			}
			std::stack<Node> walkpath = mPathfinding.FindPath(currentRequest->start_position);
			currentRequest->zombie->setWalkPath(walkpath);
			requestQueue.pop();
		}
	}
}

Grid* PathRequestManager::getGrid()
{
	return &*mPathfinding.getGrid();
}

void PathRequestManager::AddRequest(Zombie& zombie_obj, const sf::Vector2f& start_position)
{
	requestQueue.emplace(zombie_obj, start_position);
}

void PathRequestManager::TryNext()
{
	if (!isBusy && !requestQueue.empty())
	{
		currentRequest = &requestQueue.front();
		isBusy = true;
	}
}



