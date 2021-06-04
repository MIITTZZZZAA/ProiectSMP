#include "Game.h"
# define M_PI           3.14159265358979323846 





//private functions
void Game::initWindow()
{
	
	
	this->videoMode.height = 1000;
	this->videoMode.width = 1800;
	this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode), "Arcade", sf::Style::Titlebar | sf::Style::Close);
	this->window->setPosition(sf::Vector2i(0.f, 0.f));
	this->window->setFramerateLimit(144);

	this->fundal.loadFromFile("Media/fundal.png");
	this->sprite.setTexture(this->fundal);
	this->window->draw(this->sprite);
}
void Game::initVariable()
{

	this->window = nullptr;
	//game logic
	this->points = 0;
	this->enemySpawnTimerMax = 100.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->bulletSpawnTimerMax = 40.f;
	this->bulletSpawnTimer = this->bulletSpawnTimerMax;
	this->maxEnemies = 25 ;
	this->maxBullets = 5;
	this->mouseHeld = false;
	this->health = 10;
	this->endGame = false;
	this->start = false;
	this->puncte = 0;
	this->nrvieti = 5;
	this->incepereJoc = false;
	this->nrtext = false;
	this->auxBullet = 0;
	this->speedbullet = 8;
	this->speedasteroizi = 0.6;
	this->rotatie = 0;
	this->mouseHeld2 = false;
	this->afisarescor = false;
}

//constructor destructor
Game::Game()
{
	this->initVariable();
	this->MuzicaFunda.openFromFile("Sunete/Fundal.wav");
	this->MuzicaFunda.setVolume(5.f);
	this->MuzicaFunda.play();
	this->MuzicaFunda.setLoop(true);
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initNava();
	this->initviata(); 
	if (this->incepereJoc)
	{
		this->initNava();
		this->initEnemies();
		this->initbullet();
	}
}
void Game::initALL()
{
	
	
}
Game::~Game()
{
	delete this->window; 

}

const bool Game::running() const
{
	return this->window->isOpen();
}
const bool Game::getEndGame() const
{
	return this->endGame;
}

//funcionii primare
void Game::update()
{
	this->pollEvents();
	if (this->endGame == false)
	{
		this->updateMousePosition();
		
		if (this->incepereJoc && this->afisarescor == false)
		{
			this->updateMousePosition();
			this->UpdateEnemy();
			this->updateNava();
			this->updatebullet();
			this->ColiziuneBulletMeteorit();
			this->coliziuneNavaMeteoriti();
			this->updateText();
		}
		if (this->sfarsitJoc)
		{
			this->UpdateTopScore();
			this->updateText();
		}
		else
			this->updateText();
	}

	if (this->health <= 0)
		this->endGame = true;
}
void Game::render()
{
	this->window->clear();
	this->window->draw(this->sprite);
	this->renderText(*this->window);
	if (this->incepereJoc && this->afisarescor==false)
	{
		this->RanderEnemy(*this->window);
		this->rendervieti(*this->window);
		this->renderNava(*this->window);
		this->renderbullet(*this->window);
	}
	this->window->display();
}
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

