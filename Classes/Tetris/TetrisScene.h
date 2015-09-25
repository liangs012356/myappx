#ifndef __TetrisScene_SCENE_H__
#define __TetrisScene_SCENE_H__

#include "cocos2d.h"
#include "tetris/tetris.h"

class TetrisScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TetrisScene);
protected:
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){ nowKeyCode = keyCode; }
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){ nowKeyCode = cocos2d::EventKeyboard::KeyCode::KEY_NONE; m_freams_press = 0; }
	virtual void update(float delta);
	virtual void onEnter();
protected:
	void addchildat(int id, int pos_x, int pos_y, int tag, Layer *who);
	void show(bool map_need_update);
	void autodown(float time);
	void updateFreamCount(int freams_count_to_add_once);
	void resetTetris();
private:
	Tetris * tetris;				// 当前方块
	Tetris tetriss[7];				// 方块组合
	cocos2d::Sprite* tetrisbase[8];	// 8中不同颜色的小方块

	cocos2d::EventKeyboard::KeyCode nowKeyCode;		// 当前按下的按钮
	int m_freams_press;								// 按钮已按下的帧数
};

#endif // __TetrisScene_SCENE_H__
