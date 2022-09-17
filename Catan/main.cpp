
#include "catan_graph.h"

#include <boost/graph/properties.hpp>
#include <boost/graph/graphviz.hpp>

#include <chrono>

namespace catan
{
    std::ostream& operator<<(std::ostream& os, const NodeType& t)
    {
        std::vector<std::string> types{ "S", "R", "H", "-" };
        return os << types[static_cast<int>(t)];
    }
}

int main()
{
    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < 1000; ++i)
        catan::CatanGraph catan_graph (2);

    auto end = std::chrono::system_clock::now();
    

    catan::CatanGraph catan_graph(2);

    std::ofstream file(R"(C:\Users\Schwa\Desktop\grid.dot)");
    catan::Graph g = catan_graph.get_graph();
    boost::write_graphviz(file, g, make_label_writer(get(&catan::VertexProperties::type, g)));
}