// inamici
void Game::initEnemies()
{

}
void Game::spawnEnemy()
{
	// spawneaza inamici si le seteaza culoarea si pozitia
	//pozitie random si culoare random
	//adauga inamici la vector
	this->spawnrandom = rand() % 4;
	if (this->spawnrandom == 0)
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x)), // ca pozitia se calculeaza in dreapta sus
		0.f
	);

	if (this->spawnrandom == 1)
		this->enemy.setPosition(
			static_cast<float>(rand() % static_cast<int>(this->window->getSize().x)), // ca pozitia se calculeaza in dreapta sus
			this->window->getSize().y
		);

	if (this->spawnrandom == 2)
		this->enemy.setPosition(
			0, // ca pozitia se calculeaza in dreapta sus
			rand() % static_cast<int>(this->window->getSize().y )
		);

	if (this->spawnrandom == 3)
		this->enemy.setPosition(
			this->window->getSize().x, // ca pozitia se calculeaza in dreapta sus
			rand() % static_cast<int>(this->window->getSize().y )
		);


	int texturarandom = rand() % 8;
	switch (texturarandom)
	{
		case 0:
			this->texturaasteroid0.loadFromFile("Media/Meteorit0.png");
			this->enemy.setTexture(this->texturaasteroid0);
			break;
		case 1:
			this->texturaasteroid1.loadFromFile("Media/Meteorit1.png");
			this->enemy.setTexture(this->texturaasteroid1);
			break;
		case 2:
			this->texturaasteroid2.loadFromFile("Media/Meteorit2.png");
			this->enemy.setTexture(this->texturaasteroid2);
			break;
		case 3:
			this->texturaasteroid3.loadFromFile("Media/Meteorit3.png");
			this->enemy.setTexture(this->texturaasteroid3);
			break;
		case 4:
			this->texturaasteroid4.loadFromFile("Media/Meteorit4.png");
			this->enemy.setTexture(this->texturaasteroid4);
			break;
		case 5:
			this->texturaasteroid5.loadFromFile("Media/Meteorit5.png");
			this->enemy.setTexture(this->texturaasteroid5);
			break;
		case 6:
			this->texturaasteroid6.loadFromFile("Media/Meteorit6.png");
			this->enemy.setTexture(this->texturaasteroid6);
			break;
		case 7:
			this->texturaasteroid7.loadFromFile("Media/Meteorit7.png");
			this->enemy.setTexture(this->texturaasteroid7);
			break;
	default:
		break;
	}


	
	int type = rand() % 5;
	switch (type)
	{
	case 0:
		
		this->enemy.setScale(sf::Vector2f(1, 1));
		break;
	case 1:
		this->enemy.setScale(sf::Vector2f(1.25f, 1.25f));
		break;
	case 2:
		this->enemy.setScale(sf::Vector2f(1.5, 1.5));
		break;
	case 3:
		this->enemy.setScale(sf::Vector2f(2, 2));
		break;
	case 4:
		this->enemy.setScale(sf::Vector2f(2.5f, 2.5f));
		break;
	default:
		this->enemy.setScale(sf::Vector2f(3, 3));
		break;

	}

	int typee = rand() % 2;
	switch (typee)
	{
	case 0:
		this->randomrotire = 1;
		break;
	case 1:
		this->randomrotire = -1;
		break;
	default:
		break;
	}
	
	this->xmeteorit = enemy.getPosition().x;
	this->ymeteorit = enemy.getPosition().y;
	this->xnavam = naveta.getPosition().x;
	this->ynavam = naveta.getPosition().y;
	this->Pozxmeteoritmouse.push_back(this->xmeteorit);
	this->Pozymeteoritmouse.push_back(this->ymeteorit);
	this->Pozxmeteoriti.push_back(this->xnavam);
	this->Pozymeteoriti.push_back(this->ynavam);
	this->directirerotire.push_back(this->randomrotire);  // da directia
	this->enemy.setOrigin(enemy.getTexture()->getSize().x / 2, enemy.getTexture()->getSize().y / 2);
	this->rotireinamic = 0;
	this->rotire.push_back(this->rotireinamic);  // da unghiul
	this->enemies.push_back(this->enemy);
}


void Game::rotireEnemy()
{
	for(i = 0; i < this->enemies.size(); i++)
	{
		if (this->directirerotire[i] == 1)
		{
			if (this->rotire[i] < 360)
			{
				this->rotire[i] = rotire[i] + 1;
				this->enemies[i].setRotation(this->rotire[i]);
				this->directirerotire[i] = 1;
			}
			else
			{
				this->rotire[i] = 1;
			}
		}
		else if (this->directirerotire[i] == -1) {
			if (this->rotire[i] > -360)
			{
				this->rotire[i] = rotire[i] - 1;
				this->enemies[i].setRotation(this->rotire[i]);
				this->directirerotire[i] = -1;
			}
			else
			{
				this->rotire[i] = -1;
			}
		}
	}
}

