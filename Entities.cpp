#include<SFML/Graphics.hpp>
#include"Objects.hpp"
#include"Entities.hpp"
#include"World.hpp"
#include<iostream>

Player::Player()
{
	playership.loadFromFile("Resources/playership.png");
	healthbartext.loadFromFile("Resources/healthbar.png", sf::IntRect(0, 0, 185, 32));
	healthtile.loadFromFile("Resources/healthtile.png", sf::IntRect(0, 0, 36, 23));
	lasertext.loadFromFile("Resources/playerlaser1.png", sf::IntRect(0, 0, 8, 12));
	
	hp=5;
	multiplier=1;
	score=0;
	acceleration=1;
	pos.y=558;
	pos.x=184;

	healthbar.setTexture(healthbartext);
	for(int i=0;i<=4;i++)
	{
		sf::Sprite temp;
		healthblocks.push_back(temp);
		healthblocks[i].setTexture(healthtile);
		healthblocks[i].setPosition(4 + 36*i,5);
	}
	for(int i=0;i<=2;i++)
	{
		sf::Sprite temp;
		sprites.push_back(temp);
		sprites[i].setTexture(playership);
	}
	sprites[0].setTextureRect(sf::IntRect(0, 0, 34, 21));
	sprites[1].setTextureRect(sf::IntRect(0, 26, 30, 21));
	sprites[2].setTextureRect(sf::IntRect(0, 50, 30, 21));
	for(int i=0;i<sprites.size();i++)
		sprites[i].setScale(2, 2);
	
}
void Player::shootLaser()
{
	sf::Sprite temp;
	temp.setTexture(lasertext);
	lasers.push_back(temp);
	lasers[lasers.size()-1].setPosition(pos.x+17, pos.y-11);
	lasers.push_back(temp);
	lasers[lasers.size()-1].setPosition(pos.x+39, pos.y-11);
}
void Player::getHurt(int dmg)
{
	hp-=dmg;
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(xSpeed < 0)
		target.draw(sprites[1]);
	else if(xSpeed > 0)
		target.draw(sprites[2]);
	else
		target.draw(sprites[0]);
}
void Player::scoreIncrease(sf::Vector2f worth)
{
	score+=worth.x * multiplier;
	multiplier+=worth.y;
}

Enemy::Enemy()
{
	this->enemyshiptileset.loadFromFile("Resources/enemyshipset.png");
	this->hp=5;
	this->xSpeed=0;
	this->ySpeed=0;
	worth.x=50;
	worth.y=0.2;
	this->sprite.setTexture(this->enemyshiptileset);
	this->sprite.setTextureRect(sf::IntRect(8, 11, 43, 33));
	this->sprite.setPosition(200, 100);
	this->sprite.rotate(180);
}
void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
