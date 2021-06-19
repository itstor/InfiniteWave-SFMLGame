#include "GamePlay.h"

//Related Scene
#include "SplashScreen.h"

//Required Library
#include <iostream>
#include <memory>

#include "Window.h"
#include "SceneManager.h"
#include "AudioManager.h"

GamePlay::GamePlay(SharedObject& obj, bool replace) :BaseScene(obj, replace), ls(false)
{
#ifdef _DEBUG
	std::cout << "GamePlay Created" << std::endl;
#endif
	//stop main menu music
	mAudio.stopAll();

	//init view
	camera.reset(sf::FloatRect(0, 0, 3840, 2160));
	GUICamera.reset(sf::FloatRect(8118, 0, 1920, 1080));

	////init overlay
	//const sf::Color nightOverlayColor(0,0,0,200);
	//nightOverlay.setFillColor(nightOverlayColor);
	//nightOverlay.setSize(sf::Vector2f(1920, 1080));
	//nightOverlay.setPosition(8118, 0);
	//mistTex.loadFromFile("Assets/Texture/Sprites/Map/mist.png");
	//mist.setTexture(&mistTex);
	//mist.setSize(sf::Vector2f(1920, 1080));
	//mist.setPosition(8118, 0);
	
	player.setPosition(sf::Vector2f(3602.19f, 4756.3f));

	initObstacles();
	initMap();
	initLight();
}

GamePlay::~GamePlay()
{
	std::cout << "GamePlay Deleted" << std::endl;
}

void GamePlay::initMap()
{
	const int map[] = { 71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
								71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
								71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
								71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,392,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
								71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
								143,143,143,143,143,143,143,143,143,143,143,143,143,143,143,146,38,817,817,817,817,817,817,817,817,817,817,593,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,593,817,817,817,817,817,817,392,817,817,817,817,817,
								303,303,610,303,303,303,303,303,303,303,303,303,303,303,303,5,38,817,817,8,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
								303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,5,38,817,817,817,8,817,817,817,817,817,817,593,817,817,817,817,817,593,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
								303,303,578,303,303,303,303,303,303,303,303,578,303,303,303,5,38,817,8,8,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,10,10,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,
								303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,5,6,8,8,8,8,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,817,9,9,817,817,817,817,817,817,817,560,559,559,560,560,817,817,817,817,817,
								303,303,303,303,303,303,303,303,303,303,303,303,303,303,303,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,817,817,817,817,817,817,817,560,559,594,594,817,817,817,817,817,817,
								32,144,32,32,33,482,482,482,482,482,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,817,392,817,817,817,559,560,10,594,625,560,625,625,817,817,817,817,
								303,176,303,303,65,303,303,303,303,303,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,817,817,817,817,560,626,625,559,560,594,594,817,817,817,817,817,817,
								303,303,303,303,65,303,303,303,303,303,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,817,817,817,817,817,626,817,817,817,817,817,560,817,817,817,817,817,
								604,605,303,303,65,303,303,303,303,303,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,817,817,817,559,817,817,817,817,817,817,559,817,817,817,817,817,817,
								636,637,303,303,65,303,303,303,303,303,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,817,817,817,817,817,817,817,817,13,13,13,13,13,13,13,13,13,
								668,303,303,303,65,303,303,303,303,303,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,145,145,145,145,145,145,145,145,146,13,13,13,13,13,13,13,13,
								303,303,303,303,65,303,303,303,303,303,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,175,175,175,175,175,175,175,175,178,13,13,13,13,13,13,13,13,
								303,303,303,303,65,303,303,303,303,303,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,304,304,304,304,304,304,304,304,178,13,13,13,13,13,13,13,13,
								288,288,288,288,289,288,288,288,288,288,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,304,271,304,304,304,304,304,304,178,13,13,13,13,13,13,13,13,
								321,321,321,321,321,321,321,321,321,321,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,304,304,304,578,304,304,271,304,242,13,13,13,13,13,13,13,13,
								71,71,71,71,71,71,392,71,71,71,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,304,304,304,304,304,304,304,304,274,277,277,279,617,247,46,622,280,
								71,71,71,71,71,71,71,71,71,71,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,304,271,304,304,304,304,304,304,272,308,309,309,308,312,308,308,308,
								71,71,71,71,71,71,71,71,71,71,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,304,304,304,304,304,304,304,304,338,13,13,13,13,13,13,13,13,
								71,71,71,71,71,71,71,71,71,71,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,304,304,304,304,304,304,304,304,178,13,13,13,13,13,13,13,13,
								770,770,770,770,770,770,770,770,770,770,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,304,304,271,578,304,304,304,304,178,13,13,13,13,626,13,13,13,
								513,513,513,728,729,730,731,513,513,513,512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,304,304,271,304,304,304,304,304,242,13,626,13,13,593,13,626,13,
								609,609,695,537,537,537,537,541,609,609,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,575,304,304,304,304,304,304,271,304,274,13,13,13,13,13,13,593,13,
								609,609,567,567,567,567,567,567,609,609,576,577,578,579,580,581,582,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,603,604,605,606,607,304,304,304,304,304,304,304,304,271,13,13,13,626,13,13,13,13,
								609,609,609,609,609,609,609,609,609,609,608,609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,625,626,627,628,629,630,631,632,633,634,635,636,637,638,639,304,304,304,271,304,304,304,304,338,339,13,13,13,13,13,13,13,
								609,609,609,602,603,604,605,609,609,609,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,668,669,670,671,271,304,304,578,304,304,304,304,178,371,13,13,13,13,13,13,13,
								609,609,609,634,635,636,637,609,609,609,672,673,674,675,676,677,678,679,680,681,682,683,684,685,686,687,688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,304,304,304,304,271,304,304,304,178,550,13,13,13,13,392,13,13,
								609,609,609,609,667,668,609,609,609,609,704,705,706,707,708,709,710,711,712,713,714,715,716,717,718,719,720,721,722,723,724,725,726,727,728,729,730,731,732,733,734,735,304,304,304,304,304,304,304,304,178,550,13,13,626,13,13,13,13,
								609,609,609,609,609,609,609,609,609,609,736,737,738,739,740,741,742,743,744,745,746,747,748,749,750,751,752,753,754,755,756,757,758,759,760,761,762,763,764,765,766,767,767,767,767,767,767,767,767,767,402,403,13,13,13,13,13,13,13,
								770,770,770,770,770,770,770,770,770,770,768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,785,786,787,788,789,790,791,792,793,794,795,796,797,798,799,791,794,794,793,794,794,798,794,434,435,13,13,13,13,13,13,13,
								801,801,802,801,804,802,804,802,802,802,804,801,802,803,804,805,806,807,808,809,810,811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,828,829,830,831,825,825,825,825,825,825,825,825,13,13,13,13,13,13,13,13,13,
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
								809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,626,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809,809 };

	gameMap.load("Assets/Texture/Sprites/Map/jawbreaker.png", sf::Vector2u(8, 8), map, 59, 48);
	gameMap.setScale(17, 17);
}

