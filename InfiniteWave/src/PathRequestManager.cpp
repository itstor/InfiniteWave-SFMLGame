#include "PathRequestManager.h"
#include "Zombie.h"

PathRequestManager::PathRequestManager(PathFinding& path_finding): mPathfinding(path_finding), mCurrentRequest(nullptr), mPFThread(&PathRequestManager::StartProcess, this)
{
	mPFThread.launch();

}

PathRequestManager::~PathRequestManager()
{
	mPFThread.terminate();
}

void PathRequestManager::StartProcess()
{
	while (true) {
		if (!mRequestQueue.empty()) {
			mCurrentRequest = &mRequestQueue.front();
			//Skip if zombie deleted
			if (mCurrentRequest->zombie == nullptr)
			{
				mRequestQueue.pop();
				continue;
			}
			std::stack<Node> walkpath = mPathfinding.FindPath(mCurrentRequest->startPosition);
			mCurrentRequest->zombie->SetWalkPath(walkpath);
			mRequestQueue.pop();
		}
	}
}

Grid* PathRequestManager::GetGrid()
{
	return &*mPathfinding.GetGrid();
}

void PathRequestManager::AddRequest(Zombie& zombie_obj, const sf::Vector2f& start_position)
{
	mRequestQueue.emplace(zombie_obj, start_position);
}