void Game::UpdateEnemy()
{
	this->rotireEnemy();
	//updateaza timpul de spawn si spwneaza cand nr e mai mic decat max
	//muta inamicii
	//elimina inamicii la margine de ecran
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//for (auto &e: this ->enemies	)
	//folosim cu int ca trb stersi cand ajung jos
	for (i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->miscareasteroizi = atan2(this->Pozymeteoriti[i] - Pozymeteoritmouse[i], this->Pozxmeteoriti[i]- Pozxmeteoritmouse[i] );
		this->enemies[i].move( speedasteroizi * cos(miscareasteroizi), speedasteroizi * sin(miscareasteroizi));


		if (this->enemies[i].getPosition().y > this->window->getSize().y + 100 ||
			this->enemies[i].getPosition().y < -100 ||
			this->enemies[i].getPosition().x > this->window->getSize().x + 100 ||
			this->enemies[i].getPosition().x < -100
			)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->Pozxmeteoritmouse.erase(this->Pozxmeteoritmouse.begin() + i);
			this->Pozymeteoritmouse.erase(this->Pozymeteoritmouse.begin() + i);
			this->Pozxmeteoriti.erase(this->Pozxmeteoriti.begin() + i);
			this->Pozymeteoriti.erase(this->Pozymeteoriti.begin() + i);
			this->directirerotire.erase(this->directirerotire.begin() + i);
			this->rotire.erase(this->rotire.begin() + i);
			

		}
	}
}
void Game::RanderEnemy(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

// mouse
void Game::updateMousePosition()
{
	//	return void

	//updates the mouse position: 
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	this->pozitiemousex = sf::Mouse::getPosition(*this->window).x;
	this->pozitiemousey = sf::Mouse::getPosition(*this->window).y;
}



//text

void Game::initFonts()
{
	this->font.loadFromFile("Fonts/Font2.ttf");
	this->font1.loadFromFile("Fonts/GameOver.ttf");
}
void Game::initText()
{
	this->startText.setPosition(this->videoMode.width  / 2 - 150, this->videoMode.height/ 2 - 200);
	this->startText.setFont(this->font);
	this->startText.setCharacterSize(48);
	this->startText.setFillColor(sf::Color::White);
	this->startText.setString("None");	

	this->HighScoreText.setPosition(this->videoMode.width / 2 - 150, this->videoMode.height / 2 - 400);
	this->HighScoreText.setFont(this->font1);
	this->HighScoreText.setCharacterSize(200);
	this->HighScoreText.setFillColor(sf::Color::White);
	this->HighScoreText.setString("None");

	this->ExitText.setPosition(this->videoMode.width / 2 - 150, this->videoMode.height / 2 );
	this->ExitText.setFont(this->font);
	this->ExitText.setCharacterSize(48);
	this->ExitText.setFillColor(sf::Color::White);
	this->ExitText.setString("None");

	this->TopScoreText.setPosition(this->videoMode.width / 2 - 150, this->videoMode.height / 2 -100);
	this->TopScoreText.setFont(this->font);
	this->TopScoreText.setCharacterSize(48);
	this->TopScoreText.setFillColor(sf::Color::White);
	this->TopScoreText.setString("None");

	this->GameOver.setPosition(this->videoMode.width / 2 - 200, this->videoMode.height / 2 - 300);
	this->GameOver.setFont(this->font1);
	this->GameOver.setCharacterSize(200);
	this->GameOver.setFillColor(sf::Color::Red);
	this->GameOver.setString("None");


	this->Points.setPosition(10, 70);
	this->Points.setFont(this->font);
	this->Points.setCharacterSize(30);
	this->Points.setFillColor(sf::Color::White);
	this->Points.setString("None");

	this->Menu.setPosition(this->videoMode.width / 2 - 100, this->videoMode.height / 2 + 100);
	this->Menu.setFont(this->font);
	this->Menu.setCharacterSize(48);
	this->Menu.setFillColor(sf::Color::White);
	this->Menu.setString("None");

	this->Menu1.setPosition(this->videoMode.width / 2 - 100, this->videoMode.height / 2 + 200);
	this->Menu1.setFont(this->font);
	this->Menu1.setCharacterSize(48);
	this->Menu1.setFillColor(sf::Color::White);
	this->Menu1.setString("None");


}
void Game::renderText(sf::RenderTarget& target)
{
	if (this->start == false && this->sfarsitJoc == false && this->afisarescor == false)
	{
		target.draw(this->startText);
		target.draw(this->TopScoreText);
		target.draw(this->ExitText);
	}
	else if (this->start && this->sfarsitJoc == false)
	{
		target.draw(this->Points);
	}
	else if (this->afisarescor)
	{
		target.draw(this->HighScoreText);
		target.draw(this->Menu1);
	}
	else if (this->sfarsitJoc)
	{
		target.draw(this->GameOver);
		this->Points.setPosition(this->videoMode.width / 2 - 100, this->videoMode.height / 2 - 50);
		target.draw(this->Points);
		target.draw(this->Menu);
	}
}
void Game::updateText()
{



	std::stringstream ss;
	if (this->start == false && this->sfarsitJoc == false && this->afisarescor == false)
	{
		this->MuzicaFundaJoc.stop();
		
		

		ss << "Start ";
		this->startText.setString(ss.str());
		ss.str(std::string());

		ss << "High Score ";
		this->TopScoreText.setString(ss.str());
		ss.str(std::string());

		ss << "Quit ";
		this->ExitText.setString(ss.str());
		ss.str(std::string());

	}
	else if (this->start && this->sfarsitJoc == false )
	{
		ss << "Score "<<this->puncte;
		this->Points.setString(ss.str());
		ss.str(std::string());
		
	}
	else if (this->afisarescor)
	{
		std::ifstream readFile;
		readFile.open("Score.txt");
		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> highscore;
			}
		}
		readFile.close();
		this->MuzicaFundaJoc.stop();
		ss << "High Score \n       " << highscore;
		this->HighScoreText.setString(ss.str());
		ss.str(std::string());

		ss << " Menu ";
		this->Menu1.setString(ss.str());
		ss.str(std::string());

	}
	else if ( this->sfarsitJoc)
	{
		ss << "Game Over ";
		this->GameOver.setString(ss.str());
		ss.str(std::string());

		ss << "Menu ";
		this->Menu.setString(ss.str());
		ss.str(std::string());
	}
	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{

			this->mouseHeld = true;
			if (this->startText.getGlobalBounds().contains(this->mousePosView))
			{
				this->start = true;
				this->incepereJoc = true;
				this->ButonSunet.openFromFile("Sunete/Buton.wav");
				this->ButonSunet.play();
				this->MuzicaFundaJoc.openFromFile("Sunete/FundalInJoc.wav");
				this->MuzicaFundaJoc.setVolume(5.f);
				this->MuzicaFundaJoc.play();
				this->MuzicaFundaJoc.setLoop(true);
				this->MuzicaFunda.stop();

			}
			if (this->TopScoreText.getGlobalBounds().contains(this->mousePosView))
			{
				this->HS.openFromFile("Sunete/Highscore.wav");
				this->HS.setVolume(10.f);
				this->HS.play();
				this->afisarescor = true;

			}
			this->mouseHeld = true;
			if (this->ExitText.getGlobalBounds().contains(this->mousePosView))
			{
				this->window->close();

			}
			this->mouseHeld = true;
			if (this->Menu.getGlobalBounds().contains(this->mousePosView))
			{
				this->MuzicaFunda.openFromFile("Sunete/Fundal.wav");
				this->MuzicaFunda.setVolume(5.f);
				this->MuzicaFunda.play();
				this->MuzicaFunda.setLoop(true);
				this->sfarsitJoc = false;
				this->start = false;
				this->incepereJoc = false;
				this->afisarescor = false;
				this->resetGame();
				

			}
			this->mouseHeld = true;
			if (this->Menu1.getGlobalBounds().contains(this->mousePosView))
			{
				this->afisarescor = false;


			}
			this->mouseHeld = true;
			
		}
	}
	else
	{
		this->mouseHeld = false;
	}

}



