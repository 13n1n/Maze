#include <utility>
#include <cstdlib>

#define BIN__N(x) (x) | x>>3 | x>>6 | x>>9
#define BIN__B(x) (x) & 0xf | (x)>>12 & 0xf0

#define BIN8(v) (BIN__B(BIN__N(0x##v)))

#define __UP BIN8(1)
#define __RIGHT BIN8(10)
#define __DOWN BIN8(100)
#define __LEFT BIN8(1000)

class labirint;

class room{
//private:
public:
    //friend labirint;
	int m_x;
	int m_y;
	int m_n;
	int m_magicnumber;
	int __mnum;
	int __startfinish; //0 - nothing, 1 - start, 2 - finish
	bool _vis;
    bool m_way;
	room *__backroom;
//public:
    room(unsigned x, unsigned y);
	bool left();
	bool right();
	bool up();
	bool down();
	bool start();
	bool finish();
	
	bool way();
	
	std::pair<int, int> getcoords();

    bool operator == (room r){
        return m_x == r.m_x && m_y == r.m_y;
    }
};


class labirint{
public:private:
	int m_wayweight;
	room* m_rooms;
	room* m_start;
	room* m_finish;
	room* m_ball;
	room* __getroom(int x, int y, unsigned k);
	room* __getroom(unsigned x, unsigned y);
    std::pair<unsigned, unsigned> m_size;
	void __restoreway(room *r);
    void __labirint(int width, int height);
protected:
    unsigned width, height;
public:
    labirint(int _width, int _height);
    labirint();
	~labirint();
	
    bool isItBall(unsigned x, unsigned y);
	bool finished();
	std::pair<int, int> size();
	void generate(unsigned x, unsigned y);
	void goballto(int k);
    void setway(unsigned x, unsigned y);
    room getroom(unsigned __x, unsigned __y);
    room getfinish();
    room getstart();
    room getballroom();
};
