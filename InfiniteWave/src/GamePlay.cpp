#include "GamePlay.h"

//Related Scene

//Required Library
#include <iostream>

#include "Window.h"
#include "AudioManager.h"

#include "BlackZombie.h"
#include "BlueZombie.h"
#include "GameoverScene.h"
#include "NormalZombie.h"
#include "RedZombie.h"
#include "SceneManager.h"

#define NORMAL_ZOMBIE 0
#define RED_ZOMBIE 1
#define BLUE_ZOMBIE 2
#define BLACK_ZOMBIE 3


GamePlay::GamePlay(SharedObject& obj, bool replace) : BaseScene(obj, replace),
                                                      mPathFindingGrid(obstacleContainer),
                                                      mPathFinding(mPathFindingGrid), mRequestManager(mPathFinding), ls(false)
{
#ifdef _DEBUG
	std::cout << "GamePlay Created" << std::endl;
#endif
	//stop main menu music
	mAudio.stopAll();
	//init view
	camera.reset(sf::FloatRect(0, 0, 3840, 2160));
	GUICamera.reset(sf::FloatRect(8118, 0, 1920, 1080));

	//init path finding grid
	mPathFindingGrid.Setup(sf::Vector2f(8019, 6547), sf::Vector2f(136, 136));

	////init overlay
	//const sf::Color nightOverlayColor(0,0,0,200);
	//nightOverlay.setFillColor(nightOverlayColor);
	//nightOverlay.setSize(sf::Vector2f(1920, 1080));
	//nightOverlay.setPosition(8118, 0);
	//mistTex.loadFromFile("Assets/Texture/Sprites/Map/mist.png");
	//mist.setTexture(&mistTex);
	//mist.setSize(sf::Vector2f(1920, 1080));
	//mist.setPosition(8118, 0);


	//Load zombie Texture
	normalZombieTex.loadFromFile("Assets/Texture/Sprites/Zombie/normal-zombie-sprites.png");
	normalZombieTex.setSmooth(true);

	redZombieTex.loadFromFile("Assets/Texture/Sprites/Zombie/red-zombie-sprites.png");
	redZombieTex.setSmooth(true);

	blueZombieTex.loadFromFile("Assets/Texture/Sprites/Zombie/blue-zombie-sprites.png");
	blueZombieTex.setSmooth(true);

	blackZombieTex.loadFromFile("Assets/Texture/Sprites/Zombie/black-zombie-sprites.png");
	blackZombieTex.setSmooth(true);
	
	player.setPosition(sf::Vector2f(3602.19f, 4756.3f));

	initLight();
	initMap();
	initObstacles();
	initGUI();
	mPathFindingGrid.CreateGrid();

	//pfThread.launch();
}

GamePlay::~GamePlay()
{
	std::cout << "GamePlay Deleted" << std::endl;
	mWindow.GetRenderWindow()->setView(mWindow.GetRenderWindow()->getDefaultView());
}