void Game::initNava()
{
	this->textura.loadFromFile("Media/nava.png");
	this->naveta.setTexture(this->textura);
	this->naveta.setPosition(this->videoMode.width/2-25, this->videoMode.height/2 - 25);
	this->naveta.setScale(sf::Vector2f(1.f, 1.f));
	
}
void Game::rotireNava()
{
	this->angle = atan2(this->pozitiemousey - naveta.getPosition().y, this->pozitiemousex - naveta.getPosition().x);
	this->angle = angle * (180 / M_PI);
	if (this->angle < 0)
	{
		this->angle = 360 - (-angle);
	}

	naveta.setRotation(90 + angle);
}
void Game::updateNava()
{
	this->naveta.setOrigin(naveta.getTexture()->getSize().x/2, naveta.getTexture()->getSize().y/2);

	this->updateMousePosition();
	std::cout << "Mouse:" << this->pozitiemousey << "  " << this->pozitiemousex << "\n";
	std::cout << "Nava:" << naveta.getPosition().x << "  " << naveta.getPosition().y << "\n";
	if (!naveta.getGlobalBounds().contains(mousePosView))
	this->rotireNava();

	this->speed = 3;
	
	this->auxdeplasare=atan2(this->pozitiemousey - naveta.getPosition().y, this->pozitiemousex - naveta.getPosition().x);
	if (!naveta.getGlobalBounds().contains(mousePosView))
	naveta.move(speed*cos(auxdeplasare), speed*sin(auxdeplasare));
	
}
void Game::renderNava(sf::RenderTarget& target)
{
	target.draw(this->naveta);


}


