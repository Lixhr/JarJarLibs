#pragma once
#include <set>
#include "ProcessedMethod.hpp"
#include <fstream>

class GraphViz {
    public:
        struct RelationKey {
            const std::string &callee_class;
            const std::string &callee_func;
            const std::string &caller_class;
            const std::string &caller_func;
            bool is_native;

        
            bool operator<(const RelationKey& other) const {
                return std::tie(caller_class, caller_func, callee_class, callee_func) <
                       std::tie(other.caller_class, other.caller_func, other.callee_class, other.callee_func);
            }
        };

        void addRelation(RelationKey key);
    
        ~GraphViz();
        GraphViz();
        void doDotGraph(const std::string &out_file);

    private:
        std::set<RelationKey> relations;
};