void GamePlay::initMap()
{
	const int map[] = { 71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,392,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
143,143,143,143,143,143,143,143,143,143,143,143,143,143,143,146,807,817,817,817,817,817,817,817,817,817,817,593,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,593,817,817,817,817,817,817,392,817,817,817,817,817,
303,303,610,303,303,303,303,303,303,303,303,303,303,303,303,5,807,817,817,8,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,5,807,817,817,817,8,817,817,817,817,817,817,593,817,817,817,817,817,593,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
303,303,578,303,303,303,303,303,303,303,303,578,303,303,303,5,807,817,8,8,817,817,817,817,817,817,817,817,817,817,817,817,817,817,522,817,817,817,817,817,10,10,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,5,807,8,8,8,8,817,817,817,817,817,817,817,817,817,817,817,817,817,817,522,817,817,817,817,9,9,817,817,817,817,817,817,817,560,559,559,560,560,817,817,817,817,817,
303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,5,807,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,817,817,817,817,817,817,817,560,559,594,594,817,817,817,817,817,817,
32,144,32,32,33,482,482,482,482,482,32,33,34,608,36,37,807,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,817,392,817,817,817,559,560,10,594,625,560,625,625,817,817,817,817,
303,176,303,303,65,303,303,303,303,303,64,65,608,608,68,69,807,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,817,817,817,817,560,626,625,559,560,594,594,817,817,817,817,817,817,
303,303,303,303,65,303,303,303,303,303,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,817,817,817,817,817,626,817,817,817,817,817,560,817,817,817,817,817,
604,605,303,303,65,303,303,303,303,303,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,492,148,149,150,151,152,153,154,155,156,157,158,159,817,817,817,559,817,817,817,817,817,817,559,817,817,817,817,817,817,
636,637,303,303,65,303,303,303,303,303,160,161,162,163,164,165,807,167,168,169,170,171,172,173,367,367,176,367,178,492,180,181,182,183,184,185,186,187,188,189,190,191,817,817,817,817,817,817,817,817,13,13,13,13,13,13,13,13,13,
668,303,303,303,65,303,303,303,303,303,192,193,608,195,196,197,807,199,200,201,202,203,204,205,367,207,208,209,210,492,212,213,214,215,216,217,218,219,220,221,222,223,145,145,145,145,145,145,145,145,146,13,13,13,13,13,13,13,13,
303,303,303,303,65,303,303,303,303,303,224,225,608,227,228,229,230,231,232,233,234,235,236,367,367,239,240,241,242,492,244,245,246,247,248,249,250,270,270,253,254,270,270,270,270,270,270,270,270,270,178,13,13,13,13,13,13,13,13,
303,303,303,303,65,303,303,303,303,303,256,257,608,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,367,278,276,277,278,279,280,281,270,270,284,285,286,287,304,304,304,304,304,304,304,304,178,13,13,13,13,13,13,13,13,
288,288,288,288,289,288,288,288,288,288,288,289,290,608,292,293,807,295,296,297,298,299,300,301,367,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,304,271,304,304,304,304,304,304,178,13,13,13,13,13,13,13,13,
807,593,807,807,807,807,807,807,807,807,807,807,807,323,324,807,807,327,328,329,330,331,332,333,367,335,336,337,338,807,340,341,342,343,344,345,346,270,348,349,350,351,304,304,304,578,304,304,271,304,242,13,13,13,13,13,13,13,13,
559,71,71,559,71,71,392,71,71,552,352,353,354,355,356,357,358,359,360,361,362,363,364,365,367,367,368,369,370,807,372,373,374,375,376,377,378,379,380,381,270,383,304,304,304,304,304,304,304,304,270,277,277,279,617,247,46,622,280,
71,593,71,71,71,71,71,71,520,552,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,807,404,405,406,407,408,409,410,270,270,270,270,415,304,271,304,304,304,304,304,304,270,308,309,309,308,312,308,308,308,
71,71,559,71,71,71,71,71,71,520,416,417,418,419,420,421,422,423,424,425,426,427,428,807,807,431,432,807,807,807,436,437,438,439,440,441,442,270,444,445,446,447,304,304,304,304,304,304,304,304,338,13,13,13,13,13,13,13,13,
71,71,71,71,71,71,71,71,71,71,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,270,479,304,304,304,304,304,304,304,304,178,13,13,13,13,13,13,13,13,
770,770,770,770,770,770,770,770,770,770,480,481,482,483,484,485,807,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,270,270,504,505,506,507,270,270,270,511,304,304,271,578,304,304,304,304,178,13,13,13,13,626,13,13,13,
608,608,608,728,729,730,731,608,608,608,608,608,608,608,608,517,807,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,270,535,536,537,538,539,540,541,270,543,304,304,271,304,304,304,304,304,242,13,626,13,13,593,13,626,13,
609,609,695,537,537,537,537,541,609,609,544,545,546,547,548,549,807,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,270,270,270,270,270,270,270,270,270,575,304,304,304,304,304,304,271,304,270,13,13,13,13,13,13,593,13,
609,609,608,608,608,608,608,608,609,609,576,577,578,608,580,581,807,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,603,604,605,606,607,304,304,304,304,304,304,304,304,270,13,13,13,626,13,13,13,13,
609,609,609,609,609,609,609,609,609,609,608,609,608,608,612,612,277,615,616,617,618,619,620,621,622,623,624,625,626,627,628,629,630,631,632,633,634,635,636,637,638,639,304,304,304,271,304,304,304,304,338,492,492,13,13,13,13,13,13,
609,609,609,602,603,604,605,609,609,609,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,661,270,663,664,665,666,667,668,669,670,671,271,304,304,578,304,304,304,304,178,492,492,13,13,13,13,13,13,
609,609,609,634,635,636,637,609,609,609,672,673,674,608,676,677,807,679,680,681,682,683,684,685,686,687,688,689,690,691,692,693,270,695,696,697,698,699,700,701,270,703,304,304,304,304,271,304,304,304,178,492,13,13,13,13,392,13,13,
609,609,609,609,667,668,609,609,609,609,704,705,608,608,708,709,807,711,712,713,714,715,716,717,718,719,720,721,722,723,724,725,270,727,728,729,730,731,270,270,270,735,304,304,304,304,304,304,304,304,178,492,13,13,626,13,13,13,13,
609,609,609,609,609,609,609,609,609,609,736,737,738,739,740,741,807,743,744,745,746,747,748,749,750,751,752,753,754,755,756,757,758,759,760,761,762,763,764,765,766,767,767,767,767,767,767,767,767,767,402,492,13,13,13,13,13,13,13,
770,770,770,770,770,770,770,770,770,770,768,769,770,771,772,773,807,775,776,777,778,779,780,781,782,783,784,785,786,787,788,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,492,13,13,13,13,13,13,13,
808,808,808,808,808,808,807,807,807,807,807,807,807,807,807,807,807,807,808,809,810,811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,828,829,830,831,825,825,825,825,825,825,825,825,492,13,13,13,13,13,13,13,13,
817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,559,559,559,817,817,817,817,817,817,817,817,626,817,817,817,817,817,817,817,392,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
817,817,817,817,817,817,817,817,559,817,817,817,817,817,817,817,817,559,817,817,559,593,593,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,626,817,817,
817,817,817,817,817,817,817,817,817,559,817,626,817,817,817,817,559,817,817,817,817,593,593,817,559,817,817,626,559,817,817,817,817,559,559,817,559,817,817,817,817,817,817,817,817,817,559,817,817,817,626,817,817,817,817,817,817,817,817,
817,817,817,817,817,817,559,817,817,817,817,817,817,817,817,817,817,817,817,559,817,559,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,626,559,559,817,817,817,817,817,817,817,817,817,817,817,817,
817,817,817,817,817,584,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,584,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,584,817,817,817,
655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,
648,648,648,648,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,655,655,
648,648,648,648,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,647,655,655,
655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,655,
809,809,809,809,809,809,809,809,809,584,809,809,809,809,626,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,584,809,809,809,809,809,809,809,809,809,809,809,809,
809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,
809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,626,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809
 };

	gameMap.load("Assets/Texture/Sprites/Map/jawbreaker.png", sf::Vector2u(8, 8), map, 59, 48);
	gameMap.setScale(17, 17);
}

