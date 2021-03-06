#include "NavigationMenu.h"

NavigationMenu::~NavigationMenu()
{
	delete mItems;
	delete bMenu;
	touchwin(component);
	delwin(component);
}

int NavigationMenu::loopMenu(ButtonMenu dButtonMenu, std::vector<std::string> menuItems)
{
	bool breakLoop = false;

	std::vector<ButtonMenu::CButton> CButtons = dButtonMenu.CButtons;
	int nButtons = dButtonMenu.nButtons;

	int nMenuItems = menuItems.size();

	while (true)
	{
		printMenuItems(menuItems, vertHighlight);

		switch (wgetch(stdscr))
		{
			case KEY_LEFT:
				if (highlight == 0)
				{
					highlight = nButtons - 1;
				}
				else
				{
					--highlight;
				}
				break;

			case KEY_RIGHT:
				if (highlight == nButtons - 1)
				{
					highlight = 0;
				}
				else
				{
					++highlight;
				}
				break;

			case KEY_UP:
				if (vertHighlight == 0)
				{
					vertHighlight = nMenuItems - 1;
				}
				else
				{
					--vertHighlight;
				}
				break;

			case KEY_DOWN:
				if (vertHighlight == nMenuItems -1)
				{
					vertHighlight = 0;

				}
				else
				{
					++vertHighlight;
				}
				
				break;

			case 10:
				panelChoice = highlight + 1;
				menuChoice = vertHighlight + 1;
				breakLoop = true;
				break;
		}

		CButtons[0].highlightColor = backgroundColor;
		CButtons[1].highlightColor = backgroundColor;
		CButtons[2].highlightColor = backgroundColor;

		CButtons[0].FGHighlightColor = COLOR_BLACK;
		CButtons[1].FGHighlightColor = COLOR_BLACK;
		CButtons[2].FGHighlightColor = COLOR_BLACK;

		CButtons[highlight].highlightColor = COLOR_BLUE;
		CButtons[highlight].FGHighlightColor = COLOR_WHITE;

		CButtons[0].drawButton(dButtonMenu.component);
		CButtons[1].drawButton(dButtonMenu.component);
		CButtons[2].drawButton(dButtonMenu.component);

		//if (panelChoice != 0)
		//{
		//	//break;
		//}

		if (breakLoop)
		{
			break;
		}
	}

	if (panelChoice == 1)
	{
		return menuChoice;
	}
	else if (panelChoice == 2)
	{
		return 0;
	}
	else if (panelChoice == 3)
	{
		return -1;
	}

	return -2;
}


void NavigationMenu::printMenuItems(std::vector<std::string> menuItems, int highlight)
{
	int nMenuItems = menuItems.size();

	int iE;

	int xE = textStartX;
	int yE = textStartY;


	for (iE = 0; iE < nMenuItems; ++iE)
	{

		wattron(component, COLOR_PAIR(cwt::colorPair(COLOR_BLACK, COLOR_WHITE)));
		mvwprintw(component, yE, xE, (char*)menuItems[iE].c_str());
		wattroff(component, COLOR_PAIR(cwt::colorPair(COLOR_BLACK, COLOR_WHITE)));

		if (highlight == iE)
		{

			wattron(component, A_BOLD | COLOR_PAIR(cwt::colorPair(COLOR_RED, COLOR_WHITE)));
			mvwprintw(component, yE, xE, (char*)menuItems[iE].c_str());
			wattroff(component, A_BOLD | COLOR_PAIR(cwt::colorPair(COLOR_RED, COLOR_WHITE)));
			
		}
		else
		{

		}

		yE++;
	}

	wrefresh(component);
}

int NavigationMenu::getMenuChoice()
{
	return loopMenu(*bMenu, *mItems);
}

void NavigationMenu::setTextXY(int x, int y)
{
	textStartX = x;
	textStartY = y;

	werase(component);
	drawBorder();
	width -= 3;
	addTextArea();
	printMenuItems(*mItems, 0);
}