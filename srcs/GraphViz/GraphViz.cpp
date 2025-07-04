#include "GraphViz.hpp"
#include <map>

GraphViz::GraphViz() {
}

GraphViz::~GraphViz() {
}

void GraphViz::addRelation(RelationKey key) {

    if (relations.find(key) != relations.end()) {
        return;
    }

    relations.insert(key);
}

void GraphViz::test() {
    std::ofstream ofs("test.dot", std::ofstream::out);

    ofs << "digraph g {\n";
    ofs << "ranksep=2.5;\n";
    ofs << "node [shape=box];\n";
    ofs << "rankdir=TB;\n";

    struct NodeInfo {
        bool is_native = false;
    };
    std::map<std::string, NodeInfo> nodes;

    for (auto &rel : this->relations) {
        size_t caller_index = rel.caller_class.find_last_of(".") + 1;
        size_t callee_index = rel.callee_class.find_last_of(".") + 1;

        std::string caller_node = rel.caller_class.substr(caller_index) + "." + rel.caller_func;
        std::string callee_node = rel.callee_class.substr(callee_index) + "." + rel.callee_func;

        if (rel.is_native) {
            nodes[callee_node].is_native = true;
        }

        nodes[caller_node]; 
        nodes[callee_node];
    }

    ofs << "    subgraph cluster_native {\n";
    ofs << "        label=\"Target Methods\";\n";
    ofs << "        node [style=filled,color=lightblue];\n";
    ofs << "        style=filled;\n";
    ofs << "        color=lightgrey;\n";
    ofs << "        rank=sink;\n";

    for (auto &[node_name, info] : nodes) {
        if (info.is_native) {
            ofs << "        \"" << node_name << "\";\n";
        }
    }
    ofs << "    }\n";

    for (auto &[node_name, info] : nodes) {
        if (!info.is_native) {
            ofs << "\"" << node_name << "\";\n";
        }
    }



    for (auto &rel : this->relations) {
        size_t caller_index = rel.caller_class.find_last_of(".") + 1;
        size_t callee_index = rel.callee_class.find_last_of(".") + 1;

        std::string caller_node = rel.caller_class.substr(caller_index) + "." + rel.caller_func;
        std::string callee_node = rel.callee_class.substr(callee_index) + "." + rel.callee_func;

        ofs << "\"" << caller_node << "\" -> \"" << callee_node << "\";\n";
    }

    ofs << "}\n";
    ofs.close();
}


// digraph g {
//     ranksep=2.5;
//     node [shape=box];
  
//     subgraph cluster_native {
//       label="Native Methods";
//       style=filled;
//       color=lightgrey;
//       node [style=filled,color=lightblue];
  
//       "NativeClass1.funcA";
//       "NativeClass2.funcB";
//     }
  
//     "NonNativeClass1.funcX";
//     "NonNativeClass2.funcY";
  
//     "NonNativeClass1.funcX" -> "NativeClass1.funcA";
//   }