void GamePlay::initObstacles()
{
	//ROCKS
	obstacleContainer.emplace_back(sf::Vector2f(5331, 4921), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(3154, 4236), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(2470.75f, 3011.46f), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(836.35f, 2876.25f), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(7645.07f, 4238.22f), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(7236.48f, 699.15f), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(2603.79f, 423.11f), sf::Vector2f(94, 100));
	
	//WALLS
	/*left top room*/
	obstacleContainer.emplace_back(sf::Vector2f(291, 1091), sf::Vector2f(126, 126)); //left
	obstacleContainer.emplace_back(sf::Vector2f(1501, 1091), sf::Vector2f(126, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 2045, 2588 ), sf::Vector2f( 126, 126)); //right


	obstacleContainer.emplace_back(sf::Vector2f(0, 684), sf::Vector2f(2175, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f(0, 1501), sf::Vector2f(1764, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f(2042, 812), sf::Vector2f(126, 968)); //right
	obstacleContainer.emplace_back(sf::Vector2f(0, 1630), sf::Vector2f(675.68f, 960.7f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(0, 2591), sf::Vector2f(1764, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 1498, 1623 ), sf::Vector2f( 126, 273 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 1498, 2187 ), sf::Vector2f( 126, 404.5f )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 2044, 2042 ), sf::Vector2f( 126, 270 )); //right


	/*center room*/
	obstacleContainer.emplace_back(sf::Vector2f(3134, 2588), sf::Vector2f(126, 544));
	obstacleContainer.emplace_back(sf::Vector2f(3815, 2721), sf::Vector2f(126, 411.5f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(3815, 2034), sf::Vector2f(126, 411.5f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(3135, 2034), sf::Vector2f(126, 281)); //right
	obstacleContainer.emplace_back(sf::Vector2f(3135, 1908), sf::Vector2f(811.5f, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f(3265.61f, 3006.43f), sf::Vector2f(126, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 3689.61f, 3006.43f ), sf::Vector2f( 126, 126 )); //right
	
	
	/*right room*/
	obstacleContainer.emplace_back(sf::Vector2f( 6133, 2725 ), sf::Vector2f( 126, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 6133, 3408 ), sf::Vector2f( 126, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 6133, 4089 ), sf::Vector2f( 126, 126 )); //right

	
	obstacleContainer.emplace_back(sf::Vector2f(4220, 4500), sf::Vector2f(2721, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f(4900, 2183), sf::Vector2f(407, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 5580.16f, 2183 ), sf::Vector2f( 1361, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f(4220, 4088), sf::Vector2f(126, 411.5f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(4220, 3397), sf::Vector2f(126, 411.5f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(6808, 3132), sf::Vector2f(126, 537)); //right
	obstacleContainer.emplace_back(sf::Vector2f(6808, 2309), sf::Vector2f(126, 537)); //right
	obstacleContainer.emplace_back(sf::Vector2f(6808, 3962), sf::Vector2f(126, 537)); //right
	obstacleContainer.emplace_back(sf::Vector2f(4901, 2730), sf::Vector2f(126, 537)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 4899.45f, 2309.25f ), sf::Vector2f( 126, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 5032, 2863 ), sf::Vector2f( 408, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 5032, 3267.5f ), sf::Vector2f( 408, 126 )); //right




	/*left bottom room*/
	obstacleContainer.emplace_back(sf::Vector2f(1653.48f, 4236), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(1653.48f, 3829.75f), sf::Vector2f(94, 100));
	
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 4638.04f), sf::Vector2f(2175, 126.25f)); //bottom wall
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 3408), sf::Vector2f(2175, 126.25f)); //top wall
	obstacleContainer.emplace_back(sf::Vector2f(2043.0f, 4226.48f), sf::Vector2f(131, 411.56f)); //left bottom wall
	obstacleContainer.emplace_back(sf::Vector2f( 2043.0f, 3534.0 ), sf::Vector2f( 131, 411.56f )); //left top wall

	//Add light obstacle
	for (auto &obs:obstacleContainer)
	{
		ls.createLightShape(*obs.getCollider())->setRenderLightOver(false);
	}
	
	//MAP BOUNDARIES
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(-1.0f, 6536.0f));
	obstacleContainer.emplace_back(sf::Vector2f(8018.0f, 0.0f), sf::Vector2f(1.0f, 6536.0f));
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 6536.0f), sf::Vector2f(8018.0f, 1.0f));
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(8018.0f, -1.0f));
	
	//STAIRS
	obstacleContainer.emplace_back(sf::Vector2f(269, 3538), sf::Vector2f(822.28f, 272)); //left bottom room
	obstacleContainer.emplace_back(sf::Vector2f(4494, 3394), sf::Vector2f(948, 272)); //right room, top
	obstacleContainer.emplace_back(sf::Vector2f(4494, 4227), sf::Vector2f(948, 272)); //right room, bottom

	//OUTDOOR LADDER
	obstacleContainer.emplace_back(sf::Vector2f(2700, 4479), sf::Vector2f(182.81f, 176.56f)); //right room, bottom


}

