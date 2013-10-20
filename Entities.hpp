#include<SFML/Graphics.hpp>


class Player : public sf::Drawable {
	virtual void 				draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int							score;
	float						multiplier;
public:
	Player();
	void 						shootLaser();
	void						getHurt(int);
	void						scoreIncrease(sf::Vector2f);

	sf::Texture					playership;
	sf::Texture					healthbartext;
	sf::Texture					healthtile;
	sf::Texture					lasertext;


	sf::Sprite					healthbar;
	std::vector<sf::Sprite>		healthblocks;
	std::vector<sf::Sprite> 	sprites;
	std::vector<sf::Sprite>		lasers;

	sf::Vector2f				pos;	
	int							hp;	
	float						acceleration;
	float						xSpeed;
	float						ySpeed;
	
};


class Enemy : public sf::Drawable {
		virtual void 			draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Enemy();
	
	sf::Texture					enemyshiptileset;
	sf::Sprite 					sprite;
	int							hp;
	sf::Vector2f				pos;
	sf::Vector2f				worth;
	float 						xSpeed;
	float						ySpeed;
};
