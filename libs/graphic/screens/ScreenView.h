#ifndef SCREEN_VIEW_H
#define SCREEN_VIEW_H

class ScreenView {
public:
    virtual ~ScreenView();
    virtual void load();
    virtual void init();
    virtual void draw();
    virtual void destroy();
};

#endif