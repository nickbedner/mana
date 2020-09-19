#pragma once
#ifndef MANIFOLD_TABLES_H
#define MANIFOLD_TABLES_H

#include <ubermath/ubermath.h>

static const vec3 CornerDeltas[8] = {
    {{{0, 0, 0}}},
    {{{1, 0, 0}}},
    {{{1, 0, 1}}},
    {{{0, 0, 1}}},

    {{{0, 1, 0}}},
    {{{1, 1, 0}}},
    {{{1, 1, 1}}},
    {{{0, 1, 1}}}};

static const vec3 TCornerDeltas[8] = {
    {{{0, 0, 0}}},
    {{{0, 0, 1}}},
    {{{0, 1, 0}}},
    {{{0, 1, 1}}},

    {{{1, 0, 0}}},
    {{{1, 0, 1}}},
    {{{1, 1, 0}}},
    {{{1, 1, 1}}}};

static const int EdgePairs[12][3] = {
    {0, 1, 0},
    {1, 2, 2},
    {3, 2, 0},
    {0, 3, 2},

    {4, 5, 0},
    {5, 6, 2},
    {7, 6, 0},
    {4, 7, 2},

    {4, 0, 1},
    {1, 5, 1},
    {2, 6, 1},
    {3, 7, 1}};

static const int TEdgePairs[12][3] = {
    {0, 4, 0},
    {1, 5, 0},
    {2, 6, 0},
    {3, 7, 0},
    {0, 2, 1},
    {1, 3, 1},
    {4, 6, 1},
    {5, 7, 1},
    {0, 1, 2},
    {2, 3, 2},
    {4, 5, 2},
    {6, 7, 2}};

static const int CellProcEdgeMask[6][5] = {
    {0, 3, 4, 7, 0},
    {1, 2, 5, 6, 0},
    {0, 3, 1, 2, 1},
    {4, 5, 7, 6, 1},
    {0, 4, 1, 5, 2},
    {3, 7, 2, 6, 2}};

static const int TCellProcEdgeMask[6][5] = {
    {0, 1, 2, 3, 0},
    {4, 5, 6, 7, 0},
    {0, 4, 1, 5, 1},
    {2, 6, 3, 7, 1},
    {0, 2, 4, 6, 2},
    {1, 3, 5, 7, 2}};

static const int FaceProcFaceMask[3][4][3] = {
    {{1, 0, 0},
     {2, 3, 0},
     {5, 4, 0},
     {6, 7, 0}},
    {{4, 0, 1},
     {5, 1, 1},
     {7, 3, 1},
     {6, 2, 1}},
    {{3, 0, 2},
     {4, 4, 2},
     {2, 1, 2},
     {6, 5, 2}}};

static const int TFaceProcFaceMask[3][4][3] = {
    {{4, 0, 0},
     {5, 1, 0},
     {6, 2, 0},
     {7, 3, 0}},
    {{2, 0, 1},
     {6, 4, 1},
     {3, 1, 1},
     {7, 5, 1}},
    {{1, 0, 2},
     {3, 2, 2},
     {5, 4, 2},
     {7, 6, 2}}};

static const int FaceProcEdgeMask[3][4][6] = {
    {{1, 1, 0, 2, 3, 1},
     {1, 5, 4, 6, 7, 1},
     {0, 1, 5, 0, 4, 2},
     {0, 2, 6, 3, 7, 2}},
    {{0, 4, 7, 0, 3, 0},
     {0, 5, 6, 1, 2, 0},
     {1, 4, 0, 5, 1, 2},
     {1, 7, 3, 6, 2, 2}},
    {{1, 3, 0, 7, 4, 0},
     {1, 2, 1, 6, 5, 0},
     {0, 3, 2, 0, 1, 1},
     {0, 7, 6, 4, 5, 1}}};

static const int TFaceProcEdgeMask[3][4][6] = {
    {{1, 4, 0, 5, 1, 1},
     {1, 6, 2, 7, 3, 1},
     {0, 4, 6, 0, 2, 2},
     {0, 5, 7, 1, 3, 2}},
    {{0, 2, 3, 0, 1, 0},
     {0, 6, 7, 4, 5, 0},
     {1, 2, 0, 6, 4, 2},
     {1, 3, 1, 7, 5, 2}},
    {{1, 1, 0, 3, 2, 0},
     {1, 5, 4, 7, 6, 0},
     {0, 1, 5, 0, 4, 1},
     {0, 3, 7, 2, 6, 1}}};

