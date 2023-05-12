#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

void Game::initVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->enemyEnemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemyEnemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeldDown = false;
	this->health = 5;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videMode.height = 600;
	this->videMode.width = 800;
	this->window = new sf::RenderWindow(this->videMode, "Game 1");
	this->window->setFramerateLimit(60);
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::initEnemies()
{
	this->enemy = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
	this->enemy.setFillColor(sf::Color::Red);
	//this->enemy.setOutlineColor(sf::Color::Black);
	//this->enemy.setOutlineThickness(5.f);
}

void Game::update()
{
	if (this->endGame == true)
	{
		this->window->close();
		std::cout << this->points << std::endl;
	}
	while (this->window->pollEvent(this->ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		
		case sf::Event::KeyPressed:
		
			if(ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			if (ev.key.code == sf::Keyboard::Down)
				this->enemy.setPosition(sf::Vector2f(
					this->enemy.getPosition().x, this->enemy.getPosition().y+10));
			if (ev.key.code == sf::Keyboard::Up)
				this->enemy.setPosition(sf::Vector2f(
					this->enemy.getPosition().x, this->enemy.getPosition().y - 10));
			if (ev.key.code == sf::Keyboard::Right)
				this->enemy.setPosition(sf::Vector2f(
					this->enemy.getPosition().x+10, this->enemy.getPosition().y));
			if (ev.key.code == sf::Keyboard::Left)
				this->enemy.setPosition(sf::Vector2f(
					this->enemy.getPosition().x-10, this->enemy.getPosition().y));
			break;
		}
	}
	this->updateMousePositions();
	if(this->endGame == false) this->updateEnemies();
}

void Game::render()
{
	this->window->clear(sf::Color::Black);
	//this->window->draw(this->enemy);
	this->renderEnemies();
	this->window->display();
}

void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	this->enemy.setFillColor(sf::Color::Green);
	this->enemies.push_back(this->enemy);
}

void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer <= this->enemyEnemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else this->enemySpawnTimer += 1.f;
	}


	for (int i = 0;i<this->enemies.size();i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 5.f);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->mouseHeldDown = true;
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;

				//add points
				this->points += 1.f;
			}
		}
			
		
		
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
			this->health -= 1;
		}
		if (deleted)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
		if (this->health < 0) this->endGame = true;
		//std::cout << "Health : " << this->health << std::endl;
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::renderEnemies()
{
	//std::cout << this->enemies.size() << std::endl;
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}
