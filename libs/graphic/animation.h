#ifndef ANIMATION_H
#define ANIMATION_H

#include <list>
// #include <queue>
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
    bool fadeOut(T* obj, double *currTime, double fadeTime) {
        if (*currTime + elapseTime >= fadeTime) {
            obj->transparent = 0;
            return true;
        } else {
            obj->transparent = 1.0 - (*currTime + elapseTime) / fadeTime;
            return false;
        }
    }

    // DO NOT USE DIRECTLY
    template<typename T>
    bool displace(T* obj, int Dx, int Dy, double* currTime, double transTime) {
        double Ux = Dx - obj->lx;
        double Uy = Dy - obj->ly;
        double leng = sqrt(Ux*Ux + Uy*Uy);
        double distance = bezier(leng, transTime, std::min(transTime, (*currTime) + (elapseTime)));
        obj->x = obj->lx + Ux / leng * distance;
        obj->y = obj->ly + Uy / leng * distance;
        if ((*currTime) + elapseTime >= transTime) {
            obj->lx = obj->x = Dx;
            obj->ly = obj->y = Dy;
            return true;
        } else {
            return false;
        }
    }

    template<typename T>
    bool transform(T* obj, int Tx, int Ty, double* currTime, double transTime) {
        return displace(obj, obj->lx + Tx, obj->ly + Ty, currTime, transTime);
    }

    class QueueOfScenes {
    public:
        double currTime;
        // std::queue<std::vector<std::function<bool()>>> q;
        std::list<std::list<std::function<bool()>>> q;

        QueueOfScenes();

        void pushToFrontScene(const std::function<bool()> &func);
        void pushToKthScene(int k, const std::function<bool()> &func);
        void pushToBackScene(const std::function<bool()> &func);
        void pushToNewScene(const std::function<bool()> &func);
        void pushToNewKthScene(int k, const std::function<bool()> &func);
        void pushSceneToBack(const std::list<std::function<bool()>> &scene);
        void pushSceneToKth(int k, const std::list<std::function<bool()>> &funcList);
        void addBlankScene();
        void addBlankSceneToKth(int k);
        
        void run();

        // Push To Front Scene
        template<typename T>
        void pushFadeInToFrontScene(T* obj, double fadeTime = Animate::FADEIN_TIME) {
            pushToFrontScene(
                std::bind(&fadeIn<T>, obj, &currTime, fadeTime)
            );
        }

        template<typename T>
        void pushFadeOutToFrontScene(T* obj, double fadeTime = Animate::FADEOUT_TIME) {
            pushToFrontScene(
                std::bind(&fadeOut<T>, obj, &currTime, fadeTime)
            );
        }

        template<typename T>
        void pushDisplaceToFrontScene(T* obj, int Dx, int Dy, double transTime = Animate::TRANS_TIME) {
            pushToFrontScene(std::bind(&displace<T>, obj, Dx, Dy, &currTime, transTime));
        }

        template<typename T>
        void pushTransformToFrontScene(T* obj, int Tx, int Ty, double transTime = Animate::TRANS_TIME) {
            pushToFrontScene(std::bind(&transform<T>, obj, Tx, Ty, &currTime, transTime));
        }

        // Push To Back Scene
        template<typename T>
        void pushFadeInToBackScene(T* obj, double fadeTime = Animate::FADEIN_TIME) {
            pushToBackScene(std::bind(&fadeIn<T>, obj, &currTime, fadeTime));
        }

        template<typename T>
        void pushFadeOutToBackScene(T* obj, double fadeTime = Animate::FADEOUT_TIME) {
            pushToBackScene(std::bind(&fadeOut<T>, obj, &currTime, fadeTime));
        }

        template<typename T>
        void pushDisplaceToBackScene(T* obj, int Dx, int Dy, double transTime = Animate::TRANS_TIME) {
            pushToBackScene(std::bind(&displace<T>, obj, Dx, Dy, &currTime, transTime));
        }

        // Push To Kth Scene
        template<typename T>
        void pushFadeInToKthScene(int k, T* obj, double fadeTime = Animate::FADEIN_TIME) {
            pushToKthScene(k, std::bind(&fadeIn<T>, obj, &currTime, fadeTime));
        }


        template<typename T>
        void pushFadeOutToKthScene(int k, T* obj, double fadeTime = Animate::FADEOUT_TIME) {
            pushToKthScene(k, std::bind(&fadeOut<T>, obj, &currTime, fadeTime));
        }

        template<typename T>
        void pushTransformToKthScene(int k, T* obj, int Tx, int Ty, double transTime = Animate::TRANS_TIME) {
            pushToKthScene(k, std::bind(&transform<T>, obj, Tx, Ty, &currTime, transTime));
        }

        // Push To New Scene
        template<typename T>
        void pushFadeInToNewScene(T* obj, double fadeTime = Animate::FADEIN_TIME) {
            addBlankScene();
            pushFadeInToBackScene(obj, fadeTime);
        }

        template<typename T>
        void pushFadeOutToNewScene(T* obj, double fadeTime = Animate::FADEOUT_TIME) {
            addBlankScene();
            pushFadeOutToBackScene(obj, fadeTime);
        }

        template<typename T>
        void pushDisplaceToNewScene(T* obj, int Dx, int Dy, double transTime = Animate::TRANS_TIME) {
            addBlankScene();
            pushDisplaceToBackScene(obj, Dx, Dy, transTime);
        }

        // Push To New Kth Scene
        template<typename T>
        void pushFadeInToNewKthScene(int k, T* obj, double fadeTim = Animate::FADEIN_TIME) {
            addBlankSceneToKth(k);
            pushFadeInToKthScene(k, obj, fadeTim);
        }

        template<typename T>
        void pushFadeOutToNewKthScene(int k, T* obj, double fadeTime = Animate::FADEIN_TIME) {
            addBlankSceneToKth(k);
            pushFadeOutToKthScene(k, obj, fadeTime);
        }


    };

    inline QueueOfScenes queueOfScenes;
}

#endif