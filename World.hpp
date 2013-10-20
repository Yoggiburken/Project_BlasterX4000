#include<SFML/Graphics.hpp>
//#include"Entities.hpp"

class World : public sf::Drawable {
	virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:	
	World();
	void						spawnEnemy();

	sf::Texture					backtexture;
	std::vector<sf::Sprite>		backgrounds;
	void						setup();
	void						start();
	void						movements(sf::Time);
	void						getHurt(int&, int);
};
