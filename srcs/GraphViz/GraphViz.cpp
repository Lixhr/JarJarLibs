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

void GraphViz::doDotGraph(const std::string &out_file) {
    std::ostream* out_stream = &std::cout;
    std::ofstream file_stream;


    if (!out_file.empty()) {
        file_stream.open(out_file);
        if (!file_stream.is_open())
            throw (std::runtime_error("Failed to open " + out_file));
        out_stream = &file_stream;
    }

    *out_stream << "digraph g {\n";
    *out_stream << "ranksep=2.5;\n";
    *out_stream << "node [shape=box];\n";
    *out_stream << "rankdir=TB;\n";

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

    *out_stream << "    subgraph cluster_native {\n";
    *out_stream << "        label=\"Target Methods\";\n";
    *out_stream << "        node [style=filled,color=lightblue];\n";
    *out_stream << "        style=filled;\n";
    *out_stream << "        color=lightgrey;\n";
    *out_stream << "        rank=sink;\n";

    for (auto &[node_name, info] : nodes) {
        if (info.is_native) {
            *out_stream << "        \"" << node_name << "\";\n";
        }
    }
    *out_stream << "    }\n";

    for (auto &[node_name, info] : nodes) {
        if (!info.is_native) {
            *out_stream << "\"" << node_name << "\";\n";
        }
    }



    for (auto &rel : this->relations) {
        size_t caller_index = rel.caller_class.find_last_of(".") + 1;
        size_t callee_index = rel.callee_class.find_last_of(".") + 1;

        std::string caller_node = rel.caller_class.substr(caller_index) + "." + rel.caller_func;
        std::string callee_node = rel.callee_class.substr(callee_index) + "." + rel.callee_func;

        *out_stream << "\"" << caller_node << "\" -> \"" << callee_node << "\";\n";
    }

    *out_stream << "}\n";
    
}