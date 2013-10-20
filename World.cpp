#include<SFML/Graphics.hpp>
#include<iostream>
#include"World.hpp"
#include"Objects.hpp"
#include"Entities.hpp"

Player				player;
std::vector<Enemy>	enemies;
extern sf::Texture	enemyshiptileset;
World::World()
{
	backtexture.loadFromFile("Resources/background.png", sf::IntRect(0, 0, 400, 648));
	for(int i=0;i<=2;i++)
	{
		sf::Sprite temp;
		backgrounds.push_back(temp);
		backgrounds[i].setTexture(backtexture);
		backgrounds[i].setPosition(0, 648-648*i);
	}
}
void	World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(int i=0; i<backgrounds.size() ;i++)
		target.draw(backgrounds[i]);
}
void	World::setup()
{
	
}
void	World::movements(sf::Time time)
{
	for(int i=0; i<player.lasers.size();i++)
	{
		player.lasers[i].move(0, -150 * time.asSeconds());
		if(player.lasers[i].getPosition().y < 0)
			player.lasers.erase(player.lasers.begin()+i);
	}
}
void	World::getHurt(int& hp, int dmg)
{
	hp-=dmg;
	std::cout<<"enemy gets hurt "<< hp <<std::endl;
	
}

void	World::spawnEnemy()
{
	Enemy temp;
	enemies.push_back(temp);
}

void World::start()
{
	World				world;

	sf::RenderWindow 	Window(sf::VideoMode(400, 600), "ProjectBlasterX4000");
	sf::Event 			Event;
	sf::Clock 			clock;
	sf::Time 			elapsedTime;
	sf::Time			laserCooldown;
	Enemy				temp;
	laserCooldown = clock.restart();
	
	world.spawnEnemy();
	
	while(Window.isOpen())
	{
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
				case sf::Event::KeyPressed:
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						Window.close();
				break;
				default:
				break;
			}						
		}
		
		elapsedTime = clock.restart();
		laserCooldown += elapsedTime;
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.xSpeed += 150 * elapsedTime.asSeconds() * player.acceleration;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.xSpeed += -150 * elapsedTime.asSeconds() * player.acceleration;
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			player.ySpeed += -150 * elapsedTime.asSeconds() * player.acceleration;
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			player.ySpeed += 150 * elapsedTime.asSeconds() * player.acceleration;
		
		if(player.pos.x >= 0 && player.xSpeed < 0 || player.pos.x <= 332 && player.xSpeed > 0)
			player.pos.x+=player.xSpeed;
		if(player.pos.y <= 558 && player.ySpeed > 0 || player.pos.y >= 474 && player.ySpeed < 0)
			player.pos.y+=player.ySpeed;
		for(int i=0;i<player.sprites.size();i++)
			player.sprites[i].setPosition(player.pos.x, player.pos.y);	
		
		if(laserCooldown.asSeconds() >= 0.5)
		{
			laserCooldown = laserCooldown.Zero;
			player.shootLaser();
		}
		movements(elapsedTime);
		
		Window.clear();
		Window.draw(world);
		Window.draw(player);
		Window.draw(temp);
		for(int i=0; i<enemies.size();i++)
			Window.draw(enemies[i]);
		for(int i=0; i<player.lasers.size();i++)
			Window.draw(player.lasers[i]);
		for(int i=0;i<player.hp;i++)
			Window.draw(player.healthblocks[i]);
		Window.draw(player.healthbar);


		Window.display();
		
		player.xSpeed=0;
		player.ySpeed=0;
		for(int i=0;i<world.backgrounds.size();i++)
		{
			world.backgrounds[i].move(0, 0.2);
			if(world.backgrounds[i].getPosition().y > 648)
				world.backgrounds[i].setPosition(0, -648);
		}
		for(int i=0;i<enemies.size();i++)
		{	
			if(player.sprites[0].getGlobalBounds().intersects(enemies[i].sprite.getGlobalBounds()))
				player.getHurt(1);
		}

		for(int a=0;a<enemies.size();a++)
		{
			for(int i=0;i<player.lasers.size();i++)
			{
				if(player.lasers[i].getGlobalBounds().intersects(enemies[a].sprite.getGlobalBounds()))
				{
					world.getHurt(enemies[a].hp, 1);
					player.lasers.erase(player.lasers.begin()+i);
					if(enemies[a].hp <= 0)
					{
						enemies.erase(enemies.begin()+a);
						player.scoreIncrease(enemies[a].worth);
					}	
				}
			}
		}
	}
}
