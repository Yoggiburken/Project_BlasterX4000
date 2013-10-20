#include<SFML/Graphics.hpp>
#include"Objects.hpp"
#include"Entities.hpp"
#include"World.hpp"

int main()
{
	World world;
	world.setup();
	world.start();
}
