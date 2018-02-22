



#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController
{

public:

	bool GameInit(); // game initialization function
	void GameLoop(); // where the game actually takes place
	void GameDone(); // clean up! 
	void NewGame(); // make a new game!
	void OnEvent(); // simple event handler

private:



};

#endif
