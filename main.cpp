#include "function.h"
#include <cctype>
int main()
{
	int N=10, records;
	int area=0;
	bool win, lose;
	std::string word1=" MOVE ";
	std::string word2="BLOCKS";
	std::vector<std::vector<int>> map;
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	char mod;
	json config;
nlohmann::json config1;
	int start_y;
std::vector<std::string> endGame = {
        "new game",
        "end game"
    };
int yMax, xMax;
int message_len;
int start_x;
const char* message1 = "LOSE";
        getmaxyx(stdscr, yMax, xMax);
	std::ifstream  input_file("records.json");
	input_file >> config;

    // Названия пунктов меню
    std::vector<std::string> menuItems = {
        "Easy",
        "Normal",
        "Hard",
        "Special",
	"load game",
        "Exit"
    };
int highlight = 0;

startGame:
for(;;){
	clear(); // Очищаем экран

        // Вывод заголовка
        mvprintw(1, xMax / 2 - 5, "GAME MENU");

        // Вывод пунктов меню
        for (int i = 0; i < menuItems.size(); ++i) {
            if (i == highlight) {
                attron(A_REVERSE); // Выделяем выбранный пункт
            }
            mvprintw(yMax / 2 - menuItems.size() / 2 + i, xMax / 2 - menuItems[i].length() / 2, menuItems[i].c_str()); // центрируем меню
            attroff(A_REVERSE); // Выключаем выделение
        }

        refresh(); // Обновляем экран

        // Обработка ввода пользователя
        int choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = menuItems.size() - 1; // Переходим к последнему пункту, если вышли за верхнюю границу
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == menuItems.size()) {
                    highlight = 0; // Переходим к первому пункту, если вышли за нижнюю границу
                }
                break;
            case 10: // Enter (код клавиши Enter - 10)
            {
                // Обрабатываем выбранный пункт меню
                if (menuItems[highlight] == "Exit") {
                    endwin(); // Завершаем работу ncurses
                    return 0;
                }
	if (menuItems[highlight] == "Hard") {
mod='h';	
	goto hard;
	}
	else if (menuItems[highlight] == "Easy") {
mod='e'	;
	goto easy;
	}
else if (menuItems[highlight] == "Normal") {
mod = 'n';		
goto normal;
	}
	else if (menuItems[highlight] == "load game") {
    std::ifstream input_file("saves.json");
    nlohmann::json config1;
    input_file >> config1;
    input_file.close();	
	map=config1.get<std::vector<std::vector<int>>>();
	goto ldgame;
	}

else {
		goto spesial;
	}

}}}
noecho();

ldgame:
N = map[0].size();
for(;;)
	{

		attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word1.c_str()); 
		attroff(COLOR_PAIR(5));

		map = muv(map, N);

		attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word2.c_str());
		attroff(COLOR_PAIR(5));

		map = muv3(map, N);

		win=checkVin(map, N, area);
		if(win==true) {
			records=config["record"]["hardRec"];
			goto start;
		}
		map = bestMuv(map, N);
		
		lose=checkLose(map, N);
		if(lose==true) {
			goto start1;
		}
	}

hard:
	map=makemap(N, 3, 3, true);
	
	clear();
	printmap(map, N);

	for(;;)
	{

		attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word1.c_str()); 
		attroff(COLOR_PAIR(5));

		map = muv(map, N);

		attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word2.c_str());
		attroff(COLOR_PAIR(5));

		map = muv3(map, N);

		win=checkVin(map, N, area);
		if(win==true) {
			records=config["record"]["hardRec"];
			goto start;
		}
		map = bestMuv(map, N);
		
		lose=checkLose(map, N);
		if(lose==true) {
			goto start1;
		}
	}

normal:
	map=makemap(N, 3, 3, false);
	clear();
printmap(map, N);

	for(;;)
	{
		attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word1.c_str()); 
		attroff(COLOR_PAIR(5));

		map = muv(map, N);

		attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word2.c_str());
		attroff(COLOR_PAIR(5));

		map = muv3(map, N);
		win=checkVin(map, N, area);
		if(win==true) {
			records=config["record"]["normalRec"];
			goto start;
		}

		map = bestMuv(map, N);
		lose=checkLose(map, N);
		if(lose==true) {
			goto start1;
		}
	}

easy:
	map=makemap(N, 3, 3, false);
clear();
	printmap(map, N);
	for(;;) {

		attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word1.c_str()); 
		attroff(COLOR_PAIR(5));

		map = muv(map, N);

		attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word2.c_str());
		attroff(COLOR_PAIR(5));

		map = muv3(map, N);
		win=checkVin(map, N, area);
		if(win==true) {
			records=config["record"]["easyRec"];

			goto start;
		}

		map = muv2(map, N);
		lose=checkLose(map, N);
		if(lose==true) {
			goto start1;
		}
	}

start:
	{
		clear();
		int max_y, max_x;
		getmaxyx(stdscr, max_y, max_x);

		const char* message = "WIN";
		int message_len = strlen(message);
		int start_y = max_y / 2;

		int start_x = (max_x - message_len) / 2;
		mvprintw(start_y, start_x, message);

		message = "score";

		mvprintw(start_y+2, start_x, message);
		mvprintw(start_y+2, start_x+5,"%d", area);
		mvprintw(start_y+3, start_x, "record");
		mvprintw(start_y+3, start_x+6,"%d",records);

		if(area>config["record"]["hardRec"] and mod=='h') {
			mvprintw(start_y+4, start_x, "new record");
			std::ofstream output_file("records.json");
			config["record"]["hardRec"]=area;
			output_file << config.dump(4);
			output_file.close();
		}

		if(area>config["record"]["normalRec"] and mod=='n') {
			mvprintw(start_y+4, start_x, "new record");
			std::ofstream output_file("records.json");
			config["record"]["normalRec"]=area;
			output_file << config.dump(4);
			output_file.close();
		}
if(area>config["record"]["easyRec"] and mod=='e') {
			mvprintw(start_y+4, start_x, "new record");
			std::ofstream output_file("records.json");
			config["record"]["easyRec"]=area;
			output_file << config.dump(4);
			output_file.close();
		}

				

		refresh();

		getch();

	}
	goto endGame;


