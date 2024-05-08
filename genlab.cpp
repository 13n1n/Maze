#include <stdio.h>
#include "genlab.h"

#define WID first
#define HEI second
#define X first
#define Y second

using std::pair;

room::room(unsigned x, unsigned y){
    m_x = x;
    m_y = y;
    m_n = -1;
    m_magicnumber = BIN8(0000);
    __mnum = BIN8(1111);
    _vis = false;
    m_way = false;
    __backroom == NULL;
}

bool room::left(){
	return m_magicnumber & __LEFT;
}

bool room::right(){
	return m_magicnumber & __RIGHT;
}

bool room::up(){
	return m_magicnumber & __UP;
}

bool room::down(){
	return m_magicnumber & __DOWN;
}

bool room::way(){
	return m_way;
}

bool room::start(){
	return __startfinish & 1;
}

bool room::finish(){
	return __startfinish & 2;
}

pair<int, int> room::getcoords(){
	return pair<int, int>(m_x, m_y);
}

std::pair<int, int> labirint::size(){
	return m_size;
}

int n = 0;
void labirint::generate(unsigned x, unsigned y){
	room *__this = __getroom(x, y);
	__this->_vis = true;
	__this->m_n = n;
	if(n > m_wayweight){
		m_wayweight = n;
		m_finish = __this;
	}

    int _x = __this->__mnum;
	int _v = __this->m_magicnumber;
	while(_x & __UP | _x & __RIGHT | _x & __DOWN | _x & __LEFT){
#ifdef __DEBUG
		int _t = n; while(_t--) printf("\t");
		printf("(%d; %d): %d|%d|%d|%d\n", x, y,
		_x & __UP, _x & __RIGHT, _x & __DOWN, _x & __LEFT);
#endif
		int r = rand()%4;
		if(_x & (1 << r)){
			room *t = __getroom(x, y, 1 << r);
			if(t != NULL && !t->_vis){
				if(1<<r == __UP	){ t->m_magicnumber |= __DOWN;	t->__mnum &= ~__DOWN;}
				if(1<<r == __DOWN){ t->m_magicnumber |= __UP;		t->__mnum &= ~__UP;}
				if(1<<r == __RIGHT	){ t->m_magicnumber |= __LEFT;	t->__mnum &= ~__LEFT;}
				if(1<<r == __LEFT){t->m_magicnumber |= __RIGHT;	t->__mnum &= ~__RIGHT;}
				t->__backroom = __this;
				n++; generate(t->m_x, t->m_y); n--;
				__this->m_magicnumber |= (1 << r);
			}_x = _x & ~(1 << r);
			__this->__mnum = _x;
		}
	}
}

void labirint::__restoreway(room *r){
	//printf("Arrived!!!");
    while((r = r->__backroom) != NULL)
        r->m_way = true;
}

room* labirint::__getroom(int x, int y, unsigned k){
	switch(k){
	case __DOWN:
		if(y-1 < 0) return NULL;
		return m_rooms + (m_size.WID*(y-1) +  x );
	case __RIGHT:
		if(x+1 >= m_size.WID) return NULL;
		return m_rooms + (m_size.WID*( y ) + x+1);
	case __UP:
		if(y+1 >= m_size.HEI) return NULL;
		return m_rooms + (m_size.WID*(y+1) +  x );
	case __LEFT:
		if(x-1 < 0) return NULL;
		return m_rooms + (m_size.WID*( y ) + x-1);
	}
}

room labirint::getroom(unsigned x, unsigned y){
	if(!(x < m_size.WID && y < m_size.HEI)) throw "in labirint::getroom: Room does not exist!\n";
	return m_rooms[m_size.WID*(y) + x];
}

bool labirint::isItBall(unsigned x, unsigned y){
	return (m_rooms + m_size.WID*(y) + x) == m_ball;
}

bool labirint::finished(){
    return (m_finish - m_ball) != 0;
}

room* labirint::__getroom(unsigned x, unsigned y){
	if(!(x < m_size.WID && y < m_size.HEI)) throw "in labirint::__getroom: Room does not exist!\n";
	return m_rooms + (m_size.WID*(y) + x);
}

void labirint::__labirint(int width, int height){
    m_wayweight = 0;
    m_rooms = new room[width*height];
    for(unsigned i = 0; i < width; i++)
        for(unsigned j = 0; j < height; j++)
            m_rooms[width*j + i] = room(i, j);
    m_size.WID = width; m_size.HEI = height;
    unsigned x = rand()%width, y = rand()%height;
    m_start = __getroom(x, y);
    m_start->__startfinish = 1;
    generate(x, y);
    m_finish->__startfinish = 2;
    m_ball = m_start;
    //__restoreway(m_finish);
    //printf("\n");
}