void GamePlay::initButton()
{
	//Initialize button here
}

void GamePlay::initLight()
{
	//init light system
	ls.create({ 100.0f,100.0f,200.0f,200.0f }, mWindow.GetWindowSize());

	//load light texture
	flashLightTexture.loadFromFile("Assets/Texture/Sprites/Map/flashlight.png");
	flashLightTexture.setSmooth(true);

	pointLightTexture.loadFromFile("Assets/Texture/Sprites/Map/pointLightTexture.png");
	pointLightTexture.setSmooth(true);

	flashLight = ls.createLightPointEmission();
	flashLight->setOrigin(sf::Vector2f(static_cast<float>(flashLightTexture.getSize().x), static_cast<float>(flashLightTexture.getSize().y) * 0.5f));
	flashLight->setTexture(flashLightTexture);
	flashLight->setScale(-5.f, 5.f);
	flashLight->setColor(sf::Color::White);

	gunLight = ls.createLightPointEmission();
	gunLight->setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));
	gunLight->setTexture(pointLightTexture);
	gunLight->setScale(15.f, 15.f);
	gunLight->setColor(sf::Color::Yellow);
	gunLight->setTurnedOn(false);

	ls.setAmbientColor({ 30,30,30 });
}

void GamePlay::initGUI()
{
	pixelFont.loadFromFile("Assets/Font/Minecraft.ttf");
	ammoText.setFont(pixelFont);
	killText.setFont(pixelFont);
	scoreTitleText.setFont(pixelFont);
	scoreTotalText.setFont(pixelFont);
	waveTitleText.setFont(pixelFont);
	waveCurrentText.setFont(pixelFont);
	waveCompleteText.setFont(pixelFont);

	ammoText.setString("18/18");
	killText.setString("0");
	scoreTitleText.setString("Score:");
	scoreTotalText.setString("0");
	waveTitleText.setString("Wave:");
	waveCurrentText.setString("1/~");
	waveCompleteText.setString("Wave Complete");

	healthIconTex.loadFromFile("Assets/Texture/GUI/health.png");
	killIconTex.loadFromFile("Assets/Texture/GUI/kill.png");
	ammoIconTex.loadFromFile("Assets/Texture/GUI/ammo.png");
	
	healthIconRect.setTexture(&healthIconTex);
	killIconRect.setTexture(&killIconTex);
	ammoIconRect.setTexture(&ammoIconTex);
	healthBar.setFillColor(sf::Color::Red);
	ammoText.setFillColor(sf::Color(204, 153, 37));
	killText.setFillColor(sf::Color::White);
	scoreTitleText.setFillColor(sf::Color::White);
	scoreTotalText.setFillColor(sf::Color::White);
	waveTitleText.setFillColor(sf::Color::White);
	waveCurrentText.setFillColor(sf::Color::White);
	waveCompleteText.setFillColor(sf::Color::White);
	
	healthIconRect.setSize(static_cast<const sf::Vector2f>(healthIconTex.getSize()));
	killIconRect.setSize(static_cast<const sf::Vector2f>(killIconTex.getSize()));
	ammoIconRect.setSize(static_cast<const sf::Vector2f>(ammoIconTex.getSize()));
	healthBar.setSize({ 318, 28.65f });
	ammoText.setScale(1.2f, 1.2f);
	killText.setScale(1.2f, 1.2f);
	scoreTitleText.setScale(0.8f, 0.8f);
	scoreTotalText.setScale(1.5f, 1.5f);
	waveTitleText.setScale(1, 1);
	waveCurrentText.setScale(1.8f, 1.8f);
	waveCompleteText.setScale(0.0f, 0.0f);

	healthIconRect.setPosition(9581.59f, 38.3f);
	killIconRect.setPosition(9631.25f, 118.71f);
	ammoIconRect.setPosition(9786.53f, 118.71f);
	healthBar.setPosition(9642.53f, 51.45f);
	ammoText.setPosition(9850.2f, 127.2f);
	killText.setPosition(9693.63f, 127.7f);
	scoreTitleText.setPosition(8155.36f, 956.08f);
	scoreTotalText.setPosition(8155.36f, 978.27f);
	waveTitleText.setPosition(9889.69f, 926.52f);
	waveCurrentText.setPosition(9889.69f, 970.61f);
	waveCompleteText.setOrigin(waveCompleteText.getLocalBounds().left + waveCompleteText.getLocalBounds().width * 0.5f,
	                           waveCompleteText.getLocalBounds().top + waveCompleteText.getLocalBounds().height * 0.5f);
	waveCompleteText.setPosition(9078.31f, 540.0f);
}