endGame:

	 highlight = 0;

for(;;){
	clear(); 

                mvprintw(1, xMax / 2 - 5, "GAME MENU");

        // Вывод пунктов меню
        for (int i = 0; i < endGame.size(); ++i) {
            if (i == highlight) {
                attron(A_REVERSE); // Выделяем выбранный пункт
            }
            mvprintw(yMax / 2 - endGame.size() / 2 + i, xMax / 2 - endGame[i].length() / 2, endGame[i].c_str()); // центрируем меню
            attroff(A_REVERSE); // Выключаем выделение
        }

        refresh(); // Обновляем экран

        // Обработка ввода пользователя
        int choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = menuItems.size() - 1; // Переходим к последнему пункту, если вышли за верхнюю границу
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == endGame.size()) {
                    highlight = 0; 
                }
                break;
            case 10:             {
                // Обрабатываем выбранный пункт меню
                if (endGame[highlight] == "end game") {
                    endwin(); // Завершаем работу ncurses
                    return 0;
                }
		else{
		goto startGame;
	}
}}}
start1:

	clear();
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	
	 message_len = strlen(message1);
	start_y = max_y / 2;
	 start_x = (max_x - message_len) / 2;
	mvprintw(start_y, start_x, message1);
	refresh();
	getch();
	goto endGame;

spesial:
{

	
    int y = 0; // Текущая строка для вывода
endwin();

	std::cout<<"new or old (n/o)"<<std::endl;
	std::cin>>mod;
	

	std::string name;
	bool wall;
	int saiz, mans, beds, muw;
	 if (mod == 'n') {
        std::cout << "name level: " << std::endl;

        std::cin.ignore(); // Важно: Очищаем буфер после ввода символа
        std::getline(std::cin, name); // Используем getline для чтения имени

        std::cout << "saiz of map, number of @ and *: " << std::endl;
        std::cin >> saiz >> mans >> beds;
        std::cout << "how many move for *: " << std::endl;
        std::cin >> muw;
	std::cout << "wall of *(1/0): " << std::endl;

	std::cin >> wall;

        config["lewels"][name]["saiz"] = saiz;
        config["lewels"][name]["@"] = mans;
        config["lewels"][name]["*"] = beds;
        config["lewels"][name]["muve"] = muw;
        config["lewels"][name]["wall"] = wall;
	 
        std::ofstream ofs("records.json"); 
        ofs << std::setw(4) << config << std::endl; 
        ofs.close();

	}
        else if (mod == 'o') {
        std::cout << config["lewels"] << std::endl; // Выводим объект lewels целиком

        std::cout << "name level: " << std::endl;
        std::cin.ignore(); // Важно: Очищаем буфер после ввода символа
        std::getline(std::cin, name);

        if (config["lewels"].contains(name)) { // Проверка существования ключа name
            saiz = config["lewels"][name]["saiz"];
            mans = config["lewels"][name]["@"];
            beds = config["lewels"][name]["*"];
            muw = config["lewels"][name]["muve"];
            wall = config["lewels"][name]["wall"].get<bool>(); // Явное приведение типа к bool

            std::cout << "lewel fith name: " << name << std::endl;
            std::cout << "  saiz: " << saiz << std::endl;
            std::cout << "  @: " << mans << std::endl;
            std::cout << "  *: " << beds << std::endl;
            std::cout << "  muve: " << muw << std::endl;
            std::cout << "  wall: " << wall << std::endl;
		getch();
        }}
game:
	initscr();
	cbreak();
	curs_set(0);
	noecho();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	clear(); refresh();
	map = makemap(saiz,beds ,mans, wall);

	for(;;)
	{	attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word1.c_str()); 
		attroff(COLOR_PAIR(5));


	map = muv(map, saiz);

	attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word2.c_str());
		attroff(COLOR_PAIR(5));

	map = muv3(map, saiz);

	win=checkVin(map, saiz, area);
	if(win==true) {
		goto start11;
		}
	for(int i=0; i<muw; i++){
	map = bestMuv(map, saiz);}
	lose=checkLose(map, saiz);
	if(lose==true) {
		goto start1;
		}
	}
start11:
	clear();
		int max_y, max_x;
		getmaxyx(stdscr, max_y, max_x);

		const char* message = "WIN";
		int message_len = strlen(message);
		int start_y = max_y / 2;

		int start_x = (max_x - message_len) / 2;
		mvprintw(start_y, start_x, message);

		message = "score";

		mvprintw(start_y+2, start_x, message);
		mvprintw(start_y+2, start_x+5,"%d", area);
		mvprintw(start_y+3, start_x, "record");
		mvprintw(start_y+3, start_x+6,"%d",records);

		if(area>config["lewels"][name]["Rec"]) {
			mvprintw(start_y+4, start_x, "new record");
			std::ofstream output_file("records.json");
			config["lewels"][name]["Rec"]=area;
			output_file << config.dump(4);
			output_file.close();
		}
	refresh();

		getch();

	
	goto endGame;


}
	
}

