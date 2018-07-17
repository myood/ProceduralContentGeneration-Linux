#pragma once
#include <vector>
#include <iostream>
#include "SpacePartition.h"
#include "Util.h"
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>

struct Grid
{
    std::vector<std::vector<TILE>> tiles;
};

bool operator==(const Grid& lhs, const Grid& rhs)
{
    return lhs.tiles == rhs.tiles;
}

::std::ostream &operator<<(::std::ostream &os, const Grid& g)
{
    auto to_str = [](auto t)
    {
        std::ostringstream out;
        out << std::setw(2) << static_cast<int>(t);
        return out.str();
    };

    os << std::endl;
    for (const auto& row : g.tiles)
    {
        os << "[" << boost::algorithm::join(
            row | boost::adaptors::transformed(to_str), "][") << "]" << std::endl;
    }
    return os;
}

std::vector<std::vector<TILE>> createGrid(int width, int height, std::vector<SpacePartition::area_t> areas)
{ 
    auto grid = std::vector<std::vector<TILE>>(height, std::vector<TILE>(width, TILE::FLOOR));
    for (const auto& a : areas)
    {
        //top 5, bottom 10, left 3, right 7
        for (int i = a.top; i <= a.bottom; ++i)
        {
            grid[i][a.left] = TILE::WALL_SINGLE;
            grid[i][a.right] = TILE::WALL_SINGLE;
        }

        for (int j = a.left; j <= a.right; ++j)
        {
            grid[a.top][j] = TILE::WALL_SINGLE;
            grid[a.bottom][j] = TILE::WALL_SINGLE;
        }
    }
    return grid;
};