void GamePlay::Pause()
{
	std::cout << "GamePlay Paused" << std::endl;
}

void GamePlay::Resume()
{
	std::cout << "GamePlay Resume" << std::endl;
}

void GamePlay::calculateTotalZombie()
{
	const auto n = static_cast<float>(currentWave);
	
	totalNormalZombie = static_cast<int>(floor((powf(n, 2) + 15) / 4.0f));
	totalRedZombie = static_cast<int>(floor((powf(n, 2) - 3) / 4.0f));
	totalBlueZombie = static_cast<int>(floor((powf(n, 2) - 7) / 6.0f));
	totalBlackZombie = static_cast<int>(floor((powf(n, 2) - 10) / 10.0f));

	totalNormalZombie = totalNormalZombie > 0 ? totalNormalZombie : 0;
	totalRedZombie = totalRedZombie > 0 ? totalRedZombie : 0;
	totalBlueZombie = totalBlueZombie > 0 ? totalBlueZombie : 0;
	totalBlackZombie = totalBlackZombie > 0 ? totalBlackZombie : 0;

	//std::cout << totalNormalZombie << totalRedZombie << totalBrownZombie << totalBlackZombie;
	currentActiveZombie = totalNormalZombie + totalRedZombie + totalBlueZombie + totalBlackZombie;
}