void GamePlay::initObstacles()
{
	//MAP BOUNDARIES
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(-1.0f, 6536.0f)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(8018.0f, 0.0f), sf::Vector2f(1.0f, 6536.0f)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(0.0f, 6536.0f), sf::Vector2f(8018.0f, 1.0f)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(8018.0f, -1.0f)));

	//ROCKS
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(5331, 4921), sf::Vector2f(94, 100)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(3154, 4236), sf::Vector2f(94, 100)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(2470.75f, 3011.46f), sf::Vector2f(94, 100)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(836.35f, 2876.25f), sf::Vector2f(94, 100)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(7645.07f, 4238.22f), sf::Vector2f(94, 100)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(7236.48f, 699.15f), sf::Vector2f(94, 100)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(2603.79f, 423.11f), sf::Vector2f(94, 100)));
	
	//WALLS
	/*left top room*/
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(291, 1091), sf::Vector2f(94, 100))); //left
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(1501, 1091), sf::Vector2f(94, 100))); //right

	obstacleContainer.push_back(new Obstacle(sf::Vector2f(0, 684), sf::Vector2f(2175, 126))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(0, 1501), sf::Vector2f(1764, 126))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(2042, 812), sf::Vector2f(126, 968))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(546, 1627), sf::Vector2f(126, 967))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(0, 2591), sf::Vector2f(1764, 126))); //right

	/*center room*/
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(3134, 2588), sf::Vector2f(126, 544)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(3815, 2721), sf::Vector2f(126, 411.5f))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(3815, 2034), sf::Vector2f(126, 411.5f))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(3135, 2034), sf::Vector2f(126, 281))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(3135, 1908), sf::Vector2f(811.5f, 126))); //right

	/*right room*/
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(4220, 4500), sf::Vector2f(2721, 126))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(4900, 2183), sf::Vector2f(2042, 126))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(4220, 4088), sf::Vector2f(126, 411.5f))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(4220, 3397), sf::Vector2f(126, 411.5f))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(6808, 3132), sf::Vector2f(126, 537))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(6808, 2309), sf::Vector2f(126, 537))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(6808, 3962), sf::Vector2f(126, 537))); //right
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(4901, 2730), sf::Vector2f(126, 537))); //right

	/*left bottom room*/
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(1653.48f, 4236), sf::Vector2f(94, 100)));
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(1653.48f, 3829.75f), sf::Vector2f(94, 100)));
	
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(0.0f, 4638.04f), sf::Vector2f(2175, 126.25f))); //bottom wall
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(0.0f, 3408), sf::Vector2f(2175, 126.25f))); //top wall
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(2043.0f, 4226.48f), sf::Vector2f(131, 411.56f))); //left bottom wall
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(2043.0f, 3534.0), sf::Vector2f(131, 411.56f))); //left top wall


	//STAIRS
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(269, 3538), sf::Vector2f(822.28f, 272))); //left bottom room
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(4494, 3394), sf::Vector2f(948, 272))); //right room, top
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(4494, 4227), sf::Vector2f(948, 272))); //right room, bottom

	//OUTDOOR LADDER
	obstacleContainer.push_back(new Obstacle(sf::Vector2f(2700, 4479), sf::Vector2f(182.81f, 176.56f))); //right room, bottom


}