void Game::initbullet()
{
	
}
void Game::spawnbullet()
{
	this->bullet.setPosition(this->naveta.getPosition().x, this->naveta.getPosition().y);
	this->bullet.setFillColor(sf::Color::Red);
	this->bullet.setSize(sf::Vector2f(7.f, 7.f));
	this->xbullet = sf::Mouse::getPosition(*this->window).x;
	this->ybullet = sf::Mouse::getPosition(*this->window).y;
	this->xnava = naveta.getPosition().x;
	this->ynava = naveta.getPosition().y;
	

	this->bullets.push_back(this->bullet);
	this->Pozxbulletmouse.push_back(this->xbullet);
	this->Pozybulletmouse.push_back(this->ybullet);
	this->Pozxbullet.push_back(this->xnava);
	this->Pozybullet.push_back(this->ynava);
	

	


}
void Game::updatebullet()
{
	if (this->bullets.size() < this->maxBullets)
	{

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !(this->naveta.getGlobalBounds().contains(this->mousePosView)))
		{
			
				if (this->bulletSpawnTimer >= this->bulletSpawnTimerMax)
				{
					this->spawnbullet();
					this->PewPew.openFromFile("Sunete/PewPew.wav");
					this->PewPew.setVolume(10.f);
					this->PewPew.play();
					this->bulletSpawnTimer = 0.f;
				}
				else
					this->bulletSpawnTimer += 1.f;
			
		}
		




	}

	


	for (int i = 0; i < this->bullets.size(); i++)
	{
		this->miscarebullet = atan2(this->Pozybulletmouse[i]-Pozybullet[i], this->Pozxbulletmouse[i]-Pozxbullet[i]);
		this->bullets[i].move(speedbullet * cos(miscarebullet), speedbullet * sin(miscarebullet));


		if (this->bullets[i].getPosition().y > this->window->getSize().y ||
			this->bullets[i].getPosition().y < 0 ||
			this->bullets[i].getPosition().x > this->window->getSize().x ||
			this->bullets[i].getPosition().x < 0
			)
		{

			this->bullets.erase(this->bullets.begin() + i);
			this->Pozxbulletmouse.erase(this->Pozxbulletmouse.begin() + i);
			this->Pozybulletmouse.erase(this->Pozybulletmouse.begin() + i);
			this->Pozxbullet.erase(this->Pozxbullet.begin() + i);
			this->Pozybullet.erase(this->Pozybullet.begin() + i);
		}
	}


	//bullet.move(sin(abs(pozitiemousex - naveta.getPosition().x)), -cos(this->pozitiemousey - naveta.getPosition().y));
	
}
void Game::renderbullet(sf::RenderTarget& target)
{
	for (auto& e : this->bullets)
	{
		target.draw(e);
	}
}