bool GamePlay::spawnZombie(float deltaTime)
{
	spawnCooldown -= deltaTime;
	if (spawnCooldown <= 0.0f)
	{
		if (totalNormalZombie > 0)
		{
			totalNormalZombie--;
			spawn(NORMAL_ZOMBIE, player.getPosition());
		}
		else if (totalRedZombie > 0)
		{
			totalRedZombie--;
			spawn(RED_ZOMBIE, player.getPosition());
		}
		else if (totalBlueZombie > 0)
		{
			totalBlueZombie--;
			spawn(BLUE_ZOMBIE, player.getPosition());
		}
		else if (totalBlackZombie > 0)
		{
			totalBlackZombie--;
			spawn(BLACK_ZOMBIE, player.getPosition());
		}
		else
		{
			return true; //return true if all have been spawned
		}
		spawnCooldown = 1.0f;
	}
	return false;
}

void GamePlay::spawn(int zombieType, const sf::Vector2f & playerPos)
{
	float yPos = 1091.0f; //Obstacle
	float xPos = 291.0f; //Obstacle
	while (mPathFindingGrid.GetNodeType(mPathFindingGrid.GetGridIndexFromPosition({ xPos,yPos })) != NodeType::WALKABLE_NODE) {
		xPos = static_cast<float>(rand() % 8019);
		yPos = static_cast<float>(rand() % 6547);
	}
	switch (zombieType)
	{
	case NORMAL_ZOMBIE: zombieContainer.push_back(new NormalZombie({ xPos,yPos }, normalZombieTex, mRequestManager, *mAudio.getSoundBuffer("zombie_1"))); break;
	case RED_ZOMBIE: zombieContainer.push_back(new RedZombie({ xPos,yPos }, redZombieTex, mRequestManager, *mAudio.getSoundBuffer("zombie_1"))); break;
	case BLUE_ZOMBIE: zombieContainer.push_back(new BlueZombie({ xPos,yPos }, blueZombieTex, mRequestManager, *mAudio.getSoundBuffer("zombie_1"))); break;
	case BLACK_ZOMBIE: zombieContainer.push_back(new BlackZombie({ xPos,yPos }, blackZombieTex, mRequestManager, *mAudio.getSoundBuffer("zombie_1"))); break;
	default: break;
	}
}