static const int EdgeProcEdgeMask[3][2][5] = {
    {{7, 4, 3, 0, 0},
     {6, 5, 2, 1, 0}},
    {{2, 3, 1, 0, 1},
     {6, 7, 5, 4, 1}},
    {{5, 1, 4, 0, 2},
     {6, 2, 7, 3, 2}}};

static const int TEdgeProcEdgeMask[3][2][5] = {
    {{3, 2, 1, 0, 0},
     {7, 6, 5, 4, 0}},
    {{5, 1, 4, 0, 1},
     {7, 3, 6, 2, 1}},
    {{6, 4, 2, 0, 2},
     {7, 5, 3, 1, 2}},
};

static const int ProcessEdgeMask[3][4] = {
    {3, 2, 1, 0},
    {7, 5, 6, 4},
    {11, 10, 9, 8}};

static const int TProcessEdgeMask[3][4] = {
    {3, 2, 1, 0},
    {7, 5, 6, 4},
    {11, 10, 9, 8}};

static const int ExternalEdges[8][3] = {
    {0, 3, 8},
    {2, 3, 11},
    {4, 7, 8},
    {6, 7, 11},
    {0, 1, 9},
    {1, 2, 10},
    {4, 5, 9},
    {5, 6, 10}};

static const int TExternalEdges[8][3] = {
    {0, 8, 4},
    {1, 8, 5},
    {2, 9, 4},
    {3, 9, 5},
    {0, 10, 6},
    {10, 1, 7},
    {2, 11, 6},
    {11, 3, 7}};

static const int TInternalEdges[8][9] = {
    {1, 2, 3, 5, 6, 7, 9, 10, 11},
    {0, 2, 3, 4, 6, 7, 9, 10, 11},
    {0, 1, 3, 5, 6, 7, 8, 10, 11},
    {0, 1, 2, 4, 6, 7, 8, 10, 11},
    {1, 2, 3, 4, 5, 7, 8, 9, 11},
    {0, 2, 3, 4, 5, 6, 8, 9, 11},
    {0, 1, 3, 4, 5, 7, 8, 9, 10},
    {0, 1, 2, 4, 5, 6, 8, 9, 10}};

static const int TFaces[6][4] = {
    {0, 6, 2, 4},
    {1, 7, 3, 5},
    {0, 10, 1, 8},
    {2, 11, 3, 9},
    {4, 8, 5, 9},
    {6, 10, 7, 11}};

