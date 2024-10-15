#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#pragma once
#include "../headers/sudoku.h"
#include "../headers/helpers.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;

class Sudoku;
class Cell;

typedef std::unordered_map< Cell*, std::pair< int, std::unordered_set<int> > > SolvedCells;

class BaseStrategy
{
public:
    virtual SolvedCells apply(const Sudoku&) = 0;

    virtual ~BaseStrategy() = default;
};

class NakedSingle : public BaseStrategy
{
public:
    NakedSingle();

    SolvedCells apply(const Sudoku&) override;
    
    ~NakedSingle() override;
};

class ClearCandidatesByRules : public BaseStrategy
{
public:
    ClearCandidatesByRules();

    SolvedCells apply(const Sudoku&) override;
    
    ~ClearCandidatesByRules() override;
};

class HiddenSinglet : public BaseStrategy
{
public:
    HiddenSinglet();

    SolvedCells apply(const Sudoku&) override;
    
    ~HiddenSinglet() override;
};

class NakedPair : public BaseStrategy
{
public:
    NakedPair();

    SolvedCells apply(const Sudoku&) override;
    
    ~NakedPair() override;
};

class NakedTripled : public BaseStrategy
{
public:
    NakedTripled();

    SolvedCells apply(const Sudoku&) override;
    
    ~NakedTripled() override;
};


#endif //_STRATEGY_H_