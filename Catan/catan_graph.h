#pragma once

#include <boost/graph/grid_graph.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <boost/numeric/ublas/matrix.hpp>

#include <iostream>
#include <algorithm>
#include <vector>

namespace catan
{
    /* vertex and edge properties */

    enum class NodeType { settlement, road, hex, invalid };

    struct VertexProperties
    {
        NodeType type;

        VertexProperties() : type { NodeType::invalid } { };
    };

    struct EdgeProperties
    {
       // TODO
    };

    /* using declarations */

    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperties>;
    using size_type = Graph::vertices_size_type;

    class CatanGraph
    {
    private:
        Graph graph;

        size_type radius;
        size_type rows;
        size_type columns;

        std::vector<size_type> hex_tiles;
        std::vector<Graph::edge_descriptor> road_places;
        std::vector<size_type> settlement_places;

        void init_nodes();

    public:
        CatanGraph(size_type radius);
        Graph get_graph() { return graph; }
    };
}