static const int TransformedEdgesTable[256][16] = {
    {-2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 4, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 5, 1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 4, 5, 1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 9, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 2, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 2, 9, -1, 8, 5, 1, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 9, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 0, 8, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 3, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 3, 9, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 2, 3, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 3, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 3, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 6, 0, -1, 1, 8, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 4, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -1, 4, 2, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 2, 9, 6, -2, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1},
    {6, 0, 10, -1, 4, 2, 9, -1, 1, 8, 5, -2, -1, -1, -1, -1},
    {10, 1, 2, 9, 6, 5, -2, -1, -1, -1, -1, -2, -1, -1, -1, -1},
    {5, 9, 3, -1, 0, 6, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 10, 8, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -1, 8, 1, 3, 9, -2, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 3, 9, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -1, 4, 2, 5, 3, -2, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 2, 3, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -1, 1, 8, 4, 2, 3, -2, -1, -1, -1, -1, -1, -1},
    {10, 1, 2, 3, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 4, 8, -1, 10, 1, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 4, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -1, 4, 2, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -1, 0, 8, 9, 2, -2, -1, -1, -1, -1, -1, -1, -1},
    {8, 5, 7, 10, -1, 4, 9, 2, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 2, 9, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 10, 1, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 10, 1, 7, -1, 0, 8, 4, -2, -1, -1, -1, -1},
    {10, 8, 3, 9, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 3, 9, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -1, 4, 2, 3, 5, -2, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -1, 0, 8, 5, 3, 2, -2, -1, -1, -1, -1, -1, -1},
    {10, 8, 2, 3, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 2, 3, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 0, 1, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {7, 1, 8, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 7, 6, -1, 4, 9, 2, -2, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 9, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 9, 4, -1, 0, 8, 5, 7, 6, -2, -1, -1, -1, -1, -1, -1},
    {2, 9, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 0, 6, 7, 1, -2, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 1, 8, 4, 6, 7, -2, -1, -1, -1, -1, -1, -1},
    {0, 8, 3, 9, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 9, 4, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 6, 7, 1, -1, 4, 2, 5, 3, -2, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 3, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 2, 3, 4, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 11, 2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 11, 2, -1, 0, 4, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 11, 2, -1, 1, 8, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 2, 11, -1, 0, 1, 5, 4, -2, -1, -1, -1, -1, -1, -1, -1},
    {11, 9, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 11, 9, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 5, -1, 11, 9, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 11, 9, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 9, 5, -1, 2, 11, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 9, 5, -1, 2, 11, 6, -1, 0, 8, 4, -2, -1, -1, -1, -1},
    {2, 11, 6, -1, 8, 1, 3, 9, -2, -1, -1, -1, -1, -1, -1, -1},
    {2, 11, 6, -1, 1, 0, 4, 9, 3, -2, -1, -1, -1, -1, -1, -1},
    {11, 3, 4, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 11, 3, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 11, 3, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 11, 3, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 11, 2, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 2, 11, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 5, 1, -1, 0, 2, 11, 10, -2, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 2, 11, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 11, 9, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 11, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 5, -1, 0, 10, 11, 9, 4, -2, -1, -1, -1, -1, -1, -1},
    {10, 1, 11, 9, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 10, 0, 11, 2, -2, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 4, 8, 10, 11, 2, -2, -1, -1, -1, -1, -1, -1},
    {8, 1, 3, 9, -1, 0, 10, 11, 2, -2, -1, -1, -1, -1, -1, -1},
    {10, 1, 2, 11, 3, 9, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 11, 3, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 11, 3, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 1, 8, 11, 3, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 11, 3, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -1, 6, 11, 2, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 0, 4, -1, 10, 1, 7, -1, 2, 6, 11, -2, -1, -1, -1, -1},
    {8, 5, 7, 10, -1, 6, 2, 11, -2, -1, -1, -1, -1, -1, -1, -1},
    {2, 6, 11, -1, 0, 10, 4, 7, 5, -2, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -1, 4, 9, 11, 6, -2, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -1, 0, 8, 9, 11, 6, -2, -1, -1, -1, -1, -1, -1},
    {8, 5, 7, 10, -1, 4, 9, 11, 6, -2, -1, -1, -1, -1, -1, -1},
    {0, 10, 11, 9, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 2, 11, 6, -1, 10, 1, 7, -2, -1, -1, -1, -1},
    {5, 9, 3, -1, 2, 11, 6, -1, 10, 1, 7, -1, 0, 8, 4, -2},
    {6, 2, 11, -1, 10, 7, 3, 9, 8, -2, -1, -1, -1, -1, -1, -1},
    {6, 2, 11, -1, 3, 7, 10, 0, 4, 9, -2, -1, -1, -1, -1, -1},
    {10, 1, 7, -1, 6, 11, 3, 5, 4, -2, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -1, 6, 0, 8, 5, 3, 11, -2, -1, -1, -1, -1, -1},
    {10, 8, 11, 3, 4, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 11, 3, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 11, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 11, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 2, 11, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 2, 4, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 11, 9, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 11, 9, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 11, 9, 4, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 9, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 0, 1, 7, 11, 2, -2, -1, -1, -1, -1, -1, -1},
    {5, 9, 3, -1, 4, 8, 1, 7, 11, 2, -2, -1, -1, -1, -1, -1},
    {0, 8, 2, 11, 3, 9, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 11, 3, 9, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 11, 3, 4, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 11, 3, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 11, 3, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 3, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 3, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 4, -1, 7, 11, 3, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 5, 1, -1, 7, 3, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {7, 11, 3, -1, 0, 4, 1, 5, -2, -1, -1, -1, -1, -1, -1, -1},
    {4, 9, 2, -1, 11, 3, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 3, 7, -1, 0, 8, 2, 9, -2, -1, -1, -1, -1, -1, -1, -1},
    {8, 5, 1, -1, 11, 3, 7, -1, 4, 9, 2, -2, -1, -1, -1, -1},
    {7, 11, 3, -1, 0, 1, 5, 9, 2, -2, -1, -1, -1, -1, -1, -1},
    {11, 9, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 9, 7, 5, -1, 0, 8, 4, -2, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 11, 9, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 11, 9, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 11, 4, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 2, 11, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 11, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 11, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -1, 7, 11, 3, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {7, 11, 3, -1, 8, 4, 6, 10, -2, -1, -1, -1, -1, -1, -1, -1},
    {8, 5, 1, -1, 0, 10, 6, -1, 7, 11, 3, -2, -1, -1, -1, -1},
    {7, 11, 3, -1, 5, 1, 4, 6, 10, -2, -1, -1, -1, -1, -1, -1},
    {7, 11, 3, -1, 10, 6, 0, -1, 4, 9, 2, -2, -1, -1, -1, -1},
    {7, 11, 3, -1, 9, 2, 6, 10, 8, -2, -1, -1, -1, -1, -1, -1},
    {8, 5, 1, -1, 0, 10, 6, -1, 7, 11, 3, -1, 4, 9, 2, -2},
    {7, 11, 3, -1, 9, 2, 5, 1, 10, 6, -2, -1, -1, -1, -1, -1},
    {11, 9, 7, 5, -1, 0, 10, 6, -2, -1, -1, -1, -1, -1, -1, -1},
    {11, 9, 7, 5, -1, 8, 4, 6, 10, -2, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -1, 9, 8, 1, 7, 11, -2, -1, -1, -1, -1, -1, -1},
    {10, 1, 11, 9, 4, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -1, 4, 5, 7, 2, 11, -2, -1, -1, -1, -1, -1, -1},
    {10, 8, 2, 11, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -1, 4, 8, 1, 7, 11, 2, -2, -1, -1, -1, -1, -1},
    {10, 1, 2, 11, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 11, 3, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 4, -1, 10, 1, 3, 11, -2, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 11, 3, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 11, 3, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 9, 2, -1, 10, 1, 3, 11, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 9, 2, -1, 10, 1, 3, 11, -2, -1, -1, -1, -1, -1, -1},
    {4, 9, 2, -1, 8, 5, 3, 11, 10, -2, -1, -1, -1, -1, -1, -1},
    {0, 10, 2, 11, 3, 9, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 11, 9, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 11, 9, 5, -1, 0, 8, 4, -2, -1, -1, -1, -1, -1, -1},
    {10, 8, 11, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 11, 9, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 2, 11, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 1, 8, 2, 11, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 2, 11, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 2, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 11, 3, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 11, 3, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 11, 3, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 3, 4, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 9, 2, -1, 0, 6, 1, 11, 3, -2, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 11, 3, 9, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 9, 2, -1, 3, 11, 6, 0, 5, 8, -2, -1, -1, -1, -1, -1},
    {2, 11, 3, 9, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 11, 9, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 11, 9, 4, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 11, 9, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 9, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 11, 4, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 11, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 2, 11, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 11, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 4, -1, 6, 7, 3, 2, -2, -1, -1, -1, -1, -1, -1, -1},
    {5, 1, 8, -1, 6, 2, 7, 3, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 5, 4, -1, 6, 2, 3, 7, -2, -1, -1, -1, -1, -1, -1},
    {3, 9, 4, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 3, 9, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 5, 1, -1, 7, 3, 6, 9, 4, -2, -1, -1, -1, -1, -1, -1},
    {0, 1, 3, 9, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 9, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 4, -1, 7, 6, 2, 9, 5, -2, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 9, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 9, 4, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 6, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 4, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 2, 3, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 2, 3, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 5, -1, 0, 10, 2, 3, 7, -2, -1, -1, -1, -1, -1, -1},
    {10, 1, 2, 3, 4, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 3, 9, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 3, 9, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 5, 1, -1, 4, 9, 0, 10, 7, 3, -2, -1, -1, -1, -1, -1},
    {10, 1, 3, 9, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 2, 9, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 2, 9, 4, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 1, 8, 2, 9, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 2, 9, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 4, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 7, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 1, 8, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 2, 3, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 4, -1, 10, 1, 2, 3, 6, -2, -1, -1, -1, -1, -1, -1},
    {10, 8, 2, 3, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 2, 3, 4, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 3, 9, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 1, 8, 3, 9, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 3, 9, 4, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 3, 9, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 2, 9, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 2, 9, 6, 5, -1, 0, 8, 4, -2, -1, -1, -1, -1, -1},
    {10, 8, 2, 9, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 2, 9, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 1, 4, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 1, 8, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 8, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 10, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 3, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 3, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 2, 3, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 3, 9, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 3, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 3, 9, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 9, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 9, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 2, 9, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 2, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 9, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}

};

static const int EdgesTable[256][16] = {
    {-2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 3, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 3, -1, 1, 2, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {9, 0, 2, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 2, 3, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 11, 2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 11, 2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 9, 0, -1, 2, 3, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 8, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 8, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 7, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -1, 8, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 7, 9, -2, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -1, 8, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -1, 0, 3, 7, 4, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 10, 9, -1, 8, 7, 4, -2, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 7, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 4, 7, -1, 3, 11, 2, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 4, 7, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {9, 0, 1, -1, 8, 4, 7, -1, 2, 3, 11, -2, -1, -1, -1, -1},
    {1, 2, 4, 7, 9, 11, -2, -1, -1, -1, -1, -1 - 1, -1, -1, -1, -1},
    {3, 11, 10, 1, -1, 8, 7, 4, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 7, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 7, 8, -1, 0, 3, 11, 10, 9, -2, -1, -1, -1, -1, -1, -1},
    {4, 7, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {9, 5, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {9, 5, 4, -1, 0, 8, 3, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 5, 4, 1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 5, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -1, 9, 5, 4, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 0, 8, -1, 1, 2, 10, -1, 4, 9, 5, -2, -1, -1, -1, -1},
    {0, 2, 4, 5, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 5, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {9, 5, 4, -1, 2, 3, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {9, 4, 5, -1, 0, 2, 11, 8, -2, -1, -1, -1, -1, -1, -1, -1},
    {3, 11, 2, -1, 0, 4, 5, 1, -2, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 4, 5, 8, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 11, 10, 1, -1, 9, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1},
    {4, 9, 5, -1, 0, 1, 8, 10, 11, -2, -1, -1, -1, -1, -1, -1},
    {0, 3, 4, 5, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 4, 8, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 7, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 5, 7, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 5, 7, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 5, 3, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -1, 8, 7, 5, 9, -2, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -1, 0, 3, 7, 5, 9, -2, -1, -1, -1, -1, -1, -1},
    {0, 2, 5, 7, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 5, 7, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 11, -1, 5, 7, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 5, 7, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 11, -1, 0, 1, 5, 7, 8, -2, -1, -1, -1, -1, -1, -1},
    {1, 2, 5, 7, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 11, 10, 1, -1, 8, 7, 5, 9, -2, -1, -1, -1, -1, -1, -1},
    {0, 1, 5, 7, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 5, 7, 8, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 7, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 6, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 8, -1, 10, 5, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -1, 10, 5, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 5, 6, -1, 3, 8, 9, 1, -2, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 5, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 8, -1, 1, 2, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 5, 6, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 5, 6, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 11, 2, -1, 10, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, 5, 6, -1, 0, 8, 2, 11, -2, -1, -1, -1, -1, -1, -1, -1},
    {3, 11, 2, -1, 0, 1, 9, -1, 10, 5, 6, -2, -1, -1, -1, -1},
    {10, 5, 6, -1, 11, 2, 8, 9, 1, -2, -1, -1, -1, -1, -1, -1},
    {1, 3, 5, 6, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 5, 6, 8, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 5, 6, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 6, 8, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 7, 4, -1, 5, 6, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 6, 10, -1, 0, 3, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1},
    {10, 5, 6, -1, 1, 9, 0, -1, 8, 7, 4, -2, -1, -1, -1, -1},
    {10, 5, 6, -1, 7, 4, 9, 1, 3, -2, -1, -1, -1, -1, -1, -1},
    {8, 7, 4, -1, 1, 2, 6, 5, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 7, 4, -1, 1, 2, 6, 5, -2, -1, -1, -1, -1, -1, -1},
    {8, 7, 4, -1, 0, 9, 2, 5, 6, -2, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 5, 6, 7, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 11, 2, -1, 5, 6, 10, -1, 8, 7, 4, -2, -1, -1, -1, -1},
    {10, 5, 6, -1, 0, 2, 11, 7, 4, -2, -1, -1, -1, -1, -1, -1},
    {3, 11, 2, -1, 0, 1, 9, -1, 10, 5, 6, -1, 8, 7, 4, -2},
    {10, 5, 6, -1, 7, 4, 11, 2, 1, 9, -2, -1, -1, -1, -1, -1},
    {8, 7, 4, -1, 3, 11, 6, 5, 1, -2, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 5, 6, 7, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 7, 4, -1, 6, 5, 9, 0, 11, 3, -2, -1, -1, -1, -1, -1},
    {4, 5, 6, 7, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 6, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 8, -1, 9, 10, 6, 4, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 6, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 6, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 4, 6, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 8, -1, 1, 2, 4, 6, 9, -2, -1, -1, -1, -1, -1, -1},
    {0, 2, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 6, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 2, 3, -1, 9, 4, 10, 6, -2, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 11, 8, -1, 9, 4, 6, 10, -2, -1, -1, -1, -1, -1, -1},
    {2, 3, 11, -1, 0, 1, 4, 6, 10, -2, -1, -1, -1, -1, -1, -1},
    {1, 2, 4, 6, 8, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 6, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 6, 8, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 4, 6, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 6, 8, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 7, 8, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 6, 7, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 6, 7, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 6, 7, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 6, 7, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 3, 6, 7, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 6, 7, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 11, 2, -1, 10, 6, 9, 7, 8, -2, -1, -1, -1, -1, -1, -1},
    {0, 2, 6, 7, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 11, 2, -1, 8, 7, 0, 1, 10, 6, -2, -1, -1, -1, -1, -1},
    {1, 2, 6, 7, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 6, 7, 8, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 6, 7, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 6, 7, 8, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 7, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -1, 0, 3, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -1, 0, 9, 1, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -1, 1, 3, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -1, 1, 2, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -1, 1, 2, 10, -1, 0, 3, 8, -2, -1, -1, -1, -1},
    {11, 7, 6, -1, 0, 9, 10, 2, -2, -1, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -1, 2, 3, 8, 9, 10, -2, -1, -1, -1, -1, -1, -1},
    {2, 3, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 6, 7, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -1, 3, 2, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 6, 7, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 6, 7, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 6, 7, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 6, 7, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 7, 8, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 6, 8, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 4, 6, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -1, 8, 4, 11, 6, -2, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 6, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -1, 8, 4, 6, 11, -2, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -1, 0, 3, 11, 6, 4, -2, -1, -1, -1, -1, -1, -1},
    {0, 9, 10, 2, -1, 8, 4, 11, 6, -2, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 6, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 6, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 4, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -1, 2, 3, 8, 4, 6, -2, -1, -1, -1, -1, -1, -1},
    {1, 2, 4, 6, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 6, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 6, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 4, 6, 8, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 6, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 7, 11, -1, 4, 5, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 7, 11, -1, 4, 5, 9, -1, 0, 3, 8, -2, -1, -1, -1, -1},
    {11, 7, 6, -1, 1, 0, 5, 4, -2, -1, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -1, 8, 3, 1, 5, 4, -2, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -1, 4, 5, 9, -1, 1, 2, 10, -2, -1, -1, -1, -1},
    {11, 7, 6, -1, 4, 5, 9, -1, 1, 2, 10, -1, 0, 3, 8, -2},
    {11, 7, 6, -1, 0, 2, 10, 5, 4, -2, -1, -1, -1, -1, -1, -1},
    {11, 7, 6, -1, 8, 3, 2, 10, 5, 4, -2, -1, -1, -1, -1, -1},
    {4, 5, 9, -1, 3, 2, 6, 7, -2, -1, -1, -1, -1, -1, -1, -1},
    {4, 5, 9, -1, 2, 0, 8, 7, 6, -2, -1, -1, -1, -1, -1, -1},
    {3, 2, 6, 7, -1, 0, 1, 5, 4, -2, -1, -1, -1, -1, -1, -1},
    {1, 2, 4, 5, 6, 7, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {9, 4, 5, -1, 1, 10, 6, 7, 3, -2, -1, -1, -1, -1, -1, -1},
    {9, 4, 5, -1, 6, 10, 1, 0, 8, 7, -2, -1, -1, -1, -1, -1},
    {0, 3, 4, 5, 6, 7, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 5, 6, 7, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 6, 8, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 5, 6, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 5, 6, 8, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 5, 6, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -1, 9, 5, 6, 11, 8, -2, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -1, 9, 0, 3, 11, 6, 5, -2, -1, -1, -1, -1, -1},
    {0, 2, 5, 6, 8, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 5, 6, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 5, 6, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 5, 6, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 3, 5, 6, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 5, 6, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 5, 6, 8, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 5, 6, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 5, 6, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 6, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 7, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 7, 10, 11, -1, 0, 3, 8, -2, -1, -1, -1, -1, -1, -1, -1},
    {5, 7, 10, 11, -1, 0, 1, 9, -2, -1, -1, -1, -1, -1, -1, -1},
    {5, 7, 10, 11, -1, 3, 8, 9, 1, -2, -1, -1, -1, -1, -1, -1},
    {1, 2, 5, 7, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 5, 7, 11, -1, 0, 3, 8, -2, -1, -1, -1, -1, -1, -1},
    {0, 2, 5, 7, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 5, 7, 8, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 5, 7, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 5, 7, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -1, 7, 3, 2, 10, 5, -2, -1, -1, -1, -1, -1, -1},
    {1, 2, 5, 7, 8, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 5, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 5, 7, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 5, 7, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 7, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 5, 8, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 4, 5, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -1, 8, 11, 10, 4, 5, -2, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 5, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 4, 5, 8, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 3, 4, 5, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 4, 5, 8, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 5, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 5, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 4, 5, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -1, 8, 3, 2, 10, 5, 4, -2, -1, -1, -1, -1, -1},
    {1, 2, 4, 5, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 5, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 5, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 4, 5, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 5, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 7, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 8, -1, 10, 9, 4, 7, 11, -2, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 7, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 7, 8, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 4, 7, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 4, 7, 9, 11, -1, 0, 3, 8, -2, -1, -1, -1, -1, -1},
    {0, 2, 4, 7, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 7, 8, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 4, 7, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 4, 7, 8, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 3, 4, 7, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 4, 7, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 4, 7, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 4, 7, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 4, 7, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {4, 7, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 9, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 8, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 10, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 8, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 3, 9, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 8, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 11, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {2, 3, 8, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 2, 9, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 2, 3, 8, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 2, 10, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 3, 8, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 3, 8, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

static const int TransformedVerticesNumberTable[256] = {
    0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 2, 1, 3, 1, 2, 2, 2, 1, 2, 1, 2, 1,
    1, 2, 1, 1, 2, 2, 2, 1, 2, 3, 1, 1, 2, 2, 1, 1,
    1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1,
    1, 2, 2, 2, 1, 1, 2, 1, 2, 3, 2, 2, 1, 1, 1, 1,
    1, 1, 2, 1, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1,
    2, 3, 2, 2, 2, 2, 2, 1, 3, 4, 2, 2, 2, 2, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 2, 2, 3, 2, 1, 2, 1, 1, 1, 1, 1, 1,
    2, 2, 3, 2, 3, 2, 4, 2, 2, 2, 2, 1, 2, 1, 2, 1,
    1, 2, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};

static const int VerticesNumberTable[256] = {
    0, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 2, 2, 2, 1, 2, 1, 3, 1, 2, 1, 2, 1,
    1, 2, 1, 1, 2, 3, 1, 1, 2, 2, 2, 1, 2, 2, 1, 1,
    1, 1, 1, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1,
    1, 2, 2, 2, 1, 2, 1, 1, 2, 2, 3, 2, 1, 1, 1, 1,
    2, 2, 3, 2, 2, 2, 2, 1, 3, 2, 4, 2, 2, 1, 2, 1,
    1, 2, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 2, 3, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1,
    2, 3, 2, 2, 3, 4, 2, 2, 2, 2, 2, 1, 2, 2, 1, 1,
    1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,
    1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};

#endif  // MANIFOLD_TABLES_H
