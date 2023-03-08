#include "SinglyNode.h"

SinglyNode::SinglyNode() : GraphicNode::GraphicNode() {}

SinglyNode::SinglyNode(double _x, double _y, int _s, bool _sqr, int _v) : GraphicNode::GraphicNode(_x, _y, _s, _sqr) {
    val = _v;
}  