labirint::labirint(int _width, int _height){
    width = _width;
    height = _height;
    __labirint(_width, _height);
}

labirint::labirint(){
    width = 25;
    height = 25;
    __labirint(25, 25);
}

labirint::~labirint(){
    delete [] m_rooms;
}

void labirint::goballto(int k){
	int x = m_ball->m_x, y = m_ball->m_y;
	
	try{
		switch(k){

		case __UP:
			if(m_ball->up()){
				m_ball->m_way = true;
				m_ball = __getroom(x, y+1);
			}break;

		case __DOWN:
			if(m_ball->down()){
				m_ball->m_way = true;
				m_ball = __getroom(x, y-1);
			}break;

		case __LEFT:
			if(m_ball->left()){
				m_ball->m_way = true;
				m_ball = __getroom(x-1, y);
			}break;

		case __RIGHT:
			if(m_ball->right()){
				m_ball->m_way = true;
				m_ball = __getroom(x+1, y);
			}break;
		}
	}catch(char *e){
		printf(e);
	}
}
	
room labirint::getfinish(){
    return *m_finish;
}

room labirint::getstart(){
    return *m_start;
}

room labirint::getballroom(){
    return *m_ball;
}


void labirint::setway(unsigned __x, unsigned __y){
    __getroom(__x, __y)->m_way = true;
    m_ball = __getroom(__x, __y);
}

#ifdef __unix__
#include <termios.h>
#include <unistd.h>
/*int kbhit(){
     struct termios oldt,
     newt;
     int ch1,ch2,ch3;
     tcgetattr( STDIN_FILENO, &oldt );
     newt = oldt;
     newt.c_lflag &= ~( ICANON | ECHO );
     tcsetattr( STDIN_FILENO, TCSANOW, &newt );
     ch1 = getchar();
     ch2 = getchar();
     ch3 = getchar();
     tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
     //cout<<ch1<<"+"<<ch2<<"+"<<ch3<<"\n";
	 //up - 27+91+65
	 //left - 27+91+68
	 //down - 27+91+66
	 //right - 27+91+67
	 if(ch3 == 67)
		return __RIGHT;
	 if(ch3 == 65)
		return __DOWN;//__UP;
	 if(ch3 == 68)
		return __LEFT;
	 if(ch3 == 66)
		return __UP;//__DOWN;
	 return 0;
}

int main(int argc, char **argv){
	int w = 25, h = 20;
	if(argc == 2)
		w = h = atoi(*(argv+1));
	else if(argc == 3){
		w = atoi(*(argv+1));
		h = atoi(*(argv+2));
	}printf("|width: %d; height: %d|\b|\n", w, h);
	labirint floor(w, h);
	printf("\n");
	
	int keypress = 0;
	do{
		system("clear");
		if(keypress)
			floor.goballto(keypress);

		for(int j = 0; j < h*3; j++){
			for(int i = 0; i < w*3; i++){
				if(j%3 != 0 || j == 0)
					if(i%3 == 0){
						if(i == 0){
							if(j%3 == 1 && floor.getroom(i/3, j/3).left())
								printf(" ");
							else if(j%3 != 1)
								printf("+");
							else
								printf("|");
						}
					}else if(i%3 == 1){
						switch(j%3){
						case 0:
							if(floor.getroom(i/3, j/3).down())
								printf("  ");
							else
								printf("--");
							break;
						case 1:
							if(floor.ball(i/3, j/3)) printf("[]");
							else if(floor.getroom(i/3, j/3).way()) printf("::");
							else if (floor.getroom(i/3, j/3).finish()) printf("FN");
							else printf("  ");
							break;
						case 2:
							if(floor.getroom(i/3, j/3).up())
								printf("  ");
							else
								printf("--");
							break;
						}
					}else{
						if(j%3 == 1 && floor.getroom(i/3, j/3).right())
							printf(" ");
						else if(j%3 != 1)
							printf("+");
						else
							printf("|");
					}
				//if(i%3 == 2) printf(" ");
			}if(j%3 != 0 || j == 0) printf("\n");
		}

		if(!floor.finished())
			while(!(keypress = kbhit()));
	}while(!floor.finished());
	system("clear");
	printf("Congratulations! Level accomplished!!!\n");

	return 0;
}*/

#endif


#undef WID
#undef HEI
#undef X
#undef Y