void GamePlay::Update(float deltaTime)
{
	for (auto event = sf::Event{}; mWindow.GetRenderWindow()->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed: mWindow.Destroy(); break;
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
				/*Only for non-simultaneous key
				Use if statement for simultaneous key*/
			case sf::Keyboard::R: 
			{
				mAudio.playSFX("pistol_reload");
				player.Reload();
				ammoText.setString(std::string(std::to_string(player.getAmmo())).append("/18"));
			} break;
			case sf::Keyboard::F1: showGUI = !showGUI; break;
			case sf::Keyboard::F11: mWindow.ToggleFullScreen(); break;
			case sf::Keyboard::Space: mNext = SceneManager::build<GameoverScene>(mObj, true); break;
			default: break;
			}
			break;
		}
		case sf::Event::MouseButtonPressed:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					{
						if (player.Shoot())
						{
							mAudio.playSFX("pistol_shoot");
							
							bullet.setStartPos(sf::Vector2f(player.getPosition().x + 20, player.getPosition().y + 20));
							bullet.setDir(*player.getDirVect());

							gunLight->setTurnedOn(true);
							gunLightDelay = 0.0f;
							isGUIZoom = true;

							ammoText.setString(std::string(std::to_string(player.getAmmo())).append("/18"));

							bulletContainer.emplace_back(bullet);
						}
						else if (player.getAmmo() <= 0)
						{
							mAudio.playSFX("pistol_click");
						}
				} break;
				default: break;
				}
		} break;
		default: break;
		}
	}

	/*if (isGUIZoom)
	{
		zoomGUITotalTime += deltaTime;
		if (zoomGUITotalTime >= 0.01f)
		{
			static int zoomAnimFlag = 1;
			zoomGUIAmount += 0.005f * zoomAnimFlag;
			GUICamera.zoom(zoomGUIAmount);
			if (zoomGUIAmount >= 1.03f && zoomAnimFlag == 1)
			{
				zoomAnimFlag *= -1;
				zoomGUIAmount = 1.0f;
			}
			else if (zoomGUIAmount <= 0.972f && zoomAnimFlag == -1)
			{
				zoomAnimFlag *= -1;
				zoomGUIAmount = 1.0f;
				isGUIZoom = false;
			}
			zoomGUITotalTime = 0.0f;
		}
	}*/

	if (gunLight->isTurnedOn()) {
		gunLightDelay += deltaTime;

		if (gunLightDelay >= 0.1f)
			gunLight->setTurnedOn(false);
	}
	
	/*UPDATE CAMERA CENTER*/
	if ((player.getPosition().x - camera.getSize().x / 2 < 0 ||
		player.getPosition().x + camera.getSize().x / 2 > 8018) &&
		(player.getPosition().y - camera.getSize().y / 2 < 0 ||
		player.getPosition().y + camera.getSize().y / 2 > 6536))
	{
		camera.setCenter(camera.getCenter().x, camera.getCenter().y);
	}
	else if (player.getPosition().x - camera.getSize().x / 2 < 0 ||
		player.getPosition().x + camera.getSize().x / 2 > 8018)
	{
		camera.setCenter(camera.getCenter().x, player.getPosition().y);
	}
	else if (player.getPosition().y - camera.getSize().y / 2 < 0 ||
		player.getPosition().y + camera.getSize().y / 2 > 6536)
	{
		camera.setCenter(player.getPosition().x, camera.getCenter().y);
	}
	else
	{
		camera.setCenter(player.getPosition());
	}
	
	//Update player face dir and light dir
	const sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
	const sf::Vector2f worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);
	player.lookAt(worldMousePos);

	flashLight->setPosition(player.getPosition());
	gunLight->setPosition(player.getPosition());
	flashLight->setRotation(player.getAngle());
	
	//Player keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.MoveDirection(MoveDir::UP, deltaTime);
		//camera.move(0*deltaTime, -400.f*deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.MoveDirection(MoveDir::LEFT, deltaTime);
		//camera.move(-400.0f*deltaTime, 0*deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.MoveDirection(MoveDir::DOWN, deltaTime);
		//camera.move(0*deltaTime, 400.f*deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.MoveDirection(MoveDir::RIGHT, deltaTime);
		//camera.move(400.0f*deltaTime, 0*deltaTime);
	}
	//allowUpdatePath = false;
	//Update zombie and player
	player.Update(deltaTime);
	for (auto &zombie : zombieContainer) {
		zombie->Update(deltaTime, player.getPosition());
	}

	//All object collision check here
	//On Collision with obstacle or wall
	for (auto &obs : obstacleContainer)
	{
		player.CheckCollision(obs);
		for (size_t i = 0; i < bulletContainer.size(); i++)
		{	
			//Check if bullet collided with obstacle or out of radius, delete
			if (bulletContainer[i].onCollision(obs) || pow(bulletContainer[i].startPosition.x - bulletContainer[i].getPosition().x, 2)
				+ pow(bulletContainer[i].startPosition.y - bulletContainer[i].getPosition().y, 2)
				> pow(3000, 2))
			{
				bulletContainer.erase(bulletContainer.begin() + i);
			}
		}
	}

	
	for (size_t j = 0; j < zombieContainer.size(); j++) {
		//Check player attack
		if (player.onCollision(*zombieContainer[j]) && zombieContainer[j]->isAllowAttack())
		{
			zombieContainer[j]->Attack();
			player.getHit();
		}
		//Move Zombie
		//Update path finding?
		for (size_t i = 0; i < bulletContainer.size(); i++)
		{
			//Check if collided with zombie delete
			if (bulletContainer[i].onCollision(*zombieContainer[j]))
			{
				zombieContainer[j]->getHit();
				bulletContainer.erase(bulletContainer.begin() + i);
				if (zombieContainer[j]->isDead())
				{
					killCount++;
					currentActiveZombie--;
					gameScore += 1000;
					killText.setString(std::to_string(killCount));
					scoreTotalText.setString(std::to_string(gameScore));
					
					delete zombieContainer[j];
					zombieContainer.erase(zombieContainer.begin() + j);
				}
			}
		}
	}
	
	//Move everything here
	player.PlayerMove(); // Move Player
	for (auto &bul:bulletContainer) //move bullet
	{
		bul.Move(deltaTime);
	}
	for (auto &zombie:zombieContainer)
	{
		zombie->Move(deltaTime);
	}
	//Zombie PathFinding

	//Thunder Random

	//Rain Update

	//Update Wave
	if (currentActiveZombie <= 0)
	{
		nextWave = true;
		currentWave++;
		waveCurrentText.setString(std::to_string(currentWave).append("/~"));
		calculateTotalZombie();
		//Play next wave animation
		if (currentWave > 1) mAnimManager.playAnimation(AnimType::ZOOM, {0.0f,0.0f},{2.8f,0.0f},1.0f,waveCompleteText,true, 2.0f);
	}
	if (nextWave)
	{
		nextWaveDelay -= deltaTime;
		if (nextWaveDelay <= 0.0f)
		{
			if (const bool spawnedAll = spawnZombie(deltaTime); spawnedAll) {
				nextWaveDelay = 5.0f;
				nextWave = false;
			}
		}
	}

	//Update Health bar
	const float xHealthBar = (player.getHealth() / 200.0f) * 318;
	healthBar.setSize({ xHealthBar, healthBar.getSize().y });

	//update player position on grid
	mPathFindingGrid.UpdatePlayerNode(player.getPosition());

	mAnimManager.Update(deltaTime);
}

