#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h >
#include"SFML/Audio.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include <io.h> 
#include <string>
#include<stdio.h>



class Game
{
private:
	//variabile
	//window
	std::ofstream FisierScor;
	std::ifstream CitireFisier;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Texture textura;
	sf::Texture texturaasteroid0;
	sf::Texture texturaasteroid1;
	sf::Texture texturaasteroid2;
	sf::Texture texturaasteroid3;
	sf::Texture texturaasteroid4;
	sf::Texture texturaasteroid5;
	sf::Texture texturaasteroid6;
	sf::Texture texturaasteroid7;
	sf::Texture fundal;
	sf::Image poza;
	sf::Sprite sprite;
	sf::Sprite background;
	
	std::vector<std::vector<bool>> mask;
	//mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//game logic
	FILE* fisier;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	float bulletSpawnTimer;
	float bulletSpawnTimerMax;
	int maxEnemies;
	unsigned points;
	bool mouseHeld;
	int health;
	bool endGame;
	bool start;
	bool usor;
	bool mediu;
	bool greu;
	bool incepereJoc;
	bool nrtext;
	float angle;
	float pozitiemousex;
	float pozitiemousey;
	float directiex;
	float directiey;
	float speed;
	float auxdeplasare;
	int maxBullets;
	float miscarebullet;
	int auxBullet;
	float speedbullet;
	int vitezaasteroizi;
	float miscareasteroizi;
	float speedasteroizi;
	bool next;
	int i, j;
	int nrvieti;
	bool mouseHeld2;
	bool sfarsitJoc;
	int puncte;
	int contor = 1;
	int highscore;
	bool afisarescor;
	//Resources
	sf::Font font;
	sf::Font font1;
	//Text
	sf::Text startText;
	sf::Text TopScoreText;
	sf::Text ExitText;
	sf::Text GameOver;
	sf::Text Points;
	sf::Text Menu;
	sf::Text Menu1;
	sf::Text HighScoreText;

	sf::Transform transform;
	sf::Music PewPew;
	sf::Music Coliziune;
	sf::Music AsteroidDistrus;
	sf::Music MuzicaFundaJoc;
	sf::Music GameOverSound;
	sf::Music ButonSunet;
	sf::Music HS;
	sf::Music MuzicaFunda;

	// game object
	std::vector<sf::Sprite> enemies;
	sf::Sprite enemy;
	sf::Sprite naveta;
	std::vector<sf::Sprite> vieti;
	sf::Sprite viata;
	sf::RectangleShape bullet;
	std::vector<float> Pozxbulletmouse;
	std::vector<float> Pozybulletmouse;
	std::vector<float> Pozxbullet;
	std::vector<float> Pozybullet;
	
	std::vector<float> Pozxmeteoritmouse;
	std::vector<float> Pozymeteoritmouse;
	std::vector<float> Pozxmeteoriti;
	std::vector<float> Pozymeteoriti;
	std::vector<float> rotire;
	std::vector<float> directirerotire;
	float randomrotire;
	float rotireinamic;
	bool is_file_exist(const std::string& Filename);

	int rotatie;
	float xnavam;
	float ynavam;
	float xmeteorit;
	float ymeteorit;
	int spawnrandom;

	float xnava;
	float ynava;
	float xbullet;
	float ybullet;
	
	int pozxviata;
	int pozyviata;
	

	std::vector<sf::RectangleShape> bullets;

	//private f
	void initWindow();
	void initVariable();
	void initEnemies();
	void initFonts();
	void initText();
	void initNava();
	void initbullet();
public:
	Game();
	virtual ~Game();
	//accesors
	const bool running() const; 
	const bool getEndGame() const;

	//functii
	void spawnEnemy();
	void UpdateEnemy();
	void RanderEnemy(sf::RenderTarget& target);
	void update();
	void render();
	void pollEvents();
	void updateMousePosition();
	void renderText(sf::RenderTarget& target);
	void updateText();
	void updateNava();
	void renderNava(sf::RenderTarget& target);
	void rotireNava();
	void spawnbullet();
	void updatebullet();
	void renderbullet(sf::RenderTarget& target);
	void rendervieti(sf::RenderTarget& target);
	void initALL();
	void ColiziuneBulletMeteorit();
	void updateviata();
	void initviata();
	void rotireEnemy();
	
	void coliziuneNavaMeteoriti();
	void resetGame();
	void UpdateTopScore();
 };

	

