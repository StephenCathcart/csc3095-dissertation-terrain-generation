#ifndef MAIN_H
#define MAIN_H

#include "Renderer.h"
#include "GUI.h"
#include <SFGUI\SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "DiamondSquare.h"

/***		Functions	 ***/
void			startup(sf::RenderWindow &application);
void			render(Renderer &renderer, float delta);
void			shutdown();
void			drawAxisLines();

/***		Vars		***/
DiamondSquare* heightMap;
DiamondSquare* heightMapIcon;

#endif