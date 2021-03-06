
#pragma once
#include<SFML\Graphics.hpp>
#include"Button.h"
#include"Widget.h"


//CheckBox
class CheckBox : public Widget {

public:
	CheckBox(std::string s, float x, float y);

	void getFocus() override; //gain highlight
	void loseFocus() override; //lose highlight
	bool checkFocus()override; //check for focus

	void update()override; //update
	void draw(sf::RenderWindow &window)override; //draw
	void getActive(); //turn radio button on
	void loseActive(); //turn it off
	bool checkActive(); // check  if its active or not





private:
	sf::RectangleShape m_icon; //circle next to font
	bool m_hasFocus;  //does it have focus
	bool m_isActive; //is the button turned on
	sf::RectangleShape m_rect; //rectangle surrounding text
	sf::Font m_font;
	sf::Text m_text;

};