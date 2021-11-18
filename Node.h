//
// Created by jeang on 2021-10-21.
//

#ifndef CPP_OOP_VS_DOD_NODE_H
#define CPP_OOP_VS_DOD_NODE_H

#include <vector>
#include <memory>


class Node {
    public:
        int id_;
        int x_;
        int y_;
    private:
        std::vector<std::shared_ptr<Node>> incoming_nodes_;
        std::vector<std::shared_ptr<Node>> outgoing_nodes_;
};


#endif //CPP_OOP_VS_DOD_NODE_H
