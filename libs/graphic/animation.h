#ifndef ANIMATION_H
#define ANIMATION_H

#include <queue>
#include <vector>
#include <functional>

#include "GraphicNode.h"

// NOTE: Templated function cannot be seperated into multiple files

namespace Animate {
    double bezier(double S, double T, double t);

    // DO NOT USE DIRECTLY
    template<typename T> 
    bool fadeIn(T* obj, double* currTime, double fadeTime) {
        if (*currTime + elapseTime >= fadeTime) {
            obj->transparent = 1;
            return true;
        } else {
            obj->transparent = (*currTime + elapseTime) / fadeTime;
            return false;
        }
    }

    // DO NOT USE DIRECTLY
    template<typename T>
    bool fadeOut(T* obj, double *currTime, double fadeTime, bool isDel = false) {
        if (*currTime + elapseTime >= fadeTime) {
            obj->transparent = 0;
            if (isDel) {
                delete obj; // DELETE
            }
            return true;
        } else {
            obj->transparent = 1.0 - (*currTime + elapseTime) / fadeTime;
            return false;
        }
    }

    // DO NOT USE DIRECTLY
    template<typename T>
    bool transform(T* obj, int Lx, int Ly, int Tx, int Ty, double* currTime, double transTime) {
        double Ux = Tx - Lx;
        double Uy = Ty - Ly;
        double leng = sqrt(Ux*Ux + Uy*Uy);
        double distance = bezier(leng, transTime, std::min(transTime, (*currTime) + (elapseTime)));
        obj->x = Lx + Ux / leng * distance;
        obj->y = Ly + Uy / leng * distance;
        if ((*currTime) + elapseTime >= transTime) {
            obj->x = Tx;
            obj->y = Ty;
            return true;
        } else {
            return false;
        }
    }

    class QueueOfScenes {
    public:
        double currTime;
        std::queue<std::vector<std::function<bool()>>> q;

        QueueOfScenes();

        void pushToFrontScene(const std::function<bool()> &func);
        void pushToBackScene(const std::function<bool()> &func);
        void pushToNewScene(const std::function<bool()> &func);
        void pushScene(const std::vector<std::function<bool()>> &scene);
        void addBlankScene();
        
        void run();

        template<typename T>
        void pushFadeInToFrontScene(T* obj, double fadeTime = Animate::FADEIN_TIME) {
            pushToFrontScene(
                std::bind(&fadeIn<T>, obj, &currTime, fadeTime)
            );
        }

        template<typename T>
        void pushFadeOutToFrontScene(T* obj, double fadeTime = Animate::FADEOUT_TIME, bool isDel = false) {
            pushToFrontScene(
                std::bind(&fadeOut<T>, obj, &currTime, fadeTime, isDel)
            );
        }

        template<typename T>
        void pushDeleteFadeOutToFrontScene(T* obj) {
            pushFadeOutToFrontScene(obj, Animate::FADEOUT_TIME, true);
        }

        template<typename T>
        void pushTransformToFrontScene(T* obj, int Tx, int Ty, double transTime = Animate::TRANS_TIME) {
            pushToFrontScene(
                std::bind(&transform<T>, obj, obj->cx, obj->cy, Tx, Ty, &currTime, transTime)
            );
            obj->cx = Tx;
            obj->cy = Ty;
        }


        template<typename T>
        void pushFadeInToBackScene(T* obj, double fadeTime = Animate::FADEIN_TIME) {
            pushToBackScene(
                std::bind(&fadeIn<T>, obj, &currTime, fadeTime)
            );
        }

        template<typename T>
        void pushFadeOutToBackScene(T* obj, double fadeTime = Animate::FADEOUT_TIME, bool isDel = false) {
            pushToBackScene(
                std::bind(&fadeOut<T>, obj, &currTime, fadeTime, isDel)
            );
        }

        template<typename T>
        void pushDeleteFadeOutToBackScene(T* obj) {
            pushFadeOutToBackScene(obj, Animate::FADEOUT_TIME, true);
        }

        template<typename T>
        void pushTransformToBackScene(T* obj, int Tx, int Ty, double transTime = Animate::TRANS_TIME) {
            pushToBackScene(
                std::bind(&transform<T>, obj, obj->cx, obj->cy, Tx, Ty, &currTime, transTime)
            );
            obj->cx = Tx;
            obj->cy = Ty;
        }

        template<typename T>
        void pushFadeInToNewScene(T* obj, double fadeTime = Animate::FADEIN_TIME) {
            addBlankScene();
            pushFadeInToBackScene(obj, fadeTime);
        }

        template<typename T>
        void pushFadeOutToNewScene(T* obj, double fadeTime = Animate::FADEOUT_TIME, bool isDel = false) {
            addBlankScene();
            pushFadeOutToBackScene(obj, fadeTime, isDel);
        }

        template<typename T>
        void pushDeleteFadeOutToNewScene(T* obj) {
            pushFadeOutToNewScene(obj, Animate::FADEOUT_TIME, true);
        }

        template<typename T>
        void pushTransformToNewScene(T* obj, int Tx, int Ty, double transTime = Animate::TRANS_TIME) {
            addBlankScene();
            pushTransformToBackScene(obj, Tx, Ty, transTime);
        }
    };

    inline QueueOfScenes queueOfScenes;
}

#endif