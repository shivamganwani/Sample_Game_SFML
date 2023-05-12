#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<vector>
#include<iostream>
#include<ctime>

class Game
{
private:
	sf::RenderWindow *window;
	sf::VideoMode videMode;
	sf::Event ev;
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	int points;
	float enemySpawnTimer;
	float enemyEnemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeldDown;
	int health;
	bool endGame;


	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
public:
	Game();
	virtual ~Game();
	void initVariables();
	void initWindow();
	const bool running() const;
	void initEnemies();

	void update();
	void render();
	void spawnEnemy();
	void updateEnemies();
	void updateMousePositions();
	void renderEnemies();

};