void GamePlay::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.GetRenderWindow()->setView(camera);
	
	mWindow.Draw(gameMap);
	for (auto &bul:bulletContainer)
	{
		mWindow.Draw(*bul.getDraw());
	}

	mWindow.Draw(*player.getFeetDraw());
	mWindow.Draw(*player.getDraw());

	for (auto &zombie : zombieContainer) {
		mWindow.Draw(*zombie->getDraw());
	}

	ls.render(*mWindow.GetRenderWindow());
	//mPathFindingGrid.Draw(mWindow.GetRenderWindow());

	//GUI Here
	if (showGUI) {
		mWindow.GetRenderWindow()->setView(GUICamera);
		mWindow.Draw(healthIconRect);
		mWindow.Draw(killIconRect);
		mWindow.Draw(ammoIconRect);
		mWindow.Draw(healthBar);
		mWindow.Draw(ammoText);
		mWindow.Draw(killText);
		mWindow.Draw(scoreTitleText);
		mWindow.Draw(scoreTotalText);
		mWindow.Draw(waveTitleText);
		mWindow.Draw(waveCurrentText);
		mWindow.Draw(waveCompleteText);
		//Reset view back
		mWindow.GetRenderWindow()->setView(camera);
	}
	
	mWindow.EndDraw();
}