void Game::ColiziuneBulletMeteorit()
{
	//for (int i = 0; i < this->enemies.size(); i++)
	//	if (this->enemies[i].getGlobalBounds().intersects(this->naveta.getGlobalBounds()))
	//		this->enemies.erase(this->enemies.begin() + i);



	
	for (i = 0; i < this->enemies.size(); i++)
	{
		for (j = 0; j < this->bullets.size(); j++)
		{
			if (this->enemies[i].getGlobalBounds().intersects(this->bullets[j].getGlobalBounds()))
			{
				this->puncte = puncte + 1;
				this->enemies.erase(this->enemies.begin() + i);
				this->bullets.erase(this->bullets.begin() + j);

				this->Pozxmeteoritmouse.erase(this->Pozxmeteoritmouse.begin() + i);
				this->Pozymeteoritmouse.erase(this->Pozymeteoritmouse.begin() + i);
				this->Pozxmeteoriti.erase(this->Pozxmeteoriti.begin() + i);
				this->Pozymeteoriti.erase(this->Pozymeteoriti.begin() + i);

				this->Pozxbulletmouse.erase(this->Pozxbulletmouse.begin() + j);
				this->Pozybulletmouse.erase(this->Pozybulletmouse.begin() + j);
				this->Pozxbullet.erase(this->Pozxbullet.begin() + j);
				this->Pozybullet.erase(this->Pozybullet.begin() + j);
				this->directirerotire.erase(this->directirerotire.begin() + i);
				this->rotire.erase(this->rotire.begin() + i);
				this->AsteroidDistrus.openFromFile("Sunete/AsteroidLovit.wav");
				this->AsteroidDistrus.play();
				this->next=true;
			}
			if (next)
				break;

			
		}
		if (next)
		{
			
			this->next = false;
			this->i= i + 1;
			break;

		}
			
	}
	


	

}
void Game::coliziuneNavaMeteoriti()
{
	for (i = 0; i < this->enemies.size(); i++)
		if (this->enemies[i].getGlobalBounds().intersects(this->naveta.getGlobalBounds()))
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->Pozxmeteoritmouse.erase(this->Pozxmeteoritmouse.begin() + i);
			this->Pozymeteoritmouse.erase(this->Pozymeteoritmouse.begin() + i);
			this->Pozxmeteoriti.erase(this->Pozxmeteoriti.begin() + i);
			this->Pozymeteoriti.erase(this->Pozymeteoriti.begin() + i);
			this->directirerotire.erase(this->directirerotire.begin() + i);
			this->rotire.erase(this->rotire.begin() + i);
			this->updateviata();
			this->Coliziune.openFromFile("Sunete/Coliziune.wav");
			this->Coliziune.play();
		}
}

void Game::resetGame()
{
	this->afisarescor = false;
	this->initFonts();
	this->initText();
	this->initNava();
	this->initviata();
	this->initNava();
	this->initEnemies();
	this->initbullet();
	
	this->Points.setPosition(10, 70);
	this->enemies.clear();
	this-> rotatie = 0;
	this->xnavam = 0;
	this->ynavam = 0;
	this->xmeteorit = 0;
	this->ymeteorit = 0;
	this->spawnrandom = 0;
	this->xnava = 0;
	this->ynava = 0;
	this->xbullet = 0;
	this->ybullet = 0;
	this->Pozxbulletmouse.clear();
	this->Pozybulletmouse.clear();
	this->Pozxmeteoritmouse.clear();
	this->Pozymeteoritmouse.clear();
	this->Pozxmeteoriti.clear();
	this->Pozymeteoriti.clear();
	this->rotire.clear();
	this->directirerotire.clear();
	this->Pozxbulletmouse.clear();

	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->bulletSpawnTimerMax = 40.f;
	this->bulletSpawnTimer = this->bulletSpawnTimerMax;
	this->maxEnemies = 10;
	this->maxBullets = 5;
	this->mouseHeld = false;
	this->health = 10;
	this->endGame = false;
	this->start = false;
	this->puncte = 0;
	this->incepereJoc = false;
	this->nrtext = false;
	this->auxBullet = 0;
	this->speedbullet = 8;
	this->speedasteroizi = 0.6;
	this->rotatie = 0;
	this->mouseHeld2 = false;
	
}

void Game::UpdateTopScore()
{

	std::ifstream readFile;
	readFile.open("Score.txt");
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> highscore;
		}
	}
	readFile.close();

	std::ofstream writeFile("Score.txt");
	if (writeFile.is_open())
	{
		if (puncte>highscore)
		{
			highscore = puncte;
		}
		writeFile << highscore;
}
writeFile.close();
	
}





void Game::updateviata()
{
	if (nrvieti > 1)
	{
		this->vieti.pop_back();
		this->nrvieti = nrvieti - 1;
	}
	else
	{
		this->sfarsitJoc = true;
		this->incepereJoc = false;
		this->GameOverSound.openFromFile("Sunete/GameOver.wav");
		this->GameOverSound.play();
	}

}

void Game::initviata()
{
	this->pozxviata = 10;
	this->pozyviata = 10;
	this->nrvieti = 5;

	for (i = 0; i < this->nrvieti; i++)
	{
		this->textura.loadFromFile("Media/nava.png");
		this->viata.setTexture(this->textura);
		this->viata.setPosition(this->pozxviata, this->pozyviata);
		this->viata.setScale(sf::Vector2f(1.f, 1.f));
		this->pozxviata = pozxviata + viata.getTexture()->getSize().x;
		this->vieti.push_back(this->viata);
	}
}




void Game::rendervieti(sf::RenderTarget& target)
{
	for (auto& e : this->vieti)
	{
		target.draw(e);
	}
}


