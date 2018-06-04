#ifndef _DEBUGSERIAL_H_
#define _DEBUGSERIAL_H_

enum color
{
    color_black = 0,
    color_red,
    color_green,
    color_yellow,
    color_blue,
    color_magenta,
    color_cyan,
    color_gray = 7,
    color_default = 9
};

enum cursorDir
{
    cursor_up,
    cursor_down,
    cursor_right,
    cursor_left
};

class DebugSerial : public Serial
{
public:
    DebugSerial(PinName tx, PinName rx) : Serial(tx, rx) { reset(); }
    DebugSerial(PinName tx, PinName rx, int baud) : Serial(tx, rx, baud) { reset(); }
    
    void reset()
    {
        cls();
        setLetterColor(color_default);
        setBackColor(color_default);
        setLetterDefault();
        isBrightBold = false;
        isUnderLine = false;
        isFlip = false;
    }
    
    void cls()
    {
        clear();
        setPos(0, 0);
    }
        
    // cursor
    void clear()                { printf("\033[2J"); }
    void setPos(int x, int y)   { printf("\033[%d;%dH", x, y); }
    void clearToLineEnd()       { printf("\033[K"); }
    void moveCursor(cursorDir dir, int distance)
    {
        switch(dir)
        {
            case cursor_up:      up(distance);    break;
            case cursor_down:    down(distance);  break;
            case cursor_right:   right(distance); break;
            case cursor_left:    left(distance);  break;
        }
    }
    
    void up   (int distance) { printf("\033[%dA", distance); }
    void down (int distance) { printf("\033[%dB", distance); }
    void right(int distance) { printf("\033[%dC", distance); }
    void left (int distance) { printf("\033[%dD", distance); }
    
    // letter attribute
    void setLetterDefault()       { printf("\033[0m"); isBrightBold = isUnderLine = isFlip = false; }
    void setBrightBold(bool isOn) {isBrightBold = isOn; updateLetterState(); }
    void setUnderLine(bool isOn)  {isUnderLine = isOn;  updateLetterState(); }
    void setFlip(bool isOn)       {isFlip = isOn;       updateLetterState(); }
    
    // color
    void setLetterColor(color c) { printf("\033[%dm", 30 + (int)c); }
    void setBackColor(color c)   { printf("\033[%dm", 40 + (int)c); }
    
private:
    void updateLetterState()
    {
        setLetterDefault();
        if(isBrightBold) brightBold();
        if(isUnderLine)  underLine();
        if(isFlip)       flip();
    }
    void brightBold() { printf("\033[1m"); }
    void underLine()  { printf("\033[4m"); }
    void flip()       { printf("\033[7m"); }
    
private:
    bool isBrightBold;
    bool isUnderLine;
    bool isFlip;
};

#endif //_DEBUGSERIAL_H_