void GamePlay::initButton()
{
	//Initialize button here
}

void GamePlay::initBg()
{
	//Initialize background here
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
	flashLight->setOrigin(sf::Vector2f(flashLightTexture.getSize().x, flashLightTexture.getSize().y * 0.5f));
	flashLight->setTexture(flashLightTexture);
	flashLight->setScale(-5.f, 5.f);
	flashLight->setColor(sf::Color::White);

	gunLight = ls.createLightPointEmission();
	gunLight->setOrigin(sf::Vector2f(pointLightTexture.getSize().x / 2, pointLightTexture.getSize().y * 0.5f));
	gunLight->setTexture(pointLightTexture);
	gunLight->setScale(12.f, 12.f);
	gunLight->setColor(sf::Color::Yellow);
	gunLight->setTurnedOn(false);

	ls.setAmbientColor({ 30,30,30 });

	//Add light obstacle
	for (auto &obs:obstacleContainer)
	{
		ls.createLightShape(*obs->getCollider())->setRenderLightOver(false);
	}
}


void GamePlay::Pause()
{
	std::cout << "GamePlay Paused" << std::endl;
}

void GamePlay::Resume()
{
	std::cout << "GamePlay Resume" << std::endl;
}

void GamePlay::Update(float deltaTime)
{
	for (auto event = sf::Event{}; mWindow.GetRenderWindow()->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed: mWindow.Destroy(); break;
		//case sf::Event::MouseButtonPressed: 
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
				/*Only for non-simultaneous key
				Use if statement for simultaneous key*/
			case sf::Keyboard::R: 
			{
				player.Reload();
			} break;
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
							/*const int newPitch = (rand() % 5) - 2;
							mAudio.changeSFXPitch("pistol_shoot", newPitch != 0 ? static_cast<float>(newPitch) : 1);*/
							mAudio.playSFX("pistol_shoot");
							bullet.setStartPos(sf::Vector2f(player.getPosition().x + 20, player.getPosition().y + 20));
							bullet.setDir(*player.getDirVect());
							//mlight2->setTurnedOn(true);

							bulletContainer.emplace_back(bullet);
						}
				} break;
				default: break;
				}
		} break;
		default: break;
		}
	}

	//Update camera center
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
		player.Move(UP, deltaTime);
		//camera.move(0*deltaTime, -400.f*deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.Move(LEFT, deltaTime);
		//camera.move(-400.0f*deltaTime, 0*deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.Move(DOWN, deltaTime);
		//camera.move(0*deltaTime, 400.f*deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.Move(RIGHT, deltaTime);
		//camera.move(400.0f*deltaTime, 0*deltaTime);
	}

	//Update player anim
	player.Update(deltaTime);

	player.updateAllowShoot(deltaTime);

	//All object collision check here
	//On Collision with obstacle or wall
	for (auto &obs: obstacleContainer)
	{
		player.checkCollision(*obs);
		for (size_t i = 0; i < bulletContainer.size(); i++)
		{
			//Check if bullet collided with obstacle delete
			if (bulletContainer[i].onCollision(*obs))
			{
				bulletContainer.erase(bulletContainer.begin() + i);
			}

			//Check if bullet out of radius delete
			else if (pow(bulletContainer[i].startPosition.x - bulletContainer[i].getPosition().x, 2) 
				+ pow(bulletContainer[i].startPosition.y - bulletContainer[i].getPosition().y, 2) 
				> pow(1500, 2))
			{
				bulletContainer.erase(bulletContainer.begin() + i);
			}

			//TODO Check if collided with zombie
		}
	}

	//Move everything here
	player.PlayerMove(); // Move Player
	for (auto &bul:bulletContainer) //move bullet
	{
		bul.Move(deltaTime);
	}
	
	//Zombie PathFinding

	//Thunder Random

	//Rain Update
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
	//mWindow.Draw(*player.getCollider());

	//mWindow.GetRenderWindow()->setView(GUICamera);
	ls.render(*mWindow.GetRenderWindow());

	//Reset view back
	//mWindow.GetRenderWindow()->setView(camera);
	
	mWindow.EndDraw();
}

