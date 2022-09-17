
#include "catan_graph.h"

/* don't copy vertices and edge properties when copying from grid graph to adjacency list
   a grid graph doesn't have those */

namespace copy
{
    struct do_nothing
    {
        template <typename VertexOrEdge1, typename VertexOrEdge2>
        void operator()(const VertexOrEdge1&, VertexOrEdge2&) const { }
    };

    static void from_grid_graph(catan::size_type rows, catan::size_type columns, catan::Graph& graph)
    {
        boost::array<std::size_t, 2> lengths = { { rows, columns } };
        boost::grid_graph<2> grid_graph(lengths);
        copy_graph(grid_graph, graph, boost::vertex_copy(do_nothing()).edge_copy(do_nothing()));
    }
}

static void add_diagonal_edges(catan::size_type rows, catan::size_type columns, catan::Graph& graph)
{
    const std::vector<std::pair<catan::size_type, catan::size_type>> directions = {
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };

    for (catan::size_type row {}; row < rows; ++row)
    {
        for (catan::size_type column {}; column < columns; ++column)
        {
            std::ranges::for_each(directions, [&row, &column, &rows, &columns, &graph](const auto& pair)
                {
                    int i = row + pair.first;
                    int j = column + pair.second;

                    if (i >= 0 && i < rows && j >= 0 && j < columns)
                        add_edge(row * rows + column, i * columns + j, graph);
                }
            );
        }
    }
}

static void add_labels(catan::size_type radius, catan::size_type rows, catan::size_type columns, catan::Graph& graph)
{
    for (catan::size_type i = 0; i < rows; ++i)
    {
        int distance_to_center = std::abs(static_cast<int>(i - rows / 2));
        int margin = std::ceil(.5 * (distance_to_center - 1));
        bool odd_row = i % 2 != 0;

        for (int j = 0; j < columns; ++j)
        {
            if (margin <= j && j < columns - margin)
            {
                if (odd_row)
                {
                    if (j % 2 != margin % 2)
                    {
                        graph[vertex(i * columns + j, graph)].type = catan::NodeType::hex;
                    }
                    else
                    {
                        clear_vertex(i * columns + j, graph);
                        add_edge((i - 1) * columns + j, (i + 1) * columns + j, graph);
                        add_edge((i + 1) * columns + j, (i - 1) * columns + j, graph);

                        // TODO: add road
                    }
                }
                else
                {
                    graph[vertex(i * columns + j, graph)].type = catan::NodeType::settlement;

                    // TODO: add road
                }
            }
            else
            {
                clear_vertex(i * rows + j, graph);
            }
        }
    }
}

/* radius in rows and columns is specific to the grid representation */

catan::CatanGraph::CatanGraph(size_type radius) : radius { radius }, rows { 3 + 4 * radius }, columns { rows }
{
    copy::from_grid_graph(rows, columns, graph);
    add_diagonal_edges(rows, columns, graph);
    add_labels(radius, rows, columns, graph);
}